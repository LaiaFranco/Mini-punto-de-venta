#pragma once
#include "Categoria.h"
#include "CategoriaArchivo.h"
#include "Validador.h"


class CategoriaManager{

public:
    CategoriaManager();

    void AgregarCategoria();
    void ModificarCategoria(int opcion);
    void EliminarCategoria();
    void ListarCategorias();

protected:
    std::string CargarCadena();
    void Mostrar(Categoria registro);
    void MostrarActualizacion(bool ok, Categoria reg);

private:
    CategoriaArchivo _catArch;
    Validador _validar;


};
