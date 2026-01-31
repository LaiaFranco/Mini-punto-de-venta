#include "VentaArchivo.h"

VentaArchivo::VentaArchivo(std::string nombre)
:_nombreArchivo(nombre){
}

bool VentaArchivo::guardar(Venta registro){

    FILE *pFile;
    bool escribio;

    pFile = fopen(_nombreArchivo.c_str(),"ab");
    if(pFile == nullptr) return false;

    escribio = fwrite(&registro,sizeof(Venta),1,pFile);

    fclose(pFile);
    return escribio;
}

bool VentaArchivo::guardar(int pos, Venta registro){

    FILE *pFile;
    bool escribio;

    pFile = fopen(_nombreArchivo.c_str(),"rb+");
    if(pFile == nullptr) return false;

    fseek(pFile,pos* sizeof(Venta),0);

    escribio = fwrite(&registro,sizeof registro,1,pFile);

    fclose(pFile);
    return escribio;
}



Venta VentaArchivo::leer(int pos){

    Venta registro;
    FILE *pFile;
    pFile = fopen(_nombreArchivo.c_str(),"rb");

    if(pFile == nullptr) return Venta();

    fseek(pFile,pos*sizeof(Venta),SEEK_SET);
    fread(&registro,sizeof(Venta),1,pFile);

    fclose(pFile);
    return registro;
}

int VentaArchivo::getIdNuevo(){
    return getCantidadRegistro() +1;
}

int VentaArchivo::getCantidadRegistro(){

    int cantRegistros;
    FILE *pFile;

    pFile = fopen(_nombreArchivo.c_str(),"rb");
    if(pFile == nullptr) return 0;

    fseek(pFile,0,SEEK_END);
    cantRegistros = ftell(pFile)/sizeof(Venta);

   fclose(pFile);
   return cantRegistros;

}
int VentaArchivo::LeerTodos(Venta registros[], int cantidad){

    FILE *pFile;
    int result;

    pFile = fopen(_nombreArchivo.c_str(),"rb");
    if(pFile == nullptr) return 0;

    result = fread(registros,sizeof(Venta),cantidad,pFile);

    fclose(pFile);
    return result;
}

int VentaArchivo::buscarId(int id){

    Venta registro;
    for(int i=0;i < getCantidadRegistro();i++){
        registro = leer(i);
        if(registro.getNumTransaccion() == id){
            return i;
        }
    }
    return -1;
}
