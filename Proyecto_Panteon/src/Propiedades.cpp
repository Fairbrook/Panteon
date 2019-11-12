#include "Propiedades.h"
#include <string.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <typeinfo>

Propiedades::Propiedades()
{
     this->N_propiedad=0;
}

Propiedades::~Propiedades()
{
    //dtor
}

void Propiedades::setTamano(float tamano)
{
    this->Tamano=tamano;
}

void Propiedades::setLimite_personas(short int Lim)
{
    this->Limite_personas=Lim;
}

void Propiedades::setTipo(const char* tipo)
{
    strcpy(this->Tipo, tipo);
}

void Propiedades::setPredial(float predial)
{
    this->Predial=predial;
}

void Propiedades::setN_propiedad(int n)
{
    this->N_propiedad=n;

}

float Propiedades::getTamano(){return this->Tamano;}
short int Propiedades::getLimite_personas(){return this->Limite_personas;}
char* Propiedades::getTipo(){return this->Tipo;}
float Propiedades::getPredial(){return this->Predial;}
int Propiedades::getN_propiedad(){return this->N_propiedad;}

std::ostream& operator<< (std::ostream& os, const Propiedades& p){
    os << "Numero de Propiedad: " << p.N_propiedad <<
    std::endl << "Tamano: " << p.Tamano <<
    std::endl << "Limite de difuntos: " << p.Limite_personas <<
    std::endl << "Predial a pagar: " << p.Predial <<
    std::endl << "Tipo de Priopiedad: " << p.Tipo;
    return os;
}
