#include <iostream>
#include <string.h>
#include <vector>
#include <string>
#include <string.h>
using namespace std;

class Locuinta
{
    protected:
        char *nume_client;
        double suprafata_utila;
        double discount;
        double chirie_mp;
        double chirie;

    public:
        Locuinta();
        Locuinta(const char *name, double d, double c);
        Locuinta (const Locuinta &l);
        Locuinta & operator =(const Locuinta &l);
        ~Locuinta();
        friend istream & operator >>(istream &in,   Locuinta &l);
        friend ostream & operator <<(ostream &out,  const Locuinta &l);
        virtual void afis()=0;
        virtual double calcul_chirie()=0;


};

Locuinta :: Locuinta()
{
    nume_client=new char[1];
    suprafata_utila=0;
    discount=0;
    chirie_mp=0;
    chirie=0;

}

Locuinta :: Locuinta(const char *name, double d, double c)
{
    int n;
    n=strlen(name);
    nume_client=new char[n+1];
    strcpy(nume_client, name);
    discount=d;
    chirie_mp=c;
}

Locuinta::Locuinta(const Locuinta &l)
{
        int n;
        n=strlen(l.nume_client);
        nume_client=new char[n+1];
        strcpy(nume_client, l.nume_client);
        suprafata_utila=l.suprafata_utila;
        discount=l.discount;
        chirie_mp=l.chirie_mp;
        chirie=l.chirie;

}

Locuinta &Locuinta:: operator =(const Locuinta &l)
{
    if(this==&l)
        return *this;

    delete [] nume_client;

    int n;
    n=strlen(l.nume_client);
    nume_client=new char[n+1];
        strcpy(nume_client, l.nume_client);
        suprafata_utila=l.suprafata_utila;
        discount=l.discount;
        chirie_mp=l.chirie_mp;
    return *this;
}

Locuinta::~Locuinta()
{
    if(nume_client!=NULL)
    delete [] nume_client;

}

istream & operator >>(istream &in,  Locuinta &l)
{
    cout<<endl<<" Nume client: ";
    in.getline(l.nume_client, 100);
    cout<<endl<<"Discount: ";
    in>>l.discount;
    cout<<endl<<"Chirie pe metru patrat: ";
    in>>l.chirie_mp;

     return in;
}

ostream & operator <<(ostream &out, const Locuinta &l)
{
    out<<"Nume: "<<l.nume_client<<'\n';
    out<<"Suprafata utila: "<<l.suprafata_utila<<'\n';
    out<<"Discount: "<<l.discount<<"%"<<'\n';
    out<<"Pret chirie pe metru patrat: "<<l.chirie_mp<<'\n';
    out<<"Chirie: "<<l.chirie<<'\n';
     return out;
}

class Apartament:public Locuinta
{
    private:
        double suprafata;
        int etaj;

    public:
        Apartament():Locuinta(){etaj=0; suprafata=0;}
        Apartament(const char *name, double d, double c,int e, double s):Locuinta(name,d,c){etaj=e; suprafata=s; suprafata_utila=suprafata;chirie=calcul_chirie();}
        Apartament( const Apartament &l):Locuinta(l.nume_client, l.discount, l.chirie_mp){suprafata_utila=l.suprafata; etaj=l.etaj; suprafata=l.suprafata; chirie=l.chirie;}
        Apartament & operator =(const Apartament &l)
        {
            if(this==&l)
                return *this;
                Locuinta::operator=(l);
            etaj=l.etaj;
            suprafata=l.suprafata;
            chirie=l.chirie;
            return *this;
        }
        ~Apartament(){}
        friend istream & operator >>(istream &in,   Apartament &l);
        friend ostream & operator <<(ostream &out,  Apartament l);
        void afis();
        double calcul_chirie();

};
double Apartament::calcul_chirie()
{
    double x;
   x=suprafata_utila*chirie_mp;
   x=x-discount*x/100;
   return x;
}
istream & operator >>(istream &in,  Apartament &l)
{

    cout<<endl<<"Nume_ client: ";
    in.getline(l.nume_client, 100);
    cout<<endl<<"Discount: ";
    in>>l.discount;
    cout<<endl<<"Chirie pe metru patrat: ";
    in>>l.chirie_mp;
    cout<<endl<<"Etaj: ";
    in>>l.etaj;
    cout<<endl<<"Suprafata: ";
    in>>l.suprafata;
    l.suprafata_utila=l.suprafata;
    l.chirie=l.calcul_chirie();
     return in;
}

