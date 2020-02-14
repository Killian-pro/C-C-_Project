#include <Grapic.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>


using namespace grapic;
using namespace std;
const int DIMW=1600;
int continu=0;
int getperso=0;
int jeu=3;

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

struct rect
{
    Complex ori;
    Complex maxi;

};


struct World
{
    Image im;
    Image im1;
    Image imp;
    Image imp1;
    Image imp2;
    Image imp3;

    rect pince;
    int x,y,a,b,e,f,g,h;
    int score;
    int x1,y1;
    int z;
    int chance;
    float temps;

};


void init(World& d)
{
    srand(time(NULL));

    d.im=image("data/jeulaura/jeulaura.png");
    d.im1=image("data/jeulaura/blanc.png");

    d.imp=image("data/jeulaura/perso.png");
    d.imp1=image("data/jeulaura/perso1.png");
    d.imp2=image("data/jeulaura/perso2.png");
    d.imp3=image("data/jeulaura/perso3.png");

/// //////PINCE///////
    color(0,0,0);
    d.pince.maxi.x=820;
    d.pince.maxi.y=1600;
    d.pince.ori.x=800;
    d.pince.ori.y=750;
///PERSO /////////////////////:
    d.x=rand()%1200+DIMW/6;
    d.y=200;
    d.a=rand()%1200+DIMW/6;
    d.b=200;
    d.e=rand()%1200+DIMW/6;
    d.f=200;
    d.g=rand()%1200+DIMW/6;
    d.h=200;
/// ///////////////////////
    d.score=0;
    d.x1=0;
    d.y1=0;
    d.z=0;
    d.chance=0;
    float temps = 0 ;
}




void draw(World& d)

