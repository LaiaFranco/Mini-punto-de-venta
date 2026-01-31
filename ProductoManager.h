#pragma once
#include <string>
#include "Producto.h"
#include "ProductoArchivo.h"
#include "ProveedorArchivo.h"
#include "ProveedorManager.h"
#include "CategoriaArchivo.h"
#include "Categoria.h"
#include "Validador.h"

class ProductoManager{
public:
    ProductoManager();

    void CrearProducto();
    void ModificarProducto(int opcion);
    void EliminarProducto();
    void Listar(int opcion);
    void Buscar();
    std::string Buscar(std::string codigo);

    void ConsultarStockPorCategoria();
    void AjustarStock();

    float getPrecioVenta(std::string codigo);
    float getStockActual(std::string codigo);
    bool descontarStock(std::string codigo,int cantidad);
    bool restaurarStock(std::string codigo, float cantidad);


protected:
    std::string CargarCadena();
    std::string MostrarCategorias();
    std::string MotivosAjustes();

    void Mostrar(Producto registro);
    float CalcularPrecioVenta(float precioCompra);

    void OrdenarNombre(Producto *vec,int tam);
    void OrdenarPrecioVenta(Producto *vec,int tam );
    void OrdenarPlu(Producto *vec, int tam);


private:
    ProductoArchivo _productArchi;
    ProveedorArchivo _provArchi;
    ProveedorManager _provMan;
    CategoriaArchivo _catArchi;
    Validador _validar;

};
