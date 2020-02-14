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

/**
\file Grapic_func.h
\author Alexandre Meyer
*/


#ifndef GRAPIC_FUNC_H
#define GRAPIC_FUNC_H

/// \cond
#include <cassert>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <thread>
#include <chrono>
#include <vector>

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

/// \endcond


namespace grapic
{

    /** \brief Initialize the window
    */
    void winInit(const char* name, int w, int h);

    /** \brief Clear the window with the default background color
        ~~~~~~~~~~~~~~~{.c}
		bool stop=false;
		winInit("Tutorials", 500, 500);
		winClear();
		rectangle(100,100, 200, 200);
		winDisplay();
		pressSpace();
		winQuit();
        ~~~~~~~~~~~~~~~
    */
    void winClear();

    /** \brief return true if the application should be closed (because of 'ESC' or 'q' key pressed for instance)
    */
    bool winHasFinished();

    /** \brief Clear the event queue of the window
    */
    void winClearEvent();

    /** \brief Display the window. All drawing is hidden until this function is not called.
        ~~~~~~~~~~~~~~~{.c}
		bool stop=false;
		winInit("Tutorials", 500, 500);
		while( !stop )
		{
			winClear();
			draw();
			stop = winDisplay();
		}
		winQuit();
        ~~~~~~~~~~~~~~~
    */
    bool winDisplay();

    /** \brief Quit and close all things
    */
    void winQuit();

    /** \brief Change the default color
    */
	void color(unsigned char _r = 255, unsigned char _g = 255, unsigned char _b = 255, unsigned char _a = 255);

    /** \brief Change the default background color (the color used to clear the screen)
    */
	void backgroundColor(unsigned char _r = 255, unsigned char _g = 255, unsigned char _b = 255, unsigned char _a = 255);

    /** \brief Draw a circle from (xmin,ymin) to (xmax,ymax)
    */
	void circle(int xc, int yc, int radius);

    /** \brief Draw a filled circle from (xmin,ymin) to (xmax,ymax)
    */
	void circleFill(int xc, int yc, int radius);

    /** \brief Draw a rectangle from (xmin,ymin) to (xmax,ymax)
    */
	void rectangle(int xmin, int ymin, int xmax, int ymax);

    /** \brief Draw a filled rectangle from (xmin,ymin) to (xmax,ymax)
    */
	void rectangleFill(int xmin, int ymin, int xmax, int ymax);

    /** \brief Draw a line from (x1,y1) to (x2,y2)
    */
	void line(int x1, int y1, int x2, int y2);

    /** \brief Draw a pixel on (x,y) with color (r,g,b,a)
    */
	void put_pixel(int x, int y, unsigned char r, unsigned char g, unsigned char b, unsigned char a=255);

    /** \brief Draw a point at (x,y)
    */
	void point(int x, int y);

    /** \brief Draw an array of n points
    */
	void points(int p[][2], int n);

    /** \brief Draw a grid from (xmin,ymin) to (xmax,ymax) with nx columns and ny rows
    */
	void grid(int xmin, int ymin, int xmax, int ymax, int nx, int ny);

    /** \brief return a random number (integer) between rmin to rmax included
    */
	int irand(int rmin=0, int rmax=100);

    /** \brief return a random number (float) between rmin to rmax included
    */
	float frand(float rmin = 0.f, float rmax = 1.f);

    /** \brief return the time elapsed since the beginning of the process in second
    */
	float elapsedTime();

    /** \brief return the number of time the key 'key' has been pressed since the last call to this function.
        ~~~~~~~~~~~~~~~{.c}
    	if (isKeyPressed(SDLK_LEFT)) { ... }     // test if the left arrow is pressed
    	if (isKeyPressed(SDLK_LEFT)) {  ... }    // if the left arrow is pressed then do ...
    	if (isKeyPressed(SDLK_a)) {  ... }       // if the key 'a' is pressed then do ...
    	if (isKeyPressed('a')) { ... }          // if the key 'a' is pressed then do ...
        ~~~~~~~~~~~~~~~
    */
	int isKeyPressed(int key);

