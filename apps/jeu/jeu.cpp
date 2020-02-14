#include <Grapic.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>


using namespace grapic;
using namespace std;
const int DIMW=1600;
const int V3=100;
const int NB=10;
const int NIVO=3;
const float VITESSE=0.2;

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

Complex rotate (Complex p, float cx, float cy, float theta)
{

    Complex c,rot;
    c = make_complex(cx, cy);
    rot = make_complex_exp(1,theta);
    return rot*(p-c)+c;
}

//////////////////////////////////////////////////////BEGIN STRUCT/////////////////////////////////////////////////////////////////////////////////////////////
struct rect
{
    Complex ori;
    Complex maxi;
    int resistance;




};

struct rond
{
    Complex centre;
    Complex Rond;


};

struct world
{

    rond tb [V3];
    rect tab [V3];
    Complex miss;
    Complex oriv;
    int SCORE;
    Image rect[V3];
    int vie;
    Image im;
    Image imss;
    Image ims;

};





//////////////////////////////////////////////////////////////////////I N I T/////////////////////////////////////////////////////////////////////////////////////
void init (world &w, int nb_rects, float &x, float &y)
{
    int i;
    for (i=0; i<NB; i++)
    {


        w.tab[i].ori.x =(i+i+1)*750/NB;
        w.tab[i].ori.y =(DIMW/2-30);
        w.tab[i].maxi.x=(i+i+2)*750/NB;
        w.tab[i].maxi.y=(DIMW/2);
        w.tab[i].resistance=NIVO;
        w.tb[i].centre=make_complex(((w.tab[i].ori.x + w.tab[i].maxi.x) /2),((w.tab[i].ori.y + w.tab[i].maxi.y)/2));
        w.tb[i].Rond=w.tb[i].centre + make_complex(50,0);
        w.rect[i]=image("data/invader/coeur.png", false,1,1);
        w.oriv.x=DIMW/2;
        w.miss.x=DIMW/2;

    }
    w.im=image("data/invader/paysage.jpg",false,1,1);
    w.ims=image("data/invader/test.jpg",false,1,1);
    w.imss=image("data/invader/Debut.jpg",false,1,1);
    w.vie=5;
    w.miss.y=-20;
    w.SCORE=0;


}

//////////////////////////////////////////////////////////////////////D R A W /////////////////////////////////////////////////////////////////////////////////////
void drawvaiss(world &w)
{
    color(255,0,0);
    rectangleFill( w.oriv.x,w.oriv.y, w.oriv.x+50,w.oriv.y+10);
    rectangleFill( w.oriv.x+22,w.oriv.y, w.oriv.x+28,w.oriv.y+30);
}

void drawmiss(world &w)
{


    rectangleFill( w.miss.x, w.miss.y, w.miss.x+6,w.miss.y+25);
    rectangleFill( w.miss.x+44, w.miss.y, w.miss.x+50, w.miss.y+25);


}

