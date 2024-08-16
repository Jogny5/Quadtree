#include "QuadTree.h"
#include <vector>
#include <string>
#include <cmath>
#include <iostream>

using namespace std;


QuadTree::QuadTree(int size, Point t, Point b):topLeft(t),botRight(b),tam(size){

    points=0;
    this->PrimerCuad=nullptr;
    this->SegundoCuad=nullptr;
    this->TercerCuad=nullptr;
    this->CuartoCuad=nullptr;
    this->n=new Nodo(t,0);

}

QuadTree::~QuadTree(){

}

int QuadTree::totalPoints(QuadTree* quad){

    points=preOrderTotalPoints(this,0);
    return points;    

}

int QuadTree::preOrderTotalPoints(QuadTree* qtree, int tam){

    if(qtree->n->getColor()==true && qtree->PrimerCuad==nullptr){

        return 1;

    }

    else if(qtree->n->getColor()==false){

        return 0;
        
    }else{
        tam=tam+preOrderTotalPoints(qtree->PrimerCuad,tam);
        tam=tam+preOrderTotalPoints(qtree->SegundoCuad,tam);
        tam=tam+preOrderTotalPoints(qtree->TercerCuad,tam);
        tam=tam+preOrderTotalPoints(qtree->CuartoCuad,tam);
        return 0;
    }

}

int QuadTree::totalNodes(QuadTree* quad){

    int x=preOrderTotalNodes(this,1);
    return x;    

}

int QuadTree::preOrderTotalNodes(QuadTree* qtree, int tam){

    if(qtree->n->getColor()==true && qtree->PrimerCuad==nullptr){

        return 1;

    }

    else if(qtree->n->getColor()==false){

        return 1;
        
    }else{
        tam++;
        tam=tam+preOrderTotalNodes(qtree->PrimerCuad,tam);
        tam=tam+preOrderTotalNodes(qtree->SegundoCuad,tam);
        tam=tam+preOrderTotalNodes(qtree->TercerCuad,tam);
        tam=tam+preOrderTotalNodes(qtree->CuartoCuad,tam);

        return 1;
    }

}

void QuadTree::insert(Point p, int data){

    if(PrimerCuad==nullptr || SegundoCuad==nullptr || TercerCuad==nullptr || CuartoCuad==nullptr){

        Point newtopleft(0,0);
        Point newbotRight(180,180);
        this->PrimerCuad=new QuadTree(tam/2,newtopleft,newbotRight);

        newtopleft.setX(0);
        newtopleft.setY(1);
        newbotRight.setX(180);
        newbotRight.setY(180);
        this->TercerCuad=new QuadTree(tam/2,newtopleft,newbotRight);

        newtopleft.setX(1);
        newtopleft.setY(0);
        newbotRight.setX(180);
        newbotRight.setY(180);
        this->SegundoCuad=new QuadTree(tam/2,newtopleft,newbotRight);

        newtopleft.setX(1);
        newtopleft.setY(1);
        newbotRight.setX(180);
        newbotRight.setY(180);
        this->CuartoCuad=new QuadTree(tam/2,newtopleft,newbotRight);

        n->setColor();

    } 
    

    if(p.getX()>=0){
        if(p.getY()>=0){    
            insertQuad(p,data,PrimerCuad);    
        }else{
            
            insertQuad(p,data,TercerCuad); 
        }
    }else{
        if(p.getY()>0){ 
            
            insertQuad(p,data,SegundoCuad);
        }else{
            
            insertQuad(p,data,CuartoCuad);
        }
    }
    
}


