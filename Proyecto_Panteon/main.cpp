#include <iostream>
#include <stdlib.h>
#include <Propietarios.h>
#include <PropietariosController.h>

int main()
{
    short int opc;
    PropietariosController pController;
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
                std::cout << std::endl << "Introduzca la curp a buscar"<<std::endl;
                std::cin >> curp;
                Propietarios p = pController.searchCurp(curp);
                if(!p.isNull())std::cout << std::endl << p << std::endl;
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
        return 0;
}
