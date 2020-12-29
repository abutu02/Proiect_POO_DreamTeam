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

    Autovehicul(const char* marca, const char model[20], string culoare) :Autovehicul()
    {
        this->marca = new char[strlen(marca) + 1];
        strcpy_s(this->marca, strlen(marca) + 1, marca);
        strcpy_s(this->model, strlen(model) + 1, model);
        this->culoare = culoare;
        id = contor++;


    }

    Autovehicul(const char* marca, const char model[20], string culoare, int an, int* kmParcursiPerAn) :Autovehicul(marca, model, culoare)
    {
        this->an = an;
        this->kmParcursiPerAn = new int[2020 - an + 1];
        for (int i = 0; i <= 2020 - an; i++)
        {
            this->kmParcursiPerAn[i] = kmParcursiPerAn[i];
        }
    }

    Autovehicul(Autovehicul& A) :Autovehicul(A.marca, A.model, A.culoare, A.an, A.kmParcursiPerAn)
    {

    }

    ~Autovehicul()
    {
        delete[]marca;
        delete[]kmParcursiPerAn;
    }

    void setMarca(char* marca)
    {
        this->marca = new char[strlen(marca) + 1];
        strcpy_s(this->marca, strlen(marca) + 1, marca);

    }

    void setModel(char model[20])
    {
        strcpy_s(this->model, strlen(model) + 1, model);
    }

    void setCuloare(string culoare)
    {
        this->culoare = culoare;
    }

    void setAn(int an)
    {
        this->an = an;
    }

    void setKmParcursiPerAn(int* kmParcursiPerAn)
    {
        this->kmParcursiPerAn = new int[2020 - an + 1];
        for (int i = 0; i <= 2020 - an; i++)
        {
            this->kmParcursiPerAn[i] = kmParcursiPerAn[i];
        }
    }

    void setId(int id)
    {
        this->id = id;
    }

    char* getMarca()
    {
        return marca;
    }

    char* getModel()
    {
        return model;
    }

    string getCuloare()
    {
        return culoare;
    }

    int getAn()
    {
        return an;
    }

    int* getKmParcursiPerAn()
    {
        return kmParcursiPerAn;
    }

    int getId()
    {
        return id;
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
        is >> A.id;
        is >> A.marca;
        is >> A.model;
        is >> A.culoare;
        is >> A.an;
        for (int i = 0; i <= 2020 - A.an; i++)
        {
            is >> A.kmParcursiPerAn[i];
        }

        return is;
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
        return id > 0;

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


class Camion :public Autovehicul
{
    int gabarit;
    char* serieSasiu;
    int* vitezaMaximaAdmisa; // pozitia 0: viteza maxima in localitate, 1: in afara localitatii, 2: drumuri europene, 3: autostrada //are dimensiunea 4

    Camion() :Autovehicul()
    {
        gabarit = 0;
        serieSasiu = nullptr;
        vitezaMaximaAdmisa = nullptr;
    }
    Camion(int gabarit) :Autovehicul()
    {
        this->gabarit = gabarit;
        serieSasiu = nullptr;
        vitezaMaximaAdmisa = nullptr;
    }
    Camion(int gabarit, char* serieSasiu, int* vitezaMaximaAdmisa) :Autovehicul()
    {
        this->gabarit = gabarit;
        this->serieSasiu = new char[strlen(serieSasiu) + 1];
        strcpy_s(this->serieSasiu, strlen(serieSasiu) + 1, serieSasiu);
        this->vitezaMaximaAdmisa = new int[4];
        for (int i = 0; i < 4; i++)
        {
            this->vitezaMaximaAdmisa[i] = vitezaMaximaAdmisa[i];
        }
    }

    Camion(Camion& A) :Autovehicul(A.getMarca(), A.getModel(), A.getCuloare(), A.getAn(), A.getKmParcursiPerAn())
    {
        this->gabarit = A.gabarit;
        this->serieSasiu = new char[strlen(A.serieSasiu) + 1];
        strcpy_s(this->serieSasiu, strlen(A.serieSasiu) + 1, A.serieSasiu);
        this->vitezaMaximaAdmisa = new int[4];
        for (int i = 0; i < 4; i++)
        {
            this->vitezaMaximaAdmisa[i] = A.vitezaMaximaAdmisa[i];
        }
    }
};

class Coupe :public Autovehicul
{
    int nrPortiere;
    char* taraDeOrigine;
    int* preturiFiltre;
    int nrFiltre;
public:
    Coupe() :Autovehicul()
    {
        nrPortiere = 0;
        taraDeOrigine = nullptr;
        preturiFiltre = nullptr;
        nrFiltre = 0;

    }

    Coupe(const char* marca, const char model[20], string culoare, int nrPortiere, const char* taraDeOrigine) :Autovehicul(marca, model, culoare)
    {
        this->nrPortiere = nrPortiere;
        this->taraDeOrigine = new char[strlen(taraDeOrigine) + 1];
        strcpy_s(this->taraDeOrigine, strlen(taraDeOrigine) + 1, taraDeOrigine);
        preturiFiltre = nullptr;
        nrFiltre = 0;
    }

    Coupe(const char* marca, const char model[20], string culoare, int an, int* kmParcursiPerAn, int nrPortiere, const char* taraDeOrigine, int* preturiFiltre, int nrFiltre) :
        Autovehicul(marca, model, culoare, an, kmParcursiPerAn)
    {
        this->nrPortiere = nrPortiere;
        this->taraDeOrigine = new char[strlen(taraDeOrigine) + 1];
        strcpy_s(this->taraDeOrigine, strlen(taraDeOrigine) + 1, taraDeOrigine);
        this->nrFiltre = nrFiltre;
        this->preturiFiltre = new int[nrFiltre];
        for (int i = 0; i < nrFiltre; i++)
        {
            this->preturiFiltre[i] = preturiFiltre[i];
        }

    }

    Coupe(Coupe& A) :Autovehicul(A.getMarca(), A.getModel(), A.getCuloare(), A.getAn(), A.getKmParcursiPerAn())
    {
        this->nrPortiere = A.nrPortiere;
        this->taraDeOrigine = new char[strlen(A.taraDeOrigine) + 1];
        strcpy_s(this->taraDeOrigine, strlen(A.taraDeOrigine) + 1, A.taraDeOrigine);
        this->nrFiltre = A.nrFiltre;
        this->preturiFiltre = new int[A.nrFiltre];
        for (int i = 0; i < A.nrFiltre; i++)
        {
            this->preturiFiltre[i] = A.preturiFiltre[i];
        }
    }

    ~Coupe()
    {
        delete[]taraDeOrigine;
        delete[]preturiFiltre;
    }

    void setNrPortiere(int nrPortiere)
    {
        this->nrPortiere = nrPortiere;
    }

    void setTaraDeOrigine(char* taraDeOrigine)
    {
        this->taraDeOrigine = new char[strlen(taraDeOrigine) + 1];
        strcpy_s(this->taraDeOrigine, strlen(taraDeOrigine) + 1, taraDeOrigine);
    }

    void setPreturiFiltre(int* preturiFiltre)
    {
        this->preturiFiltre = new int[nrFiltre];
        for (int i = 0; i < nrFiltre; i++)
        {
            this->preturiFiltre[i] = preturiFiltre[i];
        }
    }

    void setNrFiltre(int nrFiltre)
    {
        this->nrFiltre = nrFiltre;
    }

    Coupe operator= (Coupe& A)
    {

        this->nrPortiere = A.nrPortiere;
        this->taraDeOrigine = new char[strlen(A.taraDeOrigine) + 1];
        strcpy_s(this->taraDeOrigine, strlen(A.taraDeOrigine) + 1, A.taraDeOrigine);
        this->nrFiltre = A.nrFiltre;
        this->preturiFiltre = new int[A.nrFiltre];
        for (int i = 0; i < A.nrFiltre; i++)
        {
            this->preturiFiltre[i] = A.preturiFiltre[i];
        }

        return *this;
    }

    friend ostream& operator<< (ostream& os, Coupe A)
    {
        os << A.nrPortiere;
        os << A.taraDeOrigine;
        os << A.nrFiltre;
        for (int i = 0; i < A.nrFiltre; i++)
        {
            os << A.preturiFiltre[i];
        }

        return os;
    }

    friend istream& operator>> (istream& is, Coupe& A)
    {
        is >> A.nrPortiere;
        is >> A.taraDeOrigine;
        is >> A.nrFiltre;
        for (int i = 0; i < A.nrFiltre; i++)
        {
            is >> A.preturiFiltre[i];
        }

        return is;

    }

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