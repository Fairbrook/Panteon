#ifndef PROPIETARIOS_H
#define PROPIETARIOS_H
#include <iostream>
#include <string.h>

class Propietarios
{
    public:
        Propietarios();
        ~Propietarios();

        void setNombre(const char*);
        void setDomicilio(const char*);
        void setTelefono(const char*);
        void setCurp(const char*);
        void setEdad(short int);

        char* getNombre();
        char* getDomicilio();
        char* getTelefono();
        char* getCurp();
        short int getEdad();

        void _read(char*);
        char* _write();
        bool isNull();

        friend std::ostream& operator<< (std::ostream& os, const Propietarios& p);
        friend std::istream& operator>> (std::istream& is, Propietarios& p);

        Propietarios operator= (Propietarios);
        bool operator== (Propietarios);

    private:
        char Nombre[80];
        char Domicilio[80];
        char Telefono[11];
        short int Edad;
        char Curp[18];

};

#endif // PROPIETARIOS_H
