//Realizat de Capra Bogdan

#ifndef CREATE_TABLE_FILE
#define CREATE_TABLE_FILE

#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <vector>
#include "CSV.h"

using namespace std;

class CREATE_TABLE: public CSV
{
    string name;
public:
    CREATE_TABLE();
    CREATE_TABLE(string);
    ~CREATE_TABLE();
    void exec(string);
    void infoAdd(vector<string>);
    string getName();
    friend bool checker(string);
};

bool checker(string file)
{
    fstream f(file);
    return f.good();
}

CREATE_TABLE::CREATE_TABLE()
{
    this->name="";
}

CREATE_TABLE::CREATE_TABLE(string file)
{
    if(!checker(file))
    {
        this->name="./structure/"+file+".csv";
        ofstream f("./tables/"+file+".csv");
        f<<"";
        f.close();
    }
    else
     cout<<"ERROR: File exists!\n";
}

void CREATE_TABLE::exec(string file)
{
    if(!checker(file))
    {
        this->name="./structure/"+file+".csv";
        ofstream f("./tables/"+file+".csv");
        f<<"";
        f.close();
    }
    else
     cout<<"ERROR: File exists!\n";
}

void CREATE_TABLE::infoAdd(vector<string> info)
{
    ofstream f(this->name);
    for(size_t i=0;i<info.size();++i)
        if((i+1)%4)
            f<<info[i]<<',';
        else
            f<<info[i]<<'\n';
    f.close();
}

string CREATE_TABLE::getName()
{
    return this->name;
}

CREATE_TABLE::~CREATE_TABLE()
{}


#endif