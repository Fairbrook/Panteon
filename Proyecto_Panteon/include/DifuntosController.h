#ifndef DIFUNTOSCONTROLLER_H
#define DIFUNTOSCONTROLLER_H
#include "Difuntos.h"
#include "Propiedades.h"

class DifuntosController
{
    public:
        DifuntosController();
        virtual ~DifuntosController();
        void create();
        Difuntos* read();
        void print();
        void update();
        void del();
        bool deleteBy(Difuntos);
        Difuntos searchID (int);
        Difuntos* searchByPropiedad(Propiedades);
        int getLastCont();
        bool updateBy(Difuntos);

    private:
        int lastCont;
        int lastContPropiedades;
        char fileName[20];
};

#endif // DIFUNTOSCONTROLLER_H
