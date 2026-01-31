#include "DescuentoArchivo.h"

DescuentoArchivo::DescuentoArchivo(std::string nombre)
:_nombreArchivo(nombre){
}

bool DescuentoArchivo::guardar(Descuento registro){

    FILE *pFile;
    bool escribio;

    pFile = fopen(_nombreArchivo.c_str(),"ab");
    if(pFile = nullptr) return false;

    escribio = fwrite(&registro,sizeof(Descuento),1,pFile);

    fclose(pFile);
    return escribio;
}

bool DescuentoArchivo::guardar(int pos, Descuento registro){

    FILE *pFile;
    bool escribio;

    pFile = fopen(_nombreArchivo.c_str(),"rb+");
    if(pFile == nullptr) return false;

    fseek(pFile,pos* sizeof(Descuento),0);

    escribio = fwrite(&registro,sizeof registro,1,pFile);

    fclose(pFile);
    return escribio;
}

bool DescuentoArchivo::eliminar(int pos){
    Descuento registro = leer(pos);

    if(registro.getIdDescuento() != -1){
        registro.setEstado(false);
        return guardar(pos,registro);
    }
    return false;
}

Descuento DescuentoArchivo::leer(int pos){

    Descuento registro;
    FILE *pFile;
    pFile = fopen(_nombreArchivo.c_str(),"rb");

    if(pFile == nullptr) return Descuento();

    fseek(pFile,pos*sizeof(Descuento),SEEK_SET);
    fread(&registro,sizeof(Descuento),1,pFile);

    fclose(pFile);
    return registro;
}

int DescuentoArchivo::getIdNuevo(){
    return getCantidadRegistro() +1;
}

int DescuentoArchivo::getCantidadRegistro(){

    int cantRegistros;
    FILE *pFile;

    pFile = fopen(_nombreArchivo.c_str(),"rb");

    fseek(pFile,0,SEEK_END);
    cantRegistros = ftell(pFile)/sizeof(Descuento);

   fclose(pFile);
   return cantRegistros;

}
int DescuentoArchivo::LeerTodos(Descuento registros[], int cantidad){

    FILE *pFile;
    int result;

    pFile = fopen(_nombreArchivo.c_str(),"rb");
    if(pFile == nullptr) return 0;

    result = fread(registros,sizeof(Descuento),cantidad,pFile);

    fclose(pFile);
    return result;
}

int DescuentoArchivo::buscarId(int id){

    Descuento registro;
    for(int i=0;i < getCantidadRegistro();i++){
        registro = leer(i);
        if(registro.getIdDescuento() == id){
            return i;
        }
    }
    return -1;
}
