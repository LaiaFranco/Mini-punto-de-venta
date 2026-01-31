#include "CategoriaArchivo.h"


CategoriaArchivo::CategoriaArchivo(std::string nombre)
:_nombreArchivo(nombre){
}

bool CategoriaArchivo::guardar(Categoria registro){

    FILE *pFile;
    bool escribio;

    pFile = fopen(_nombreArchivo.c_str(),"ab");
    if(pFile == nullptr) return false;

    escribio = fwrite(&registro,sizeof(Categoria),1,pFile);

    fclose(pFile);
    return escribio;
}

bool CategoriaArchivo::guardar(int pos, Categoria registro){

    FILE *pFile;
    bool escribio;

    pFile = fopen(_nombreArchivo.c_str(),"rb+");
    if(pFile == nullptr) return false;

    fseek(pFile,pos* sizeof(Categoria),0);

    escribio = fwrite(&registro,sizeof registro,1,pFile);

    fclose(pFile);
    return escribio;
}

bool CategoriaArchivo::eliminar(int pos){
    Categoria registro = leer(pos);

    if(registro.getNumeroCategoria() != -1){
        registro.setEstado(false);
        return guardar(pos,registro);
    }
    return false;
}

int CategoriaArchivo::existeCategoria(std::string nombre){

    Categoria registro;
    for(int i=0; i<getCantidadRegistro();i++){
            registro = leer(i);
            if(registro.getNombre() == nombre && registro.getEstado()) return 0;
            if(registro.getNombre() == nombre && !registro.getEstado()) return 1;
    }
    return 2;
}

Categoria CategoriaArchivo::leer(int pos){

    Categoria registro;
    FILE *pFile;
    pFile = fopen(_nombreArchivo.c_str(),"rb");

    if(pFile == nullptr) return Categoria();

    fseek(pFile,pos*sizeof(Categoria),SEEK_SET);
    fread(&registro,sizeof(Categoria),1,pFile);

    fclose(pFile);
    return registro;
}

int CategoriaArchivo::getIdNuevo(){
    return getCantidadRegistro() +1;
}

int CategoriaArchivo::getCantidadRegistro(){

    int cantRegistros;
    FILE *pFile;

    pFile = fopen(_nombreArchivo.c_str(),"rb");
    if(pFile == nullptr) return 0;

    fseek(pFile,0,SEEK_END);
    cantRegistros = ftell(pFile)/sizeof(Categoria);

   fclose(pFile);
   return cantRegistros;

}
int CategoriaArchivo::LeerTodos(Categoria registros[], int cantidad){

    FILE *pFile;
    int result;

    pFile = fopen(_nombreArchivo.c_str(),"rb");
    if(pFile == nullptr) return 0;

    result = fread(registros,sizeof(Categoria),cantidad,pFile);

    fclose(pFile);
    return result;
}

int CategoriaArchivo::buscarId(int id){

    Categoria registro;
    for(int i=0;i < getCantidadRegistro();i++){
        registro = leer(i);
        if(registro.getNumeroCategoria() == id){
            return i;
        }
    }
    return -1;
}
