#ifndef PROPIETARIOSCONTROLLER_H
#define PROPIETARIOSCONTROLLER_H
#include "Propietarios.h"

class PropietariosController
{
    public:
        PropietariosController();
        virtual ~PropietariosController();
        void create();
        Propietarios* read();
        void print();
        void update();
        void del();
        Propietarios searchCurp(char*);

        bool updateBy(Propietarios);
    protected:

    private:
        int lastCont;
        char fileName[20];

};

#endif // PROPIETARIOSCONTROLLER_H
