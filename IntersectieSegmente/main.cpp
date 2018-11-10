#include <iostream>
#include <math.h>

using namespace std;

#include "punct.h"

double determinant(double d11, double d12, double d21, double d22)
{
    return (d11 * d22) - (d21 * d12);
}

void determinaIntersectie(punct a, punct b, punct c, punct d)
{
    double det = determinant(b.x - a.x, c.x - d.x, b.y - a.y, c.y - d.y);

    punct m;

    if(det != 0)
    {
        double p, q;

        p = determinant(c.x - a.x, c.x - d.x, c.y - a.y, c.y - d.y) / det;
        //q = determinant(b.x - a.x, c.x - a.x, b.y - a.y, c.y - a.y) / det;

        m.x = (1-p) * a.x + p * b.x;
        m.y = (1-p) * a.y + p * b.y;
        cout << m.x << ", " << m.y << endl;
        return;
    }

    if( punct::determinaColiniaritate(a, b, c) )
    {

        cout << "Punctele sunt coliniare." << endl;

        double rapACB = punct::determinaRaport(a, c, b);
        double rapADB = punct::determinaRaport(a, d, b);


        cout<<rapACB<<" "<<rapADB;
        if(rapACB > 0 && rapACB < 1)
        {

            if(rapADB < 0 || rapADB > 1)
            {
                cout << "Intersectia este segmentul 2." << endl;
            }
            else
            {
                cout << "Intersectia este segmentul de la (" << c.x << ", " << c.y << ") la (" << b.x << ", " << b.y << ")." << endl;
            }
        }
        else
        {
            if(rapADB > 0 && rapADB < 1)
            {
                cout << "Intersectia este segmentul de la (" << a.x << ", " << a.y << ") la (" << d.x << ", " << d.y << ")." << endl;
            }
            else
            {
                cout << "Segmentele nu se intersecteaza.";
            }
        }
        return;
    }
    cout << "Segmentele nu se intersecteaza";
}

int main()
{
    int n = 4;
    double x, y;
    punct p[1000];
    for(int i = 0; i < n; i++)
    {
        cout << "Introduceti (x, y) pentru A" << i+1 << ":\n";

        cin >> p[i].x;
        cin >> p[i].y;
        p[i].z = 0;
        p[i].indice = i+1;
    }
    double testRap = 1/3;


    determinaIntersectie(p[0], p[1], p[2], p[3]);


    return 0;
}
