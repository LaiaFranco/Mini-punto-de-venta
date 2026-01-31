#include "Menu.h"
#include<iostream>

using namespace std;

Menu::Menu(){}
string Menu::CargarCadena(){
    string texto;
    if(cin.peek()=='\n'){
        cin.ignore();
    }
    getline(cin,texto);
    return texto;
}

void Menu::MostrarMenuPrincipal(){
    cout<<"||  BIENVENIDO  ||"<<endl;

    system("pause");
    system("cls");
    int opcion;

    while(true){
        _userMan.InicializarSistema();
        MostrarEncabezdoLogin();

    string usuario;
    string contrasenia;
    int rol;

    for(int i = 0; i < 3; i++){

    cout<<endl<<endl;
    cout<<"||LEGAJO: ";
    usuario = CargarCadena();
    cout<<"||CONTRASENIA: ";
    contrasenia = CargarCadena();

    if(!(_validador.ValidarContrasenias(contrasenia) and _validador.ValidarUsuario(usuario))){
           cout<<endl<<"LEGAJO Y/O CONTRASENIA INCORRECTO."<<endl;

    }else{
        rol = _userMan.Login(usuario,contrasenia);

        if(rol == 1 or rol == 2){
            MenuRol(rol,usuario);
            break;
        }

        system("pause");
        system("cls");
        MostrarEncabezdoLogin();
        cout<<endl<<"LEGAJO Y/O CONTRASENIA INCORRECTO ;( "<<endl;
            if(i == 2){
                cout<<"Usuario bloqueado temporalmente.Vuelva a intentarlo mas tarde..."<<endl<<endl;
                system("pause");
                system("cls");
                return;
            }
    }
        system("pause");
        system("cls");
        MostrarEncabezdoLogin();
    }
    }

}
void Menu::MenuRol(int rol, std::string usuario){
    if(rol == 1){
        MenuAdministrador(usuario);
    }else if(rol == 2){
        MenuVendedor(usuario);
    }
}

void Menu::MenuAdministrador(std::string usuario){
    int opcion;
    do{
            system("cls");
        cout<<"                  -- MENU ADMINISTRADOR --                "<<endl;
        cout<<endl;
        cout<<" ........................... ...........................  "<<endl;
        cout<<"|| 1.GESTION DE USUARIOS   | | 2.GESTION DE CLIENTES   || "<<endl;
        cout<<" ........................... ...........................  "<<endl;
        cout<<" ........................... ...........................  "<<endl;
        cout<<"|| 3.GESTION DE PRODUCTOS  | | 4.GESTION DE VENTAS     || "<<endl;
        cout<<" ........................... ...........................  "<<endl;
        cout<<" ........................... ...........................  "<<endl;
        cout<<"|| 5.GESTION DE CATEGORIAS | | 6.REPORTES              || "<<endl;
        cout<<" ........................... ...........................  "<<endl;
        cout<<" ........................... ...........................  "<<endl;
        cout<<"|| 7.CONFIGURACION         | | 0.SALIR                 || "<<endl;
        cout<<" ........................... ...........................  "<<endl;
        cout<<endl;
        cout<<"_OPCION: ";
        cin>>opcion;

        OpcionMenuAdministrador(opcion, usuario);

    }while(opcion != 0);

}
void Menu::MostrarEncabezdoLogin(){
    system("cls");
    cout<<"................................... "<<endl;
    cout<<"||        INICIO DE SESION       || "<<endl;
    cout<<"................................... "<<endl;

}
void Menu::OpcionMenuAdministrador(int opcion, std::string usuario){
    switch(opcion){
    case 1:
        MenuGestionUsuarios();
        break;
    case 2:
        MenuGestionClientes();
        break;
    case 3:
        MenuGestionProductos();
        break;
    case 4:
        MenuGestionVentas();
        break;
    case 5:
        MenuGestionCategorias();
        break;
    case 6:
        MenuReportes();
        break;
    case 7:
        MenuConfiguracion(usuario);
        break;
    case 0:
        cout<<"Saliendo..."<<endl;
        break;
    }

}

