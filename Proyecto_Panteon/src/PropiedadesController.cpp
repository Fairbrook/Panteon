#include "PropiedadesController.h"
#include "fstream"
#include "iomanip"
#include <stdio.h>
#include <stdlib.h>

PropiedadesController::PropiedadesController()
{
    strcpy(this->fileName,"propiedades.txt");
}

PropiedadesController::~PropiedadesController()
{
    //dtor
}

void PropiedadesController::create(){
    Propiedades p;
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
        Propiedades prueba = this->searchN_propiedad(p.getN_propiedad());
        if(prueba.isNull()){
            file = new std::ofstream(this->fileName,std::ios::app);
            *file << p._write();
            file->close();
            std::cout << "Agregado Correctamente" << std::endl;
            return;
        }
    }
    std::cout << "Numero de propiedad existente" << std::endl;
}


Propiedades* PropiedadesController::read(){
    char data[200];
    short int cont = 0;
    Propiedades* result = NULL;
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
    result = new Propiedades[cont];
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

Propiedades PropiedadesController::searchN_propiedad(int N){
    Propiedades* data = this->read();


    for(int i= 0; i < this->lastCont; i++){

        if(data[i].getN_propiedad()==N)return data[i];
    }
    Propiedades p;
    return p;
}

void PropiedadesController::print(){
    Propiedades* data = this->read();
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


void PropiedadesController::update(){

    int n_propiedad;
    short int limite_personas;
    float tamano;
    float predial;
    short int opc;
    char cadena[80];
    Propiedades* data = this->read();

    std::cout << "Introduzca la curp del propietario a modificar: " ;
    std::cin >>n_propiedad;

    Propiedades p=this->searchN_propiedad(n_propiedad);
    if(p.isNull()){
        std::cout << "No se encontro"<<std::endl;
        return;
    }

    std::cout << "\n\nElemento seleccionado: \n" << p;
    std::cout << "\n-- Seleccione la propiedad a actualizar --\n";
    std::cout << "[1]Numero de Propiedad" << std::endl;
    std::cout << "[2]Tamaño" << std::endl;
    std::cout << "[3]Limite de Personas" << std::endl;
    std::cout << "[4]Deuda Predial" << std::endl;
    std::cout << "[5]Tipo" << std::endl;
    std::cout << "[0]Salir" << std::endl;
    std::cout << "Opcion: ";
    std::cin >> opc;
    std::cin.ignore(1000,'\n');

    switch(opc){
        case 1:
            std::cout << "Introduzca el nuevo Numero de propiedad: ";
            std::cin>>n_propiedad;
            p.setN_propiedad(n_propiedad);
            break;
        case 2:
            std::cout << "Introduzca el nuevo Tamaño: ";
            std::cin>>tamano;
            p.setTamano(tamano);
            break;
        case 3:
            std::cout << "Introduzca el nuevo Limite de personas: ";
            std::cin>>limite_personas;
            p.setLimite_personas(limite_personas);
            break;
        case 4:
            std::cout << "Introduzca el nuevo Predial: ";
            std::cin>>predial;
            p.setPredial(predial);
            break;
        case 5:
            std::cout << "Introduzca la nueva Edad: ";
            std::cin.getline(cadena,sizeof(cadena));
            p.setTipo(cadena);
            break;
    }

    std::ofstream file(this->fileName);

    for(int i = 0; i< this->lastCont; i++){
        file << p._write();
    }
    file.close();
    std::cout << "Cambios guardados" << std::endl;

}


void PropiedadesController::del(){
    int n_propiedad;
    char opc;
    Propiedades* data = this->read();

    std::cout << "Introduzca el numero de propiedad a eliminar: " ;
    std::cin >>n_propiedad;

    Propiedades p=this->searchN_propiedad(n_propiedad);
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
            if(data[i].getN_propiedad()!=n_propiedad)
                file << data[i]._write();
        }
        file.close();
        std::cout << "Cambios guardados" << std::endl;
    }else std::cout << "Operacion cancelada" << std::endl;

}
