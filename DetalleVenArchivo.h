#pragma once
#include "DetalleVenta.h"

class DetalleVenArchivo{
    public:
    DetalleVenArchivo(std::string nombre = "DetalleVenta.dat");

    bool guardar(DetalleVenta registro);
    bool guardar(int pos, DetalleVenta registro);

    DetalleVenta leer(int pos);

    int getIdNuevo();
    int getCantidadRegistro();
    int LeerTodos(DetalleVenta registros[], int cantidad);
    int buscarId(int id);

private:
    std::string _nombreArchivo;







};
