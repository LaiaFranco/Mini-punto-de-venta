#include "Validador.h"


Validador::Validador(){}

bool Validador::ValidarTamanios(std::string atributo,int tamanio){
    if(atributo.size() <= tamanio){
            return true;
    }
    return false;
}
bool Validador::ValidarTamanioExactos(std::string atributo,int tam){
    if(atributo.size() == tam) return true;

    return false;
}

bool Validador::ValidarTamDni(std::string dni){
    if(dni.size() == 9){
        return true;
    }else{
    return false;
    }
}

bool Validador::ValidarContrasenias(std::string contrasenia, int tam ){
    if(contrasenia.size() == tam){
        return true;
    }else{
        return false;
    }
}
bool Validador::ValidarUsuario(std::string usuario){
    if(usuario.size() == 6){
        return true;
    }else{
        return false;
    }
}
bool Validador::ValidarCuit(std::string cuit){
    if(cuit.size() == 11)return true;
    return false;
}
