#include <Grapic.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>


using namespace grapic;
using namespace std;
const int DIMW=500;
const int V3=60;
const int V5=50;




struct World
{
    Image im;

};


void init(World& d)
{

    d.im =  image("data/licorne/paysage.jpg", true, 255, 255, 255);

}
void update(World &d)
{
    const float vitesse = 20.f;
    float temps = elapsedTime();

}




void draw(World& d,int &x, int &y,float &m)

{
    const float vitesse = 20.f;
    float temps = elapsedTime();

    if (isKeyPressed(SDLK_RIGHT))
    {
        x++;
        if (x>900)
            x=900;
    }
    if (isKeyPressed(SDLK_LEFT))
    {
        x--;
        if (x<0)
            x = 0;
    }
    if (isKeyPressed(SDLK_UP))
    {
        y=y+1;
    }
    if (y>0)
    {
        y=y+1;

        if ( y>360)
        {
            y=0;
        }
    }

    image_draw(d.im, -2,-2);

    color(0,0,0);
    rectangleFill( 22+x,5+y,28+x,30+y);

    color(255,0,0);
    rectangleFill( x,5,50+x,15);
    rectangleFill( 22+x,5,28+x,30);

        if (m<380)
    {
        m=m+0.05;

        if ( m>380)
        {
            m=0;
        }

    }
    int i;
    color(0,205,0);
    for (i=0; i<10;i++)
    {


    rectangleFill(((i+i+2)*750/10),330-m,(i+i+1)*750/10,360-m);   //Xmax Ymin Xmin Ymin
//    rectangleFill(80,330-m,130,360-m);                            //BOUGER VARIABLE X SELEMENT
//    rectangleFill(160,330-m,210,360-m);
//    rectangleFill(240,330-m,290,360-m);
//    rectangleFill(320,330-m,370,360-m);
//    rectangleFill(400,330-m,450,360-m);
//    rectangleFill(480,330-m,530,360-m);
//    rectangleFill(560,330-m,610,360-m);
//    rectangleFill(640,330-m,690,360-m);
//    rectangleFill(720,330-m,770,360-m);
//    rectangleFill(800,330-m,850,360-m);
//    rectangleFill(880,330-m,940,360-m);
if ((22+x)>((i+i+1)*750/10) && ((i+i+2)*750/10)>(28+x) && ((30+y) >  (330-m )))
        {
           rectangleFill(((i+i+2)*750/10),330-m,(i+i+1)*750/10,360-m);
           color(0,0,0);
           m=0;
        }
    }


}



int main(int, char** )
{
    int x=5;
    int y=0;
    float m=0;
    World dat;
    winInit("MyProg",950, 360);

    init(dat);
     bool stop=true;
    setKeyRepeatMode(true);


    while( !winHasFinished() )
    {
        winClear();
        draw(dat,x,y,m);
        winDisplay();
    }


    winQuit();
    return 0;
}

