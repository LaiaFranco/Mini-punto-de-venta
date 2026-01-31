#pragma once
#include <string>
#include <sstream>
#include "Usuario.h"
#include "Validador.h"


class UsuarioArchivo{

public:
    UsuarioArchivo(std::string nombre = "Usuarios.dat");

    bool guardar(Usuario registro);
    bool guardar(int pos, Usuario registro);
    bool eliminar(int pos);

    Usuario leer(int pos);

    std::string getLegajoNuevo();
    int getCantidadRegistro();
    int LeerTodos(Usuario registros[], int cantidad);
    int buscarLegajo(std::string legajo);

    bool ValidarDni(std::string dni);

private:
    std::string _nombreArchivo;
    Validador _validar;
};
