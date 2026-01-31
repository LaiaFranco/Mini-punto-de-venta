#include "ProveedorArchivo.h"

ProveedorArchivo::ProveedorArchivo(std::string nombre)
:_nombreArchivo(nombre){
}

bool ProveedorArchivo::guardar(Proveedor registro){

    FILE *pFile;
    bool escribio;

    pFile = fopen(_nombreArchivo.c_str(),"ab");
    if(pFile == nullptr) return false;

    escribio = fwrite(&registro,sizeof(Proveedor),1,pFile);

    fclose(pFile);
    return escribio;
}

bool ProveedorArchivo::guardar(int pos, Proveedor registro){

    FILE *pFile;
    bool escribio;

    pFile = fopen(_nombreArchivo.c_str(),"rb+");
    if(pFile == nullptr) return false;

    fseek(pFile,pos* sizeof(Proveedor),0);

    escribio = fwrite(&registro,sizeof registro,1,pFile);

    fclose(pFile);
    return escribio;
}

bool ProveedorArchivo::eliminar(int pos){
    Proveedor registro = leer(pos);

    if(registro.getCuit() != ""){
        registro.setEstado(false);
        return guardar(pos,registro);
    }
    return false;
}

Proveedor ProveedorArchivo::leer(int pos){

    Proveedor registro;
    FILE *pFile;
    pFile = fopen(_nombreArchivo.c_str(),"rb");

    if(pFile == nullptr) return Proveedor();

    fseek(pFile,pos*sizeof(Proveedor),SEEK_SET);
    fread(&registro,sizeof(Proveedor),1,pFile);

    fclose(pFile);
    return registro;
}


int ProveedorArchivo::getCantidadRegistro(){

    int cantRegistros;
    FILE *pFile;

    pFile = fopen(_nombreArchivo.c_str(),"rb");

    fseek(pFile,0,SEEK_END);
    cantRegistros = ftell(pFile)/sizeof(Proveedor);

   fclose(pFile);
   return cantRegistros;
}

int ProveedorArchivo::LeerTodos(Proveedor registros[], int cantidad){

    FILE *pFile;
    int result;

    pFile = fopen(_nombreArchivo.c_str(),"rb");
    if(pFile == nullptr) return 0;

    result = fread(registros,sizeof(Proveedor),cantidad,pFile);

    fclose(pFile);
    return result;
}

int ProveedorArchivo::buscarCuit(std::string cuit){
    Proveedor registro;
    for(int i=0;i < getCantidadRegistro();i++){
        registro = leer(i);
        if(registro.getCuit() == cuit){
            return i;
        }
    }
    return -1;
}