void QuadTree::insertQuad(Point p, int data, QuadTree* quad){

    QuadTree* actual;
    if (((int)botRight.getX() - (int)topLeft.getX()) <= 1
        || (botRight.getY() - topLeft.getY()) <= 1) {
        
            n->setColor();
            n->setPoblacion(data);
            n->setLatitud(p.getX());
            n->setLongitud(p.getY());
           

        
        
           
        return;
        
    }else if(quad!=nullptr){
        
        actual=quad;
        actual->insertQuad(p,data,nullptr);

    }else{

        if (PrimerCuad == NULL || SegundoCuad==NULL || TercerCuad==NULL || CuartoCuad==NULL){     
                Point newtopleft(0,0);
                Point newbotRight(0,0);                        

                newtopleft.setX(topLeft.getX());
                newtopleft.setY(topLeft.getY());
                newbotRight.setX(botRight.getX()/2);
                newbotRight.setY(botRight.getY()/2);

                this->PrimerCuad=new QuadTree(tam/2,newtopleft,newbotRight);

                newtopleft.setX(abs(botRight.getX()+topLeft.getX())/2);
                newbotRight.setY(abs(botRight.getY())/2);

                this->SegundoCuad=new QuadTree(tam/2,newtopleft,newbotRight);

                newtopleft.setY(abs(botRight.getY()+topLeft.getY())/2);
                newbotRight.setX(abs(botRight.getX())/2);

                this->TercerCuad=new QuadTree(tam/2,newtopleft,newbotRight);

                newtopleft.setX(abs(botRight.getX()+topLeft.getX())/2);
                newtopleft.setY(abs(botRight.getY()+topLeft.getY())/2);
                
                this->CuartoCuad=new QuadTree(tam/2,newtopleft,newbotRight);
                
        }

     
        if ((abs(topLeft.getX()) + abs(botRight.getX())) / 2 >= abs(p.getX())) {
            //primer cuadrante     
            if ((abs(topLeft.getY()) + abs(botRight.getY())) / 2 >= abs(p.getY())) {                       
            
                n->setColor();
                actual=PrimerCuad;

                actual->insertQuad(p,data,nullptr);
                
            }
 
            //tercer cuadrante
            else {

                Point punto(p.getX(),p.getY()-tam/2);            
                n->setColor();
                actual=TercerCuad;
                TercerCuad->insertQuad(punto,data,nullptr);
                
            }
        }
        else {
            //segundo cuadrante
            if ((abs(topLeft.getY()) + abs(botRight.getY())) / 2 >= abs(p.getY())) {
            
                Point punto(p.getX()-tam/2,p.getY());
                
                n->setColor();
                actual=SegundoCuad;
                SegundoCuad->insertQuad(punto,data,nullptr);
            }
 
            //cuarto cuadrante
            else {
            
                Point punto(p.getX()-tam/2,p.getY()-tam/2);
                
                n->setColor();
                actual=CuartoCuad;
                CuartoCuad->insertQuad(punto,data,nullptr);
                
            }
        }

    }
    
}


vector<Nodo* > QuadTree::list(){

    lista.clear();
    preOrderList(this,this);
    return lista;
}

void QuadTree::preOrderList(QuadTree* qtree, QuadTree* original){

    if(qtree->n->getColor()==true && PrimerCuad==nullptr && SegundoCuad==nullptr && TercerCuad==nullptr && CuartoCuad==nullptr){

        original->pushLista(qtree->n);

    }

    else{
        
        if(qtree->PrimerCuad!=nullptr){
            preOrderList(qtree->PrimerCuad,original);
        }

        if(qtree->SegundoCuad!=nullptr){
            preOrderList(qtree->SegundoCuad,original);
        }

        if(qtree->TercerCuad!=nullptr){
            preOrderList(qtree->TercerCuad,original);
        }

        if(qtree->CuartoCuad!=nullptr){
            preOrderList(qtree->CuartoCuad,original);
        }

    }

}


int QuadTree::countRegion(Point p, int d){

    int suma=0;

    if(p.getX()+d>=0){
        if(p.getY()+d>=0){          //tiene puntos en el primer cuadrante
         
            int dxRight=p.getX()+d;
            int dxLeft=p.getX()-d;
            if(dxLeft<0){
                dxLeft=0;
            }
            int dyUp=p.getY()+d;
            int dyDown=p.getY()-d;
            if(dyDown<0){
                dyDown=0;
            }

            suma=suma+preOrderCountRegion(PrimerCuad,dxLeft,dxRight,dyUp,dyDown);
        }
        if(p.getY()-d<0){           //tiene puntos en el tercer cuadrante 

            int dxRight=p.getX()+d;
            int dxLeft=p.getX()-d;
            if(dxLeft<0){
                dxLeft=0;
            }
            int dyUp=p.getY()+d;
            int dyDown=p.getY()-d;
            if(dyUp>=0){
                dyUp=0;
            }
            suma=suma+preOrderCountRegion(TercerCuad,dxLeft,dxRight,dyUp,dyDown);
        }
    }
    if(p.getX()-d<0){         
        if(p.getY()+d>=0){          //tiene puntos en el segundo cuadrante

            int dxRight=p.getX()+d;
            int dxLeft=p.getX()-d;
            if(dxRight>=0){
                dxRight=-1;
            }
            int dyUp=p.getY()+d;
            int dyDown=p.getY()-d;
            if(dyDown<0){
                dyDown=0;
            }

            suma=suma+preOrderCountRegion(SegundoCuad,dxLeft,dxRight,dyUp,dyDown);
        }
        if(p.getY()-d<0){           //tiene puntos en el cuarto cuadrante

            int dxRight=p.getX()+d;
            int dxLeft=p.getX()-d;
            if(dxRight>=0){
                dxRight=-1;
            }
            int dyUp=p.getY()+d;
            int dyDown=p.getY()-d;
            if(dyUp>=0){
                dyUp=-1;
            }

            suma=suma+preOrderCountRegion(CuartoCuad,dxLeft,dxRight,dyUp,dyDown);
        }
    }


    return suma;

}

