#include <iostream>
#include <Propietarios.h>
#include <PropietariosController.h>

int main()
{
    PropietariosController controller;
    controller.create();
    controller.print();
    controller.update();
    controller.del();
    return 0;
}
