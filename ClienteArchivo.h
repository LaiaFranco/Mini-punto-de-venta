#pragma once
#include<string>
#include "Cliente.h"

class ClienteArchivo{
public:
    ClienteArchivo(std::string nombre = "Clientes.dat");

    bool guardar(Cliente &registro);
    bool guardar(int pos, Cliente registro);
    bool eliminar(int pos);

    Cliente leer(int pos);

    int getIdNuevo();
    int getCantidadRegistro();
    int LeerTodos(Cliente cliente[], int cantidad);

    bool ValidarDni(std::string dni);

    int buscarDni(std::string dni);

private:
    std::string _nombreArchivo;

};
