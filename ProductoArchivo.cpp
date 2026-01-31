#include "ProductoArchivo.h"

ProductoArchivo::ProductoArchivo(std::string nombre)
:_nombreArchivo(nombre){
}

bool ProductoArchivo::guardar(Producto registro){

    FILE *pFile;
    bool escribio;

    pFile = fopen(_nombreArchivo.c_str(),"ab");
    if(pFile == nullptr) return false;

    escribio = fwrite(&registro,sizeof(Producto),1,pFile);

    fclose(pFile);
    return escribio;

}

bool ProductoArchivo::guardar(int pos, Producto registro){

    FILE *pFile;
    bool escribio;

    pFile = fopen(_nombreArchivo.c_str(),"rb+");
    if(pFile == nullptr) return false;

    fseek(pFile,pos* sizeof(Producto),0);

    escribio = fwrite(&registro,sizeof registro,1,pFile);

    fclose(pFile);
    return escribio;
}

bool ProductoArchivo::eliminar(int pos){
    Producto registro = leer(pos);

    if(registro.getIdProducto() != ""){
        registro.setEstado(false);
        return guardar(pos,registro);
    }
    return false;
}

Producto ProductoArchivo::leer(int pos){

    Producto registro;
    FILE *pFile;
    pFile = fopen(_nombreArchivo.c_str(),"rb");

    if(pFile == nullptr) return Producto();

    fseek(pFile,pos*sizeof(Producto),SEEK_SET);
    fread(&registro,sizeof(Producto),1,pFile);

    fclose(pFile);
    return registro;
}
std::string ProductoArchivo::GenerarCodigode13(){

     std::string codigo = "";
        for(int i=0; i<13; i++){
        int dig = rand() % 10;
        codigo += char('0' + dig);
        }
    return codigo;
}

bool ProductoArchivo::existeCodigo(std::string cod){

    int cant = getCantidadRegistro();
    Producto *vec = new Producto[cant];
    LeerTodos(vec,cant);

    for(int i=0;i<cant;i++){
        if(vec[i].getIdProducto() == cod){
            delete[] vec;
            return false;
        }
    }
    delete[] vec;
    return true;
}

bool ProductoArchivo::getCodigoNuevo(std::string codigo){

    bool repetido = true;

    repetido = existeCodigo(codigo);

    return repetido;
}

int ProductoArchivo::getCantidadRegistro(){

    int cantRegistros;
    FILE *pFile;

    pFile = fopen(_nombreArchivo.c_str(),"rb");
    if(pFile ==  nullptr) return 0;

    fseek(pFile,0,SEEK_END);
    cantRegistros = ftell(pFile)/sizeof(Producto);

   fclose(pFile);
   return cantRegistros;

}
int ProductoArchivo::LeerTodos(Producto registros[], int cantidad){

    FILE *pFile;
    int result;

    pFile = fopen(_nombreArchivo.c_str(),"rb");
    if(pFile == nullptr) return 0;

    result = fread(registros,sizeof(Producto),cantidad,pFile);

    fclose(pFile);
    return result;
}

int ProductoArchivo::buscarIdProducto(std::string id){

    Producto registro;
    for(int i=0;i < getCantidadRegistro();i++){
        registro = leer(i);
        if(registro.getIdProducto() == id){
            return i;
        }
    }
    return -1;
}
