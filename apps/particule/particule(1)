#include <Grapic.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <random>


using namespace grapic;
using namespace std;

//int x=550;
//int y=300;

const int DIMW=1500;
const int G=9.81;


struct Complex
{
    float x;
    float y;
};

Complex make_complex(float x, float y)
{
    Complex c;
    c.x = x;
    c.y = y;
    return c;
}

Complex make_complex_exp(float r, float theta)
{
    Complex c;
    c.x = r*cos(theta);
    c.y = r*sin(theta);
    return c;
}

Complex operator+(Complex a, Complex b)
{
    Complex c;
    c.x = a.x+b.x;
    c.y = a.y+b.y;
    return c;
}

Complex operator-(Complex a, Complex b)
{
    Complex c;
    c.x = a.x-b.x;
    c.y = a.y-b.y;
    return c;
}


Complex operator*(float lambda, Complex b)
{
    Complex c;
    c.x = b.x*lambda;
    c.y = b.y*lambda;
    return  c;
}

Complex operator*(Complex b,float lambda)
{
    Complex c;
    c.x = lambda*b.x;
    c.y = lambda*b.y;
    return  c;
}


Complex scale (Complex p, float cx, float cy, float lambda)
{
    Complex c;
    c = make_complex (cx, cy);
    return lambda*(p-c)+c;
}

Complex operator*(Complex a, Complex b)
{
    Complex c;
    c.x = a.x*b.x-a.y*b.y;
    c.y = a.x*b.y+a.y*b.x;
    return c;
}

struct particule
{
    Complex position;
    Complex vitesse;
    Complex force;
    Complex acceleration;
    float masse;

};
struct world
{
    Complex part;
    particule tab[DIMW];
    int nbparticules;
    float dt;

};
void ajoutforce (particule &p)
{
    float dt =0.1;

    p.force=p.force+make_complex ( 0, -(p.masse*G));

}

void partupdate (particule &p)
{
    float dt =0.01;
    p.vitesse = p.vitesse +p.force*(dt/p.masse);
    p.position=p.position+p.vitesse*dt;
    p.force.x = 0;
    p.force.y = 0;

}

void init( particule &p)
{

    p.vitesse = make_complex(0,0);
    p.masse=1;
    p.position=make_complex(DIMW/2,DIMW/2);
    p.force=make_complex(0,0);

}

void positiond ( particule &p)

{
    color (255,0,0);
    circleFill(p.position.x,p.position.y,20);
    if (p.position.y<0)
    {
        p.position.y=-50*p.position.y;
        //p.position.y=DIMW/2;
    }


}





int main(int, char** )
{


    winInit("MyProg",1500, 800);
    particule parti ;
    world ww;
    init(parti);
    while( !winHasFinished() )
    {
        winClear();
        ajoutforce(parti);
        partupdate(parti);
        positiond(parti);

        winDisplay();
    }


    winQuit();
    return 0;
}

