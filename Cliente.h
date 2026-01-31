#pragma once
#include "Persona.h"
#include<string>

class Cliente: public Persona{
public:
    Cliente();
    Cliente(std::string nombre,std::string apellido,std::string dni,std::string direccion,std::string telefono,std::string mail, Fecha fechaNac,int edad,bool estado,int id);

    int  getIdCliente();
    void setIdCliente(int id);


private:
    int _idCliente;

};
