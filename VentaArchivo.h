#pragma once
#include "Venta.h"

class VentaArchivo{
public:
    VentaArchivo(std::string nombre = "Venta.dat");

    bool guardar(Venta registro);
    bool guardar(int pos, Venta registro);

    Venta leer(int pos);

    int getIdNuevo();
    int getCantidadRegistro();
    int LeerTodos(Venta registros[], int cantidad);
    int buscarId(int id);

private:
    std::string _nombreArchivo;

};