void Menu::MenuGestionUsuarios(){
   int opcion;
   do{
        system("pause");
        system("cls");
   cout<<" == GESTION DE USARIOS =="<<endl;
    cout<<"1. ALTA USUARIO    "<<endl;
    cout<<"2. MODIFICAR USUARIO "<<endl;
    cout<<"3. ELIMINAR USUARIO" <<endl;
    cout<<"4. LISTAR USUARIOS" <<endl;
    cout<<"5. BUSCAR USUARIO POR LEGAJO"<<endl;
    cout<<"0.SALIR  "<<endl;

    cout<<endl<<"OPCION: ";
    cin>>opcion;

    OpcionGestionUsuarios(opcion);
    }while(opcion !=0);

}

void Menu::OpcionGestionUsuarios(int opcion){
    switch(opcion){
    case 1:{
        system("pause");
        system("cls");
        _userMan.CrearUsuario();
        break;
    }
    case 2:{
        system("pause");
        system("cls");
        int opc;
        opc = _subMenu.SubMenuModificar();
        _userMan.ModificarUsuario(opc);
        break;
    }
    case 3:{
        system("pause");
        system("cls");
        _userMan.EliminarUsuario();
        break;
    }
    case 4:{
        system("pause");
        system("cls");
        int opcion;
        opcion = _subMenu.SubMenuListar();
        system("cls");
        _userMan.ListarUsuarios(opcion);
        break;
    }
    case 5:{
        system("pause");
        system("cls");
        _userMan.BuscarUsuario();
        break;
    }
    case 0:
        cout<<"Saliendo..."<<endl;
        break;

    }
}
void Menu::MenuGestionClientes(){
     int opcion;
   do{
        system("pause");
        system("cls");
    cout<<" == GESTION DE CLIENTES =="<<endl;
    cout<<"1. ALTA CLIENTE    "<<endl;
    cout<<"2. MODIFICAR DATOS DEL CLIENTE "<<endl;
    cout<<"3. ELIMINAR REGISTRO DE CLIENTE" <<endl;
    cout<<"4. LISTAR CLIENTES" <<endl;
    cout<<"5. BUSCAR REGISTRO POR DNI"<<endl;
    cout<<"0.SALIR  "<<endl;

    cout<<endl<<"OPCION: ";
    cin>>opcion;
    if(opcion < 0 && opcion > 5){
            cout<<"OPCION INCORRECTA"<<endl;
            continue;
    }

    OpcionGestionClientes(opcion);
    }while(opcion !=0);
}
void Menu::OpcionGestionClientes(int opcion){
    switch(opcion){
    case 1:{
         system("pause");
         system("cls");
        _cliMan.AgregarCliente();
        break;
    }
    case 2:{
         system("pause");
         system("cls");
         int opcion;
         opcion = _subMenu.SubMenuModificarCliente();
        _cliMan.Modificar(opcion);
        break;
    }
    case 3:{
         system("pause");
         system("cls");
        _cliMan.EliminarCliente();
        break;
    }
    case 4:{
         system("pause");
         system("cls");
         int opcion = _subMenu.SubMenuListar();
        _cliMan.ListadoOpcion(opcion);
        break;
    }
    case 5:{
         system("pause");
         system("cls");
        _cliMan.buscar();
        break;
    }
    case 0:{
        system("pause");
        system("cls");
        cout<<"Saliendo..."<<endl;
        break;
    }
    }

}

