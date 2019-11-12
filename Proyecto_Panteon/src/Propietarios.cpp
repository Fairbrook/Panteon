#include "Propietarios.h"
#include <string.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <typeinfo>

Propietarios::Propietarios()
{
    strcpy(this->Curp,"none");
}

Propietarios::~Propietarios()
{
    //dtor
}

void Propietarios::setNombre(const char* nombre){
    strcpy(this->Nombre,nombre);
}
void Propietarios::setDomicilio(const char* domicilio){
    strcpy(this->Domicilio,domicilio);
}
void Propietarios::setTelefono(const char* telefono){
    strcpy(this->Telefono,telefono);
}
void Propietarios::setCurp(const char* curp){
    strcpy(this->Curp,curp);
}
void Propietarios::setEdad(short int edad){
    this->Edad = edad;
}
char* Propietarios::getNombre(){return this->Nombre;}
char* Propietarios::getDomicilio(){return this->Domicilio;}
char* Propietarios::getTelefono(){return this->Telefono;}
char* Propietarios::getCurp(){return this->Curp;}
short int Propietarios::getEdad(){return this->Edad;}

std::ostream& operator<< (std::ostream& os, const Propietarios& p){
    os << "Nombre: " << p.Nombre <<
    std::endl << "Curp: " << p.Curp <<
    std::endl << "Domicilio: " << p.Domicilio <<
    std::endl << "Telefono: " << p.Telefono <<
    std::endl << "Edad: " << p.Edad;
    return os;
}

std::istream& operator>> (std::istream& is, Propietarios& p){
    std::cin.ignore(100,'\n');
    std::cout << "Introduzca el Nombre: ";
    std::cin.getline(p.Nombre,sizeof(p.Nombre));
    std::cout << "Introduzca el Curp: ";
    std::cin >> p.Curp;
    std::cin.ignore(100,'\n');
    std::cout << "Introduzca el Domicilio: ";
    std::cin.getline(p.Domicilio,sizeof(p.Domicilio));
    std::cout << "Introduzca el Telefono: ";
    std::cin >> p.Telefono;
    std::cout << "Introduzca la Edad: ";
    std::cin >> p.Edad;
    return is;
}

char* Propietarios::_write(){
    char* data = new char[200];
    char aux[3];
    itoa(this->Edad,aux,10);
    strcpy(data, this->Nombre);
    strcat(data,"|");
    strcat(data,this->Curp);
    strcat(data,"|");
    strcat(data,this->Domicilio);
    strcat(data,"|");
    strcat(data,this->Telefono);
    strcat(data,"|");
    strcat(data,aux);
    strcat(data,"\n");
    return data;
}

void Propietarios::_read(char info[]){
    char* data;

    data = strtok(info,"|");
    strcpy(this->Nombre,data);

    data = strtok(NULL,"|");
    strcpy(this->Curp,data);

    data = strtok(NULL,"|");
    strcpy(this->Domicilio,data);

    data = strtok(NULL,"|");
    strcpy(this->Telefono,data);

    data = strtok(NULL,"|");
    this->Edad = atoi(data);
}

bool Propietarios::isNull(){
    if(strcmp(this->Curp,"none")==0)return true;
    else return false;
}
