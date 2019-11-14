#ifndef PROPIEDADESCONTROLLER_H
#define PROPIEDADESCONTROLLER_H
#include <Propiedades.h>
#include <Propietarios.h>

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
        bool deleteBy(Propiedades);
        int getLastCont();
        Propiedades searchN_propiedad(int N);
        Propiedades* searchByPropietario(Propietarios);
        bool updateBy(Propiedades);

    protected:

    private:
        int lastCont;
        int lastContPropietarios;
        char fileName[20];
};

#endif // PROPIEDADESCONTROLLER_H