void Menu::MenuGestionProductos(){
    int opcion;
   do{
        system("pause");
        system("cls");
   cout<<" == GESTION DE PRODUCTOS =="<<endl;
    cout<<"1. CARGAR PRODUCTO    "<<endl;
    cout<<"2. MODIFICAR  "<<endl;
    cout<<"3. ELIMINAR " <<endl;
    cout<<"4. LISTAR PRODUCTOS" <<endl;
    cout<<"5. BUSCAR "<<endl;
    cout<<"6. CONSULTAR STOCK POR CATEGORIA"<<endl;
    cout<<"7. AJUSTAR STOCK"<<endl;
    cout<<"0.SALIR  "<<endl;
    cout<<"==> 8. GESTIONAR PROVEEDORES"<<endl;

    cout<<endl<<"OPCION: ";
    cin>>opcion;

    OpcionGestionProductos(opcion);
    }while(opcion !=0);
}
void Menu::OpcionGestionProductos(int opcion){
    switch(opcion){
        case 1:{
            system("cls");
            _productMan.CrearProducto();
            break;
        }
        case 2:{
            int opcion = _subMenu.SubMenuModificarProducto();
            _productMan.ModificarProducto(opcion);
            break;
        }
        case 3:{
            system("cls");
            _productMan.EliminarProducto();
            break;
        }
        case 4:{
            system("cls");
            int opcion = _subMenu.SubMenuListarProducto();
            system("pause");
            system("cls");
            _productMan.Listar(opcion);
            break;
        }
        case 5:{
            system("cls");
            _productMan.Buscar();
            break;
        }
        case 6:{
            system("cls");
            _productMan.ConsultarStockPorCategoria();
            break;
        }
        case 7:{
            system("cls");
            _productMan.AjustarStock();
            break;
        }
        case 8:{
            MenuGestionProveedores();
            break;
        }
        case 0:{
            break;
        }
    }

}
void Menu::MenuGestionCategorias(){
    int opcion;
   do{
        system("pause");
        system("cls");
   cout<<" == GESTION DE CATEGORIAS =="<<endl;
    cout<<"1. CREAR CATEGORIA    "<<endl;
    cout<<"2. MODIFICAR  "<<endl;
    cout<<"3. ELIMINAR " <<endl;
    cout<<"4. LISTAR CATEGORIAS" <<endl;
    cout<<"0.SALIR  "<<endl;

    cout<<endl<<"OPCION: ";
    cin>>opcion;

    OpcionGestionCategoria(opcion);
    }while(opcion !=0);

}
void Menu::OpcionGestionCategoria(int opcion){
    switch(opcion){
    case 1:{
        system("pause");
        system("cls");
        _catMan.AgregarCategoria();
        break;
    }
    case 2:{
        int opcion;
        opcion = _subMenu.SubMenuModificarCat();
        _catMan.ModificarCategoria(opcion);
        break;
    }
    case 3:{
        system("pause");
        system("cls");
        _catMan.EliminarCategoria();
        break;
        }
    case 4:{
        system("pause");
        system("cls");
        _catMan.ListarCategorias();
        break;
    }
    case 0:
        cout<<"Saliendo..."<<endl;
        break;
    }


}

void Menu::MenuVendedor(std::string usuario){
    int opcion;
    do{
        system("cls");
        cout<<"                  -- MENU VENDEDOR --                "<<endl;
        cout<<endl;
        cout<<" ........................... ...........................  "<<endl;
        cout<<"|| 1.NUEVA VENTA            | | 0.SALIR                 || "<<endl;
        cout<<" ........................... ...........................  "<<endl;
        cout<<endl;
        cout<<"_OPCION: ";
        cin>>opcion;

        if(opcion == 1){
            _ventMan.NuevaVenta(usuario);
        }else if(opcion == 0){
            cout<<"Saliendo..."<<endl;
        }else{
            cout<<"OPCION INCORRECTA"<<endl;
            system("pause");
        }

    }while(opcion != 0);
}

void Menu::MenuGestionVentas(){
    int opcion;
    do{
        system("pause");
        system("cls");
        cout<<" == GESTION DE VENTAS =="<<endl;
        cout<<"1. LISTAR TODAS LAS VENTAS"<<endl;
        cout<<"2. CONSULTAR POR NUMERO DE TRANSACCION"<<endl;
        cout<<"3. ANULAR VENTA"<<endl;
        cout<<"0. SALIR"<<endl;

        cout<<endl<<"OPCION: ";
        cin>>opcion;

        OpcionGestionVentas(opcion);
    }while(opcion != 0);
}

