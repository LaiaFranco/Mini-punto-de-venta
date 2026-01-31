#include "UsuarioArchivo.h"

UsuarioArchivo::UsuarioArchivo(std::string nombre)
:_nombreArchivo(nombre){
}

bool UsuarioArchivo::guardar(Usuario registro){

    FILE *pFile;
    bool escribio;

    pFile = fopen(_nombreArchivo.c_str(),"ab");
    if(pFile == nullptr) return false;

    escribio = fwrite(&registro,sizeof(Usuario),1,pFile);

    fclose(pFile);
    return escribio;

}

bool UsuarioArchivo::guardar(int pos, Usuario registro){

    FILE *pFile;
    bool escribio;

    pFile = fopen(_nombreArchivo.c_str(),"rb+");
    if(pFile == nullptr) return false;

    fseek(pFile,pos* sizeof(Usuario),0);

    escribio = fwrite(&registro,sizeof registro,1,pFile);

    fclose(pFile);
    return escribio;
}

bool UsuarioArchivo::eliminar(int pos){
    Usuario registro = leer(pos);

    if(registro.getLegajo() != ""){
        registro.getPersona().setEstado(false);
        return guardar(pos,registro);
    }
    return false;
}

Usuario UsuarioArchivo::leer(int pos){

    Usuario registro;
    FILE *pFile;
    pFile = fopen(_nombreArchivo.c_str(),"rb");

    if(pFile == nullptr) return Usuario();

    fseek(pFile,pos*sizeof(Usuario),SEEK_SET);
    fread(&registro,sizeof(Usuario),1,pFile);

    fclose(pFile);
    return registro;
}

std::string UsuarioArchivo::getLegajoNuevo(){
  int cantidad = getCantidadRegistro();

    if(cantidad == 0) return "100001";

    Usuario reg = leer(cantidad-1);
    std::string ultimo = reg.getLegajo();

    for(int i = ultimo.size()-1; i >= 0; i--){
        if(ultimo[i] < '9'){
            ultimo[i]++;
            break;
        }else{
            ultimo[i]='0';
        }
    }
    return ultimo;
}

int UsuarioArchivo::getCantidadRegistro(){

    int cantRegistros;
    FILE *pFile;

    pFile = fopen(_nombreArchivo.c_str(),"rb");
    if(pFile == nullptr) return 0;

    fseek(pFile,0,SEEK_END);
    cantRegistros = ftell(pFile)/sizeof(Usuario);

   fclose(pFile);
   return cantRegistros;

}
int UsuarioArchivo::LeerTodos(Usuario registros[], int cantidad){

    FILE *pFile;
    int result;

    pFile = fopen(_nombreArchivo.c_str(),"rb");
    if(pFile == nullptr) return 0;

    result = fread(registros,sizeof(Usuario),cantidad,pFile);

    fclose(pFile);
    return result;
}

int UsuarioArchivo::buscarLegajo(std::string legajo){
    Usuario registro;
    for(int i=0;i < getCantidadRegistro();i++){
        registro = leer(i);
        if(registro.getLegajo() == legajo){
            return i;
        }
    }
    return -1;
}
bool UsuarioArchivo::ValidarDni(std::string dni){
    FILE *pFile;
    Usuario registro;

    if(!_validar.ValidarTamDni(dni))return false;

    pFile = fopen(_nombreArchivo.c_str(),"rb");
    if(pFile == nullptr) return true;

    while(fread(&registro,sizeof(Usuario),1,pFile)){
        if(registro.getPersona().getDni() == dni){
            fclose(pFile);
            return false;
        }
    }
    fclose(pFile);
    return true;
}
