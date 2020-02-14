#include <Grapic.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>


using namespace grapic;
using namespace std;
const int DIMW=200;


///////////////////////////////////////////PARTICULE////////////////////////////////////////////////////////////////////////////////////////////////////////
struct Complex
{
    float x;
    float y;
};
//typedef struct Vec2 Complex;


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

Complex operator/(Complex a, int d)
{
    Complex c = make_complex((a.x)/d, (a.y)/d);

    return c;
}
struct Color
{
    int r;
    int g;
    int b;
};

struct marchand
{

    float prix;
    Complex pos;
    Color client;
    int nbclient;
    float gain;

};
struct marchands
{
    marchand tab[100];
    int nbmarchand;
};
float distance(Complex P1,Complex P2)
{
    return sqrt((P1.x-P2.x)*(P1.x-P2.x)+(P1.y-P2.y)*(P1.y-P2.y));

}
int posmarch(int x, int y,marchands &ms)
{
    Complex posclient;
    posclient.x=x;
    posclient.y=y;
    float mn,m;
    int i;
    int indmin =0 ;

    mn = ms.tab[0].prix + distance( ms.tab[0].pos, posclient) ;
    for (i=1; i<ms.nbmarchand ; i++)
    {

        m= ms.tab[i].prix+distance( ms.tab[i].pos, posclient);
        if (m<mn)
        {
            mn=m;
            indmin=i;
        }
    }
    return indmin;
}
void rentreargent(marchand &m)
{
    m.gain=m.nbclient*m.prix;
}

void initmarchand(marchand &ms)
{
    ms.nbclient=0;
    ms.client.b=rand()%256;
    ms.client.g=rand()%256;
    ms.client.r=rand()%256;

    ms.prix=2+rand()%5;

    ms.pos.x=rand()%DIMW;
    ms.pos.y=rand()%DIMW/2;
    ms.gain=0;

}

void init (marchands &ms,  int nbmarchands)
{

    int i;
    ms.nbmarchand=nbmarchands;
    for (i=0 ; i<ms.nbmarchand; i++)
    {
        initmarchand(ms.tab[i]);
    }


}

void drawmarchands(marchands &ms)
{
    int i;

    for (i=0; i<ms.nbmarchand ; i++)
    {
//        color(ms.tab[i].client.r,ms.tab[i].client.g,ms.tab[i].client.b);
        color(255,0,0);
        circleFill(ms.tab[i].pos.x,ms.tab[i].pos.y,2);
    }
}

void traitevente(marchands &ms ,int affichage )
{
    int i,x,y, indmim;
    for (i=0; i<ms.nbmarchand ; i++)
        ms.tab[i].nbclient=0;

    for (x=0; x<DIMW; x++)
    {

        for (y=0 ; y<DIMW; y++)
        {


            indmim = posmarch( x,y,ms)  ;

            ms.tab[indmim].nbclient++;
            if(affichage==0)
            put_pixel(x,y,ms.tab[indmim].client.r,ms.tab[indmim].client.g,ms.tab[indmim].client.b);


        }
    }


}
void majmarchands(marchands &ms)
{   int i,j;
    int maxclient=0;
    int indicebestpos = 0;
    marchands ms1=ms;
    marchands msr=ms;
    Complex deplacement[4]= {make_complex(0,1),make_complex(1,0),make_complex(0,-1),make_complex(-1,0)};
    Complex diffprix[3]={make_complex(0,0),make_complex(0,10),make_complex(0,-10)};
    for (i=0; i<ms.nbmarchand ; i++)
    {
        for(j=0; j<4 ; j++)
        {
            ms1.tab[i].pos=ms1.tab[i].pos+deplacement[j];
            traitevente(ms1,1);
            if (maxclient < ms1.tab[i].nbclient)
            {

                maxclient=ms1.tab[i].nbclient;
                indicebestpos = j;

            } ms1=ms;
        }
        msr.tab[i].pos=msr.tab[i].pos+deplacement[indicebestpos];
    }

     for (i=0; i<ms.nbmarchand ; i++)
    {
        for(j=0; j<3 ; j++)
        {
            ms1.tab[i].pos=ms1.tab[i].pos+diffprix[j];
            traitevente(msr,1);
            if (maxclient < ms1.tab[i].nbclient)
            {

                maxclient=ms1.tab[i].nbclient;
                indicebestpos = j;

            } ms1=ms;
        }
        ms1.tab[i].pos=ms1.tab[i].pos+diffprix[indicebestpos];
    }





}


int main(int, char** )
{


    marchands ms;
    winInit("Glace",DIMW, DIMW/2);
    backgroundColor(255,255,255);

    bool stop=true;
    init(ms,5);

    while( !winHasFinished() )
    {
        winClear();
        traitevente(ms,0);
        drawmarchands(ms);
        majmarchands(ms);

        winDisplay();
    }


    winQuit();
    return 0;
}

