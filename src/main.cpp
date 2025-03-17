#include <iostream>
#include "windows.h"
#include <cstdio>
#include <cmath>
#include "graphics.h"

#define PI 3.141592653589793

using namespace std;

struct Pozitie { double x, y; };

double unghi;
double si, co;
bool buffer;
double i;

void fractal(Pozitie, Pozitie, int);
void fractal2(double, Pozitie, Pozitie, int);

int main()
{
    int driver, mod;
    initwindow(1920, 1080, "Fractal");

    Pozitie c, d, m;
    int l;

    m.x = getmaxx() / 2;
    m.y = getmaxy() / 2;

    l = 150;
    c.x = m.x + l / 2;
    c.y = m.y + l / 2 + 200;

    d.x = m.x - l / 2;
    d.y = m.y + l / 2 + 200;

    for (i = 0; i <= 180; i += 0.3)
    {
        setactivepage(buffer);
        setvisualpage(1 - buffer);
        cleardevice();
        unghi = i * PI / 180.0;
        si = sin(unghi); co = cos(unghi);
        fractal2(l, d, c, 8);
        //Sleep(25);
        
        buffer = 1 - buffer;
    }

    si = sin(unghi); co = cos(unghi);
    fractal2(l, d, c, 8);
    //fractal(d, c, 10);
    getch();
    return 0;
}

void fractal(Pozitie d, Pozitie c, int iter)
{
    if (iter > 0)
    {
        Pozitie a, b, e, mij;

        a.x = d.x + (c.y - d.y); a.y = d.y - (c.x - d.x);
        b.x = c.x + (c.y - d.y); b.y = c.y - (c.x - d.x);

        line(a.x, a.y, b.x, b.y);
        line(b.x, b.y, c.x, c.y);
        line(d.x, d.y, a.x, a.y);
        line(c.x, c.y, d.x, d.y);

        mij.x = (a.x + b.x) / 2.0; mij.y = (a.y + b.y) / 2.0;
        e.x = mij.x + (b.y - mij.y);
        e.y = mij.y - (b.x - mij.x);

        fractal(a, e, iter - 1);
        fractal(e, b, iter - 1);
    }
}

void fractal2(double l, Pozitie d, Pozitie c, int iter)
{
    if (iter > 0)
    {
        Pozitie a, b, e;
        Pozitie bp;
        double d1, d2, ab;

        a.x = d.x + (c.y - d.y); a.y = d.y - (c.x - d.x);
        b.x = c.x + (c.y - d.y); b.y = c.y - (c.x - d.x);

        line(a.x, a.y, b.x, b.y);
        line(b.x, b.y, c.x, c.y);
        line(d.x, d.y, a.x, a.y);
        line(c.x, c.y, d.x, d.y);

        bp.x = co * (b.x - a.x) + si * (b.y - a.y) + a.x;
        bp.y = -si * (b.x - a.x) + co * (b.y - a.y) + a.y;

        d1 = l; d2 = co * l;

        e.x = a.x - (d2 / d1) * (a.x - bp.x);
        e.y = a.y - (d2 / d1) * (a.y - bp.y);

        fractal2(d2, a, e, iter - 1);
        fractal2(si * l, e, b, iter - 1);
    }
}
