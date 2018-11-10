struct punct
{
    double x;
    double y;
    double z;
    int indice;

    bool operator==(punct p)
    {
        return (this->x == p.x && this->y == p.y && this->z == p.z);
    }

    static double determinaRaport(punct a, punct b, punct c)
    {
        if(a.y != b.y)
            return (c.y - a.y)/(b.y - a.y);
        if(a.x != b.x)
            return (c.x - a.x)/(b.x - a.x);
        if(a.z != b.z)
            return (c.z - a.z)/(b.z - a.z);

        return 0;
    }

    static bool verificaEcuatii(punct a, punct b, punct c, double rap)
    {
        if( (c.x - a.x) == rap*(b.x - a.x) &&
            (c.y - a.y) == rap*(b.y - a.y) &&
            (c.z - a.z) == rap*(b.z - a.z) )
            return true;

        return false;
    }

    static void determinaCombinatieAfina(punct a, punct b, punct c)
    {
        if(a == b)
        {
            cout << "A" << b.indice << " = " << "1*" << "A" << a.indice << " + 0*" << "A" << c.indice;
            return;
        }
        if(a == c)
        {
            cout << "A" << c.indice << " = " << "1*" << "A" << a.indice << " + 0*" << "A" << b.indice;
            return;
        }
        if(b == c)
        {
            cout << "A" << b.indice <<  " = " << "1*" << "A" << c.indice << " + 0*" << "A" << b.indice;
            return;
        }

        if( a == b && a == c)
        {
            cout << "\nToate cele 3 puncte coincid.";
        }

        double rap = determinaRaport(a, b, c);

        if(rap == 0)
        {
            cout << "Punctele nu sunt coliniare.";
            return;
        }

        if( !verificaEcuatii(a, b, c, rap) )
        {
            cout << "Punctele nu sunt coliniare.";
            return;
        }

        cout << "A" << c.indice << " = " << 1-rap << "*" << "A" << a.indice << " + " << rap << "*" << "A" << b.indice;
    }

    static bool determinaColiniaritate(punct a, punct b, punct c)
    {
        if( a == b || a == c || b == c)
        {
            return true;
        }

        double rap = determinaRaport(a, b, c);
        if(rap == 0)
        {
            return false;
        }

        if( !verificaEcuatii(a, b, c, rap) )
        {
            return false;
        }
        return true;
    }

    //0 - coliniare; 1 - r e la stanga lui pq; -1 - r e la dreapta lui pq
    static int testOrientare(punct p, punct q, punct r)
    {
        double minor1, minor2, minor3;
        minor1 = q.x*r.y - q.y*r.x;
        minor2 = -p.x*r.y + p.y*r.x;
        minor3 = p.x*q.y - p.y*q.x;

        double rez = minor1 + minor2 + minor3;
        if(rez > 0)
            return 1;
        if(rez == 0)
            return 0;
        return -1;
    }

    int dist(punct p)
    {
        return sqrt( (x - p.x)*(x - p.x) + (y - p.y)*(y - p.y) );
    }
};
