#pragma once
#include<string>
#include "UsuarioManager.h"
#include "ClienteManager.h"
#include "CategoriaManager.h"
#include "ProductoManager.h"
#include "ProveedorManager.h"
#include "Validador.h"
#include "SubMenu.h"
#include "VentaManager.h"
#include "ProductoArchivo.h"
#include "ClienteArchivo.h"
#include "UsuarioArchivo.h"

class Menu{
public:
    Menu();
    void MostrarMenuPrincipal();
    void MenuRol(int rol,std::string usuario);
    void MenuAdministrador(std::string usuario);
    void OpcionMenuAdministrador(int opcion, std::string usuario);

    void MenuGestionUsuarios();
    void OpcionGestionUsuarios(int opcion);

    void MenuGestionClientes();
    void OpcionGestionClientes(int opcion);

    void MenuGestionProductos();
    void OpcionGestionProductos(int opcion);

    void MenuGestionCategorias();
    void OpcionGestionCategoria(int opcion);
    
    void MenuVendedor(std::string usuario);
    
    void MenuGestionVentas();
    void OpcionGestionVentas(int opcion);
    
    void MenuGestionProveedores();
    void OpcionGestionProveedores(int opcion);
    
    void MenuConfiguracion(std::string usuario);
    void OpcionConfiguracion(int opcion, std::string usuario);
    
    void MenuReportes();
    void OpcionReportes(int opcion);

protected:
    std::string CargarCadena();
    void MostrarEncabezdoLogin();

private:
    UsuarioManager _userMan;
    ClienteManager _cliMan;
    CategoriaManager _catMan;
    ProductoManager _productMan;
    ProveedorManager _provMan;
    Validador _validador;
    SubMenu _subMenu;
    VentaManager _ventMan;
    ProductoArchivo _productArchi;
    ClienteArchivo _cliArchi;
    UsuarioArchivo _userArchi;




};
