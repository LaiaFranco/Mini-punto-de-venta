#pragma once
#include<string>

class Proveedor{

public:
    Proveedor();
    Proveedor(std::string cuit,std::string nombre,std::string direccion,std::string telefono, std::string email, bool estado);

    std::string getCuit();
    std::string getNombre();
    std::string getDireccion();
    std::string getTelefono();
    std::string getEmail();
    bool getEstado();

    void setCuit(std::string cuit);
    void setNombre(std::string nombre);
    void setDireccion(std::string direccion);
    void setTelefono(std::string telefono);
    void setEmail(std::string email);
    void setEstado(bool estado);

private:
    char _cuit[13];
    char _nombre[50];
    char _direccion[30];
    char _telefono[20];
    char _email[50];
    bool _estado;

};