    /** \brief (de)Activate the repeat mode: when the user presses continuously on the key touch is repeated. It has to be set at the beguinning of the program.
    */
	void setKeyRepeatMode(bool repeat);

    /** \brief Stop the program during d milliseconds
        ~~~~~~~~~~~~~~~{.c}
    	if (isKeyPressed(SDLK_LEFT)) {  ... }    // if the left arrow is pressed then do ...
    	if (isKeyPressed(SDLK_a)) {  ... }       // if the key 'a' is pressed then do ...
    	if (isKeyPressed('a')) { ... }          // if the key 'a' is pressed then do ...
        ~~~~~~~~~~~~~~~
    */
    inline void delay(int d)
    {
        //std::this_thread::sleep_for(std::chrono::milliseconds(d));
        SDL_Delay(d);
    }

    /** \brief return true if the mouse button 'button' is pressed
        ~~~~~~~~~~~~~~~{.c}
        if (isMousePressed(SDL_BUTTON_LEFT)) { ... }    // test if the left button of the mouse is pressed
        ~~~~~~~~~~~~~~~
    */
	bool isMousePressed(int button);

    /** \brief After this function (x,y) store the mouse position
        ~~~~~~~~~~~~~~~{.c}
        int x,y;
        mousePos(x,y);                                                                          // test if the left button of the mouse is pressed
        if ((isMousePressed(SDL_BUTTON_LEFT)) && (x>10) && (y>10) && (x<50) && (y<50)) { ... }  // if the user clicks if the square (10,10)(50,50)
        ~~~~~~~~~~~~~~~
    */
	void mousePos(int& x, int& y);

    /** \brief Manage standard event like key 'ESC', quit, etc.
    */
	bool winManageEvent();

    /** \brief Change the default size of the font
    */
	void fontSize(int s);

    /** \brief Print the text txt , up left corner is (x,y)
        ~~~~~~~~~~~~~~~{.c}
        fontSize(24);                               // Change the default font to the size 24
        print( 10, 20, "Bonjour");                  // Print the text "Bonjour" with the left corner (10,20)
        ~~~~~~~~~~~~~~~
    */
	void print(int x, int y, const char* txt);

    /** \brief Print the integer nb, up left corner is (x,y)
        ~~~~~~~~~~~~~~~{.c}
        print( 10, 20, 128);                      // Print the number "128" with the left corner (10,20)
        ~~~~~~~~~~~~~~~
    */
	void print(int x, int y, int nb);

    /** \brief Print the float nb, up left corner is (x,y)
        ~~~~~~~~~~~~~~~{.c}
        print( 10, 20, 3.1415);                      // Print the number "3.1415" with the left corner (10,20)
        ~~~~~~~~~~~~~~~
    */
	void print(int x, int y, float nb);

    /** \brief Stop the program until key 'space'is pressed
    */
    void pressSpace();


    /// \cond
	class Image
	{
    public:
		Image() : surface(NULL), texture(NULL), has_changed(false) {}

        friend int image_width(const Image& im);
        friend int image_height(const Image& im);
        friend bool image_isInit(const Image& im);
        friend Image image(const char* filename, bool transparency, unsigned char r, unsigned char g, unsigned b, unsigned char a);
        friend Image image(int w, int h);
        friend void image_savePNG(const Image& im, const char* filename);
        friend void image_draw(Image& im, int x, int y, int w, int h);
        friend void image_draw(Image& im, int x, int y, int w, int h, float angle, int flip);
        friend unsigned char image_get(const Image& im, int x, int y, int c);
        friend void image_set(Image& im, int x, int y, unsigned char r, unsigned char g, unsigned b, unsigned char a);
        friend void image_printInfo(const Image& im);



    protected:
		SDL_Surface* surface;
		SDL_Texture* texture;
		bool has_changed;
	};
    /// \endcond


