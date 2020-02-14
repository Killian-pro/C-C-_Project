#include <Grapic.h>
#include <stdlib.h>
#include <time.h>
#include <random>


using namespace grapic;
using namespace std;


//const int DIMW = rand()%260;
//const int surfacew=950;
//const int  surfaceH = 360;
//const int   licorneW = 20;
//const int  licorneH = 20;

const int  x=5;
//const int   y=5;
//const int   x_mur = surfacew-100;
//int   mur_vitesse = 0.05;
const int   y_mur = 0;
//const int   y_mur0=DIMW;
//const int   espace = licorneH;
//const int   y_move=10;




struct World
{
    Image im;
    Image ims;
    Image imss;
    Image imsss;
};

void init(World& d)
{
    d.im =  image("data/licorne/paysage.jpg", true, 255, 255, 255);
    d.ims = image("data/licorne/mur.jpg",false,100,100);
    //d.imss = image("mur.jpg",false,100,100);
    d.imsss = image("data/licorne/licorne.png",false,100,100);
}

void draw(World& d,int &y,int n, float &x_mur, int &y_mur0)

{

    srand(time(NULL));
    winClear();
    image_draw(d.im, -2,-2);
    image_draw(d.ims,x_mur,y_mur0,100,100);
    //image_draw(d.imss,x_mur,y_mur,100,100);
    image_draw(d.imsss, x,y,200,130);
    if (isKeyPressed(SDLK_UP))
    {

        y++;

        if (y>230)
            y=230;
    }



    if (isKeyPressed(SDLK_DOWN))
    {

        y--;
        if (y<0)
            y = 0;
    }
    if (x_mur>0)
    {
        x_mur=x_mur-0.5;

        if (x_mur==0)
        {
            x_mur=850;
             y_mur0=rand()%260;
        }

    }
    if (x_mur<=200 && x_mur >=-100 && y>(y_mur) && y<(y_mur+200))
    {
        print(5,5,"collision");
    }


}


int main(int, char** )
{

    World dat;
    winInit("MyProg",950, 360);
    bool stop=true;
    setKeyRepeatMode(true);
    init(dat);
    int y=5;
    int n=0;
    float x_mur=850;
    int y_mur0=rand()%260;
    while( !winHasFinished() )
    {
        draw(dat,y,n,x_mur,y_mur0);
        winDisplay();
    }


    winQuit();
    return 0;
}

