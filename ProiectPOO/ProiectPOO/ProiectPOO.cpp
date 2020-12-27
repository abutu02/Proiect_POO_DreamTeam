
#include <iostream>
#include <vector>
using namespace std;

class Autovehicul
{
    char* marca;
    char model[20];
    string culoare;
    int an;
    int* kmParcursiPerAn;
    int id;
    static int contor;

public:

    Autovehicul()
    {
        marca = nullptr;
        strcpy_s(model, 1, "");
        culoare = "";
        an = 0;
        kmParcursiPerAn = nullptr;
        id = 0;
    }

    Autovehicul(const char* marca, const char model[20], string culoare):Autovehicul()
    {
        this->marca = new char[strlen(marca) + 1];
        strcpy_s(this->marca, strlen(marca) + 1, marca);
        strcpy_s(this->model, strlen(model) + 1, model);
        this->culoare = culoare;
        id = contor++;


    }

    Autovehicul(const char* marca, const char model[20], string culoare, int an, int* kmParcursiPerAn):Autovehicul(marca, model, culoare)
    {
        this->an = an;
        this->kmParcursiPerAn = new int[2020 - an + 1];
        for (int i = 0; i <= 2020 - an; i++)
        {
            this->kmParcursiPerAn[i] = kmParcursiPerAn[i];
        }
    }

    Autovehicul( Autovehicul& A):Autovehicul(A.marca, A.model, A.culoare, A.an, A.kmParcursiPerAn)
    {
        
    }

    ~Autovehicul()
    {
        delete[]marca;
        delete[]kmParcursiPerAn;
    }

    Autovehicul operator= (Autovehicul& A)
    {
        this->marca = new char[strlen(A.marca) + 1];
        strcpy_s(this->marca, strlen(A.marca) + 1, A.marca);
        strcpy_s(this->model, strlen(A.model) + 1, A.model);
        this->culoare = A.culoare;
        this->an = A.an;
        this->kmParcursiPerAn = new int[2020 - A.an + 1];
        for (int i = 0; i <= 2020 - A.an; i++)
        {
            this->kmParcursiPerAn[i] = A.kmParcursiPerAn[i];
        }
        this->id = A.id;

        return *this;
    }

    friend ostream& operator<< (ostream& os, Autovehicul A)
    {
        os << A.id;
        os << A.marca;
        os << A.model;
        os << A.culoare;
        os << A.an;
        for (int i = 0; i <= 2020 - A.an; i++)
        {
            os << A.kmParcursiPerAn[i];
        }
        
        return os;
    }

    friend istream& operator>> (istream& is, Autovehicul& A)
    {

    }

    int operator[](int index)
    {
        return this->kmParcursiPerAn[index];
    }

    int* operator+ (Autovehicul A)
    {
        if (an == A.an)
        {
            int* km = new int[2020 - an + 1];
            for (int i = 0; i <= 2020 - an; i++)
            {
                km[i] = A.kmParcursiPerAn[i] + kmParcursiPerAn[i];
            }
            return km;
        }
        return nullptr;
    }

    void operator++()
    {
        this->id++;
    }

    void operator++(int x)
    {
        this->id++;
    }

    operator const char* ()
    {
        const char* a = culoare.c_str();
        return a;
    }

    bool operator!()
    {
        return id > 0 ;

    }

    bool operator > (Autovehicul A)
    {
        return A.an > an;
    }

    bool operator==(Autovehicul A)
    {
        if (A.an != an)
        {
            return false;
        }
        if (strcmp(A.marca, marca) != 0)
        {
            return false;
        }
        if (strcmp(A.model, model) != 0)
        {
            return false;
        }

        return true;


    }

};

class SUV:public Autovehicul
{
    const char* combustibil;
    int nrLocuri;
    int* kmSchimbUlei;
    int nrSchimburiUlei;
    
};

class Camion:public Autovehicul
{
    int gabarit;
    char* serieSasiu;
    int* vitezaMaximaAdmisa; // pozitia 0: viteza maxima in localitate, 1: in afara localitatii, 2: drumuri europene, 3: autostrada
};

class Coupe:public Autovehicul
{
    int nrPortiere;
    char* taraDeOrigine;
    int* preturiFiltre;
    int nrFiltre;

};

class ParcAuto
{
    vector <Autovehicul*>Autovehicule; 
    char* numeParcAuto;
    int* pretPerAutovehicul;

};



int Autovehicul::contor = 1;

int main()
{
    int* kmParcursi = new int[2];
    kmParcursi[0] = 12900;
    kmParcursi[1] = 20000;
    Autovehicul* A = new Autovehicul("Audi", "A4", "Negru", 2019, kmParcursi);
    int* kmParcursi2 = new int[2];
    kmParcursi2[0] = 1400;
    kmParcursi2[1] = 2040;
    Autovehicul* B = new Autovehicul("BMW", "3Series", "Alb", 2019, kmParcursi2);
    for (int i = 0; i < 2; i++)
    {
        cout << (*A + *B)[i];
    }

}
//getteri, setteri ptr cls Autovehicul
//ptr celelalte 3 clase constructori, destructori, operator =, operator >>, <<, getteri, setteri
//ptr parcAuto: constructori, destructori, operator =, operator >>, <<, getteri, setteri
//instalare github din linia de comanda
//