int QuadTree::preOrderCountRegion(QuadTree* qtree, int dxLeft, int dxRight, int dyUp, int dyDown){ 
    

    if(qtree->n->getColor()==true && qtree->PrimerCuad==nullptr){

        return 1;

    }

    else if(qtree->n->getColor()==false){

        return 0;
        
    }else{

       

        if(abs(qtree->botRight.getX()-qtree->topLeft.getX())/2>=abs(dxLeft) || 
        abs(qtree->botRight.getX()-qtree->topLeft.getX())/2>=abs(dxRight)){          

            if(abs(qtree->botRight.getY()-qtree->topLeft.getY())/2>=abs(dyUp) || 
            abs(qtree->botRight.getY()-qtree->topLeft.getY())/2>=abs(dyDown)){

                if(abs(qtree->botRight.getY()-qtree->topLeft.getY())/2>=abs(dyUp) || 
                abs(qtree->botRight.getY()-qtree->topLeft.getY())/2>=abs(dyDown)){

                    suma=suma+preOrderCountRegion(qtree->PrimerCuad,dxLeft,dxRight,dyUp,dyDown);

                }
            }

            if(abs(qtree->botRight.getY()-qtree->topLeft.getY())/2<abs(dyUp) || 
            abs(qtree->botRight.getY()-qtree->topLeft.getY())/2<abs(dyDown)){

                if(abs(qtree->botRight.getY()-qtree->topLeft.getY())/2<abs(dyUp) || 
                abs(qtree->botRight.getY()-qtree->topLeft.getY())/2<abs(dyDown)){

                    suma=suma+preOrderCountRegion(qtree->TercerCuad,dxLeft,dxRight,dyUp,dyDown);

                }
            }
            
        }

        if(abs(qtree->botRight.getX()-qtree->topLeft.getX())/2<abs(dxLeft) || 
        abs(qtree->botRight.getX()-qtree->topLeft.getX())/2<abs(dxRight)){          

            if(abs(qtree->botRight.getY()-qtree->topLeft.getY())/2>=abs(dyUp) || 
            abs(qtree->botRight.getY()-qtree->topLeft.getY())/2>=abs(dyDown)){

                if(abs(qtree->botRight.getY()-qtree->topLeft.getY())/2>=abs(dyUp) || 
                abs(qtree->botRight.getY()-qtree->topLeft.getY())/2>=abs(dyDown)){

                    suma=suma+preOrderCountRegion(qtree->SegundoCuad,dxLeft,dxRight,dyUp,dyDown);

                }
            }

            if(abs(qtree->botRight.getY()-qtree->topLeft.getY())/2<abs(dyUp) || 
            abs(qtree->botRight.getY()-qtree->topLeft.getY())/2<abs(dyDown)){

                if(abs(qtree->botRight.getY()-qtree->topLeft.getY())/2<abs(dyUp) || 
                abs(qtree->botRight.getY()-qtree->topLeft.getY())/2<abs(dyDown)){

                    suma=suma+preOrderCountRegion(qtree->CuartoCuad,dxLeft,dxRight,dyUp,dyDown);

                }
            }
            
        }

        return suma;

        
    }


}