void Menu::OpcionGestionVentas(int opcion){
    switch(opcion){
    case 1:{
        _ventMan.ListarTodasLasVentas();
        break;
    }
    case 2:{
        _ventMan.ConsultarPorNumTransaccion();
        break;
    }
    case 3:{
        _ventMan.AnularVenta();
        break;
    }
    case 0:{
        break;
    }
    default:{
        cout<<"OPCION INCORRECTA"<<endl;
        system("pause");
        break;
    }
    }
}

void Menu::MenuGestionProveedores(){
    int opcion;
    do{
        system("pause");
        system("cls");
        cout<<" == GESTION DE PROVEEDORES =="<<endl;
        cout<<"1. ALTA PROVEEDOR"<<endl;
        cout<<"2. MODIFICAR PROVEEDOR"<<endl;
        cout<<"3. ELIMINAR PROVEEDOR"<<endl;
        cout<<"4. LISTAR PROVEEDORES"<<endl;
        cout<<"5. BUSCAR PROVEEDOR"<<endl;
        cout<<"0. SALIR"<<endl;

        cout<<endl<<"OPCION: ";
        cin>>opcion;

        OpcionGestionProveedores(opcion);
    }while(opcion != 0);
}

void Menu::OpcionGestionProveedores(int opcion){
    switch(opcion){
    case 1:{
        system("pause");
        system("cls");
        _provMan.AgregarProveedor();
        break;
    }
    case 2:{
        system("pause");
        system("cls");
        int opc = _subMenu.SubMenuModificarProveedor();
        if(opc != 0){
            _provMan.ModificarProveedor(opc);
        }
        break;
    }
    case 3:{
        system("pause");
        system("cls");
        _provMan.EliminarProveedor();
        break;
    }
    case 4:{
        _provMan.ListarProveedores();
        break;
    }
    case 5:{
        system("pause");
        system("cls");
        _provMan.BuscarProveedor();
        break;
    }
    case 0:{
        break;
    }
    default:{
        cout<<"OPCION INCORRECTA"<<endl;
        system("pause");
        break;
    }
    }
}

void Menu::MenuConfiguracion(std::string usuario){
    int opcion;
    do{
        system("cls");
        cout<<"                  -- MENU CONFIGURACION --                "<<endl;
        cout<<endl;
        cout<<" ........................... ...........................  "<<endl;
        cout<<"|| 1.CAMBIAR CONTRASENIA     | | 2.RECUPERAR DATOS      || "<<endl;
        cout<<" ........................... ...........................  "<<endl;
        cout<<" ........................... ...........................  "<<endl;
        cout<<"|| 3.CERRAR SESION           | | 0.SALIR                 || "<<endl;
        cout<<" ........................... ...........................  "<<endl;
        cout<<endl;
        cout<<"_OPCION: ";
        cin>>opcion;

        OpcionConfiguracion(opcion, usuario);

    }while(opcion != 0);
}

