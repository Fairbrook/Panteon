#include "PropiedadesController.h"
#include "fstream"
#include "iomanip"
#include <stdio.h>
#include <stdlib.h>
#include <Propietarios.h>
#include <DifuntosController.h>
#include <Difuntos.h>
#include <PropietariosController.h>

PropiedadesController::PropiedadesController()
{
    strcpy(this->fileName,"propiedades.txt");
}

PropiedadesController::~PropiedadesController()
{
    //dtor
}

int PropiedadesController::getLastCont(){return this->lastContPropietarios; }

void PropiedadesController::create(){
    Propiedades p;
    std::cin>>p;
    std::ifstream test(this->fileName);
    std::ofstream* file;
    if(p.isNull()){
        std::cout << "Elemento no guardado" << std::endl;
        return;
    }
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
        file = new std::ofstream(this->fileName,std::ios::app);
        *file << p._write();
        file->close();
        std::cout << "Agregado Correctamente" << std::endl;
        return;
    }
}

Propiedades* PropiedadesController::read(){
    char data[200];
    short int cont = 0;
    Propiedades* result = NULL;
    std::ifstream file(this->fileName);
    if(file.fail()){
        this->lastCont = 0;
        file.close();
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

Propiedades* PropiedadesController::searchByPropietario(Propietarios propietario){
    Propiedades* data = this->read();
    Propiedades* result = NULL;
    int cont = 0;
    for(int i= 0; i < this->lastCont; i++){
        if(data[i].getPropietario() == propietario)cont++;
    }
    this->lastContPropietarios = cont;

    result = new Propiedades[cont];
    cont = 0;

    for(int i= 0; i < this->lastCont; i++){
        if(data[i].getPropietario()==propietario){
            result[cont] = data[i];
            cont++;
        }
    }
    return result;
}

void PropiedadesController::print(){
    Propiedades* data = this->read();
    if(this->lastCont==0){
            std::cout << "No hay datos" << std::endl;
            return;
    }
    for(int i = 0; i< this->lastCont; i++){
        std::cout << std::endl << std::endl;
        std::cout << data[i] << std::endl;
    }
}

bool PropiedadesController::updateBy(Propiedades p){
    Propiedades* data = this->read();
    std::ofstream file(this->fileName);
    for(int i = 0; i< this->lastCont; i++){
        if(data[i]==p)file << p._write();
        else file << data[i]._write();
    }
    file.close();
    return true;
}

void PropiedadesController::update(){

    int n_propiedad;
    short int limite_personas;
    float tamano;
    float predial;
    short int opc;
    char cadena[80];
    Propietarios aux;
    PropietariosController propietariosCtl;
    Propiedades* data = this->read();
    char curp[18];

    std::cout << "Introduzca el ID de la Propiedad a modificar: " ;
    std::cin >>n_propiedad;

    Propiedades p=this->searchN_propiedad(n_propiedad);
    if(p.isNull()){
        std::cout << "No se encontro"<<std::endl;
        return;
    }

    std::cout << "\n\nElemento seleccionado: \n" << p;
    std::cout << "\n-- Seleccione la propiedad a actualizar --\n";
    std::cout << "[1]Tamaño" << std::endl;
    std::cout << "[2]Limite de Personas" << std::endl;
    std::cout << "[3]Deuda Predial" << std::endl;
    std::cout << "[4]Tipo" << std::endl;
    std::cout << "[5]Propietario" << std::endl;
    std::cout << "[0]Salir" << std::endl;
    std::cout << "Opcion: ";
    std::cin >> opc;
    std::cin.ignore(1000,'\n');

    switch(opc){
        case 1:
            std::cout << "Introduzca el nuevo Tamaño: ";
            std::cin>>tamano;
            p.setTamano(tamano);
            break;
        case 2:
            std::cout << "Introduzca el nuevo Limite de personas: ";
            std::cin>>limite_personas;
            p.setLimite_personas(limite_personas);
            break;
        case 3:
            std::cout << "Introduzca el nuevo Predial: ";
            std::cin>>predial;
            p.setPredial(predial);
            break;
        case 4:
            std::cout << "Introduzca la nueva Edad: ";
            std::cin.getline(cadena,sizeof(cadena));
            p.setTipo(cadena);
            break;
        case 5:
            do{
                std::cout << "Introduzca El curp del propietario: ";
                std::cin.getline(curp,sizeof(curp));
                if (std::cin.fail()){
                    std::cin.clear();
                    break;
                }
                aux = propietariosCtl.searchCurp(curp);
                if(aux.isNull())std::cout << "\n**Error: El propietario no existe**\n\n";
                else p.setPropietario(aux);
            }while(aux.isNull());
            break;
    }

    this->updateBy(p);
    std::cout << "Cambios guardados" << std::endl;

}

bool PropiedadesController::deleteBy(Propiedades Propiedad){
    Propiedades* data = this->read();
    DifuntosController difuntosCtl;
    Difuntos* difuntos = difuntosCtl.searchByPropiedad(Propiedad);
    for(int i=0; i < difuntosCtl.getLastCont();i++){
        difuntosCtl.deleteBy(difuntos[i]);
    }
    std::ofstream file(this->fileName);
    for(int i = 0; i< this->lastCont; i++){
        if(data[i].getN_propiedad()!=Propiedad.getN_propiedad())
            file << data[i]._write();
    }
    file.close();
    return true;
}


void PropiedadesController::del(){
    int n_propiedad;
    char opc;

    std::cout << "Introduzca el numero de propiedad a eliminar: " ;
    std::cin >>n_propiedad;

    Propiedades p=this->searchN_propiedad(n_propiedad);
    if(p.isNull()){
        std::cout << "No se encontro"<<std::endl;
        return;
    }

    std::cout << "\n\nElemento seleccionado: \n" << p;
    std::cout << "\nSe borraran todos los datos relacionados\nRealmente desea eliminarlo?(s/n) ";
    std::cin>>opc;
    std::cin.ignore(1000,'\n');

    if(opc=='s'){
        this->deleteBy(p);
        std::cout << "Cambios guardados" << std::endl;
    }else std::cout << "Operacion cancelada" << std::endl;

}
