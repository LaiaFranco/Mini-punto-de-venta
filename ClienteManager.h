#pragma once
#include <string>
#include "Fecha.h"
#include "Persona.h"
#include "Cliente.h"
#include "ClienteArchivo.h"
#include "Validador.h"

class ClienteManager{

public:
    ClienteManager();

    void AgregarCliente();
    void EliminarCliente();
    void Modificar(int opcion);

    void ListadoOpcion(int opcion);
    void listarPorApellido();
    void listarPorNombre();
    void listarPorEdad();

    Cliente buscarPorDni();
    void buscar();

protected:
    std::string CargarCadena();
    void MostrarCliente(Cliente cliente);

private:
    ClienteArchivo _cArchi;
    Fecha _fecha;
    Validador _validar;

};
