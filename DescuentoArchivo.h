#pragma once
#include "Descuento.h"

class DescuentoArchivo{
public:
    DescuentoArchivo(std::string nombre = "Descuento.dat");

    bool guardar(Descuento registro);
    bool guardar(int pos, Descuento registro);
    bool eliminar(int pos);

    Descuento leer(int pos);

    int getIdNuevo();
    int getCantidadRegistro();
    int LeerTodos(Descuento registros[], int cantidad);
    int buscarId(int id);

private:
    std::string _nombreArchivo;

};