{
    image_draw(d.im,0,0,DIMW,DIMW/2);
    color (255,0,0);
    rectangleFill(0,0,DIMW,DIMW/8);
/// ////////CAISSE/////////
    color (0,0,0);
    rectangleFill(20,20,180,180);

/// ///JOYSTICK/////
    color(0,0,255);
    rectangleFill(800,20,980,180);
    color(0,0,0);
    circleFill(890,90,50);
    color(255,105,180);
    circleFill(890+d.x1,90+d.y1,50);

    /// ///BOUTON///
    color(0,0,0);
    circleFill(1390,90,60);
    color(0,255,255);
    circleFill(1390,90,50+d.z);
/// ///RECIPIENT/////
    color(0,0,0);
    rectangle(0,DIMW/8,280,DIMW/4);
    color (100,100,100);
    rectangleFill(5,DIMW/8+5,275,DIMW/4-5);

    ///PINCE
    int x=30;
    rectangleFill(d.pince.ori.x,d.pince.ori.y,d.pince.maxi.x,d.pince.maxi.y);
    rectangleFill(d.pince.ori.x-50,d.pince.ori.y-10,d.pince.ori.x+70,d.pince.ori.y);
    rectangleFill(d.pince.ori.x-50,d.pince.ori.y-10,d.pince.ori.x-40,d.pince.ori.y-50);
    rectangleFill(d.pince.ori.x+60,d.pince.ori.y-10,d.pince.ori.x+70,d.pince.ori.y-50);
    ///PINCE BOUGE
    rectangleFill(d.pince.ori.x+60-x,d.pince.ori.y-40,d.pince.ori.x+70,d.pince.ori.y-50);
    rectangleFill(d.pince.ori.x-40+x,d.pince.ori.y-40,d.pince.ori.x-40,d.pince.ori.y-50);



///perso///
    if (d.x>1600)
    {
        d.x=1550;
    }
    if (d.x<0)
    {
        d.x=10;
    }
    if (d.a>1600)
    {
        d.a=1550;
    }
    if (d.a<0)
    {
        d.a=10;
    }
    if (d.e>1600)
    {
        d.e=1550;
    }
    if (d.e<0)
    {
        d.e=10;
    }
    if (d.g>1600)
    {
        d.g=1550;
    }
    if (d.g<0)
    {
        d.g=10;
    }
///////
    if (d.y>700)
    {
        d.y=650;
    }
    if (d.y<DIMW/8)
    {
        d.y=200;
    }
    if (d.b>700)
    {
        d.b=650;
    }
    if (d.b<DIMW/8)
    {
        d.b=200;
    }
    if (d.f>700)
    {
        d.f=650;
    }
    if (d.f<DIMW/8)
    {
        d.f=200;
    }
    if (d.h>700)
    {
        d.h=650;
    }
    if (d.h<DIMW/8)
    {
        d.h=200;
    }

    image_draw(d.imp,d.x,d.y,150,150);
    image_draw(d.imp1,d.a,d.b,150,150);
    image_draw(d.imp2,d.e,d.f,150,150);
    image_draw(d.imp3,d.g,d.h,150,150);


///SCORE///
    color(255,0,0);
    fontSize(20);
    print(50,100,"score:");
    print(110,100,d.score);
    print(80,50,d.chance);
///temps//
float temps=180-d.temps;
 print(50,150,"time:");
 print(100,150,temps);



}
void update(World &d)
{
d.temps=elapsedTime();

    if (continu==1)
    {

        d.pince.ori.y++;

        if(d.pince.ori.y>DIMW/2-50)
        {
            d.pince.ori.y=DIMW/2-50;
            d.pince.ori.x--;
            d.pince.maxi.x--;
            if(d.pince.ori.x<10)
            {
                d.pince.ori.x=0;
                d.pince.maxi.x=50;

            }

            if(d.pince.ori.x==50)
                continu=2;

        }


    }
    if (continu==3)
    {
        d.pince.ori.y--;
        if (d.pince.ori.y<DIMW/8+50)
        {
            d.pince.ori.y=DIMW/8+50;
            continu=1;

        }

    }

    if (getperso==1 & d.y>200 && d.x<DIMW/6 && continu==2)
    {

        d.y--;

    }
    if (getperso==2 && d.b>200 && d.a<DIMW/6 && continu==2)
    {


        d.b--;

    }
    if (getperso==3 && d.f>200 && d.e<DIMW/6 && continu==2)
    {
        d.f--;

    }
    if (getperso==4 && d.h>200 && d.g<DIMW/6 && continu ==2)
    {
        d.h--;
    }
    if (isKeyPressed(SDLK_LEFT))
    {
        d.pince.ori.x=d.pince.ori.x-1;
        d.pince.maxi.x=d.pince.maxi.x-1;
        d.x1=-20;
        if(d.pince.ori.x<0)
        {
            d.pince.ori.x=0;
            d.pince.maxi.x=20;
        }


    }
    if (isKeyPressed(SDLK_RIGHT))
    {
        d.x1=20;
        d.pince.ori.x=d.pince.ori.x+1;
        d.pince.maxi.x=d.pince.maxi.x+1;
        if(d.pince.ori.x>DIMW)
        {
            d.pince.ori.x=DIMW;
            d.pince.maxi.x=DIMW+20;

        }


    }

    if (isKeyPressed(SDLK_SPACE))
    {
        d.z=-5;
        continu=3;



    }
    else
    {
        d.z=0;
    }


    if(d.x-5<d.pince.ori.x-50 && d.x+155>d.pince.ori.x+70 && d.y-5<d.pince.ori.y-100 && d.y+155>d.pince.ori.y && continu==1 && (getperso==0 || getperso==1))
    {
        d.x=d.pince.ori.x-70;
        d.y=d.pince.ori.y-140;
        getperso=1;
    }
    if(d.x-20>-100 && d.x<280 && d.y>DIMW/8-50 && d.y+140<DIMW/4)
    {
        d.chance=rand()%2+1;
        if (d.chance==2)
        {
            d.score=d.score+10;
        }
        d.y=200;
        d.x=rand()%1200+DIMW/6;
        getperso=0;


    }

    if(d.a-5<d.pince.ori.x-50 && d.a+155>d.pince.ori.x+70 && d.b-5<d.pince.ori.y-100 && d.b+155>d.pince.ori.y && continu==1 && (getperso==0 || getperso==2))
    {
        d.a=d.pince.ori.x-70;
        d.b=d.pince.ori.y-140;
        getperso=2;

    }
    if(d.a-20>-100 && d.a<280 && d.b>DIMW/8-50 && d.b+140<DIMW/4)
    {
        d.chance=rand()%4+1;
        if (d.chance==2)
        {
            d.score=d.score+20;
        }
        d.a=rand()%1200+DIMW/6;
        d.b=200;
        getperso=0;

    }

    if(d.e-5<d.pince.ori.x-50 && d.e+155>d.pince.ori.x+70 && d.f-5<d.pince.ori.y-100 && d.f+155>d.pince.ori.y && continu==1 && (getperso==0 || getperso==3))
    {
        d.e=d.pince.ori.x-70;
        d.f=d.pince.ori.y-140;
        getperso=3;
    }
    if(d.e-20>-100 && d.e<280 && d.f>DIMW/8-50 && d.f+140<DIMW/4)
    {

        d.e=rand()%1200+DIMW/6;
        d.f=200;
        getperso=0;

    }

    if(d.g-5<d.pince.ori.x-50 && d.g+155>d.pince.ori.x+70 && d.h-5<d.pince.ori.y-100 && d.h+155>d.pince.ori.y && continu==1 && (getperso==0 || getperso==4) )
    {
        d.g=d.pince.ori.x-70;
        d.h=d.pince.ori.y-140;
        getperso=4;
    }
    if(d.g-20>-100 && d.g<280 && d.h>DIMW/8-50 && d.h+140<DIMW/4)
    {
        d.chance=rand()%8+1;
        if (d.chance==2)
        {
            d.score=d.score+200;
        }
        d.g=rand()%1200+DIMW/6;
        d.h=200;
        getperso=0;

    }


        if (d.temps>181)
        {

        jeu=1;
            }
}
void fin(World &w)
{
     fontSize(100);
     color(255,0,0);
     print(DIMW/2-200,DIMW/2-200,"Jeu fini");
print(DIMW/2-200,DIMW/2-300,"score:");
 print(DIMW/2-200,DIMW/2-400,w.score);
  color(0,0,0);
  print(50,150,"rejouer:");
  print(450,150,"appuyer sur F1");
  if (isKeyPressed(SDLK_F1))
  {
      jeu=0;
  }

}
void debut()
{
     fontSize(100);
     color(0,0,0);
     print(50,150,"but du jeu:");
print(50,150,"commencer");

      jeu=0;


}



int main(int, char** )
{

    World dat;

    winInit("LABOOM",DIMW,DIMW/2);

    init(dat);

    bool stop=true;
    setKeyRepeatMode(true);


    while( !winHasFinished() )
    {
        winClear();
        if (jeu==3)
        {
        image_draw(dat.im1,0,0,DIMW,DIMW/2);
       debut();
        }
        if (jeu==0)
        {
        draw(dat);
        update(dat);
        }
        if (jeu==1)
        {
        image_draw(dat.im1,0,0,DIMW,DIMW/2);
        fin(dat);
        }

        winDisplay();
    }


    winQuit();
    return 0;
}

