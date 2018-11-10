#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>

using namespace std;

#include "punct.h"

//i am not proud of this
punct origine;

void interschimba(punct &p1, punct &p2)
{
    punct temp = p1;
    p1 = p2;
    p2 = temp;
}

int cmpPolar(const void* p1, const void* p2)
{
    punct *a = (punct*)p1;
    punct *b = (punct*)p2;


    int orientare = punct::testOrientare(origine, *a, *b);
    if(orientare == 0)
    {
        return (origine.dist(*a) >= origine.dist(*b)) ? -1 : 1;
    }

    if(orientare == 1)
        return -1;
    return 1;
}

vector<punct> AcoperireConvexa(punct p[], int n)
{
    int ymin = p[0].y, minim = 0;
    for (int i = 1; i < n; i++)
    {
        int y = p[i].y;

        if ((y < ymin) || (ymin == y && p[i].x < p[minim].x))
            ymin = p[i].y, minim = i;
    }

    interschimba(p[0], p[minim]);

    origine = p[0];
    qsort(p+1, n-1, sizeof(punct), cmpPolar);

    int m = 1;
    for (int i=1; i<n; i++)
    {
        while (i < n-1 && punct::testOrientare(origine, p[i], p[i+1]) == 0)
            i++;
        p[m] = p[i];
        m++;
    }

    vector<punct> frontiera;
    frontiera.push_back(p[0]);
    frontiera.push_back(p[1]);

    for(int i = 2; i < m; i++)
    {
        while(frontiera.size() > 2 &&
                punct::testOrientare(frontiera[frontiera.size() - 2], frontiera.back(), p[i]) != 1)
            frontiera.pop_back();
        frontiera.push_back(p[i]);
    }
    return frontiera;
}

int cmpYX(const void* p1, const void* p2)
{
    punct *a = (punct*)p1;
    punct *b = (punct*)p2;

    if(a->y == b->y)
        return (a->x < b->x) ? -1 : 1;

    return (a->y < b->y) ? -1 : 1;

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
        p[i].indice = i+1;
    }

    if(punct::determinaColiniaritate(p[0], p[1], p[2]) && punct::determinaColiniaritate(p[1], p[2], p[3]))
    {
        qsort(p, n, sizeof(punct), cmpYX);
        cout << "I = { A" << p[0].indice << ", A" << p[3].indice << " }" <<endl;
        cout << "J = { A" << p[1].indice << ", A" << p[2].indice << " }" <<endl;
        return 0;
    }

    vector<punct> frontiera = AcoperireConvexa(p, n);

    if(frontiera.size() == 3)
    {
        int indicePunctInterior = 1^2^3^4;

        cout << "I = { ";
        for(int i = 0; i < frontiera.size(); i++)
        {
            cout << "A" << frontiera[i].indice << " ";
            indicePunctInterior = indicePunctInterior^frontiera[i].indice;
        }
        cout << "}" << endl;
        cout << "J = { A" << indicePunctInterior << " }" <<endl;

        return 0;
    }

    cout << "I = { A" << frontiera[0].indice << ", A" << frontiera[2].indice << " }" <<endl;
    cout << "J = { A" << frontiera[1].indice << ", A" << frontiera[3].indice << " }" <<endl;

    return 0;
}
