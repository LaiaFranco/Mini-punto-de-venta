#pragma once
#include "UsuarioArchivo.h"
#include "Usuario.h"
#include "Fecha.h"
#include "Validador.h"
#include<string>

class UsuarioManager{
public:
    UsuarioManager();

    void InicializarSistema();
    void CrearUsuario();
    std::string getObtenerRol();
    int Login(std::string usuario, std::string contrasenia);

    void MostrarUsuario(Usuario registro);
    void EliminarUsuario();

    void ModificarUsuario(int opcion);
    void MostrarActualizacion(bool ok,Usuario registro);

    void ListarUsuarios(int opcion);
    void BuscarUsuario();
    void CambiarContrasenia(std::string legajo);

    std::string getMostrarNombreCajero(std::string legajo);

protected:
    std::string CargarCadena();
    void OrdenarVecApellido(Usuario *vec,int tam);
    void OrdenarVecNombre(Usuario vec[],int tam);
    void OrdenarVecEdad(Usuario vec[],int tam);
private:
    UsuarioArchivo _UserArchi;
    Fecha _fecha;
    Validador _validar;
    std::string vecRoles[2] = {"Administrador","Vendedor"};
};
