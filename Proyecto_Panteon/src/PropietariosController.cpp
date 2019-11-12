#include "PropietariosController.h"
#include "fstream"
#include "iomanip"

PropietariosController::PropietariosController()
{

}

PropietariosController::~PropietariosController()
{
    //dtor
}

void PropietariosController::create(){
    std::ifstream test("propietarios.txt");
    std::ofstream* file;
    if(test.fail())file = new std::ofstream("propietarios.txt");
    else file = new std::ofstream("propietarios.txt",std::ios::app);
    test.close();

    Propietarios p;
    std::cin>>p;
    *file << p._write();
    file->close();
}

Propietarios* PropietariosController::read(){
    char data[200];
    short int cont = 0;
    Propietarios* result;
    std::ifstream file("propietarios.txt");
    if(file.fail()){
        this->lastCont = 0;
        return result;
    }
    while(!file.eof()){
        file.getline(data,sizeof(data));
        cont++;
    }
    cont -= 1;
    result = new Propietarios[cont];
    file.clear();
    file.seekg(0, std::ios::beg);
    this->lastCont = cont;
    for(int i= 0; i < cont;i++){
        file.getline(data,sizeof(data));
        result[i]._read(data);
    }
    file.close();
    return result;
}

void PropietariosController::print(){
    Propietarios* data = this->read();
    for(int i = 0; i< this->lastCont; i++){
        std::cout << std::endl;
        std::cout << i << ")" << std::endl;
        std::cout << data[i] << std::endl;
    }
}

void PropietariosController::update(){
    Propietarios* data = this->read();
    char cadena[80];
    short int edad;
    short int id, opc;
    for(int i = 0; i< this->lastCont; i++){
        std::cout << std::endl;
        std::cout << "[" << i << "]" << std::endl;
        std::cout << data[i] << std::endl;
    }
    std::cout << "Seleccione el elemento a actualizar: " ;
    std::cin >>id;
    std::cout << "\n\nElemento seleccionado: \n" << data[id];
    std::cout << "\n-- Seleccione la propiedad a actualizar --\n";
    std::cout << "[1]Nombre" << std::endl;
    std::cout << "[2]CURP" << std::endl;
    std::cout << "[3]Domicilio" << std::endl;
    std::cout << "[4]Telefono" << std::endl;
    std::cout << "[5]Edad" << std::endl;
    std::cout << "[0]Salir" << std::endl;
    std::cout << "Opcion: ";
    std::cin >> opc;
    std::cin.ignore(1000,'\n');

    switch(opc){
        case 1:
            std::cout << "Introduzca el nuevo Nombre: ";
            std::cin.getline(cadena,sizeof(cadena));
            data[id].setNombre(cadena);
            break;
        case 2:
            std::cout << "Introduzca la nueva CURP: ";
            std::cin.getline(cadena,sizeof(cadena));
            data[id].setCurp(cadena);
            break;
        case 3:
            std::cout << "Introduzca el nuevo Domicilio: ";
            std::cin.getline(cadena,sizeof(cadena));
            data[id].setDomicilio(cadena);
            break;
        case 4:
            std::cout << "Introduzca el nuevo Telefono: ";
            std::cin.getline(cadena,sizeof(char[11]));
            data[id].setTelefono(cadena);
            break;
        case 5:
            std::cout << "Introduzca la nueva Edad: ";
            std::cin >> edad;
            data[id].setEdad(edad);
            break;
    }
    std::ofstream file("propietarios.txt");
    for(int i = 0; i< this->lastCont; i++){
        file << data[i]._write();
    }
    file.close();
    std::cout << "Cambios guardados";

}

void PropietariosController::del(){
    Propietarios* data = this->read();
    short int id;
    for(int i = 0; i< this->lastCont; i++){
        std::cout << std::endl;
        std::cout << "[" << i << "]" << std::endl;
        std::cout << data[i] << std::endl;
    }
    std::cout << "Seleccione el elemento a eliminar: " ;
    std::cin >>id;
    std::ofstream file("propietarios.txt");
    for(int i = 0; i< this->lastCont; i++){
        if(i!=id)file << data[i]._write();
    }
    file.close();
    std::cout << "Cambios guardados";
}
