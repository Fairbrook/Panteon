#include "Difuntos.h"
#include <string.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <Propiedades.h>
#include <PropiedadesController.h>
#include <DifuntosController.h>


Difuntos::Difuntos()
{
    this->ID=false;
}

Difuntos::~Difuntos()
{
    //dtor
}

void Difuntos::setFecha(const char* fecha){strcpy(this->Fecha,fecha);}
void Difuntos::setID(int id){this->ID=id;}
void Difuntos::setNombre(const char* nombre){strcpy(this->Nombre,nombre);}
void Difuntos::setPropiedad(Propiedades p){this->propiedad = p;}
void Difuntos::setPropiedad(int id){
    PropiedadesController controller;
    this->propiedad = controller.searchN_propiedad(id);
}

char* Difuntos::getNombre(){return this->Nombre;}
char* Difuntos::getFecha(){return this->Fecha;}
int Difuntos::getID(){return this->ID;}
Propiedades Difuntos::getPropiedad(){return this->propiedad;}

std::ostream& operator<< (std::ostream& os, const Difuntos& p)
{
    os << "ID: " << p.ID <<
    std::endl << "Nombre: " << p.Nombre <<
    std::endl << "Fecha de difuncion: " << p.Fecha;
    return os;
}

std::istream& operator>> (std::istream& is, Difuntos& d)
{
    int idPropiedad;
    PropiedadesController propiedadesCtl;
    DifuntosController difuntosCtl;
    Propiedades p;
    Difuntos test;
    do{
        std::cout << "Introduzca ID: ";
        std::cin >> d.ID;
        test= difuntosCtl.searchID(d.ID);
        if (std::cin.fail()){
            std::cin.clear();
            return is;
        }
        if(!test.isNull())std::cout << "\n**Error: ID existente**\n\n";
    }while(!test.isNull());

    std::cin.ignore(100,'\n');
    std::cout << "Introduzca el Nombre: ";
    std::cin.getline(d.Nombre,sizeof(d.Nombre));
    std::cout << "Introduzca la fecha de difuncion (dd-mm-aa):";
    std::cin.getline(d.Fecha,sizeof(d.Fecha));
    do{
        std::cout << "Introduzca el numero de la propiedad: ";
        std::cin >> idPropiedad;
        if (std::cin.fail()){
            std::cin.clear();
            return is;
        }
        p = propiedadesCtl.searchN_propiedad(idPropiedad);
        difuntosCtl.searchByPropiedad(p);
        if(p.getPredial()>0)
            std::cout << "\n**Error: Presenta adeudo en predial**\n\n";
        else if(difuntosCtl.getLastCont()>=p.getLimite_personas()){
            std::cout << "\n**Error: La propiedad seleccionada esta llena**\n\n";
        }else{
            d.propiedad = p;
            break;
        }
    }while(true);
    std::cin.ignore(100,'\n');
    return is;
}

char* Difuntos::_write()
{
    char* data = new char[200];
    char aux[10];
    itoa(this->ID,aux,10);
    strcpy(data, this->Nombre);
    strcat(data,"|");
    strcat(data,aux);
    strcat(data,"|");
    strcat(data,this->Fecha);
    strcat(data,"|");
    itoa(this->propiedad.getN_propiedad(),aux,10);
    strcat(data,aux);
    strcat(data,"\n");
    return data;
}

void Difuntos::_read(char info[])
{
    char* data;
    int id;

    data = strtok(info,"|");
    strcpy(this->Nombre,data);

    data = strtok(NULL,"|");
    this->ID = atoi(data);

    data = strtok(NULL,"|");
    strcpy(this->Fecha,data);

    data = strtok(NULL,"|");
    id = atoi(data);
    this->setPropiedad(id);
}

bool Difuntos::isNull()
{
    if(this->ID==0)return true;
    else return false;
}


bool Difuntos::operator==(Difuntos d){
    return(this->ID==d.ID);
}
