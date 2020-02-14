#include <Grapic.h>
#include <math.h>
using namespace grapic;



const int DIMW=800;


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
    c.x = lambda*b.x;
    c.y = lambda*b.y;
    return c;
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

Complex rotate (Complex p, float cx, float cy, float theta)
{

    Complex c,rot;
    c = make_complex(cx, cy);
    rot = make_complex_exp(1,theta);
    return rot*(p-c)+c;
}

double interpolation (int a , int b ,float i)
{
    return (1-i)*a + i * b ;
}

struct Color
{
    int r;
    int g;
    int b;
};


void dessin ()
{
    int i;
//    xx.x1=make_complex(10,10);
//    xx.y1=make_complex(10,10);
//    xx.x2=make_complex(500,500);
//    xx.y2=make_complex(500 ,500);

    Complex p = make_complex(10, 24);
    Complex q = make_complex(348, 567);
    Color c1 = {0, 0, 255};
    Color c2 = {255, 255, 0};

    int step = 10;

    for(i = 0;i<step;i++)
    {
        float t1 = (i  )/(float)step;
        float t2 = (i+1)/(float)step;
        float x1 = interpolation(p.x, q.x, t1);
        float x2 = interpolation(p.x, q.x, t2);
        float y1 = interpolation(p.y, q.y, t1);
        float y2 = interpolation(p.y, q.y, t2);

        int r = interpolation(c1.r, c2.r, t1);
        int g = interpolation(c1.g, c2.g, t1);
        int b = interpolation(c1.b, c2.b, t1);
        color(r, g, b);
//        line(x1+i, y1, x2, y2+i);
        line(x1, y1, x2, y2);
    }


}



int main (int, char ** )
{
    winInit("polygone lineaire", DIMW+200, DIMW);

   while (!winHasFinished())
    {   winClear();
        backgroundColor( 255,255,255 );
        dessin();
        winDisplay();

    }
    winQuit();
    return 0;
}

