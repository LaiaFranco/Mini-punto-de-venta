#include "DetalleVenArchivo.h"

DetalleVenArchivo::DetalleVenArchivo(std::string nombre)
:_nombreArchivo(nombre){
}

bool DetalleVenArchivo::guardar(DetalleVenta registro){

    FILE *pFile;
    bool escribio;

    pFile = fopen(_nombreArchivo.c_str(),"ab");
    if(pFile == nullptr) return false;

    escribio = fwrite(&registro,sizeof(DetalleVenta),1,pFile);

    fclose(pFile);
    return escribio;
}

bool DetalleVenArchivo::guardar(int pos, DetalleVenta registro){

    FILE *pFile;
    bool escribio;

    pFile = fopen(_nombreArchivo.c_str(),"rb+");
    if(pFile == nullptr) return false;

    fseek(pFile,pos* sizeof(DetalleVenta),0);

    escribio = fwrite(&registro,sizeof registro,1,pFile);

    fclose(pFile);
    return escribio;
}



DetalleVenta DetalleVenArchivo::leer(int pos){

    DetalleVenta registro;
    FILE *pFile;
    pFile = fopen(_nombreArchivo.c_str(),"rb");

    if(pFile == nullptr) return DetalleVenta();

    fseek(pFile,pos*sizeof(DetalleVenta),SEEK_SET);
    fread(&registro,sizeof(DetalleVenta),1,pFile);

    fclose(pFile);
    return registro;
}

int DetalleVenArchivo::getIdNuevo(){
    return getCantidadRegistro() +1;
}

int DetalleVenArchivo::getCantidadRegistro(){

    int cantRegistros;
    FILE *pFile;

    pFile = fopen(_nombreArchivo.c_str(),"rb");

    fseek(pFile,0,SEEK_END);
    cantRegistros = ftell(pFile)/sizeof(DetalleVenta);

   fclose(pFile);
   return cantRegistros;

}
int DetalleVenArchivo::LeerTodos(DetalleVenta registros[], int cantidad){

    FILE *pFile;
    int result;

    pFile = fopen(_nombreArchivo.c_str(),"rb");
    if(pFile == nullptr) return 0;

    result = fread(registros,sizeof(DetalleVenta),cantidad,pFile);

    fclose(pFile);
    return result;
}

int DetalleVenArchivo::buscarId(int id){

    DetalleVenta registro;
    for(int i=0;i < getCantidadRegistro();i++){
        registro = leer(i);
        if(registro.getIdDetalle() == id){
            return i;
        }
    }
    return -1;
}
