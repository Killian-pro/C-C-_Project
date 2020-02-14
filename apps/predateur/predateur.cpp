#include <Grapic.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>

using namespace grapic;
using namespace std;
const int DWH=800;
const int DWL=1600;
const int NMAX=100;

const int DVP=5; //proie
const int DVPR=5; //predateur


const double B=0.001;
const double A=0.045;
const double D=0.0002;
const double L=0.025;
const int N=-1;

struct Ecosysteme
{
    double nbp;
    double nbpr;
    double Alpha ;
     double Delta ;
      double Lambda ;
       double Beta ;
       int i;

};

 void evolution_eco(Ecosysteme &e)
 {
      e.i++;

     double nbpt =e.nbp;
     double nbptr =e.nbpr;
     e.nbp= nbpt*(e.Alpha+1)-e.Beta*nbpt*nbptr ;
      e.nbpr= -nbptr*(e.Delta-1)+e.Lambda*nbpt*nbptr;



 }

 void init (Ecosysteme &e)
 {
   e.Alpha=A;
     e.Beta=B;
     e.Delta=D;
     e.Lambda=L;
     e.nbpr=40;
     e.nbp=120;
 }

 void draw (Plot &p, Ecosysteme &e)
{

    color(0,0,0);
      plot_add(p, e.i,e.nbp,0);
      plot_add(p, e.i,e.nbpr,1);
//         rectangleFill(5,5,e.nbpr,e.nbp);
      plot_draw(p, 5 ,5 ,DWL ,DWH,true);



}



int main(int, char** )
{

    winInit("predateur",DWL, DWH);
    Plot p;
    Ecosysteme e;
    plot_setSize(p , N);
    init(e);

    while( !winHasFinished() )
    {
 winClear();

        evolution_eco(e);
        draw(p,e);
        delay(1000);
        winDisplay();
    }

    winQuit();
    return 0;
}
