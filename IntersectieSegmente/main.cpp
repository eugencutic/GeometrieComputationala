#include <iostream>
#include <math.h>
#include <algorithm>

using namespace std;

#include "punct.h"

double determinant(double d11, double d12, double d21, double d22)
{
    return (d11 * d22) - (d21 * d12);
}

void determinaIntersectie(punct a, punct b, punct c, punct d)
{
    double det = determinant(b.x - a.x, c.x - d.x, b.y - a.y, c.y - d.y);
    double p;

    punct m;

    if(det != 0)
    {
        p = determinant(c.x - a.x, c.x - d.x, c.y - a.y, c.y - d.y) / det;
    }
    if(det != 0 && p >= 0 && p <= 1)
    {
        m.x = (1-p) * a.x + p * b.x;
        m.y = (1-p) * a.y + p * b.y;
        cout << m.x << ", " << m.y << endl;
        return;
    }

    if( punct::determinaColiniaritate(a, b, c) && punct::determinaColiniaritate(b, c , d) )
    {

        punct min1 = punct::minPct(a, b);
        punct min2 = punct::minPct(c, d);
        punct max1 = punct::maxPct(a, b);
        punct max2 = punct::maxPct(c, d);

        punct temp = punct::minPct(max1, max2);

        if (min1 == min2 && max1 == max2)
        {
            cout << "Segmentele sunt identice\n";
        }
        if (max2 < min1)
        {
            cout << "Intersectia este MULTIMEA VIDA\n";
            return;
        }
        if (max2 == min1)
        {
            cout << "Segmentele se intersecteaza in punctul (" << min1.x << "," << min1.y << ")\n";
            return;
        }
        if (min2 < min1)
        {
            cout <<"Segmentele se intersectaza in segmentul: (" << min1.x << "," << min1.y << ") , (" << temp.x << "," << temp.y << ")\n";
            return;
        }
        if (min1 == min2 && min2 == temp)
        {
            cout << "Segmentele se intersecteaza in punctul (" << min1.x << "," << min1.y << ")\n";
            return;
        }

        if (min2 < temp)
        {
            cout << "Segmentele se intersectaza in segmentul: (" << min2.x << "," << min2.y << ") , (" << temp.x << "," << temp.y << ")\n";
            return;
        }

        if (min2 == temp)
        {
            cout << "Segmentele se intersecteaza in punctul (" << min2.x << "," << min2.y << ")\n";
            return;
        }
        cout << "Intersectia este MULTIMEA VIDA\n";
        return;
    }
    cout << "Segmentele nu se intersecteaza\n";
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



    determinaIntersectie(p[0], p[1], p[2], p[3]);


    return 0;
}
