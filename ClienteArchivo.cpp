#include "ClienteArchivo.h"

ClienteArchivo::ClienteArchivo(std::string nombre){
    _nombreArchivo = nombre;
}

bool ClienteArchivo::guardar(Cliente &registro){

    FILE *pFile;
    bool escribio;

    pFile = fopen(_nombreArchivo.c_str(),"ab");
    if(pFile == nullptr){
            return false;
    }
    escribio = fwrite(&registro,sizeof(Cliente),1,pFile);

    fclose(pFile);
    return escribio;
}

bool ClienteArchivo::guardar(int pos, Cliente registro){

    FILE *pFile;
    bool escribio;

    pFile = fopen(_nombreArchivo.c_str(),"rb+");
    if(pFile == nullptr) return false;

    fseek(pFile,pos* sizeof(Cliente),0);

    escribio = fwrite(&registro,sizeof registro,1,pFile);

    fclose(pFile);
    return escribio;
}

bool ClienteArchivo::eliminar(int pos){
    Cliente registro = leer(pos);

    if(registro.getIdCliente() != -1){
        registro.setEstado(false);
        return guardar(pos,registro);
    }
    return false;
}

Cliente ClienteArchivo::leer(int pos){

    Cliente registro;
    FILE *pFile;
    pFile = fopen(_nombreArchivo.c_str(),"rb");

    if(pFile == nullptr) return Cliente();

    fseek(pFile,pos*sizeof(Cliente),SEEK_SET);
    fread(&registro,sizeof(Cliente),1,pFile);

    fclose(pFile);
    return registro;
}

int ClienteArchivo::getIdNuevo(){
    return getCantidadRegistro() +1;
}

int ClienteArchivo::getCantidadRegistro(){

    int cantRegistros;
    FILE *pFile;

    pFile = fopen(_nombreArchivo.c_str(),"rb");
    if(pFile == nullptr) return 0;

    fseek(pFile,0,SEEK_END);
    cantRegistros = ftell(pFile)/sizeof(Cliente);

   fclose(pFile);
   return cantRegistros;

}
int ClienteArchivo::LeerTodos(Cliente Clientes[], int cantidad){

    FILE *pFile;
    int result;

    pFile = fopen(_nombreArchivo.c_str(),"rb");
    if(pFile == nullptr) return 0;

    result = fread(Clientes,sizeof(Cliente),cantidad,pFile);

    fclose(pFile);
    return result;
}
bool ClienteArchivo::ValidarDni(std::string dni){
    FILE *pFile;
    Cliente registro;

    if(sizeof dni != 8)return false;

    pFile = fopen(_nombreArchivo.c_str(),"rb");
    if(pFile == nullptr) return true;

    while(fread(&registro,sizeof(Cliente),1,pFile)){
        if(registro.getDni() == dni){
            fclose(pFile);
            return false;
        }
    }
    fclose(pFile);
    return true;
}

int ClienteArchivo::buscarDni(std::string dni){

    Cliente registro;
    for(int i=0;i < getCantidadRegistro();i++){
        registro = leer(i);
        if(registro.getDni() == dni){
            return i;
        }
    }
    return -1;
}
