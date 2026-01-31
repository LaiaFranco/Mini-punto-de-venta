#pragma once
#include<string>
#include"Producto.h"


class ProductoArchivo{

public:
    ProductoArchivo(std::string nombre = "Productos.dat");

    bool guardar(Producto registro);
    bool guardar(int pos, Producto registro);
    bool eliminar(int pos);

    Producto leer(int pos);

    bool getCodigoNuevo(std::string codigo);

    int getCantidadRegistro();
    int LeerTodos(Producto registros[], int cantidad);
    int buscarIdProducto(std::string id);

protected:
    std::string GenerarCodigode13();
    bool existeCodigo(std::string cod);

private:
    std::string _nombreArchivo;

};
