#include <Grapic.h>
#include <math.h>
using namespace grapic;



const int DIMW=500;


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

Complex rotate (Complex p, float cx, float cy, float theta)
{

    Complex c,rot;
    c = make_complex(cx, cy);
    rot = make_complex_exp(1,theta);
    return rot*(p-c)+c;
}

struct solarsystem
{
    Complex terre;
    Complex lune;
    Complex mars;
    Complex soleil;
    Complex mercure;
    Complex venus;
    Complex saturne;
    Complex uranus;
    Complex neptune;
    Complex jupiter;
    Image im;
};

void init (solarsystem & ss)
{
    ss.im =image("data/systemsolaire/systemsolaire.jpg");
    ss.soleil = make_complex(DIMW , DIMW/2);
    ss.mercure = ss.soleil+make_complex(30 ,0);
    ss.venus =  ss.soleil+make_complex(50 ,0);
    ss.terre =  ss.soleil+make_complex(80 , 0);
    ss.lune =  ss.terre+make_complex( 30 ,0 );
    ss.mars =  ss.soleil+make_complex(150, 0);
    ss.jupiter=ss.soleil+make_complex(200, 0);
    ss.saturne =ss.soleil+make_complex(250, 0);
    ss.uranus =ss.soleil+make_complex(300, 0);
    ss.neptune=ss.soleil+make_complex(360, 0);



}

void draw(solarsystem ss)
{
    image_draw(ss.im, -2,-2);
    color (255,255,0);
    circleFill(ss.soleil.x, ss.soleil.y ,15);
     color (255,0,0);
    circleFill(ss.mars.x, ss.mars.y ,10);
     color (0,0,255);
    circleFill(ss.terre.x, ss.terre.y ,7);
     color (200,200,200);
    circleFill(ss.lune.x, ss.lune.y ,2);
    color (0,255,255);
    circleFill(ss.mercure.x, ss.mercure.y ,3);
     color (150,0,255);
     circleFill(ss.venus.x, ss.venus.y ,5);
     color (150,25,255);
     circleFill(ss.saturne.x, ss.saturne.y ,15);
     color (150,200,255);
      line(ss.saturne.x+20,ss.saturne.y+5,ss.saturne.x-20,ss.saturne.y);
     color (180,25,255);
     circleFill(ss.uranus.x, ss.uranus.y ,5);
     color (150,55,55);
     circleFill(ss.neptune.x, ss.neptune.y ,5);
      color (50,0,0);
    circleFill(ss.jupiter.x, ss.jupiter.y ,15);



}

void update (solarsystem &ss)
{
    Complex luneavant ;
    ss.mars=rotate(ss.mars,ss.soleil.x,ss.soleil.y,0.001);
    luneavant=ss.lune-ss.terre;
    ss.terre=rotate(ss.terre,ss.soleil.x,ss.soleil.y,0.003);
     ss.lune=ss.terre+luneavant;
    ss.lune=rotate(ss.lune,ss.terre.x,ss.terre.y,0.009);
    ss.mercure=rotate(ss.mercure,ss.soleil.x,ss.soleil.y,0.002);
    ss.venus=rotate(ss.venus,ss.soleil.x,ss.soleil.y,0.005);
    ss.jupiter=rotate(ss.jupiter,ss.soleil.x,ss.soleil.y,0.0004);
    ss.saturne=rotate(ss.saturne,ss.soleil.x,ss.soleil.y,0.0003);
    ss.uranus=rotate(ss.uranus,ss.soleil.x,ss.soleil.y,0.0005);
    ss.neptune=rotate(ss.neptune,ss.soleil.x,ss.soleil.y,0.0007);
}
int main (int ,char **)
{
    bool stop=false;
    solarsystem sola;
    winInit("sola", 1000, 800);
    init(sola);
    while (!stop)
    {
        backgroundColor( 0,0,0 );
        winClear();
        draw(sola);
        update(sola);
        stop = winDisplay();
    }
    winQuit();
    return 0;
}

