//Realizat de Capra Bogdan

#ifndef SRC_FILE
#define SRC_FILE

#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

class CSV
{
    vector<vector<string>> array;
    size_t lines;
    size_t *length;
    char arr[255];
public:
    CSV();
    CSV(vector<vector<string>>,size_t);
    ~CSV();
    void CSVread(string);
    void TXTread(string);
    vector<vector<string>> getArray();
    void setArray(vector<vector<string>>);
    size_t getLines();
    void setLines(size_t);
    friend istream &operator>>(istream&,CSV&);
    friend ostream &operator<<(ostream&,CSV&);
};

istream &operator>>(istream &input, CSV &csv)
{
    string CSVfile,TXTfile;
    input>>CSVfile>>TXTfile;
    csv.CSVread(CSVfile);
    csv.TXTread(TXTfile);
    return input;
}

ostream &operator<<(ostream &output, CSV &csv)
{
    output<<csv.lines;
    return output;
}

CSV::CSV(vector<vector<string>> array, size_t lines)
{
    this->lines=lines;
    this->array=array;
}

CSV::CSV()
{
    this->lines=0;
    this->length=new size_t;
}

CSV::~CSV()
{
    delete this->length;
}

void CSV::CSVread(string file)
{
    ifstream in(file);
    string line, field;

    vector<string> v;
	this->lines=0;

    this->array.clear();

    while (getline(in, line))
    {
        v.clear();
        stringstream ss(line);
		++this->lines;
        while (getline(ss, field, ','))
            v.push_back(field);
        this->array.push_back(v);
    }
	in.close();
}

void CSV::TXTread(string file)
{
    ifstream in(file);
    string line, field;

    vector<string> v;
	this->lines=0;

    this->array.clear();

    while (getline(in, line))
    {
        v.clear();
        stringstream ss(line);
		++this->lines;
        while (getline(ss, field, ' '))
            v.push_back(field);
        this->array.push_back(v);
    }
	in.close();
}

size_t CSV::getLines()
{
    return this->lines;
}

void CSV::setLines(size_t lines)
{
    this->lines=lines;
}

void CSV::setArray(vector<vector<string>> array)
{
    this->array=array;
}

#endif