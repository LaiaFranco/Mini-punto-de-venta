#pragma once
#include<string>
#include<cstring>
#include "Fecha.h"
#include "Validador.h"

class Persona{
public:
    Persona();
    Persona(std::string nombre ,std::string apellido,std::string dni,std::string direccion,std::string telefono,std::string mail, Fecha fechaNac,int edad,bool estado);

    std::string getNombre();
    std::string getApellido();
    std::string getDni();
    std::string getDireccion();
    std::string getTelefono();
    std::string getMail();
    Fecha getFechaNac();
    int getEdad();
    bool getEstado();

    void setNombre(std::string nombre);
    void setApellido(std::string apellido);
    void setDni(std::string dni);
    void setDireccion(std::string direccion);
    void setTelefono(std::string telefono);
    void setMail(std::string mail);
    void setFechaNac(Fecha fechaNac);
    void setEdad(int edad);
    void setEstado(bool estado);

    std::string getNombreCompleto();

private:
    char _nombre[50];
    char _apellido[50];
    char _dni[15];
    char _direccion[50];
    char _telefono[50];
    char _mail[50];
    Fecha _fechaNac;
    int _edad;
    bool _estado;

    int tam = 50;
    int tam1 = 15;
    Validador _validar;
};
