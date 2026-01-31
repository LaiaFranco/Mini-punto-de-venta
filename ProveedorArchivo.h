#pragma once
#include "Proveedor.h"

class ProveedorArchivo{
public:
    ProveedorArchivo(std::string nombre = "Proveedor.dat");

    bool guardar(Proveedor registro);
    bool guardar(int pos, Proveedor registro);
    bool eliminar(int pos);

    Proveedor leer(int pos);

    int getCantidadRegistro();
    int LeerTodos(Proveedor registros[], int cantidad);
    int buscarCuit(std::string cuit);

private:
    std::string _nombreArchivo;

};
