#include "Persona.h"


Persona::Persona(){
strcpy(_nombre, "");
strcpy(_apellido,"");
strcpy(_dni,"");
strcpy(_direccion,"");
strcpy(_telefono,""),
strcpy(_mail,"");
_fechaNac = Fecha(),
_edad =0;
_estado = false;
}

Persona::Persona(std::string nombre,std::string apellido,std::string dni,std::string direccion,std::string telefono,std::string mail, Fecha fechaNac,int edad,bool estado){
    setNombre(nombre);
    setApellido(apellido);
    setDni(dni);
    setDireccion(direccion);
    setTelefono(telefono);
    setMail(mail);
    setFechaNac(fechaNac);
    setEdad(edad);
    setEstado(estado);
}

std::string Persona::getNombre(){
return _nombre;}
std::string Persona::getApellido(){
return _apellido;}
std::string Persona::getDni(){
return _dni;}
std::string Persona::getDireccion(){
return _direccion;}
std::string Persona::getTelefono(){
return _telefono;}
std::string Persona::getMail(){
return _mail;}
Fecha Persona::getFechaNac(){
return _fechaNac;}
int Persona::getEdad(){
return _edad;}
bool Persona::getEstado(){
return _estado;}

void Persona::setNombre(std::string nombre){
    if( _validar.ValidarTamanios(nombre,tam)){
        strncpy(_nombre,nombre.c_str(),50);
        _nombre[49] = '\0';
    }
}
void Persona::setApellido(std::string apellido){
    if(_validar.ValidarTamanios(apellido,tam)){
        strncpy(_apellido,apellido.c_str(),50);
        _apellido[49] = '\0';
    }
}
void Persona::setDni(std::string dni){
        if(_validar.ValidarTamanios(dni,tam1)){
        strncpy(_dni,dni.c_str(),15);
        _dni[14] = '\0';
        }

}
void Persona:: setDireccion(std::string direccion){
    if(_validar.ValidarTamanios(direccion,tam)){
        strncpy(_direccion,direccion.c_str(),50);
        _direccion[49] = '\0';
    }
}
void Persona::setTelefono(std::string telefono){
    if(_validar.ValidarTamanios(telefono,tam)){
        strncpy(_telefono,telefono.c_str(),50);
        _telefono[49] = '\0';
    }
}
void Persona::setMail(std::string mail){
    if(_validar.ValidarTamanios(mail,tam)){
        strncpy(_mail,mail.c_str(),50);
        _mail[49] = '\0';
    }
}
void Persona::setFechaNac(Fecha fechaNac){
    _fechaNac = fechaNac;
}
void Persona::setEdad(int edad){
    _edad = edad;
}
void Persona:: setEstado(bool estado){
    _estado = estado;
}

std::string Persona::getNombreCompleto(){
    return std::string(_nombre) + " " + std::string(_apellido);
}