void Menu::OpcionConfiguracion(int opcion, std::string usuario){
    switch(opcion){
    case 1:{
        system("cls");
        string legajo;
        cout<<"INGRESE LEGAJO DEL USUARIO: ";
        legajo = CargarCadena();
        _userMan.CambiarContrasenia(legajo);
        system("pause");
        break;
    }
    case 2:{
        system("cls");
        int opcionRecuperar;
        cout<<" == RECUPERAR DATOS =="<<endl;
        cout<<"1. RECUPERAR PRODUCTO"<<endl;
        cout<<"2. RECUPERAR CLIENTE"<<endl;
        cout<<"3. RECUPERAR USUARIO"<<endl;
        cout<<"0. SALIR"<<endl;
        cout<<endl<<"OPCION: ";
        cin>>opcionRecuperar;

        switch(opcionRecuperar){
        case 1:{
            string codigo;
            cout<<"INGRESE CODIGO DEL PRODUCTO: ";
            codigo = CargarCadena();

            int pos = _productArchi.buscarIdProducto(codigo);
            if(pos >= 0){
                Producto prod = _productArchi.leer(pos);
                if(!prod.getEstado()){
                    prod.setEstado(true);
                    if(_productArchi.guardar(pos, prod)){
                        cout<<"** PRODUCTO RECUPERADO CORRECTAMENTE **"<<endl;
                    } else {
                        cout<<"** ERROR AL RECUPERAR PRODUCTO **"<<endl;
                    }
                } else {
                    cout<<"** PRODUCTO YA ESTA ACTIVO **"<<endl;
                }
            } else {
                cout<<"** PRODUCTO NO ENCONTRADO **"<<endl;
            }
            break;
        }
        case 2:{
            string dni;
            cout<<"INGRESE DNI DEL CLIENTE: ";
            dni = CargarCadena();

            int pos = _cliArchi.buscarDni(dni);
            if(pos >= 0){
                Cliente cliente = _cliArchi.leer(pos);
                if(!cliente.getEstado()){
                    cliente.setEstado(true);
                    if(_cliArchi.guardar(pos, cliente)){
                        cout<<"** CLIENTE RECUPERADO CORRECTAMENTE **"<<endl;
                    } else {
                        cout<<"** ERROR AL RECUPERAR CLIENTE **"<<endl;
                    }
                } else {
                    cout<<"** CLIENTE YA ESTA ACTIVO **"<<endl;
                }
            } else {
                cout<<"** CLIENTE NO ENCONTRADO **"<<endl;
            }
            break;
        }
        case 3:{
            string legajo;
            cout<<"INGRESE LEGAJO DEL USUARIO: ";
            legajo = CargarCadena();

            int pos = _userArchi.buscarLegajo(legajo);
            if(pos >= 0){
                Usuario user = _userArchi.leer(pos);
                if(!user.getPersona().getEstado()){
                    user.getPersona().setEstado(true);
                    if(_userArchi.guardar(pos, user)){
                        cout<<"** USUARIO RECUPERADO CORRECTAMENTE **"<<endl;
                    } else {
                        cout<<"** ERROR AL RECUPERAR USUARIO **"<<endl;
                    }
                } else {
                    cout<<"** USUARIO YA ESTA ACTIVO **"<<endl;
                }
            } else {
                cout<<"** USUARIO NO ENCONTRADO **"<<endl;
            }
            break;
        }
        }
        system("pause");
        break;
    }
    case 3:{
        cout<<"** CERRANDO SESION **"<<endl;
        system("pause");
        system("cls");
        MostrarMenuPrincipal();
        return;
    }
    case 0:{
        break;
    }
    default:{
        cout<<"OPCION INCORRECTA"<<endl;
        system("pause");
        break;
    }
    }
}

void Menu::MenuReportes(){
    int opcion;
    do{
        system("pause");
        system("cls");
        cout<<" == MENU REPORTES =="<<endl;
        cout<<"1. PRODUCTO MAS VENDIDO"<<endl;
        cout<<"2. VENTAS TOTALES POR DIA O MES"<<endl;
        cout<<"3. VENDEDOR CON MAS TRANSACCIONES"<<endl;
        cout<<"4. RECAUDACION (DIARIA, MENSUAL, ANUAL)"<<endl;
        cout<<"0. SALIR"<<endl;

        cout<<endl<<"OPCION: ";
        cin>>opcion;

        OpcionReportes(opcion);
    }while(opcion != 0);
}

void Menu::OpcionReportes(int opcion){
    switch(opcion){
    case 1:{
        system("pause");
        system("cls");
        _ventMan.ReporteProductoMasVendido();
        break;
    }
    case 2:{
        system("pause");
        system("cls");
        _ventMan.ReporteVentasPorDiaOMes();
        break;
    }
    case 3:{
        system("pause");
        system("cls");
        _ventMan.ReporteVendedorMasTransacciones();
        break;
    }
    case 4:{
        system("pause");
        system("cls");
        _ventMan.ReporteRecaudacion();
        break;
    }
    case 0:{
        break;
    }
    default:{
        cout<<"OPCION INCORRECTA"<<endl;
        system("pause");
        break;
    }
    }
}
