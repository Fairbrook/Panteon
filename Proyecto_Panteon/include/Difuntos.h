#ifndef DIFUNTOS_H
#define DIFUNTOS_H
#include <iostream>
#include <string.h>
#include <Propiedades.h>


class Difuntos
{
    public:
        Difuntos();
        virtual ~Difuntos();

        void setID(int);
        void setFecha(const char*);
        void setNombre(const char*);
        void setPropiedad(int);
        void setPropiedad(Propiedades);

        int getID();
        char* getFecha();
        char* getNombre();
        Propiedades getPropiedad();

        void _read(char*);
        char* _write();
        bool isNull();

        friend std::ostream& operator<< (std::ostream& os, const Difuntos& p);
        friend std::istream& operator>> (std::istream& is, Difuntos& p);

        bool operator== (Difuntos);

    private:
        char Nombre[80];
        char Fecha[10];
        int ID;
        Propiedades propiedad;
};

#endif // DIFUNTOS_H
