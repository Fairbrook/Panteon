#ifndef PROPIETARIOSCONTROLLER_H
#define PROPIETARIOSCONTROLLER_H
#include "Propietarios.h"

class PropietariosController
{
    public:
        PropietariosController();
        virtual ~PropietariosController();
        void create();
        Propietarios*read();
        void print();
        void update();
        void del();

    protected:

    private:
        int lastCont;

};

#endif // PROPIETARIOSCONTROLLER_H
