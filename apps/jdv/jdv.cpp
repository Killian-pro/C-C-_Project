#include <Grapic.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>

using namespace grapic;
using namespace std;
const int DWH=800;
const int DWL=1500;
const int NMAX=100;

struct jeudelavie
{
    int grille[NMAX][NMAX];
    int dx,dy;
    int nbvivants;
    Image im;
    Image ims;
    int nbmorts;
};
void init (struct jeudelavie &jdvl,int nl,int nc)
{
    int i,j;
    jdvl.dx=nl;
    jdvl.dy=nc;
    jdvl.im =  image("data/licorne/licorne.png");
    jdvl.ims = image("data/bird/bird2.png");
    for(i=0; i<jdvl.dx+1; i++)
        for (j=0; j<jdvl.dy+1; j++)
        {
            jdvl.grille[i][j]=0;
        }
    jdvl.nbvivants=0;
    jdvl.nbmorts=nc+nl-jdvl.nbvivants;


}
void etat_init(struct jeudelavie &jdvl, int nbvivants)
{
    int i,j,k;
    jdvl.nbvivants = nbvivants;
    jdvl.nbmorts=(jdvl.dx+jdvl.dy)-nbvivants;
    srand(time(NULL));
    for (k=0; k<nbvivants; k++)
    {
        do
        {
            i=1+rand()%jdvl.dx;
            j=1+rand()%jdvl.dy;
        }
        while (jdvl.grille[i][j]==1);
        jdvl.grille[i][j]=1;
    }
}

int etat_suivant(struct jeudelavie &jvdl)
{
    struct jeudelavie jdvl2;
    int i,j,a,b,nb;
    int nbchangements=0;

    jdvl2=jvdl;

    for (i=1 ; i<=jdvl2.dx; i++)
    {

        for (j=1 ; j<=jdvl2.dy; j++)
        {
            nb=0;

            for (a=i-1 ; a<=i+1; a++)
            {

                for (b=j-1 ; b<=j+1; b++)
                {
                    nb=nb+jdvl2.grille[a][b];

                }
            }
            nb=nb-jdvl2.grille[i][j];

            if (jdvl2.grille[i][j]==0 && nb==3)
            {
                jvdl.grille[i][j]=1;
                jvdl.nbmorts--;
                jvdl.nbvivants++;
                nbchangements++;


            }

            if (jdvl2.grille[i][j]==1 && (nb>=4 ||nb <= 1))
            {
                jvdl.grille[i][j]=0;
                jvdl.nbmorts++;
                jvdl.nbvivants--;
                nbchangements++;

            }
        }
    }
    return nbchangements;

}


void draw(jeudelavie &jdvl)

{
    int i,j;

    grid(0, 0,DWL-2,DWH-2, jdvl.dx, jdvl.dy);

    for (i=1; i<jdvl.dx+1; i++)
    {
        for (j=1; j<jdvl.dy+1; j++)
        {
            if (jdvl.grille[i][j] == 0 )
            {
                image_draw (jdvl.im, (i-1)*DWL/jdvl.dx,(j-1)*DWH/jdvl.dy,DWL/jdvl.dx,DWH/jdvl.dy ) ;
            }
            if (jdvl.grille[i][j] == 1 )
            {
                image_draw (jdvl.ims, (i-1)*DWL/jdvl.dx,(j-1)*DWH/jdvl.dy,2*DWL/jdvl.dx, 2*DWH/jdvl.dy ) ;
            }

        }



    }

}

int main(int, char** )
{
    int nbc;


    jeudelavie j;

    winInit("jvd",DWL, DWH);
    backgroundColor( 200, 200,200);


    init(j,5,5);

    etat_init(j,5);

    while( !winHasFinished() )
    {
        winClear();
        draw(j);

        nbc=etat_suivant(j);
        cout<<nbc<<endl;
        cout<<j.nbvivants<<endl;
        winDisplay();
        delay(1000);

    }



    winQuit();
    return 0;
}

