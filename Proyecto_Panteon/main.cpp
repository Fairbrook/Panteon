#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <Propietarios.h>
#include <PropietariosController.h>
#include <Propiedades.h>
#include <PropiedadesController.h>
#include <Difuntos.h>
#include <DifuntosController.h>

void Menu_Propietarios();

void Menu_Propiedades();

void Menu_Difuntos();

int main()
{
    short int opc;

    do
    {
        system("cls");
        std::cout << "--- Sistema Panteon --" << std::endl << std::endl;

        std::cout << "[1]Menu Propietarios" << std::endl;
        std::cout << "[2]Menu Propiedades" << std::endl;
        std::cout << "[3]Menu Difuntos" << std::endl<< std::endl;

        std::cout << "[10]Salir" << std::endl;
        std::cout << "Seleccione una opcion: ";
        std::cin >> opc;
        std::cin.ignore(100,'\n');
        switch(opc)
        {
        case 1:
            Menu_Propietarios();
            break;
        case 2:
            Menu_Propiedades();
            break;
        case 3:
            Menu_Difuntos();
            break;

        }

    }while(opc!=10);

    return 0;
}


void Menu_Propietarios()
{
    short int opc;
    PropietariosController pController;
    PropiedadesController propiedadesCntl;
    do{
        system("cls");
        std::cout << "--- Sistema Panteon --" << std::endl << std::endl;
        std::cout << "* Propietarios: " << std::endl;
        std::cout << "[1]Ver todos los propietarios" << std::endl;
        std::cout << "[2]Agregar un propietario" << std::endl;
        std::cout << "[3]Buscar un propietario" << std::endl;
        std::cout << "[4]Modificar un propietario" << std::endl;
        std::cout << "[5]Eliminar un propietario" << std::endl << std::endl;

        std::cout << "[10]Salir" << std::endl;
        std::cout << "Seleccione una opcion: ";
        std::cin >> opc;
        std::cin.ignore(100,'\n');
        switch(opc){
            case 1:
                pController.print();
                break;
            case 2:
                std::cout << std::endl;
                pController.create();
                break;
            case 3:{
                char curp[80];
                std::cout << std::endl << "Introduzca la curp a buscar: ";
                std::cin >> curp;
                Propietarios p = pController.searchCurp(curp);

                if(!p.isNull()){
                        std::cout << std::endl << p << std::endl;
                        Propiedades* prop = propiedadesCntl.searchByPropietario(p);
                        std::cout << std::endl << "Propiedades: " << propiedadesCntl.getLastCont() << std::endl;
                        for(int i=0; i < propiedadesCntl.getLastCont();i++){
                            std::cout << prop[i] << std::endl << std::endl;
                        }
                }
                else std::cout << std::endl << "No se encontro" << std::endl;}
                break;
            case 4:
                pController.update();
                break;
            case 5:
                pController.del();
                break;
        }
        system("pause");
    }while(opc!=10);

}


void Menu_Propiedades()
{
  short int opc;
    PropiedadesController pController;
    DifuntosController difuntosCtl;
    do{
        system("cls");
        std::cout << "--- Sistema Panteon --" << std::endl << std::endl;
        std::cout << "* Propiedades: " << std::endl;
        std::cout << "[1]Ver todas las propiedades" << std::endl;
        std::cout << "[2]Agregar una propiedad" << std::endl;
        std::cout << "[3]Buscar una propiedad" << std::endl;
        std::cout << "[4]Modificar una propiedad" << std::endl;
        std::cout << "[5]Eliminar una propiedad" << std::endl << std::endl;

        std::cout << "[10]Salir" << std::endl;
        std::cout << "Seleccione una opcion: ";
        std::cin >> opc;
        std::cin.ignore(100,'\n');
        switch(opc){
            case 1:
                pController.print();
                break;
            case 2:
                std::cout << std::endl;
                pController.create();
                break;
            case 3:{
                int N_propiedad;
                std::cout << std::endl << "Introduzca el numero de la propiedad buscar: ";
                std::cin >> N_propiedad;
                Propiedades p = pController.searchN_propiedad(N_propiedad);
                if(!p.isNull()){
                        std::cout << std::endl << p << std::endl;
                        std::cout << std::endl << "Propietario: " << std::endl;
                        std::cout << p.getPropietario() << std::endl;
                        Difuntos* difuntos = difuntosCtl.searchByPropiedad(p);
                        std::cout << std::endl << "Difuntos: " << std::endl;
                        for(int i=0; i < difuntosCtl.getLastCont();i++){
                            std::cout << difuntos[i] << std::endl << std::endl;
                        }
                }
                else std::cout << std::endl << "No se encontro" << std::endl;}
                break;
            case 4:
                pController.update();
                break;
            case 5:
                pController.del();
                break;
        }
        system("pause");
    }while(opc!=10);


}

void Menu_Difuntos()
{
short int opc;
    DifuntosController pController;
    do{
        system("cls");
        std::cout << "--- Sistema Panteon --" << std::endl << std::endl;
        std::cout << "* Difuntos: " << std::endl;
        std::cout << "[1]Ver todos los Difuntos" << std::endl;
        std::cout << "[2]Agregar un Difunto" << std::endl;
        std::cout << "[3]Buscar un Difunto" << std::endl;
        std::cout << "[4]Modificar un Difunto" << std::endl;
        std::cout << "[5]Eliminar un Difunto" << std::endl << std::endl;

        std::cout << "[10]Salir" << std::endl;
        std::cout << "Seleccione una opcion: ";
        std::cin >> opc;
        std::cin.ignore(100,'\n');
        switch(opc){
            case 1:
                pController.print();
                break;
            case 2:
                std::cout << std::endl;
                pController.create();
                break;
            case 3:{
                int id;
                std::cout << std::endl << "Introduzca el ID del difunto a buscar: "<<std::endl;
                std::cin >> id;
                Difuntos p = pController.searchID(id);
                if(!p.isNull()){
                        std::cout << std::endl << p << std::endl;
                        std::cout << std::endl << "Propiedad: " << std::endl;
                        std::cout << p.getPropiedad() << std::endl;
                }
                else std::cout << std::endl << "No se encontro" << std::endl;}
                break;
            case 4:
                pController.update();
                break;
            case 5:
                pController.del();
                break;
        }
        system("pause");
    }while(opc!=10);
}





