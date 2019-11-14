#include "DifuntosController.h"
#include "fstream"
#include "iomanip"
#include "Difuntos.h"
#include "PropiedadesController.h"

DifuntosController::DifuntosController()
{
    strcpy(this->fileName,"difuntos.txt");
}

DifuntosController::~DifuntosController()
{
    //dtor
}

int DifuntosController::getLastCont(){return this->lastContPropiedades;}

void DifuntosController::create(){
    Difuntos p;
    std::cin>>p;
    std::ifstream test(this->fileName);
    std::ofstream* file;
    if(p.isNull()||p.getPropiedad().isNull()){
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

Difuntos* DifuntosController::read(){
    char data[200];
    short int cont = 0;
    Difuntos* result = NULL;
    std::ifstream file(this->fileName);
    if(file.fail()){
        this->lastCont = 0;
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

Difuntos* DifuntosController::searchByPropiedad(Propiedades propiedad){
    Difuntos* data = this->read();
    Difuntos* result = NULL;
    int cont = 0;
    for(int i= 0; i < this->lastCont; i++){
        if(data[i].getPropiedad() == propiedad)cont++;
    }
    this->lastContPropiedades = cont;

    result = new Difuntos[cont];
    cont = 0;

    for(int i= 0; i < this->lastCont; i++){
        if(data[i].getPropiedad()==propiedad){
            result[cont] = data[i];
            cont++;
        }
    }
    return result;
}

void DifuntosController::print(){
    Difuntos* data = this->read();
    if(this->lastCont==0){
            std::cout << "No hay datos" << std::endl;
            return;
    }
    for(int i = 0; i< this->lastCont; i++){
        std::cout << std::endl;
        std::cout << data[i] << std::endl;
    }
    std::cout << std::endl;
}

bool DifuntosController::updateBy(Difuntos d){
    Difuntos* data = this->read();
    std::ofstream file(this->fileName);
    for(int i = 0; i< this->lastCont; i++){
        if(data[i]==d)file << d._write();
        else file << data[i]._write();
    }
    file.close();
    return true;
}

void DifuntosController::update(){
    int id;
    short int opc;
    char cadena[80];
    Difuntos* data = this->read();
    Propiedades aux;
    PropiedadesController propiedadesCtl;
    int idPropiedad;

    std::cout << "Introduzca el ID del difunto a modificar: " ;
    std::cin >>id;

    Difuntos p=this->searchID(id);
    if(p.isNull()){
        std::cout << "No se encontro"<<std::endl;
        return;
    }

    std::cout << "\n\nElemento seleccionado: \n" << p;
    std::cout << "\n-- Seleccione la propiedad a actualizar --\n";
    std::cout << "[1]Nombre" << std::endl;
    std::cout << "[2]Fecha difuncion" << std::endl;
    std::cout << "[3]Propiedad" << std::endl;
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
            std::cout << "Introduzca la nueva Fecha: ";
            std::cin.getline(cadena,sizeof(cadena));
            p.setFecha(cadena);
            break;
        case 3:
            do{
                std::cout << "Introduzca el numero de la propiedad: ";
                std::cin >> idPropiedad;
                if (std::cin.fail()){
                    std::cin.clear();
                    break;
                }
                aux = propiedadesCtl.searchN_propiedad(idPropiedad);
                this->searchByPropiedad(aux);
                if(aux==p.getPropiedad())break;
                if(aux.getPredial()>0)
                    std::cout << "\n**Error: Presenta adeudo en predial**\n\n";
                else if(this->getLastCont()>=aux.getLimite_personas()){
                    std::cout << "\n**Error: La propiedad seleccionada esta llena**\n\n";
                }else{
                    p.setPropiedad(aux);
                    std::cout << aux.getN_propiedad();
                    break;
                }
            }while(true);
            break;
    }

    this->updateBy(p);
    std::cout << "Cambios guardados" << std::endl;

}

bool DifuntosController::deleteBy(Difuntos difunto){
    Difuntos* data = this->read();
    std::ofstream file(this->fileName);
    for(int i = 0; i< this->lastCont; i++){
        if(data[i].getID()!=difunto.getID())
            file << data[i]._write();
    }
    file.close();
}

void DifuntosController::del(){
    int id;
    char opc;

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
        this->deleteBy(p);
        std::cout << "Cambios guardados" << std::endl;
    }else std::cout << "Operacion cancelada" << std::endl;

}
