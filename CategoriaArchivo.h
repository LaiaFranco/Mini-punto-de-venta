#pragma once
#include "Categoria.h"

class CategoriaArchivo{
public:
    CategoriaArchivo(std::string nombre = "Categoria.dat");

    bool guardar(Categoria registro);
    bool guardar(int pos, Categoria registro);
    bool eliminar(int pos);

    Categoria leer(int pos);

    int existeCategoria(std::string nombre);
    int getIdNuevo();
    int getCantidadRegistro();
    int LeerTodos(Categoria registros[], int cantidad);
    int buscarId(int id);


private:
    std::string _nombreArchivo;


};
