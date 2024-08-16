#include <iostream>
#include "QuadTree.h"
#include <vector>
#include "chrono"
#include "utility"
#include "fstream"


using namespace std;

int main(){

    ifstream file;
    file.open("worldcitiespop_fixed.csv");

    string line;
    string pop;
    string lat;
    string longitud;

    getline(file,line,';');
    getline(file,line,';');
    getline(file,line,';');
    getline(file,line,';');
    getline(file,line,';');
    getline(file,line,';');
    getline(file,line,';');

    int x=0;

    Point b(0,0);
    Point t(180,180);

    QuadTree* quad=new QuadTree(180,b,t);

    Point p(5,5);
    

    while(x<1500000){


        getline(file,line,';');
        getline(file,line,';');
        getline(file,line,';');
        getline(file,line,';');
        getline(file,line,';');
        pop = line;
        getline(file,line,';');
        lat = line;
        getline(file,line,';');
        longitud = line;

        float f1=stof(lat);
        float f2=stof(longitud);

        p.setX(f1);
        p.setY(f2);

        quad->insert(p,x);

        x++;
    }

    cout<<quad->AggregateRegion(b,5000000)<<endl;
    cout<<quad->countRegion(b,5000000);

    return 0;
}