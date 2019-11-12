#include "PropietariosController.h"
#include "fstream"
#include "iomanip"

PropietariosController::PropietariosController()
{
    strcpy(this->fileName,"propietarios.txt");
}

PropietariosController::~PropietariosController()
{
    //dtor
}

void PropietariosController::create(){
    Propietarios p;
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
        Propietarios prueba = this->searchCurp(p.getCurp());
        if(prueba.isNull()){
            file = new std::ofstream(this->fileName,std::ios::app);
            *file << p._write();
            file->close();
            std::cout << "Agregado Correctamente" << std::endl;
            return;
        }
    }
    std::cout << "Curp existente" << std::endl;
}

Propietarios* PropietariosController::read(){
    char data[200];
    short int cont = 0;
    Propietarios* result = NULL;
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

Propietarios PropietariosController::searchCurp(char* curp){
    Propietarios* data = this->read();
    for(int i= 0; i < this->lastCont; i++){
        if(strcasecmp(data[i].getCurp(),curp)==0)return data[i];
    }
    Propietarios p;
    return p;
}

void PropietariosController::print(){
    Propietarios* data = this->read();
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

void PropietariosController::update(){
    char curp[18];
    short int edad;
    short int opc;
    char cadena[80];
    Propietarios* data = this->read();

    std::cout << "Introduzca la curp del propietario a modificar: " ;
    std::cin >>curp;

    Propietarios p=this->searchCurp(curp);
    if(p.isNull()){
        std::cout << "No se encontro"<<std::endl;
        return;
    }

    std::cout << "\n\nElemento seleccionado: \n" << p;
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
            p.setNombre(cadena);
            break;
        case 2:
            std::cout << "Introduzca la nueva CURP: ";
            std::cin.getline(cadena,sizeof(cadena));
            p.setCurp(cadena);
            break;
        case 3:
            std::cout << "Introduzca el nuevo Domicilio: ";
            std::cin.getline(cadena,sizeof(cadena));
            p.setDomicilio(cadena);
            break;
        case 4:
            std::cout << "Introduzca el nuevo Telefono: ";
            std::cin.getline(cadena,sizeof(char[11]));
            p.setTelefono(cadena);
            break;
        case 5:
            std::cout << "Introduzca la nueva Edad: ";
            std::cin >> edad;
            p.setEdad(edad);
            break;
    }

    std::ofstream file(this->fileName);

    for(int i = 0; i< this->lastCont; i++){
        file << p._write();
    }
    file.close();
    std::cout << "Cambios guardados" << std::endl;

}

void PropietariosController::del(){
    char curp[18];
    char opc;
    Propietarios* data = this->read();

    std::cout << "Introduzca la curp del propietario a eliminar: " ;
    std::cin >>curp;

    Propietarios p=this->searchCurp(curp);
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
            if(strcasecmp(data[i].getCurp(),curp)!=0)
                file << data[i]._write();
        }
        file.close();
        std::cout << "Cambios guardados" << std::endl;
    }else std::cout << "Operacion cancelada" << std::endl;

}
