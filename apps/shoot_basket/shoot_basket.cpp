#include <Grapic.h>
#include <iostream>
#include <math.h>

using namespace grapic;
using namespace std;

const int DIMW=1600;
const float FRICTION = 0.8;
const float dt=0.04;
int but=1;



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

Complex rotate (Complex p,float cx, float cy, float theta)
{
    Complex c,rot;
    c=make_complex(cx,cy);
    rot = make_complex_exp(1,theta);
    return rot*(p-c)+c;
}


struct Particule
{
    float m; //La masse (1D)
    Vec2 p; //La position (2D)
    Vec2 v; //La vitesse (2D)
    Vec2 f; //La force (2D)
    int a,b;
    int score;

    Vec2 perso;

};


void partAddForce(Particule &p, Vec2 f)
{
    p.f=p.f + f;
}

void partUpdatePV(Particule &p)
{
    p.v=p.v+(dt/p.m)*p.f;
    p.p=p.p+(dt*p.v);
}
void partInit(Particule &p)
{
    int hauteur;
    srand(time(NULL));
    hauteur=rand()%DIMW/3;
    p.m=1;
    p.p.x=40;
    p.p.y=20;
    p.v.x=0;
    p.v.y=0;
    p.a=DIMW-80;
    p.b=hauteur;
    p.score=0;
    p.perso.x=20;
    p.perso.y=120;





}
void draw(Particule &p)
{

    int i;
    int z;
    z=p.p.y;
    ///////
    color (255,155,0);
    circleFill(p.perso.x,p.perso.y,20);
    rectangleFill(p.perso.x-5,p.perso.y,p.perso.x,p.perso.y-80);
    rectangleFill(p.perso.x-30,p.perso.y-40,p.perso.x+20,p.perso.y-50);
    triangleFill(p.perso.x-5,p.perso.y-70,p.perso.x+20,p.perso.y-120,p.perso.x+10,p.perso.y-80);
    triangleFill(p.perso.x-5,p.perso.y-70,p.perso.x-35,p.perso.y-140,p.perso.x-10,p.perso.y-90);
    if (z>p.perso.y)
    {
        z=p.perso.y;
    }
    rectangleFill(p.perso.x+10,p.perso.y-40,p.perso.x+20,z);


    //////ballon///
    color(255,255,255);
    circleFill(p.p.x, p.p.y, 20);
/////panier/////

    rectangleFill(p.a,p.b,p.a+80,p.b+10);
    rectangleFill(p.a+75,p.b,p.a+80,p.b+70);
    for (i=0; i<8; i++)
        rectangle(p.a+10*i*i/8,p.b-40*i/4,p.a+70,p.b+10);

//////score/////
    color(255,0,0);
    fontSize(20);
    print(DIMW-150,DIMW/2-50,"score:");
    print(DIMW-90,DIMW/2-50,p.score);

    color(255,255,255);
    fontSize(200);
    if (but==3)
    {
        print(DIMW/4,DIMW/6,"Y E A H");
    }





}
void autom(Particule &p)
{

            p.p.x=p.a;
            p.p.y=p.b;



       but=1;



}



void update(Particule &p)
{
    Vec2 G;

    G.y=-9.81;
    int x,y;
   if (isKeyPressed(SDLK_a))
    {
    autom(p);
    }


    if (isMousePressed(SDL_BUTTON_LEFT))
    {
        but=1;
        mousePos(x,y);
        if (x>500)
        {
            x=500;
        }

        if (y>350)
        {
            y=350;
        }
        p.p.x=40;
        p.p.y=0;
        p.v.x=-1;
        p.v.y=-1;
        if (p.v.x<0)
        {

            p.v.x=50+x/5;
            p.v.y=50+y/5;

        }
        fontSize(50);
        print(150,DIMW/2-50,x);
        print(150,DIMW/2-100,y);
    }
    if(p.p.x < 0)
    {
        p.p.x = -p.p.x;
        p.v.x = -p.v.x;
        p.v = FRICTION*p.v;
    }

    if (p.p.y < 0)
    {
        p.p.y = -p.p.y;
        p.v.y = -p.v.y;
        p.v = FRICTION*p.v;
        but=0;

    }
    if(p.p.x > DIMW )
    {
        p.p.x =40;
        p.v.x =0;
        p.v.y=50;
        p.p.y =0;
    }

//    if(p.p.x > (p.a+70) && ( p.p.y >(p.b+70) && p.p.y<p.b ))
//    {
//       p.p.x =2*DIMW-p.p.x;
//       p.v.x =-p.v.x;
//       p.v = FRICTION*p.v;
//    }

    if (p.p.y > DIMW/2)
    {
        p.p.y =DIMW-p.p.y;
        p.v.y =-p.v.y;
        p.v = FRICTION*p.v;
    }
    partAddForce(p, G);
    partUpdatePV(p);
    p.f.x=0;
    p.f.y=0;

    if (p.p.x>p.a && p.p.y>(p.b-20) && p.p.y<(p.b+20)&&but==1)
    {
        p.b=rand()%DIMW/3;
        p.score=p.score+1;
        but=3;

    }

}


int main(int, char **)
{


    Particule p;
    Vec2 G;
    winInit("Particules", DIMW, DIMW/2);
//    bool stop=true;
//    setKeyRepeatMode(true);
    backgroundColor( 0, 0, 0 );


    partInit(p);

    while( !winHasFinished())
    {
        winClear();
        draw(p);
        update(p);
        winDisplay();
    }
    winQuit();
    return 0;
}
