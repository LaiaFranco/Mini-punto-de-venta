#include "Proveedor.h"
#include <cstring>

Proveedor::Proveedor(){
    strcpy(_cuit,"");
    strcpy(_nombre,"");
    strcpy(_direccion,"");
    strcpy(_telefono,"");
    strcpy(_email,"");
    _estado = false;
}

Proveedor::Proveedor(std::string cuit,std::string nombre,std::string direccion,std::string telefono, std::string email, bool estado){
    setCuit(cuit);
    setNombre(nombre);
    setDireccion(direccion);
    setTelefono(telefono);
    setEmail(email);
    setEstado(estado);
}

std::string Proveedor::getCuit(){
return _cuit;}
std::string Proveedor::getNombre(){
return _nombre;}
std::string Proveedor::getDireccion(){
return _direccion;}
std::string Proveedor::getTelefono(){
return _telefono;}
std::string Proveedor::getEmail(){
return _email;}
bool Proveedor::getEstado(){
return _estado;}

void Proveedor::setCuit(std::string cuit){
    if(cuit.size() <= 13){
        strncpy(_cuit,cuit.c_str(),12);
        _cuit[12] = '\0';
    }
}
void Proveedor::setNombre(std::string nombre){
    if(nombre.size() <= 50){
        strncpy(_nombre,nombre.c_str(),50);
        _nombre[49] = '\0';
    }
}
void Proveedor::setDireccion(std::string direccion){
    if(direccion.size() <= 30){
        strncpy(_direccion,direccion.c_str(),29);
        _direccion[29] = '\0';
    }
}
void Proveedor::setTelefono(std::string telefono){
    if(telefono.size() <= 20){
        strncpy(_telefono,telefono.c_str(),19);
        _telefono[19] = '\0';
    }
}
void Proveedor::setEmail(std::string email){
    if(email.size() <= 50){
        strncpy(_email,email.c_str(),50);
        _email[49] = '\0';
    }
}
void Proveedor::setEstado(bool estado){
    _estado = estado;
}
