#include <Grapic.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <random>


using namespace grapic;
using namespace std;

//int x=550;
//int y=300;




struct World
{
    Image im;
    Image ims;
    Image imss;

};

void init(World& d)
{
    d.im =  image("data/bird/bird1.png", false,1,1);
    d.ims = image("data/bird/bird2.png",true,1,1);
    d.imss = image("data/bird/arbre.jpg",true,1,1);
}

void draw(World& d,int &x, int &y)

{
    int n=0;
    winClear();
    backgroundColor(0,0,0);
    image_draw(d.imss, 0,0);


    if (isMousePressed(SDL_BUTTON_LEFT))
    {
        mousePos(x,y);
    }
    if (isKeyPressed(SDLK_z))
    {
        y++;
        if (y>700)
            y =700;

    }
    if (isKeyPressed(SDLK_s))
    {
        y--;
        if (y<0)
            y = 0;
    }
    if (isKeyPressed(SDLK_e))
    {
        x++;
        if (x>1300)
            x =1300;

    }
    if (isKeyPressed(SDLK_a))
    {
        x--;
        if (x<0)
            x= 0;
    }
    if(y%2 && x%2 || y%1 && x%1 || y%3 && x%3 )
    {
        image_draw(d.im, x+20,y);

    }
    else
    {
        image_draw(d.ims, x,y);
    }




}
void jeu()
{
    int z,x;
    z=rand()%1500;
    x=rand()%800;
    color(255,0,0);
    circleFill(z,x,20);
}

int main(int, char** )
{

    int x=1;
    int y=1;

    World dat;
    winInit("MyProg",1500, 800);
    bool stop=true;
    setKeyRepeatMode(true);
    init(dat);
    while( !winHasFinished() )
    {
        draw(dat,x,y);
        winDisplay();
    }


    winQuit();
    return 0;
}

