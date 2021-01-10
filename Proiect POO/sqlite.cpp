//Realizat de Butucaru Andreea

#include "./src/CSV.h"
#include "./src/CREATE_TABLE.h"
#include "./src/DISPLAY_TABLE.h"
#include "./src/DROP_TABLE.h"
#include "./src/INSERT_INTO.h"
#include "./src/DELETE_FROM.h"
#include "./src/UPDATE.h"
#include "./src/SELECT.h"

void tokenize(string const &str, const char delim, vector<string> &out)
{
    out.clear();
    size_t start;
    size_t end=0;
 
    while((start=str.find_first_not_of(delim, end))!=string::npos)
    {
        end=str.find(delim, start);
        out.push_back(str.substr(start,end-start));
    }
}

int main(int argc, char *argv[])
{

    string buffer,temp;
    vector<string> out;
    bool open=true,good;
    size_t index=1;
    CREATE_TABLE create;
    DROP_TABLE drop;
    DISPLAY_TABLE display;
    INSERT_INTO insert;
    DELETE_FROM del;
    UPDATE update;
    SELECT selection;

    //cazul in care se executa programul fara parametri
    if(argc==1)
    {
        //se afiseaza interfata SQLite de inceput
        time_t now=time(0);
        tm *gmtm = gmtime(&now);
        cout<<"SQLite version ASE "<<asctime(gmtm);
        cout<<"Connected to a \033[0;31mtransient in-memory database\033[0m\n";
        
        //armarea CLI-ului
        while(open)
        {
            //citirea comenzii
            cout<<"sqlite> ";
            getline(cin,buffer);
            //convertirea in litere mici
            transform(buffer.begin(), buffer.end(), buffer.begin(),
            [](unsigned char c){
                return tolower(c);
            });
            //comanda quit - iese din aplicatie si sterge query-urile salvate temporar
            if(buffer=="quit"||buffer=="quit()")
            {
                for(size_t i=0;i<index;++i)
                {
                    temp="./query/SELECT_"+to_string(i+1)+".csv";
                    remove(temp.c_str());
                }
                open=false;
            }
            //clear - sterge ecranul
            else if(buffer=="clear"||buffer=="clear()")
                system("@cls||clear");
            else
            {
                //se fragmenteaza comanda in functie de spatiu
                tokenize(buffer,' ',out);
                if((out.size()==4||out.size()==5)&&out[0]=="create"&&out[1]=="table")
                {
                    //se preia numele tabelului
                    create.exec(*(out.begin()+2));
                    //se preia structura
                    temp=*(out.end()-1);
                    //se convertesc caracterele separatoare in spatii
                    for(size_t i=0;i<temp.length();++i)
                        if(temp[i]==')'||temp[i]=='('||temp[i]==',')
                            temp[i]=' ';
                    //se fragmenteaza parametrul de structura a tabelului
                    tokenize(temp,' ',out);
                    //se verifica daca structura structura buna parcurgand parametrii
                    good=true;
                    if(out.size()%4==0&&out.size())
                        for(size_t i=1;i<out.size()&&good;i+=4)
                        {
                            if(out[i]!="char"&&out[i]!="varchar"&&out[i]!="binary"&&out[i]!="varbinary"&&out[i]!="tinytext"&&out[i]!="text"&&out[i]!="mediumtext"&&out[i]!="largetext")
                                good=false;
                        }
                    else
                        good=false;
                    //daca e buna executa comanda, altfel afiseaza o eroare
                    if(good)
                        create.infoAdd(out);
                    else
                    {
                        drop.exec(create.getName(),false);
                        cout<<"Syntax error or failed execution!\n";
                    }
                }
                //comanda de stergere a tabelului
                else if(out.size()==3&&out[0]=="drop"&&out[1]=="table")
                    drop.exec(out[2],true);
                //afisare tabel
                else if(out.size()==3&&out[0]=="display"&&out[1]=="table")
                    display.exec(out[2]);
                //inserare element in tabel
                else if(out.size()==5&&out[0]=="insert"&&out[1]=="into"&&out[3]=="values")
                {
                    //se preia numele tabelului
                    insert.setName(out[2]);
                    //se preia valoarea de inserare
                    temp=*(out.end()-1);
                    for(size_t i=0;i<temp.length();++i)
                        if(temp[i]==')'||temp[i]=='('||temp[i]==',')
                            temp[i]=' ';
                    //se converteste in array valoarea
                    tokenize(temp,' ',out);
                    //se insereaza valoarea
                    insert.exec(out);
                }
                else if(out.size()==5&&out[0]=="delete"&&out[1]=="from"&&out[3]=="where")
                {
                    //se preia numele tabelului
                    del.setName(out[2]);
                    //se preia valoarea de stergere
                    temp=*(out.end()-1);
                    for(size_t i=0;i<temp.length();++i)
                        if(temp[i]=='=')
                            temp[i]=' ';
                    //se converteste in array valoarea
                    tokenize(temp,' ',out);
                    //se sterge valoarea
                    if(out.size()==2)
                        del.exec(del.findParameter(*(out.begin())),*(out.end()-1));
                    else
                        cout<<"Syntax error or failed execution!\n";
                }
                else if(out.size()==6&&out[0]=="update"&&out[2]=="set"&&out[4]=="where")
                {
                    //se preia numele tabelului
                    update.setName(out[2]);
                    //se preia valoarea de update
                    temp=*(out.end()-1);
                    for(size_t i=0;i<temp.length();++i)
                        if(temp[i]=='=')
                            temp[i]=' ';
                    //se converteste in array valoarea
                    tokenize(temp,' ',out);
                    //se face update valoarea
                    if(out.size()==4)
                        update.exec(update.findParameter(out[0]),update.findParameter(out[1]),out[2],out[3]);
                    else
                        cout<<"Syntax error or failed execution!\n";
                }
                else if(out.size()==3&&out[0]=="select")
                {
                    //se preia numele tabelului
                    selection.setName(*(out.end()-1));
                    selection.setSaveName("SELECT_"+to_string(index)+".csv");
                    //se preia parametrul de select
                    temp=out[1];
                    //se converteste in array valoarea
                    for(size_t i=0;i<temp.length();++i)
                        if(temp[i]==','||temp[i]=='('||temp[i]==')')
                            temp[i]=' ';
                    tokenize(temp,' ',out);
                    //se realizeaza comanda select
                    for(size_t i=0;i<out.size();++i)
                        selection.exec(selection.findParameter(out[i]),good);
                    if(good)
                        ++index;
                }
                //analog, decat ca se preia si parametrul where
                else if(out.size()==5&&out[0]=="select"&&out[3]=="where")
                {
                    selection.setName(out[2]);
                    selection.setSaveName("SELECT_"+to_string(index)+".csv");
                    tokenize(*(out.end()-1),'=',selection.where);
                    temp=out[1];
                    for(size_t i=0;i<temp.length();++i)
                        if(temp[i]==','||temp[i]=='('||temp[i]==')')
                            temp[i]=' ';
                    tokenize(temp,' ',out);
                    for(size_t i=0;i<out.size();++i)
                        selection.exec(selection.findParameter(out[i]),selection.findParameter(*(selection.where.begin())),*(selection.where.end()-1),good);
                    if(good)
                        ++index;
                }
                //este cazul special in care se face doar un copy la tabel
                else if(out.size()==4&&out[0]=="select"&&out[1]=="all"&&out[2]=="form")
                {
                    temp=out[3];
                    ofstream out("./query/SELECT_"+to_string(index)+".csv");
                    ifstream in("./tables/"+temp+".csv");
                    if(in.good())
                        while(getline(in,temp))
                            out<<temp<<'\n';
                    else
                        cout<<"Syntax error or failed execution!\n";
                    in.close();
                    out.close();
                }
                //cazul in care sintaxa nu este corecta
                else if(out.size())
                    cout<<"Syntax error or failed execution!\n";
            }
        }
    }
    //cazul comanda CLI cu parametrii - conceptul este asemanator ca si cazul fara parametrii
    else
    {
        for(int i=0;i<argc;++i)
        {
            ifstream f(argv[i]);
            while(getline(f,buffer))
            {
                transform(buffer.begin(), buffer.end(), buffer.begin(),
                [](unsigned char c){
                    return tolower(c);
                });
                if(buffer=="quit"||buffer=="quit()")
                {
                    for(size_t i=0;i<index;++i)
                    {
                        temp="./query/SELECT_"+to_string(i+1)+".csv";
                        remove(temp.c_str());
                    }
                    open=false;
                }
                else if(buffer=="clear"||buffer=="clear()")
                    system("@cls||clear");
                else
                {
                    tokenize(buffer,' ',out);
                    if((out.size()==4||out.size()==5)&&out[0]=="create"&&out[1]=="table")
                    {
                        create.exec(*(out.begin()+2));
                        temp=*(out.end()-1);
                        for(size_t i=0;i<temp.length();++i)
                            if(temp[i]==')'||temp[i]=='('||temp[i]==',')
                                temp[i]=' ';
                        tokenize(temp,' ',out);
                        good=true;
                        if(out.size()%4==0&&out.size())
                            for(size_t i=1;i<out.size()&&good;i+=4)
                            {
                                if(out[i]!="char"&&out[i]!="varchar"&&out[i]!="binary"&&out[i]!="varbinary"&&out[i]!="tinytext"&&out[i]!="text"&&out[i]!="mediumtext"&&out[i]!="largetext")
                                    good=false;
                            }
                        else
                            good=false;
                        if(good)
                            create.infoAdd(out);
                        else
                        {
                            drop.exec(create.getName(),false);
                        }
                    }
                    else if(out.size()==3&&out[0]=="drop"&&out[1]=="table")
                        drop.exec(out[2],true);
                    else if(out.size()==3&&out[0]=="display"&&out[1]=="table")
                        display.exec(out[2]);
                    else if(out.size()==5&&out[0]=="insert"&&out[1]=="into"&&out[3]=="values")
                    {
                        insert.setName(out[2]);
                        temp=*(out.end()-1);
                        for(size_t i=0;i<temp.length();++i)
                            if(temp[i]==')'||temp[i]=='('||temp[i]==',')
                                temp[i]=' ';
                        tokenize(temp,' ',out);
                        insert.exec(out);
                    }
                    else if(out.size()==5&&out[0]=="delete"&&out[1]=="from"&&out[3]=="where")
                    {
                        del.setName(out[2]);
                        temp=*(out.end()-1);
                        for(size_t i=0;i<temp.length();++i)
                            if(temp[i]=='=')
                                temp[i]=' ';
                        tokenize(temp,' ',out);
                        if(out.size()==2)
                            del.exec(del.findParameter(*(out.begin())),*(out.end()-1));
                    }
                    else if(out.size()==6&&out[0]=="update"&&out[2]=="set"&&out[4]=="where")
                    {
                        update.setName(out[2]);
                        temp=*(out.end()-1);
                        for(size_t i=0;i<temp.length();++i)
                            if(temp[i]=='=')
                                temp[i]=' ';
                        tokenize(temp,' ',out);
                        if(out.size()==4)
                            update.exec(update.findParameter(out[0]),update.findParameter(out[1]),out[2],out[3]);     
                    }
                    else if(out.size()==3&&out[0]=="select")
                    {
                        selection.setName(*(out.end()-1));
                        selection.setSaveName("SELECT_"+to_string(index)+".csv");
                        temp=out[1];
                        for(size_t i=0;i<temp.length();++i)
                            if(temp[i]==','||temp[i]=='('||temp[i]==')')
                                temp[i]=' ';
                        tokenize(temp,' ',out);
                        for(size_t i=0;i<out.size();++i)
                            selection.exec(selection.findParameter(out[i]),good);
                        if(good)
                            ++index;
                    }
                    else if(out.size()==5&&out[0]=="select"&&out[3]=="where")
                    {
                        selection.setName(out[2]);
                        selection.setSaveName("SELECT_"+to_string(index)+".csv");
                        tokenize(*(out.end()-1),'=',selection.where);
                        temp=out[1];
                        for(size_t i=0;i<temp.length();++i)
                            if(temp[i]==','||temp[i]=='('||temp[i]==')')
                                temp[i]=' ';
                        tokenize(temp,' ',out);
                        for(size_t i=0;i<out.size();++i)
                            selection.exec(selection.findParameter(out[i]),selection.findParameter(*(selection.where.begin())),*(selection.where.end()-1),good);
                        if(good)
                            ++index;
                    }
                    else if(out.size()==4&&out[0]=="select"&&out[1]=="all"&&out[2]=="form")
                    {
                        temp=out[3];
                        ofstream out("./query/SELECT_"+to_string(index)+".csv");
                        ifstream in("./tables/"+temp+".csv");
                        if(in.good())
                            while(getline(in,temp))
                                out<<temp<<'\n';
                        in.close();
                        out.close();
                    }
                }
            }
            f.close();
        }
    }
    return 0;
}