void draw(world &w)
{
    drawmiss(w);
    drawvaiss(w);
    int i,j;
    for (i=0; i<NB; i++ )

    {
        if (w.tab[i].resistance>0 )
        {

            j++;
            color(15*i*j,5*i,25*i);
//        rectangleFill((i+i+1)*750/NB,(DIMW/2-30)-m,(i+i+2)*750/NB,(DIMW/2)-m);
            rectangleFill(w.tab[i].ori.x,w.tab[i].ori.y, w.tab[i].maxi.x,w.tab[i].maxi.y);

            circleFill(w.tb[i].Rond.x,w.tb[i].Rond.y,8);

            color (255,255,255);
            circleFill (w.tb[i].centre.x,w.tb[i].centre.y,10);

        }

        for (j=0 ; j<5 ; j++)
        {
            if (w.vie>0)
            {
                image_draw(w.rect[j],(j+1)*100/5, DIMW/2-50,20,20);


            }

        }



    }
}
//////////////////////////////////////////////////////////////////////UPDATE/////////////////////////////////////////////////////////////////////////////////////
void update(world &w, float &x, float &y,float &m)
{
    int i,x1;
///////////////////////////////////////////////////////////////DEPLACEMENT TOUCHE///////////////////////////////////////////////////////////////////////////
    if (isKeyPressed(SDLK_RIGHT))
    {
        x=+2;
        w.oriv.x=w.oriv.x+x;
        if(w.miss.y<-15 && w.miss.y<DIMW/2-100 )
        {
            w.miss.x=w.oriv.x;
        }

        if ( w.oriv.x>DIMW-50)
        {
            w.oriv.x=DIMW-50;
            w.miss.x=w.oriv.x;
        }



    }
    if (isKeyPressed(SDLK_LEFT))
    {

        x= -2;
        w.oriv.x=w.oriv.x+x;
        if (w.miss.y<-15 && w.miss.y<DIMW/2-100 )
        {
            w.miss.x=w.oriv.x;
        }



        if (w.oriv.x<=0)

        {
            w.oriv.x = 0;

        }



    }
    if (isKeyPressed(SDLK_UP))
    {

        w.miss.y=w.miss.y+10;


    }

    if (w.miss.y>-15)
    {
        w.miss.y=w.miss.y+1;

        if ( w.miss.y>DIMW/2)
        {
            w.miss.y=-25;

        }
    }



//////////////////////////////////////////////////////////////DEPLACEMENT MUR//////////////////////////////////////////////////////////////////////////////////////////////

    for (i=0; i<NB; i++)
    {
        w.tab[i].ori.y=w.tab[i].ori.y-m;
        w.tab[i].maxi.y=w.tab[i].maxi.y-m;
        w.tb[i].centre.y=(w.tab[i].ori.y+w.tab[i].maxi.y)/2-m;


        if (w.tab[i].maxi.y>(DIMW/2-30))
        {
            m=VITESSE;

        }



        if ( w.tab[i].ori.y<0)
        {

            w.tab[i].maxi.y=DIMW/2;
            w.tab[i].ori.y =(DIMW/2-30);
            w.tb[i].centre.y=(w.tab[i].ori.y+w.tab[i].maxi.y)/2;
            w.tb[i].Rond.y= w.tab[i].ori.y+20;
            for (int j=0; j<2; j++)
            {
                w.vie=w.vie-j;

            }


        }

    }
    for (i=0; i<NB; i++ )

    {
        if (w.tab[i].resistance<0 )
        {
            w.tab[i].ori.y=(DIMW/2);
            w.tab[i].maxi.y=(DIMW/2)-30;
        }
    }


//////////////////////////////////////////////////COLLISION//////////////////////////////////////////////////////////////////////////

    for(i = 0; i<NB ; i++)
    {

        Complex rondavant;

        rondavant=w.tb[i].centre-w.tb[i].Rond;
        w.tb[i].Rond=w.tb[i].centre+ rondavant;
        w.tb[i].Rond= rotate ( w.tb[i].Rond,w.tb[i].centre.x,w.tb[i].centre.y,0.01);


        if((w.miss.x>w.tab[i].ori.x || w.miss.x +44 >w.tab[i].ori.x ) && (w.miss.x+6 <w.tab[i].maxi.x || w.miss.x +50 <w.tab[i].maxi.x ) &&  w.miss.y+25 > w.tab[i].ori.y && w.miss.y+25<DIMW/2-30)
        {


            w.SCORE=w.SCORE+5;
            w.miss.y=-25;


            w.tab[i].resistance= w.tab[i].resistance-1;

            w.tab[i].maxi.y=DIMW/2;
            w.tab[i].ori.y =(DIMW/2-30);
            w.tb[i].centre.y=(w.tab[i].ori.y+w.tab[i].maxi.y)/2;

            w.tb[i].Rond.y=w.tab[i].ori.y+20;





        }
//        if ( w.tb[i].Rond.y < w.miss.y &&  w.tb[i].Rond.y > w.miss.y-10 && w.tb[i].Rond.x < w.miss.x )
//        {
//            w.SCORE=w.SCORE-1;
//        }
    }
/////////////////////////////////////////////////////SCORE/////////////////////////////////////////////////////////////////////////////////////////////////
    color(255,0,0);
    fontSize(20);
    print(DIMW-150,DIMW/2-50,"score:");
    print(DIMW-90,DIMW/2-50,w.SCORE);

    for (i=0; i<NB; i++)
    {


        if ( w.tab[0].resistance<0 && w.tab[NB-1].resistance<0 && w.tab[NB-1*i].resistance<0 )
        {

            image_draw(w.im,0,0,DIMW,DIMW/2);
            color(0,0,0);
            fontSize(140);
            print(DIMW/2-100,DIMW/4,"WIN");
            print(DIMW/2-150,DIMW/4-150,"SCORE :");
            print(DIMW/2-100,DIMW/4-300,w.SCORE);


        }
    }

}

void settings()
{
    color(0,0,0);
            fontSize(55);
            print(50,DIMW/3,"TIRER:");
            print(50,DIMW/3-50,"FLECHE HAUT");
            print(50,DIMW/3-200,"DEPLACEMENT:");
            print(50,DIMW/3-250,"FLECHE DROITE / GAUCHE");
             print(DIMW/2+50,DIMW/3,"JOUER:");
            print(DIMW/2+50,DIMW/3-50,"F1");
            print(DIMW/2+50,DIMW/3-200,"QUITTER:");
            print(DIMW/2+50,DIMW/3-250,"F3");


}


/////////////////////////////////////////////////////MAIN///////////////////////////////////////////////////////////////////////////////////////////////////

int main(int, char** )
{
    float x=5;
    float y=0;
    float m=0;

    world dat;

    winInit("Invaders",DIMW, DIMW/2);


    bool stop=true;
    setKeyRepeatMode(true);
    int vrai=0;
    init(dat,5,x,y);




    while( !winHasFinished() )
    {
        if (isKeyPressed(SDLK_F1))
        {
            vrai=1;
        }
        if (isKeyPressed(SDLK_F2))
        {
            vrai=2;
        }
        if (isKeyPressed(SDLK_F3))
        {
            vrai=3;
        }
        winClear();
     image_draw(dat.imss,0,0,DIMW,DIMW/2);
        if (vrai==1)
        {
 image_draw(dat.ims,0,0,DIMW,DIMW/2);
            draw(dat);
            update(dat,x,y,m);

        }
        if (vrai==2)
        {
            image_draw(dat.im,0,0,DIMW,DIMW/2);
            settings();
        }
        if (vrai==3)
        {
            winQuit();
        }
        winDisplay();
    }

    winQuit();
    return 0;
}