int QuadTree::AggregateRegion(Point p, int d){

    int suma=0;

    if(p.getX()+d>=0){
        if(p.getY()+d>=0){          //tiene puntos en el primer cuadrante
         
            int dxRight=p.getX()+d;
            int dxLeft=p.getX()-d;
            if(dxLeft<0){
                dxLeft=0;
            }
            int dyUp=p.getY()+d;
            int dyDown=p.getY()-d;
            if(dyDown<0){
                dyDown=0;
            }

            suma=suma+preOrderAggregateRegion(PrimerCuad,dxLeft,dxRight,dyUp,dyDown);
        }
        if(p.getY()-d<0){           //tiene puntos en el tercer cuadrante 

            int dxRight=p.getX()+d;
            int dxLeft=p.getX()-d;
            if(dxLeft<0){
                dxLeft=0;
            }
            int dyUp=p.getY()+d;
            int dyDown=p.getY()-d;
            if(dyUp>=0){
                dyUp=0;
            }
            suma=suma+preOrderAggregateRegion(TercerCuad,dxLeft,dxRight,dyUp,dyDown);
        }
    }
    if(p.getX()-d<0){         
        if(p.getY()+d>=0){          //tiene puntos en el segundo cuadrante

            int dxRight=p.getX()+d;
            int dxLeft=p.getX()-d;
            if(dxRight>=0){
                dxRight=-1;
            }
            int dyUp=p.getY()+d;
            int dyDown=p.getY()-d;
            if(dyDown<0){
                dyDown=0;
            }

            suma=suma+preOrderAggregateRegion(SegundoCuad,dxLeft,dxRight,dyUp,dyDown);
        }
        if(p.getY()-d<0){           //tiene puntos en el cuarto cuadrante

            int dxRight=p.getX()+d;
            int dxLeft=p.getX()-d;
            if(dxRight>=0){
                dxRight=-1;
            }
            int dyUp=p.getY()+d;
            int dyDown=p.getY()-d;
            if(dyUp>=0){
                dyUp=-1;
            }

            suma=suma+preOrderAggregateRegion(CuartoCuad,dxLeft,dxRight,dyUp,dyDown);
        }
    }


    return suma;

}

int QuadTree::preOrderAggregateRegion(QuadTree* qtree, int dxLeft, int dxRight, int dyUp, int dyDown){
    
    
    if(qtree->n->getColor()==true && qtree->PrimerCuad==nullptr){

        return qtree->n->getPoblacion();

    }

    else if(qtree->n->getColor()==false){

        return 0;
        
    }else{

        

        if(abs(qtree->botRight.getX()-qtree->topLeft.getX())/2>=abs(dxLeft) || 
        abs(qtree->botRight.getX()-qtree->topLeft.getX())/2>=abs(dxRight)){          

            if(abs(qtree->botRight.getY()-qtree->topLeft.getY())/2>=abs(dyUp) || 
            abs(qtree->botRight.getY()-qtree->topLeft.getY())/2>=abs(dyDown)){

                if(abs(qtree->botRight.getY()-qtree->topLeft.getY())/2>=abs(dyUp) || 
                abs(qtree->botRight.getY()-qtree->topLeft.getY())/2>=abs(dyDown)){

                    suma=suma+preOrderCountRegion(qtree->PrimerCuad,dxLeft,dxRight,dyUp,dyDown);

                }
            }

            if(abs(qtree->botRight.getY()-qtree->topLeft.getY())/2<abs(dyUp) || 
            abs(qtree->botRight.getY()-qtree->topLeft.getY())/2<abs(dyDown)){

                if(abs(qtree->botRight.getY()-qtree->topLeft.getY())/2<abs(dyUp) || 
                abs(qtree->botRight.getY()-qtree->topLeft.getY())/2<abs(dyDown)){

                    suma=suma+preOrderCountRegion(qtree->TercerCuad,dxLeft,dxRight,dyUp,dyDown);

                }
            }
            
        }

        if(abs(qtree->botRight.getX()-qtree->topLeft.getX())/2<abs(dxLeft) || 
        abs(qtree->botRight.getX()-qtree->topLeft.getX())/2<abs(dxRight)){          

            if(abs(qtree->botRight.getY()-qtree->topLeft.getY())/2>=abs(dyUp) || 
            abs(qtree->botRight.getY()-qtree->topLeft.getY())/2>=abs(dyDown)){

                if(abs(qtree->botRight.getY()-qtree->topLeft.getY())/2>=abs(dyUp) || 
                abs(qtree->botRight.getY()-qtree->topLeft.getY())/2>=abs(dyDown)){

                    suma=suma+preOrderCountRegion(qtree->SegundoCuad,dxLeft,dxRight,dyUp,dyDown);

                }
            }

            if(abs(qtree->botRight.getY()-qtree->topLeft.getY())/2<abs(dyUp) || 
            abs(qtree->botRight.getY()-qtree->topLeft.getY())/2<abs(dyDown)){

                if(abs(qtree->botRight.getY()-qtree->topLeft.getY())/2<abs(dyUp) || 
                abs(qtree->botRight.getY()-qtree->topLeft.getY())/2<abs(dyDown)){

                    suma=suma+preOrderCountRegion(qtree->CuartoCuad,dxLeft,dxRight,dyUp,dyDown);

                }
            }
            
        }

        return suma;

        
    }


}

void QuadTree::pushLista(Nodo* n){

    lista.push_back(n);

}