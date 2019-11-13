#include "Difuntos.h"
#include <string.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <typeinfo>


Difuntos::Difuntos()
{
    this->ID=false;
}

Difuntos::~Difuntos()
{
    //dtor
}

void Difuntos::setFecha(const char* fecha)
{
    strcpy(this->Fecha,fecha);
}

void Difuntos::setID(int id)
{
    this->ID=id;
}

void Difuntos::setNombre(const char* nombre)
{
   strcpy(this->Nombre,nombre);
}

char* Difuntos::getNombre(){return this->Nombre;}
char* Difuntos::getFecha(){return this->Fecha;}
int Difuntos::getID(){return this->ID;}

std::ostream& operator<< (std::ostream& os, const Difuntos& p)
{
    os << "Nombre: " << p.Nombre <<
    std::endl << "ID: " << p.ID <<
    std::endl << "Fecha de difuncion: " << p.Fecha;
    return os;
}

std::istream& operator>> (std::istream& is, Difuntos& p)
{
    std::cin.ignore(100,'\n');
    std::cout << "Introduzca el Nombre: ";
    std::cin.getline(p.Nombre,sizeof(p.Nombre));
    std::cout << "Introduzca ID: ";
    std::cin >> p.ID;
    std::cin.ignore(100,'\n');
    std::cout << "Introduzca la fecha de difuncion (dd-mm-aa):";
    std::cin.getline(p.Fecha,sizeof(p.Fecha));
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
    strcat(data,"\n");
    return data;
}

void Difuntos::_read(char info[])
{
    char* data;

    data = strtok(info,"|");
    strcpy(this->Nombre,data);

    data = strtok(NULL,"|");
    this->ID = atoi(data);

    data = strtok(NULL,"|");
    strcpy(this->Fecha,data);
}

bool Difuntos::isNull()
{
    if(this->ID==0)return true;
    else return false;
}