    /** \brief Return an image loaded from the file filename
        ~~~~~~~~~~~~~~~{.c}
        struct Data
        {
            Image im;
        };
        void init(Data& d)
        {
            d.im = image("data/grapic.bmp", true, 255, 255, 255, 255);      // load the image "data/grapic.bmp" with transparency for the color (255,255,255,255)
        }
        void draw(Data& d)
        {
            image_draw(d.im, 0, 255);                                       // Draw the image with the left corner (0,255)
        }
        ~~~~~~~~~~~~~~~
    */
	Image image(const char* filename, bool transparency=false, unsigned char r=255, unsigned char g=255, unsigned b=255, unsigned char a=255);

    /** \brief Return an image of width=w and height=h
    */
	Image image(int w, int h);

    /** \brief Save the image into the file: format is PNG
    */
	void image_savePNG(const Image& im, const char* filename);

    /** \brief Draw the image at position (x,y) with width=w and height=h (if w<0 or h<0 the original size of the image is used)
    */
	void image_draw(Image& im, int x, int y, int w=-1, int h=-1);

    /** \brief Draw the image at position (x,y) with width=w and height=h (if w<0 or h<0 the original size of the image is used); angle indicate the angle of rotation and flip: 0=no flip, 1=horizontal flip, 2=vertical flip
    */
    void image_draw(Image& im, int x, int y, int w, int h, float angle, float flip=SDL_FLIP_NONE);

    /** \brief return the color component c of the pixel (x,y) of the image im.
        c must be 0 for the red component, 1 for the green component, 2 for the blue component or 3 for the alpha/opacity component.
    */
	unsigned char image_get(const Image& im, int x, int y, int c=0);

    /** \brief Set the pixel (x,y) of the image im with the color c
    */
	void image_set(Image& im, int x, int y, unsigned char r, unsigned char g, unsigned b, unsigned char a);

    /** \brief return the width of the image
    */
	inline int image_width(const Image& im) { return im.surface->w; }

    /** \brief return the height of the image
    */
	inline int image_height(const Image& im) { return im.surface->h; }

    /** \brief return true if the image is initialized
        ~~~~~~~~~~~~~~~{.c}
    	d.im = image("data/grapic.bmp", true, 255, 255, 255, 255);
        if (!image_isInit(d.im))                                            // if the image was not loaded, try an other path
            d.im = image("../data/grapic.bmp", true, 255,255,255,255 );
        ~~~~~~~~~~~~~~~
    */
	inline bool image_isInit(const Image& im) { return im.surface && im.texture;  }

    /** \brief Print the informations of the image im
    */
	void image_printInfo(const Image& im);


    /// \cond
	class Menu
	{
    public:
	    Menu() : select(0), visible(true) {}

       	friend void menu_add(Menu& m, const std::string& str);
        friend void menu_change(Menu& m, int i, const std::string& str);
        friend void menu_draw(Menu& m, int xmin, int ymin, int xmax, int ymax);
        friend int menu_select(const Menu& m);
        friend void menu_setSelect(Menu& m, int s);
        friend int caseToPixel(const Menu& m, int c, int ymin, int ymax);

    protected:
	    std::vector<std::string> txt;
	    int select;
	    bool visible;
	};
    /// \endcond

	/** \brief Add a line to the menu m with the text str
        ~~~~~~~~~~~~~~~{.c}
		Menu m;
		bool stop=false;
		winInit("Tutorials", 500, 500);
		menu_add( m, "Question 1");
		menu_add( m, "Question 2");
		while( !stop )
		{
			winClear();
			menu_draw(m, 5,5, 100, 102);
			switch(menu_select(m))
			{
				case 0 : draw1(); break;
				case 1 : draw2(); break;
			}
			stop = winDisplay();
		}
		winQuit();
        ~~~~~~~~~~~~~~~
	*/
	void menu_add(Menu& m, const std::string& str);

	//! \brief Change the text of a line in the menu
	void menu_change(Menu& m, int i, const std::string& str);

