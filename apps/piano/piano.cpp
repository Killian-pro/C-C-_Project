#include <Grapic.h>
#include <iostream>
#include <math.h>

using namespace grapic;
using namespace std;

const int DIMW=1500;

struct Vec2
{
    float x;
    float y;
};
typedef struct Vec2 Complex;


Complex make_complex(float x,float y)
{
    Complex c;
    c.x=x;
    c.y=y;
    return c;
}

Complex make_complex_exp(float r,float theta_deg)
{
    Complex c;
    c.x=r*cos(theta_deg);
    c.y=r*sin(theta_deg);
    return c;
}


Complex operator+(Complex a, Complex b)
{
    Complex c;
    c.x=a.x+b.x;
    c.y=a.y+b.y;
    return c;
}

Complex operator-(Complex a, Complex b)
{
    Complex c;
    c.x=a.x-b.x;
    c.y=a.y-b.y;
    return c;
}


Complex operator*(float lambda, Complex a)
{
    Complex c;
    c.x=lambda*a.x;
    c.y=lambda*a.y;
    return c;
}

Complex scale(Complex p, float cx, float cy, float lambda)
{
    Complex c;
    c=make_complex(cx,cy);
    return lambda*(p-c)+c;
}

Complex operator*(Complex a, Complex b)
{
    Complex c;
    c.x=a.x*b.x-a.y*b.y;
    c.y=a.x*b.y+a.y*b.x;
    return c;
}
struct Particule
{
      Image im;
    int x;
    int y;
    int e;
    int f;
    int z;
    int g;
    int nb;
    int score;
    int m;
    int o;
    float vitesse;
};




void partInit(Particule &p)
{


    p.im=image("data/bird/kfc.png");
    p.x=DIMW/2;
    p.y=0;
    p.z=DIMW+50;
    p.g=0;
    p.nb=rand()%DIMW;
    p.score=0;
    p.e=DIMW+50;
    p.f=0+500;
    p.m=DIMW+50;
    p.o=DIMW/4;
    p.vitesse=0.1;
}

void update(Particule &p)
{
    image_draw(p.im,p.x,p.y,80,80);

    if (isKeyPressed(SDLK_LEFT)&& p.x>0)

    {
        p.x=p.x-5;
    }
    if (isKeyPressed(SDLK_RIGHT)&& p.x<(DIMW-50))

    {
        p.x=p.x+5;

    }


    if(p.y<(DIMW/2) && p.y>0)
    {
        p.y--;

        if(p.y<(DIMW/2)&&p.y>(DIMW/2)-100)
        {
            p.y=0;

        }

    }


    if(p.z>-20)
    {

        p.z--;
        if (p.z<0)
        {
            p.z=DIMW+100+p.nb ;

            p.nb=rand()%DIMW/4;

        }

    }

    if(p.z>DIMW+300)
    {

        p.z=50;
    }

     if(p.m>-10)
    {

        p.m=p.m-p.vitesse;
        if (p.m<10)
        {
            p.m=DIMW+100;
        }

    }
    if(p.e>-20)
    {

        p.e--;
        if (p.e<0)
        {
            p.e=DIMW+100;


        }
    }
    if (isKeyPressed(SDLK_SPACE)&& p.y<(DIMW/2)-50)
    {
        p.y=p.y+2;
    }
    if ((p.x>p.z && p.x < p.z+4)||(p.x>p.e && p.x < p.e+4) )
    {
        p.score=p.score+1;
    }

    if ((p.x>p.z && p.x < p.z+50 && p.y<p.g+p.nb)||(p.x>p.e && p.x < p.e+50 && p.y<p.f+p.nb && (p.y+50)>p.f)||((p.o-20)<p.y)&&((p.o+20)>p.y)&&(p.x<p.m+30)&&(p.x>p.m-30))
    {


        fontSize(100);
        color(255,0,0);
        print(DIMW/2-200,DIMW/2-200,"GAME OVER");
        p.score=0;
        p.vitesse=0.01;
    }
    if (p.score>2)
    {
        p.e=p.e-2;
    }

  if (p.score>4)
    {
        p.z=p.z-2;
    }
      if (p.score>6)
    {
        p.vitesse=p.vitesse+0.001;
        if (p.vitesse<1)
            {
                p.vitesse=1;
            }
    }



}

void partDraw(Particule &p)
{
    rectangleFill(p.x,p.y,p.x+50,p.y+50);
    color(255,255,255);
      if (p.score%2)
    {
     color(25,255,25);
    }
    else{
            color(255,0,0);
    }
    rectangleFill(p.e,p.f,p.e+50,p.f+p.nb);
    rectangleFill(p.z,p.g,p.z+50,p.g+p.nb);
      color(253,106,2);
    circleFill(p.m,p.o,40);

    fontSize(100);
    color(255,0,0);
    print(DIMW/2-200,DIMW/2-200,p.score);



}

int main(int, char **)
{
    Particule dat;

    winInit("Particules", DIMW, DIMW/2);
    backgroundColor( 0, 0, 0 );

    bool stop=true;
    setKeyRepeatMode(true);

    partInit(dat);

    while( !winHasFinished())
    {
        winClear();
        partDraw(dat);
        update(dat);
        winDisplay();
    }
    winQuit();
    return 0;
}




