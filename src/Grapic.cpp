/****************************************************************************
Copyright (C) 2010-2020 Alexandre Meyer

This file is part of Grapic.

Grapic is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Grapic is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Grapic.  If not, see <http://www.gnu.org/licenses/>.
*****************************************************************************/

#include <cassert>
#include <Grapic.h>
#include <cstdio>

namespace grapic
{



grapic::Grapic Grapic::currentGrapic;


Grapic::Grapic() :
    m_width(-1),
    m_height(-1),
    m_window(NULL),
    m_renderer(NULL),
    m_font(NULL),
    m_fontFile(""),
    m_fontSize(-1),
    m_quit(false),
    m_anim(false),
    m_keyRepeatMode(false)
{
    m_currentColor.r = 0;
    m_currentColor.g = 0;
    m_currentColor.b = 0;
    m_currentColor.a = 255;
    m_backgroundColor.r = 255;
    m_backgroundColor.g = 255;
    m_backgroundColor.b = 255;
    m_backgroundColor.a = 255;
}


void Grapic::help() const
{
    printf("Help:\n");
    printf("   q,ESC: quit\n");
    printf("   F12: save the screen\n");
    printf("   F1: hide/show the menu (if you use one in your program)\n");
    printf("   h: help\n");
}


void Grapic::init(const char* name, int w, int h)
{
    // Initialisation de la SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << std::endl;
        SDL_Quit();
        assert(0);
        exit(1);
    }

    if (TTF_Init() != 0)
    {
        std::cout << "Erreur lors de l'initialisation de la SDL_ttf : " << SDL_GetError() << std::endl;
        SDL_Quit();
        assert(0);
        exit(1);
    }

    int imgFlags = IMG_INIT_PNG;
    if( !( IMG_Init( imgFlags ) & imgFlags ) )
    {
        printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
        SDL_Quit();
        assert(0);
        exit(1);
    }

    //system("cd");
    //setFont( 20, "data/ttf/Raleway-Regular.ttf");
    setFont( 20, "data/ttf/Roboto-Regular.ttf");

    // Creation de la fenetre
    m_window = SDL_CreateWindow(name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_SHOWN ); //| SDL_WINDOW_RESIZABLE);
    if (m_window == NULL)
    {
        std::cout << "Erreur lors de la creation de la fenetre : " << SDL_GetError() << std::endl;
        SDL_Quit();
        assert(0);
        exit(1);
    }

    SDL_SetWindowTitle(m_window, name);

    m_renderer = SDL_CreateRenderer( m_window, -1, SDL_RENDERER_ACCELERATED);

    m_width = w;
    m_height = h;
    m_quit = false;
    m_anim = false;

    SDL_SetRenderDrawBlendMode( m_renderer, SDL_BLENDMODE_BLEND);

    initKeyArray();
    help();
}



bool saveScreenshotPNG(std::string filepath, SDL_Window* SDLWindow, SDL_Renderer* SDLRenderer)
{
    SDL_Surface* saveSurface = NULL;
    SDL_Surface* infoSurface = NULL;
    infoSurface = SDL_GetWindowSurface(SDLWindow);
    if (infoSurface == NULL)
    {
        std::cerr << "Failed to create info surface from window in saveScreenshotBMP(string), SDL_GetError() - " << SDL_GetError() << "\n";
    }
    else
    {
        unsigned char * pixels = new (std::nothrow) unsigned char[infoSurface->w * infoSurface->h * infoSurface->format->BytesPerPixel];
        if (pixels == 0)
        {
            std::cerr << "Unable to allocate memory for screenshot pixel data buffer!\n";
            return false;
        }
        else
        {
            if (SDL_RenderReadPixels(SDLRenderer, &infoSurface->clip_rect, infoSurface->format->format, pixels, infoSurface->w * infoSurface->format->BytesPerPixel) != 0)
            {
                std::cerr << "Failed to read pixel data from SDL_Renderer object. SDL_GetError() - " << SDL_GetError() << "\n";
                pixels = NULL;
                return false;
            }
            else
            {
                saveSurface = SDL_CreateRGBSurfaceFrom(pixels, infoSurface->w, infoSurface->h, infoSurface->format->BitsPerPixel, infoSurface->w * infoSurface->format->BytesPerPixel, infoSurface->format->Rmask, infoSurface->format->Gmask, infoSurface->format->Bmask, infoSurface->format->Amask);
                if (saveSurface == NULL)
                {
                    std::cerr << "Couldn't create SDL_Surface from renderer pixel data. SDL_GetError() - " << SDL_GetError() << "\n";
                    return false;
                }
                //SDL_SaveBMP(saveSurface, filepath.c_str());
                IMG_SavePNG(saveSurface, filepath.c_str());
                SDL_FreeSurface(saveSurface);
                saveSurface = NULL;
            }
            delete[] pixels;
        }
        SDL_FreeSurface(infoSurface);
        infoSurface = NULL;
    }
    return true;
}



bool Grapic::manageEvent()
{
    SDL_Event event;
    SDL_PumpEvents();
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            m_quit = true;
            break;
        case SDL_KEYDOWN:
            if (((size_t) event.key.keysym.scancode < m_keyStates.size()) && ((m_keyRepeatMode) || (event.key.repeat==0)))
            {
                m_keyStates[event.key.keysym.scancode]++; // = 1;
                //last_key= event.key;    // conserver le dernier evenement
            }

            if ((event.key.keysym.sym == SDLK_ESCAPE) || (event.key.keysym.sym == SDLK_q))
                m_quit = true;
            else if (event.key.keysym.sym == SDLK_F12)
            {
                saveScreenshotPNG( "grapic.png", m_window, m_renderer);
                printf("Save grapic.png\n");
            }
            else if (event.key.keysym.sym == SDLK_h)
            {
                help();
            }
            break;
        case SDL_KEYUP:
            // modifier l'etat du clavier
            if((size_t) event.key.keysym.scancode < m_keyStates.size())
            {
                m_keyStates[event.key.keysym.scancode]= 0;
                //last_key= event.key;    // conserver le dernier evenement
            }
            break;
        default:
            break;
        }
    }
    return m_quit;
}


int Grapic::keyHasBeenPressed(unsigned int key)
{
    SDL_Scancode code= SDL_GetScancodeFromKey(key);
    assert((size_t) code < m_keyStates.size());

    int res = (int)  m_keyStates[code];
    if (!m_keyRepeatMode)
    {
        m_keyStates[code]= 0;
    }
    return res;
}






} // namespace
