
/*! \mainpage GrAPiC

<br>
\image html grapic_samples.jpg
<br>
\section intro Introduction

GrAPiC is a small, easy-to-use framework to add graphical functionalities to your C/C++ code. Its main goal is to provide easy
graphical functions to be used in introduction courses of algorithm and programming in C/C++.
It is based on SDL2 but to use it you need to know only few very simples functions.
The Grapic archive comes with the needed SDL part, you do not have to install SDL. Just unzip and enjoy !
<br>
<br>
<br>

\section download Download
Download and install the last version:\htmlinclude "VERSION.html".
Previous versions may be downloaded from the [download](../download) directory.

<br>
<br>
<br>
\section start How to start ?

\subsection win Run on Windows
  - Install Codeblocks from: [http://www.codeblocks.org/downloads](http://www.codeblocks.org/downloads)\n
    Take the one with MinGW like codeblocks-16.01mingw-setup.exe

  - Download the archive file, see section download.

  - Run with CodeBlocks
     - Open the file Grapic/build/windows/grapic_workspace with Codeblocks
     - Select in the projects manager (on the left) the project you want with the right button "Activate project":
       \image html cb_activatePrj.jpg "Selection of the project in Codeblocks" width=400
     - And run the program !

\subsection linux Run on Linux
  - Install SDL2, SDL_Image for SDL2 and SDL_ttf for SDL2 ; for instance with
    \code
    sudo apt-get install libsdl2-dev libsdl2-ttf-dev libsdl2-image-dev
    \endcode

  - Download the archive file, see section download.

  - Run with CodeBlocks
     - Open the file Grapic/build/linux/grapic_workspace with Codeblocks.
     - Select in the projects manager (on the left) the project you want with the right button "Activate project":
       \image html cb_activatePrj.jpg "Selection of the project in Codeblocks" width=400
     - And run the program !
  - Run in the Terminal:
     - cd ....grapic
     - make
     - bin/demo


\subsection mac Run on MacOS
  - Download the archive file, see section download.

  - Run in the Terminal:
     - cd grapic
     - make
     - bin/demo

\subsection edit Edit my first program
The kernel source code of grapic is in grapic/src. The source codes of the programs/demos/tutorials are in grapic/apps.
You can edit your first program by editing the file grapic/apps/start/main_start.cpp
\image html cb_editStart.jpg width=10

\subsection create Create a new project
You can create your own project.
 - Copy the directory apps/start into apps/MYPROJECT  (replace MYPROJECT by the name you want)
 - Rename apps/MYPROJECT/main_start.cpp into main_MYPROJECT.cpp
 - Edit the file Grapic/premake4.lua and add at the end
make_project( "MYPROJECT", 	"apps/MYPROJECT/main_MYPROJECT.cpp" )
 - Run the script 'premake.bat' on windows; or 'make premake' on Linux/MacOS




<br>
<br>
<br>
\section tuto Tutorials

<br>
<br>
<br>
\subsection tuto1 Tutorial 1: Simple program
\image html tuto_simple.jpg "The code of the tutorial 1 "simpleDrawing" illustrates the basis of Grapic" width=200px
\include "../../apps/tutorials/tuto1_Simple.cpp"

<br>
<br>
<br>
\subsection tuto2 Tutorial 2: First Loop
\image html tuto_drawing.jpg "The code of the tutorial 2 shows how to write the main loop of a Grapic application" width=200px
\include "../../apps/tutorials/tuto2_FirstLoop.cpp"

<br>
<br>
<br>
\subsection tuto3 Tutorial 3: Drawing
\image html tuto_drawing.jpg "The code of the tutorial 3 shows how to draw rectangles, circles, lines, etc." width=200px
\include "../../apps/tutorials/tuto3_Drawing.cpp"

<br>
<br>
<br>
\subsection tuto4 Tutorial 4: Keyboard
\image html tuto_drawing.jpg "The code of the tutorial 4 shows how to manage the keyboard." width=200px
\include "../../apps/tutorials/tuto4_Keyboard.cpp"

<br>
<br>
<br>
\subsection tuto5 Tutorial 5: Mouse
\image html tuto_mouse.jpg "The code of the tutorial 5 shows how manage the mouse to draw a square" width=200px
\include "../../apps/tutorials/tuto5_Mouse.cpp"

<br>
<br>
<br>
\subsection tuto6 Tutorial 6: Menu
\image html tuto_menu.jpg "The code of the tutorial 6 shows how to create a simple menu." width=200px
\include "../../apps/tutorials/tuto6_Menu.cpp"

<br>
<br>
<br>
\subsection tuto7 Tutorial 7: Animation
\image html tuto_animation.jpg "The code of the tutorial 2 shows how to display a simple animation depending on the elapsed time." width=200px
\include "../../apps/tutorials/tuto7_Animation.cpp"

<br>
<br>
<br>
\subsection tuto8 Tutoria 8: Plot/Graph
\image html tuto_plot.jpg "The plot code illustrates the drawing of a graph entering values of a function" width=200px
\include "../../apps/tutorials/tuto8_Plot.cpp"

<br>
<br>
<br>
\subsection tutoDemo Tutoria 9: Demo
\image html tuto_demo.jpg "The demo code illustrates many functionalities of Grapic" width=200px
\include "../../apps/tutorials/tuto9_demo.cpp"


<br>
<br>
<br>
\section Examples

Grapic comes with several small examples. It can be used as source of inspiration.


\subsection tetris Tetris
\image html tetris.jpg "A example of tetris" width=200px
\include "../../apps/demo_tetris/main_tetris.cpp"


\subsection pacman Pacman
\image html pacman.jpg "Pacman" width=200px
\include "../../apps/demo_pacman/main_pacman.cpp"



<br>
<br>
\section problems Current problems

- int main() ==> int main(int , char **)

- Image im = image("data\papillon.jpg") ==> Image im = image("data//papillon.jpg")   or Image im = image("data\\papillon.jpg")

- Even tutorials do not compile 
   - check in directory 'extern' that you have the version for your computer: mingw for windows, macox for mac and nothing for 
        linux since you have to install them with the apt-get explained in the Section installtion
   - Try to rerun premake with premake.bat on windows or make premake on linux/macos

*/
