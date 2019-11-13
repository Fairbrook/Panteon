#ifndef PROPIEDADESCONTROLLER_H
#define PROPIEDADESCONTROLLER_H
#include <Propiedades.h>

class PropiedadesController
{
    public:
        PropiedadesController();
        virtual ~PropiedadesController();

        void create();
        Propiedades* read();
        void print();
        void update();
        void del();
        Propiedades searchN_propiedad(int N);

    protected:

    private:
        int lastCont;
        char fileName[20];
};

#endif // PROPIEDADESCONTROLLER_H
