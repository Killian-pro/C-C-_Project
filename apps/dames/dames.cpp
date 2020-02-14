#include <Grapic.h>
using namespace grapic;
const int DIMW=1600;
const int NBCASE=70; //taille
const int DIM=9;
int vide=0;


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



struct pion
{
    Vec2 blanc[20];
    Vec2 noir [20];
    Vec2 vide [20];

};



bool caseNoir(int i, int j)
{
    return ((j*10 + i) % 2) == 0;
}

void damier()
{
    int i, j;
    for (i = 1; i < 11; ++i)
        for (j = 0; j < 5; ++j)
        {
            if (caseNoir(i, j))
            {
                color(255, 255, 255);
            }

            else
            {
                color(150, 150, 150);
            }


            rectangleFill( (i + i-1)*NBCASE, (j+j+2)*NBCASE, (i +i+1)*NBCASE, (j +j+ 1)*NBCASE);
            rectangleFill( (i + i+1)*NBCASE, (j+j+2)*NBCASE, (i +i+4)*NBCASE, (j +j+3)*NBCASE);


        }
    color(0,0,0);
    rectangle(70,70,1470,770);
}

void initpion(pion &p)
{
    int i,j;
    for (i = 1; i < 11; ++i)
        for (j = 0; j < 2; ++j)
        {
            if (caseNoir(i, j))
            {
                p.noir[i].x=(i + i-1)*NBCASE-70;
                p.noir[i].y=(j+j+1)*NBCASE+35;
                p.noir[j].x=(i + i+1)*NBCASE-70;
                p.noir[j].y=(j+j+2)*NBCASE+35;
                color(0,0,0);
//                circleFill((i + i-1)*NBCASE-70,(j+j+1)*NBCASE+35,10);
//             circleFill((i + i+1)*NBCASE-70,(j+j+2)*NBCASE+35,10);
                circleFill(p.noir[i].x,p.noir[i].y,20);
                circleFill(p.noir[j].x,p.noir[j].y,20);
                vide=1;

            }
            if (caseNoir(i, j))
            {
                p.blanc[i].x=(i + i-1)*NBCASE-70;
                p.blanc[i].y=(j+j+1)*NBCASE+450;
                p.blanc[j].x=(i + i+1)*NBCASE-70;
                p.blanc[j].y=(j+j+2)*NBCASE+450;
                color(255,255,255);
                //   circleFill((i + i-1)*NBCASE-70,(j+j+1)*NBCASE+450,10);
                //   circleFill((i + i+1)*NBCASE-70,(j+j+2)*NBCASE+450,10);
                circleFill(p.blanc[i].x,p.blanc[i].y,20);
                circleFill(p.blanc[j].x,p.blanc[j].y,20);
                vide=1;
            }

        }

}

void update (pion &p)
{
    int x,y;
    int i,j;
   if ( isMousePressed(SDL_BUTTON_LEFT))
   {
       mousePos(x,y);
        p.blanc[i].x=x;
       p.blanc[i].y=y;

  circleFill(p.blanc[i].x,p.blanc[i].y,20);
   }}


int main(int, char ** )
{

    pion p;
    winInit("plateau", DIMW, DIMW/2);

    while( !winHasFinished() )
    {
        winClear();
        damier();
       initpion(p);
        update(p);
        winDisplay();
    }
    winQuit();
    return 0;
}

