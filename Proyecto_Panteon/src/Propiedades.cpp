#include "Propiedades.h"
#include <string.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <Propietarios.h>
#include <PropietariosController.h>
#include <PropiedadesController.h>


Propiedades::Propiedades()
{
     this->N_propiedad=0;
}

Propiedades::~Propiedades()
{
    //dtor
}


void Propiedades::setPropietario(char *propietario){
    PropietariosController controller;
    this->propietario = controller.searchCurp(propietario);
}

void Propiedades::setPropietario(Propietarios propietario){this->propietario = propietario;}
void Propiedades::setTamano(float tamano){this->Tamano=tamano;}
void Propiedades::setLimite_personas(short int Lim){this->Limite_personas=Lim;}
void Propiedades::setTipo(const char* tipo){strcpy(this->Tipo, tipo);}
void Propiedades::setPredial(float predial){this->Predial=predial;}
void Propiedades::setN_propiedad(int n){this->N_propiedad=n;}

float Propiedades::getTamano(){return this->Tamano;}
short int Propiedades::getLimite_personas(){return this->Limite_personas;}
char* Propiedades::getTipo(){return this->Tipo;}
float Propiedades::getPredial(){return this->Predial;}
int Propiedades::getN_propiedad(){return this->N_propiedad;}
Propietarios Propiedades::getPropietario(){return this->propietario;}

std::ostream& operator<< (std::ostream& os, const Propiedades& p){
    os << "Numero de Propiedad: " << p.N_propiedad <<
    std::endl << "Tama�o de la propiedad: " << p.Tamano <<
    std::endl << "Limite de difuntos: " << p.Limite_personas <<
    std::endl << "Predial a pagar: " << p.Predial <<
    std::endl << "Tipo de Priopiedad: " << p.Tipo;
    return os;
}

std::istream& operator>> (std::istream& is, Propiedades& p){
    char curp[18];
    Propiedades prueba;
    Propietarios aux;
    PropietariosController propietariosCtl;
    PropiedadesController propiedadesCtl;
    do{
        std::cout << "Introduzca el Numero de la propiedad: ";
        std::cin>>p.N_propiedad;
        if (std::cin.fail()){
            p.N_propiedad = 0;
            std::cin.clear();
            return is;
        }
        prueba = propiedadesCtl.searchN_propiedad(p.N_propiedad);
        if(!prueba.isNull())std::cout << "\n**Error: ID existente**\n\n";
    }while(!prueba.isNull());
    std::cout << "Introduzca Tama�o de la propiedad: ";
    std::cin >> p.Tamano;
    std::cout << "Limite de difuntos: ";
    std::cin>>p.Limite_personas;
    std::cout << "Introduzca el adeudo del predial: ";
    std::cin >> p.Predial;
    std::cout << "Introduzca Tipo de Propiedad: ";
    std::cin >> p.Tipo;
    std::cin.ignore(100,'\n');
    do{
        std::cout << "Introduzca El curp del propietario: ";
        std::cin.getline(curp,sizeof(curp));
        if (std::cin.fail()){
            p.N_propiedad = 0;
            std::cin.clear();
            return is;
        }
        aux = propietariosCtl.searchCurp(curp);
        if(aux.isNull())std::cout << "\n**Error: El propietario no existe**\n\n";
        else p.setPropietario(aux);
    }while(aux.isNull());
    return is;
}

char* Propiedades::_write(){
    char* data = new char[200];
    char n_propiedad[10];
    char tamano[10];
    char limite[2];
    char predial[8];

    itoa(this->N_propiedad,n_propiedad,10);
    itoa(this->Tamano,tamano,10);
    itoa(this->Limite_personas,limite,10);
    itoa(this->Predial,predial,10);

    strcpy(data, n_propiedad);
    strcat(data,"|");
    strcat(data,tamano);
    strcat(data,"|");
    strcat(data,limite);
    strcat(data,"|");
    strcat(data,predial);
    strcat(data,"|");
    strcat(data,this->Tipo);
    strcat(data,"|");
    strcat(data,this->propietario.getCurp());
    strcat(data,"\n");
    return data;
}

void Propiedades::_read(char info[]){
    char* data;

    data = strtok(info,"|");
    this->N_propiedad = atoi(data);

    data = strtok(NULL,"|");
    this->Tamano = atof(data);

    data = strtok(NULL,"|");
    this->Limite_personas = atoi(data);

    data = strtok(NULL,"|");
    this->Predial = atof(data);

    data = strtok(NULL,"|");
    strcpy(this->Tipo,data);

    data = strtok(NULL,"|");
    this->setPropietario(data);

}

bool Propiedades::isNull(){
    if(this->N_propiedad==0)return true;
    else return false;
}

Propiedades Propiedades::operator= (Propiedades p){
    this->N_propiedad = p.N_propiedad;
    this->Tamano = p.Tamano;
    this->Limite_personas = p.Limite_personas;
    this->Predial = p.Predial;
    strcpy(this->Tipo,p.Tipo);
    this->propietario = p.propietario;
    return *this;
}

bool Propiedades::operator==(Propiedades p){
    return(this->N_propiedad==p.N_propiedad);
}
