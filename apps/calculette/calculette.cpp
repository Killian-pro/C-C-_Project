#include <Grapic.h>
#include <math.h>
#include <iostream>
#include <string.h>
using namespace std ;
using namespace grapic;

const int VAR=255;
const int MAX=50;
bool stop=false;

struct Data
{
    int x=0;
    int y=0;
    int m=0;
    char w[VAR];
    char o;

};

//void update(Data &d)
//{
//  const float vitesse = 20.f;
//float temps = elapsedTime();
//d.x =temps + 1;


//}
void choisir(Data &d)
{
    cout<<endl<<"veuillez choisir deux nombres , ainsi qu'un signe"<<endl;
    cin >> d.x>> d.o>> d.y;
    switch (d.o)
    {
    case '+':
        cout<< (d.m = d.x+d.y)<<endl  ;
        break;
    case '-':
        cout<< (d.m = d.x-d.y)<<endl  ;
        break;
    case '*':
        cout<< (d.m = d.x*d.y)<<endl  ;
        break;
    case '/':
        if (d.m==0)
            cout<<"error";
        else cout<< (d.m = d.x/d.y)<<endl ;
        break;
    }
}
void calcul (Data &d)
{
    if (isMousePressed(SDL_BUTTON_LEFT))
    {
        int x,y;
        mousePos(x, y);
        if (x<590 && x>490 && y>200 && y<290)
        {
            d.m = d.x+d.y;
            d.w[0] = '+';
        }
        if (x<590 && x>490 && y>120 && y<200)
        {
            d.m = d.x-d.y;
            d.w[1]= '-';
        }

        if (x<590 && x>490 && y>50 && y<120)
        {
            d.m = d.x*d.y;
            d.w[2] = '*';
        }
    }

    if(isKeyPressed(SDLK_LSHIFT))
    {

        choisir(d);
    }
}
void calc (Data &d)
{


    if (isKeyPressed(SDLK_F1))
    {
        d.x++;
    }

    if (isKeyPressed(SDLK_F2))
    {

        d.y++;
    }

}


void init(Data &d)
{


    color(255,255,255,255); //blanc
    rectangleFill(155,5,600,450);


    color (0,0,0,255); //noir
    rectangle(195,350,550,440);

    grid( 590, 290, 200, 30, 4, 3); //Xmax Ymax Xmin Ymin

    print( 250, 250, "1"); // Y X ?
    print( 350, 250, "2"); // Y X ?
    print( 450, 250, "3"); // Y X ?
    print( 550, 250, "+"); // Y X ?

    print( 250, 150, "4"); // Y X ?
    print( 350, 150, "5"); // Y X ?
    print( 450, 150, "6"); // Y X ?
    print( 550, 150, "-"); // Y X ?

    print( 250, 50, "7"); // Y X ?
    print( 350, 50, "8"); // Y X ?
    print( 450, 50, "9"); // Y X ?
    print( 550, 50, "*"); // Y X ?

    print( 20, 40, "shiftleft");
    print( 20, 20, "for try again");

}




void draw(Data &d)
{

    init(d);
    calcul(d);
    int n,z,e;
    // char k[VAR];
    n=d.x;
    z=d.y;
    e=d.m;
    // k[0]=d.w[0];
    print (250, 400, n);
    // print (300,400 ,k[0]);
    print (350,400,z);
    print (450,400,"=");
    print (500,400,e);


}
int main(int, char** )
{

    Data dat;
    winInit("calculette", 700, 500);
    backgroundColor( 200, 200,200);
    choisir(dat);
    while( !winHasFinished() )
    {
        winClear();
        draw(dat);
        winDisplay();
        //update(dat);
        calc(dat);
    }

    winQuit();
    return 0;
}

