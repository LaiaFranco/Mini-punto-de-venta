#pragma once
#include <string>
#include "Validador.h"
#include "Proveedor.h"
#include "ProveedorArchivo.h"

class ProveedorManager{
public:
    ProveedorManager();

    void AgregarProveedor();
    void ModificarProveedor(int opcion);
    void EliminarProveedor();
    void ListarProveedores();
    void BuscarProveedor();
    void MostrarParaProducto(Proveedor registro);

protected:
    std::string CargarCadena();
    void Mostrar(Proveedor registro);

private:
    Validador _validador;
    ProveedorArchivo _provArchi;


};
