#include <Grapic.h>
#include <iostream>
#include <math.h>

using namespace grapic;
using namespace std;

const int DIMW=1500;
const int MAXPART = 100;
const float FRICTION = 0.8;
const float dt=0.01;
const int k = 500;
const float g = 9.81;
const int M=1;


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


struct Particule{
    float m; //La masse (1D)
    Vec2 p; //La position (2D)
    Vec2 v; //La vitesse (2D)
    Vec2 f; //La force (2D)
};

struct Spring
{
    int i1;
    int i2;
    float k;
    float lg;
};

struct World
{
    Particule tab[MAXPART];
    int nbparticules;
    float dt;
    Spring ressort[MAXPART];
    int nbRessorts;
};

int add_particule(World &w , int x , int y)
{
    w.tab[w.nbparticules].p=make_complex(x,y);
    w.tab[w.nbparticules].v=make_complex(0,0);
    w.tab[w.nbparticules].k=k;
    w.tab[w.nbparticules].m=M;
    return w.nbparticules-1;
}
int addspring (world &w , int t1,int t2)
{
    w.ressort[w.nb.ressort].i1=i1;
     w.ressort[w.nb.ressort].i2=i2;
 w.ressort[w.nb.ressort].k=k;
 w.ressort[w.nb.ressort].fg=distance(w.part[i1].p,w.part[i2].p)  ;
  w.ressort[w.nb.ressort].lg=lg;
    w.nb.ressort++;
    return (w.nb.ressort-1);

}
void initworld(world&w)
{
    w.nbparticukes=0;
    w.nbressorts=0;
}
void
void partAddForce(Particule &p, Vec2 f){
    p.f=p.f + f;
}

void partUpdatePV(Particule &p){
    p.v=p.v+(dt/p.m)*p.f;
    p.p=p.p+(dt*p.v);
}
void partInit(Particule &p){

    p.m=1;
    p.p.x=DIMW/2;
    p.p.y=DIMW/2;
    p.p.x=DIMW/2;
    p.p.y=DIMW/2;
    p.v.x=0;
    p.v.y=0;
    p.f.x=400;
    p.f.y=530;

}

void update(Particule &p){
    Vec2 G;
    G.x=0;
    G.y=-9.81;
    int x,y;

     if (isMousePressed(SDL_BUTTON_LEFT))
    {
        mousePos(x,y);
        p.p.x=x;
        p.p.y=y;


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
    }
    if(p.p.x > DIMW)
    {
        p.p.x =2*DIMW-p.p.x;
        p.v.x =-p.v.x;
        p.v = FRICTION*p.v;
    }
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
}
void partDraw(Particule &p){
    color(255,255,255);
    circleFill(p.p.x, p.p.y, 20);
}



int main(int, char **){
    World dat;
    Particule p;
    Vec2 G;
    winInit("Particules", DIMW, DIMW/2);
    backgroundColor( 0, 0, 0 );


    partInit(p);

    while( !winHasFinished())
        {
        winClear();
        update(p);
        partDraw(p);
        winDisplay();
    }
    winQuit();
    return 0;
}




