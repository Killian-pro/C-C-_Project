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

#ifndef GRAPIC_H
#define GRAPIC_H

#include <cassert>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <cmath>

#include <Grapic_func.h>

//#include <SDL.h>
//#include <SDL_ttf.h>
//#include <SDL_image.h>




//! \todo Finish coding the game "dame"




namespace grapic
{


/**
* @brief The Grapic class
*/
class Grapic
{
public:
    Grapic();
    void init(const char* name, int w, int h);
    void clear();
    void clearEvent();
    bool display();
    bool hasFinished();
    void quit();
    bool isInit();
    inline void color(unsigned char r, unsigned char g, unsigned b, unsigned char a);
    inline SDL_Color& getColor();
    inline SDL_Color& getBackgroundColor();
    inline void backgroundColor(unsigned char r, unsigned char g, unsigned b, unsigned char a);
    inline int inverseY(int y);
    inline void setFont(int s, const char* ttf=NULL);
    const SDL_Window* window() const;
    SDL_Renderer * renderer();
    TTF_Font* font();
    int keyHasBeenPressed(unsigned int sc);
    void setKeyRepeatMode(bool kr);
    static Grapic& singleton(bool secure=true);
    bool manageEvent();

protected:
    int m_width;
    int m_height;
    SDL_Window* m_window;
    SDL_Renderer *m_renderer;
    TTF_Font *m_font;
    std::string m_fontFile;
    int m_fontSize;
    bool m_quit;
    bool m_anim;
    SDL_Color m_currentColor;
    SDL_Color m_backgroundColor;
    std::vector<int> m_keyStates;
    bool m_keyRepeatMode;

    void initKeyArray();
    void help() const;

    static Grapic currentGrapic;
};



inline    Grapic& Grapic::singleton(bool secure)
    {
        if (secure)
        {
            if (!currentGrapic.isInit())
            {
                std::cout<<"You have to call winInit before any call to Grapic functions !"<<std::endl;
                exit(1);
            }
        }
        return currentGrapic;
    }



inline    bool Grapic::hasFinished()
    {
        return m_quit;
    }

inline    bool Grapic::isInit()
    {
        return m_window;
    }


inline  const  SDL_Window* Grapic::window() const
{
    return m_window;
}

inline     SDL_Renderer * Grapic::renderer()
{
    return m_renderer;
}

inline TTF_Font* Grapic::font()
{
    return m_font;
}


inline void Grapic::initKeyArray()
{
    int keys;
    const unsigned char *state= SDL_GetKeyboardState(&keys);
    m_keyStates.assign(state, state + keys);
}


inline void Grapic::clear()
{
    // Clear the entire screen to our selected color.
    SDL_SetRenderDrawColor(m_renderer, m_backgroundColor.r, m_backgroundColor.g, m_backgroundColor.b, m_backgroundColor.a);
    SDL_RenderClear(m_renderer);
    SDL_SetRenderDrawColor(m_renderer, m_currentColor.r, m_currentColor.g, m_currentColor.b, m_currentColor.a);
}

inline void Grapic::clearEvent()
{
    SDL_Event events;
    SDL_PumpEvents();
    while (SDL_PollEvent(&events))
    {
    }
    initKeyArray();
}


inline bool Grapic::display()
{
    manageEvent();
    SDL_RenderPresent(m_renderer);
    return m_quit;
}


inline void Grapic::quit()
{
    TTF_CloseFont(m_font);
    SDL_DestroyWindow(m_window);
    SDL_DestroyRenderer(m_renderer);
    m_font = NULL;
    m_window = NULL;
    m_renderer = NULL;
    SDL_Quit();
}


inline void Grapic::setKeyRepeatMode(bool kr)
{
    m_keyRepeatMode = kr;
}

inline void Grapic::color(unsigned char r, unsigned char g, unsigned b, unsigned char a)
{
    m_currentColor.r = r;
    m_currentColor.g = g;
    m_currentColor.b = b;
    m_currentColor.a = a;
    SDL_SetRenderDrawColor(m_renderer, m_currentColor.r, m_currentColor.g, m_currentColor.b, m_currentColor.a);
}


inline SDL_Color& Grapic::getColor()
{
    return m_currentColor;
}

inline SDL_Color& Grapic::getBackgroundColor()
{
    return m_backgroundColor;
}


inline void Grapic::backgroundColor(unsigned char r, unsigned char g, unsigned b, unsigned char a)
{
    m_backgroundColor.r = r;
    m_backgroundColor.g = g;
    m_backgroundColor.b = b;
    m_backgroundColor.a = a;
}


inline int Grapic::inverseY(int y)
{
    SDL_GetRendererOutputSize(m_renderer, &m_width, &m_height);
    return m_height - y - 1;
}


inline void Grapic::setFont(int s, const char* ttf)
{
    if ((m_fontSize==s) && (ttf && m_fontFile==std::string(ttf))) return;
    if (m_font) TTF_CloseFont(m_font);
    m_fontSize = s;
    if (ttf) m_fontFile = ttf;
    m_font = TTF_OpenFont( m_fontFile.c_str(), m_fontSize);
    if (!m_font) m_font = TTF_OpenFont( ("../"+m_fontFile).c_str(), m_fontSize);
    if (!m_font) m_font = TTF_OpenFont( ("../../"+m_fontFile).c_str(), m_fontSize);
    if (!m_font) m_font = TTF_OpenFont( ("../../../"+m_fontFile).c_str(), m_fontSize);
    if (!m_font) m_font = TTF_OpenFont( ("../../../../"+m_fontFile).c_str(), m_fontSize);
    if (!m_font)
    {
        std::cout << "Erreur lors de l'initialisation de la police : " << SDL_GetError() << std::endl;
        SDL_Quit();
        assert(0);
        exit(1);
    }
}



} // namespace

#endif