	//! \brief Draw the menu on the screen. See menu_add for an example of usage.
	void menu_draw(Menu& m, int xmin=5, int ymin=5, int xmax=-1, int ymax=-1);

	//! \brief return the line selected in the menu. See menu_add for an example of usage.
	inline int menu_select(const Menu& m) { return m.select; }

	//! \brief return the line selected in the menu. See menu_add for an example of usage.
    inline void menu_setSelect(Menu& m, int s) { m.select = s; }


    /// \cond
    typedef std::vector< std::pair<float,float> > Curve;
	class Plot
	{
    public:
	    Plot() : nb_plot_max(-1) {}

        friend void plot_clear(Plot& p );
        friend void plot_setSize(Plot& p, const int n);
        friend void plot_add(Plot& p, float x, float y, int curve_n);
        friend void plot_draw( const Plot& p, int xmin, int ymin, int xmax, int ymax, bool clearOrNot);
        friend void plot_minMax(  const Plot& p, float& fxmin, float& fymin, float& fxmax, float& fymax, int& maxsize);

    protected:
	    std::vector< Curve  > dat;
	    int nb_plot_max;
	};
    /// \endcond

    //! @todo: plot: setColor for each curves
    //! @todo: setRangeXMinMax for each curves
	//! \brief Clear the data stored
	inline void plot_clear(Plot& p ) { for(int i=0;i<p.dat.size();++i) p.dat[i].clear(); p.dat.clear(); }

    //! \brief Define the size of the stored value of the funtion (<0 means infinity)
	inline void plot_setSize(Plot& p, const int n)   { plot_clear(p); p.nb_plot_max = n; }

    //! \brief Add a point (x,y=f(x)) to the curve number curve_n
	void plot_add(Plot& p, float x, float y, int curve_n=0);

    //! \brief Draw the curve in the rectangle (xmin,ymin,xmax,ymax); clear the rectangle if clearOrNot is true
	void plot_draw( const Plot& p, int xmin, int ymin, int xmax, int ymax, bool clearOrNot=true);




    /**
        \brief Draw a triangle from the vertices (x1, y1), (x2, y2) and (x3, y3). (Code provided by Bastien DOIGNIES, many thanks)
     */
    void triangle(int x1, int y1,  int x2, int y2, int x3, int y3);

    /**
        \brief Draw a regular polygon with line_numbers edges centred on (x, y). (Code provided by Bastien DOIGNIES, many thanks)
     */
    void regular_polygone(int x, int y, unsigned int apotheme, unsigned int line_number);

    /**
        \brief Draw a filled triangle from the vertices (x1, y1), (x2, y2), (x3, y3)
     */
    void triangleFill( int x1, int y1,
                              int x2, int y2,
                              int x3, int y3);


    /**
        \brief Draw a filled regular polygon with line_numbers edges centred on (x, y). (Code provided by Bastien DOIGNIES, many thanks)
    */
    void regular_polygonFill(int x, int y, unsigned int apotheme, unsigned int line_number);


    /**
        \brief Decide if a point (px, py) is inside the triangle (ax, ay), (bx, by), (cx, xy). (Code provided by Bastien DOIGNIES, many thanks)
        \return true if inside, false otherwise
     */
    bool isInTriangle(float px, float py, float ax, float ay, float bx, float by, float cx, float cy);


    /** \brief  Draw a simple(no edge-crossing) and without holes filled polygon
     * \param   p[]    : array of integer which represent the coordinate of each vertices
     * \param   number : number of element in p[], must be even (point are two integers each)!
     * \warning Draw nothing if there are not enough vertices or if number is not even
     * \warning Undetermined draw if the polygon is not simple
     (Code provided by Bastien DOIGNIES, many thanks)
     */
    void polygonFill(int p[][2], unsigned int number);


    /** \brief Draw a polygon. (Code provided by Bastien DOIGNIES, many thanks)
     */
    void polygon(int p[][2], unsigned int number);


} // namespace

#endif


#include <documentations.h>