ostream & operator <<(ostream &out, Apartament l)
{
    out<<"Nume: "<<l.nume_client<<'\n';
    out<<"Suprafata totala: "<<l.suprafata_utila<<'\n';
    out<<"Discount: "<<l.discount<<"%"<<'\n';
    out<<"Chirie pe metru patrat: "<<l.chirie_mp<<'\n';
    out<<"Etaj: "<<l.etaj<<'\n';
    out<<"Suprafata: "<<l.suprafata<<'\n';
    out<<"Chirie: "<<l.chirie<<'\n';
    return out;
}
void Apartament:: afis()
{
    cout<<"Nume: "<<nume_client<<'\n';
    cout<<"Suprafata utila: "<<suprafata_utila<<'\n';
    cout<<"Discount: "<<discount<<"%"<<'\n';
    cout<<"Chirie pe metru patrat: "<<chirie_mp<<'\n';
    cout<<"Etaj: "<<etaj<<'\n';
    cout<<"Suprafata: "<<suprafata<<'\n';
    cout<<"Chirie: "<<chirie<<'\n';
}

class Casa:public Locuinta
{
    protected:
        double supr_curte;
        double pret_curte;
        int etaje;
        double *supr_etaje;

    public:
        Casa():Locuinta(){supr_curte=0; pret_curte=0; etaje=0; supr_etaje=new double[etaje+1];}
        Casa(const char *name, double d, double c,double sc,double pc, int e, double *se):Locuinta(name,d,c)
        {
            supr_curte=sc;
            pret_curte=pc;
            suprafata_utila=0;
            etaje=e;
            supr_etaje=new double[etaje+1];
            for(int i=0;i<e;i++)
                {supr_etaje[i]=se[i];
                suprafata_utila=suprafata_utila+se[i];
                }
            chirie=calcul_chirie();


        }

        Casa( const Casa &l):Locuinta(l.nume_client, l.discount, l.chirie_mp)
        {
            supr_curte=l.supr_curte;
            pret_curte=l.pret_curte;
            etaje=l.etaje;
            supr_etaje=new double[l.etaje+1];
            for(int i=0;i<l.etaje;i++)
                supr_etaje[i]=l.supr_etaje[i];
                suprafata_utila=l.suprafata_utila;
                chirie=l.chirie;
        }

        Casa & operator =(const Casa &l)
        {
            if(this==&l)
                return *this;
                Locuinta::operator=(l);
             supr_curte=l.supr_curte;
             pret_curte=l.pret_curte;
            etaje=l.etaje;
            supr_etaje=new double[l.etaje+1];
            for(int i=0;i<l.etaje;i++)
                supr_etaje[i]=l.supr_etaje[i];
            suprafata_utila=l.suprafata_utila;
            chirie=l.chirie;
            return *this;
        }
        ~Casa(){delete [] supr_etaje;}
        friend istream & operator >>(istream &in,   Casa &l);
        friend ostream & operator <<(ostream &out,  Casa l);
        void afis();
        double calcul_chirie();
};

double Casa::calcul_chirie()
{
    double x;
   x=suprafata_utila*chirie_mp;
   x=x-discount*x/100;
   x=x+supr_curte*pret_curte;
   return x;
}

istream & operator >>(istream &in,  Casa &l)
{
    cout<<"Nume client: ";
    in.getline(l.nume_client, 100);
    cout<<endl<<"Discount: ";
    in>>l.discount;
    cout<<endl<<"Chirie pe metru patrat: ";
    in>>l.chirie_mp;
    cout<<endl<<"Etaje: ";
    in>>l.etaje;
    cout<<endl<<"Suprafata curte: ";
    in>>l.supr_curte;
    cout<<endl<<"Pret pe mp la curte: ";
    in>>l.pret_curte;
    l.suprafata_utila=0;
    cout<<endl<<"Suprafata fiecarui etaj: ";
    for(int i=0;i<l.etaje;i++)
        {
            in>>l.supr_etaje[i];
            l.suprafata_utila=l.suprafata_utila+l.supr_etaje[i];
        }
    l.chirie=l.calcul_chirie();
    return in;
}

