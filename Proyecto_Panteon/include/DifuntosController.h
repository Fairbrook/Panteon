#ifndef DIFUNTOSCONTROLLER_H
#define DIFUNTOSCONTROLLER_H
#include "Difuntos.h"

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
        Difuntos searchID (int);

    private:
        int lastCont;
        char fileName[20];
};

#endif // DIFUNTOSCONTROLLER_H
