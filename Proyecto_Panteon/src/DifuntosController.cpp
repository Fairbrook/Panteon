#include "DifuntosController.h"
#include "fstream"
#include "iomanip"

DifuntosController::DifuntosController()
{
    strcpy(this->fileName,"difuntos.txt");
}

DifuntosController::~DifuntosController()
{
    //dtor
}

void DifuntosController::create(){
    Difuntos p;
    std::cin>>p;
    std::ifstream test(this->fileName);
    std::ofstream* file;
    if(test.fail()){
        test.close();
        file = new std::ofstream(this->fileName);
        *file << p._write();
        file->close();
        std::cout << "Agregado Correctamente" << std::endl;
        return;
    }
    else{
        test.close();
        Difuntos prueba = this->searchID(p.getID());
        if(prueba.isNull()){
            file = new std::ofstream(this->fileName,std::ios::app);
            *file << p._write();
            file->close();
            std::cout << "Agregado Correctamente" << std::endl;
            return;
        }
    }
    std::cout << "ID existente" << std::endl;
}

Difuntos* DifuntosController::read(){
    char data[200];
    short int cont = 0;
    Difuntos* result = NULL;
    std::ifstream file(this->fileName);
    if(file.fail()){
        this->lastCont = 0;
        std::cout << "No hay datos" << std::endl;
        return result;
    }
    while(!file.eof()){
        file.getline(data,sizeof(data));
        cont++;
    }
    cont -= 1;
    result = new Difuntos[cont];
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

Difuntos DifuntosController::searchID(int id){
    Difuntos* data = this->read();
    for(int i= 0; i < this->lastCont; i++){
        if(data[i].getID()==id)return data[i];
    }
    Difuntos p;
    return p;
}

void DifuntosController::print(){
    Difuntos* data = this->read();
    if(this->lastCont==0){
            std::cout << "No hay datos" << std::endl;
            return;
    }
    for(int i = 0; i< this->lastCont; i++){
        std::cout << std::endl;
        std::cout << i << ")" << std::endl;
        std::cout << data[i] << std::endl;
    }
}

void DifuntosController::update(){
    int id;
    short int opc;
    char cadena[80];
    Difuntos* data = this->read();

    std::cout << "Introduzca el ID del propietario a modificar: " ;
    std::cin >>id;

    Difuntos p=this->searchID(id);
    if(p.isNull()){
        std::cout << "No se encontro"<<std::endl;
        return;
    }

    std::cout << "\n\nElemento seleccionado: \n" << p;
    std::cout << "\n-- Seleccione la propiedad a actualizar --\n";
    std::cout << "[1]Nombre" << std::endl;
    std::cout << "[2]ID" << std::endl;
    std::cout << "[3]Fecha difuncion" << std::endl;
    std::cout << "[0]Salir" << std::endl;
    std::cout << "Opcion: ";
    std::cin >> opc;
    std::cin.ignore(1000,'\n');

    switch(opc){
        case 1:
            std::cout << "Introduzca el nuevo Nombre: ";
            std::cin.getline(cadena,sizeof(cadena));
            p.setNombre(cadena);
            break;
        case 2:
            std::cout << "Introduzca la nueva ID: ";
            std::cin>>id;
            p.setID(id);
            break;
        case 3:
            std::cout << "Introduzca la nueva Fecha: ";
            std::cin.getline(cadena,sizeof(cadena));
            p.setFecha(cadena);
            break;
    }

    std::ofstream file(this->fileName);

    for(int i = 0; i< this->lastCont; i++){
        file << p._write();
    }
    file.close();
    std::cout << "Cambios guardados" << std::endl;

}

void DifuntosController::del(){
    int id;
    char opc;
    Difuntos* data = this->read();

    std::cout << "Introduzca la ID del propietario a eliminar: " ;
    std::cin >>id;

    Difuntos p=this->searchID(id);
    if(p.isNull()){
        std::cout << "No se encontro"<<std::endl;
        return;
    }

    std::cout << "\n\nElemento seleccionado: \n" << p;
    std::cout << "\nRealmente desea eliminarlo?(s/n) ";
    std::cin>>opc;
    std::cin.ignore(1000,'\n');

    if(opc=='s'){
        std::ofstream file(this->fileName);
        for(int i = 0; i< this->lastCont; i++){
            if(data[i].getID()!=id)
                file << data[i]._write();
        }
        file.close();
        std::cout << "Cambios guardados" << std::endl;
    }else std::cout << "Operacion cancelada" << std::endl;

}
