#ifndef PROPIEDADES_H
#define PROPIEDADES_H
#include <iostream>
#include <string.h>
#include <Propietarios.h>



class Propiedades
{
    public:
        Propiedades();
        virtual ~Propiedades();

        void setTamano(float);
        void setLimite_personas(short int);
        void setTipo(const char*);
        void setPredial(float);
        void setN_propiedad(int);
        void setPropietario(char *);
        void setPropietario(Propietarios);

        float getTamano();
        short int getLimite_personas();
        char* getTipo();
        float getPredial();
        int getN_propiedad();
        Propietarios getPropietario();

        void _read(char*);
        char* _write();
        bool isNull();

        friend std::ostream& operator<< (std::ostream& os, const Propiedades& p);
        friend std::istream& operator>> (std::istream& is, Propiedades& p);

        Propiedades operator= (Propiedades);
        bool operator== (Propiedades);

    private:
        float Tamano;
        short int Limite_personas;
        char Tipo[6];
        float Predial;
        int N_propiedad;
        Propietarios propietario;
};

#endif // PROPIEDADES_H