ostream & operator <<(ostream &out, Casa l)
{
    cout<<"Nume: "<<l.nume_client<<'\n';
    cout<<"Suprafata utila: "<<l.suprafata_utila<<'\n';
    cout<<"Discount: "<<l.discount<<"%"<<'\n';
    cout<<"Chirie pe metru patrat: "<<l.chirie_mp<<'\n';
    cout<<"Suprafata curtii: "<<'\n';
    cout<<"Pretul curtii pe metru patrat: "<<l.pret_curte<<'\n';
    cout<<"Numar de etaje: "<<l.etaje<<'\n';
    for(int i=0;i<l.etaje;i++)
    if(i!=0)
        cout<<"Suprafata etajului "<<i<<" este: "<<l.supr_etaje[i]<<'\n';
    else
        cout<<"Suprafata parterului este: "<<l.supr_etaje[i]<<'\n';

    cout<<"Chirie: "<<l.chirie<<'\n';
    return out;
}
void Casa:: afis()
{
    cout<<"Nume: "<<nume_client<<'\n';
    cout<<"Suprafata utila: "<<suprafata_utila<<'\n';
    cout<<"Discount: "<<discount<<"%"<<'\n';
    cout<<"Chirie pe metru patrat: "<<chirie_mp<<'\n';
    cout<<"Suprafata curtii: "<<supr_curte<<'\n';
    cout<<"Pretul curtii pe metru patrat: "<<pret_curte<<'\n';
    cout<<"Numar de etaje: "<<etaje<<'\n';
    for(int i=0;i<etaje;i++)
    if(i!=0)
        cout<<"Suprafata etajului "<<i<<"este: "<<supr_etaje[i]<<'\n';
    else
        cout<<"Suprafata parterului este: "<<supr_etaje[i]<<'\n';
   cout<<"Chirie: "<<chirie<<'\n';

}

template <class T>
class Gestiune
{
    protected:
        static int nr;
        vector <Locuinta *> v ;
        vector <double> chirii;

    public:
        Gestiune(){};
        Gestiune( Locuinta *x, double c);
        Gestiune(const Gestiune &l);
        Gestiune & operator =(const Gestiune &l);
        Gestiune & operator +=(T x);
        void afis();
        ~Gestiune(){v.clear(); chirii.clear();}



};
template <class T>
Gestiune<T>::Gestiune( Locuinta *x, double c)
{
   v=x;
   chirii=c;
}


template <class T>
Gestiune<T>::Gestiune(const Gestiune &l)
{
    v=l.v;
    chirii=l.chirii;

}
template <class T>
Gestiune<T> &Gestiune<T> :: operator =(const Gestiune &x)
{
        if(this==&x)
        return *this;

    v.clear();
    chirii.clear();

    v=x.v;
    chirii=x.chirii;

    return *this;

}

template <class T>
Gestiune<T> & Gestiune<T>:: operator +=(T x)
{
    nr++;
    v.push_back(x);
    chirii.push_back(x->calcul_chirie());
    return *this;
}

template <class T>
void Gestiune<T>::afis()
{
    int i;
    for(i=0;i<nr;i++)
       {
        v[i]->afis();
        cout<<"Chirie: "<<chirii[i]<<'\n';
        cout<<endl;
       }

}
template <class T>
int Gestiune <T> ::nr=0;

template <>
class Gestiune<string>
{
    protected:
        static int nr_clienti;
        vector <string> nume ;


    public:
        Gestiune(){};
        Gestiune( vector<string> n);
        Gestiune(const Gestiune &l);
        Gestiune & operator =(const Gestiune &l);
        Gestiune & operator +=(string x);
        void afis();
        ~Gestiune(){nume.clear();}


};


Gestiune<string>::Gestiune(vector<string> n)
{
  nume=n;
}


Gestiune<string>::Gestiune(const Gestiune<string> &l)
{
   nume=l.nume;

}

Gestiune<string> &Gestiune<string> :: operator =(const Gestiune &x)
{
        if(this==&x)
        return *this;

    nume.clear();

    nume=x.nume;

    return *this;

}

Gestiune<string> & Gestiune<string>:: operator +=(string x)
{
    nr_clienti++;
    nume.push_back(x);
    return *this;
}

void Gestiune<string>::afis()
{
    int i;
    for(i=0;i<nr_clienti;i++)
       {
        cout<<nume[i]<<'\n';
       }

}

int Gestiune <string> ::nr_clienti=0;

int main()
{
    int i,n;
     char w;

    Gestiune<Locuinta *> g;

    cin>>n;
    char q;
    for(i=1;i<=n;i++)
    {
        cin>>q;
        cin.get();
        if(q=='a')
        {
            Apartament *a;
            a=new Apartament;
            cin>>(*a);
            g+=a;
        }
        else
            if(q=='c')
        {
            Casa *c;
            c=new Casa;
            cin>>(*c);
            g+=c;
        }
    }

    g.afis();

    /*string s;
    int n,i;
    Gestiune<string> g;
    cin>>n;
    cin.get();
    for(i=0;i<n;i++)
    {
       getline(cin,s);
        g+=s;

    }
    g.afis();
*/
    return 0;
}
