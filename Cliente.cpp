#include "Cliente.h"
#include<iostream>

Cliente::Cliente()
:Persona::Persona("","","","","","",Fecha(),0,false),_idCliente(0){
}

Cliente::Cliente(std::string nombre,std::string apellido,std::string dni,std::string direccion,std::string telefono,std::string mail, Fecha fechaNac,int edad,bool estado,int id)
:Persona::Persona(nombre,apellido,dni,direccion,telefono,mail,fechaNac,edad,estado),_idCliente(id){
}

int Cliente::getIdCliente(){
return _idCliente;}

void Cliente::setIdCliente(int id){
    _idCliente = id;
}
