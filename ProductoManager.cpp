#include "ProductoManager.h"
#include<iostream>

using namespace std;
ProductoManager::ProductoManager(){
}

string ProductoManager::CargarCadena(){
    string texto;
    if(cin.peek()=='\n'){
        cin.ignore();
    }
    getline(cin,texto);
    return texto;
}
string ProductoManager::MostrarCategorias(){

    Categoria cat;
    int cantidad = _catArchi.getCantidadRegistro();
    for(int i = 0; i < cantidad; i++){
        cat = _catArchi.leer(i);
        if(cat.getEstado()){
            cout<<cat.getNumeroCategoria()<<endl;
            cout<<cat.getNombre()<<endl;
            cout<<"---------------------------"<<endl;
        }
    }

    int opcion;
    cout<<endl<<"Seleccione numero de categoria: ";
    cin>>opcion;

    for(int i=0; i<cantidad; i++){
        cat = _catArchi.leer(i);
        if(cat.getNumeroCategoria() == opcion){
            return cat.getNombre();
        }
    }

}
void ProductoManager::CrearProducto(){

    Producto regitro;
    string idProducto,cuit,nombre;
    string nombreCategoria;
    float precioCompra,precioVenta,stock;
    const int TAM_CODIGO = 13;

    bool val = false;
    bool okProdu = false;


   while (true) {
        system("cls");
        cout << "INGRESAR CODIGO DE PRODUCTO (13 digitos): ";
        idProducto = CargarCadena();

        val = _validar.ValidarTamanioExactos(idProducto, TAM_CODIGO);
        if (!val) {
            cout<<"*** CODIGO INVALIDO ***" << endl;
            cout<<"Debe ser �nico y tener 13 d�gitos" << endl << endl;
            system("pause");
            continue;
        }

        int cantidad = _productArchi.getCantidadRegistro();
        if (cantidad == 0) {
            okProdu = true;
        } else {
            okProdu = _productArchi.getCodigoNuevo(idProducto);
        }

        if (!okProdu) {
            cout<<"*** CODIGO INVALIDO ***" << endl;
            cout<<"Codigo ya existente" << endl << endl;
            system("pause");
            continue;
        }

        break;
    }

    system("pause");
    system("cls");
    cout<<"CUIT PROVEEDOR: ";
    cuit = CargarCadena();

    int pos = _provArchi.buscarCuit(cuit);
    if(pos < 0){
        _provMan.AgregarProveedor();

    }else{

        Proveedor reg = _provArchi.leer(pos);
        _provMan.MostrarParaProducto(reg);
    }
    system("pause");
    system("cls");
    cout<<"NOMBRE DEL PRODUCTO: ";
    nombre = CargarCadena();
    system("pause");
    system("cls");
    cout<<"CATEGORIA: "<<endl;
    nombreCategoria = MostrarCategorias();
    system("pause");
    system("cls");
    cout<<"PRECIO DE COMPRA: $";
    cin>>precioCompra;
    precioVenta = CalcularPrecioVenta(precioCompra);
    cout<<"PRECIO DE VENTA: $"<<precioVenta<<endl;
    system("pause");
    system("cls");
    cout<<"STOCK: ";
    cin>>stock;

    regitro = Producto(idProducto,cuit,nombre,nombreCategoria,precioCompra,precioVenta,stock,true);
    bool ok = _productArchi.guardar(regitro);
    if(ok){
        Mostrar(regitro);
        cout<<endl<<"Se guardo correctamente el producto!!"<<endl;
    }else{
        cout<<"HUBO UN ERROR"<<endl;
    }
}
void ProductoManager::ModificarProducto(int opcion){
    Producto registro;
    string idProducto;
    string categoria;
    float precioCompra, precioVenta;
    bool ok;
    int pos;

    if(opcion > 0 && opcion <= 4){
        cout<<"INGRESE ID/CODIGOD DE PRODUCTO: ";
        idProducto = CargarCadena();

        pos = _productArchi.buscarIdProducto(idProducto);
        if(pos < 0){
            cout<<"ID/CODIGO INEXISTENTE" <<endl;
            return;
        }
    registro = _productArchi.leer(pos);
    }
    switch(opcion){
    case 1: {
        system("cls");
        string cuit;
        cout<<"--MODIFICAR CUIT"<<endl<<endl;
        cout<<"INGRESAR NUEVO CUIT: ";
        cuit = CargarCadena();
        if(!_validar.ValidarCuit(cuit)){
            cout<<"CUIT INVALIDO"<<endl;
            return ;
        }
        registro.setCuitProveedor(cuit);
        ok = _productArchi.guardar(pos,registro);
        if(ok){
            Mostrar(registro);
            cout<<"Actualizado correctamente!!"<<endl;
        }else{
            cout<<"Ocurrio un error en la actualizacion.Intentar de nuevo"<<endl;
        }

        break;
    }
    case 2:{
        system("cls");
        cout<<"--MODIFICAR CATEGORIA"<<endl;
        cout<<endl;
        categoria = MostrarCategorias();
        registro.setCategoria(categoria);
        ok = _productArchi.guardar(pos,registro);
        if(ok){
            Mostrar(registro);
            cout<<endl<<"Se actualizo correctamente!!"<<endl;
        }else {
            cout<<"Ocurrio un error."<<endl;
        }
        break;
    }
    case 3: {
        system("cls");
        cout<<"--MODIFICAR PRECIO DE COMPRA"<<endl<<endl;
        cout<<"PRECIO DE COMPRA ANTERIOR: "<<registro.getPrecioCompra()<<endl;
        cout<<"INGRESE NUEVO PRECIO DE COMPRA: ";
        cin>>precioCompra;
        registro.setPrecioCompra(precioCompra);
        ok = _productArchi.guardar(pos,registro);
        if(ok){
            Mostrar(registro);
            cout<<endl<<"Se actualizo correctamente"<<endl;
        }else{
            cout<<"Ocurrio un error."<<endl;
        }
        break;
    }
    case 4: {
        system("cls");
        cout<<"--MODIFICAR PRECIO DE VENTA"<<endl<<endl;
        cout<<"PRECIO DE VENTA ANTERIOR: "<<registro.getPrecioCompra()<<endl;
        cout<<"INGRESE NUEVO PRECIO DE VENTA: ";
        cin>>precioVenta;
        registro.setPrecioVenta(precioVenta);
        ok = _productArchi.guardar(pos,registro);
        if(ok){
            Mostrar(registro);
            cout<<endl<<"Se actualizo correctamente"<<endl;
        }else{
            cout<<"Ocurrio un error."<<endl;
        }
        break;
    }
    case 0:
        cout<<"Saliendo..."<<endl;
        break;
    }
}
void ProductoManager::EliminarProducto(){
    Producto registro;
    string idProducto;
    char opcion;
    bool ok;
    cout<<"--ELIMINAR PORODUCTO"<<endl<<endl;
    cout<<"INGRESE ID/CODIGO DEL PRODUCTO: ";
    idProducto = CargarCadena();
    int pos = _productArchi.buscarIdProducto(idProducto);
    if(pos < 0){
        cout<<"EL ARTICULO NO EXISTE"<<endl;
        return;
    }
    system("pause");
    system("cls");
    cout<<"ESTA SEGURO QUE DESEA ELIMINARLO? (S/N): ";
    cin>>opcion;
    if(opcion == 's' or opcion == 'S'){
            ok = _productArchi.eliminar(pos);
            registro = _productArchi.leer(pos);
            system("pause");
            system("cls");
            if(ok){
            Mostrar(registro);
            cout<<"El articulo se elimino correctamente!!"<<endl;
            }else{
                cout<<"Ocurrio un error"<<endl;
            }
    }
}

void ProductoManager::Listar(int opcion){
    int cantidad = _productArchi.getCantidadRegistro();
    Producto *vecProducto = new Producto[cantidad];

    _productArchi.LeerTodos(vecProducto,cantidad);

    int cantidadActivos = 0;
    for(int i=0;i<cantidad;i++){
        if(vecProducto[i].getEstado() == true){
            cantidadActivos++;
        }
    }

    Producto *vecActivos = new Producto[cantidadActivos];
    int contador = 0;
    for(int i=0; i<cantidad;i++){
        if(vecProducto[i].getEstado() == true){
            vecActivos[contador] = vecProducto[i];
            contador++;
        }
    }
    switch(opcion){
        case 1: {
            OrdenarNombre(vecActivos,cantidadActivos);
            for(int i=0; i<cantidadActivos;i++){
                Mostrar(vecActivos[i]);
                cout<<"-------------------------------------"<<endl;
            }
            delete[]vecActivos;
            delete[]vecProducto;
            break;
        }
        case 2:{
            OrdenarPrecioVenta(vecActivos,cantidadActivos);
            for(int i=0; i<cantidadActivos; i++){
                Mostrar(vecActivos[i]);
                cout<<"---------------------------------------"<<endl;
            }
            delete[]vecActivos;
            delete[]vecProducto;
            break;
        }
        case 3: {
            OrdenarPlu(vecActivos,cantidadActivos);
            for(int i=0; i<cantidadActivos; i++){
                Mostrar(vecActivos[i]);
                cout<<"---------------------------------------"<<endl;
            }
            delete[]vecActivos;
            delete[]vecProducto;
            break;
        }
        case 0:
            break;

    }

}
void ProductoManager::Buscar(){
    string codigo;
    Producto registro;

    cout<<"INGRESE CODIGO DE PRODUCTO A BUSCAR: ";
    codigo = CargarCadena();
    int pos = _productArchi.buscarIdProducto(codigo);

    while(pos < 0){
        cout<<"CODIGO NO ENCONTRADO"<<endl;
        cout<<"INGRESE CODIGO DE PRODUCTO A BUSCAR: ";
        codigo = CargarCadena();
        int pos = _productArchi.buscarIdProducto(codigo);
    }
    registro = _productArchi.leer(pos);
    system("pause");
    system("cls");

    cout<<"PRODUCTO RELACIONADO: "<<registro.getNombre()<<endl;
    Mostrar(registro);

}

string ProductoManager::Buscar(std::string codigo){
    Producto registro;

    int pos = _productArchi.buscarIdProducto(codigo);
    if(pos < 0 ){
        return "";
    }

    registro = _productArchi.leer(pos);
    if(registro.getEstado()){
        return registro.getNombre();
    }

    return "";

}

void ProductoManager::ConsultarStockPorCategoria(){

    int cantidadCategorias = _catArchi.getCantidadRegistro();
    Categoria *vecNumCategorias = new Categoria[cantidadCategorias];

    _catArchi.LeerTodos(vecNumCategorias,cantidadCategorias);

    cout<<"DE QUE CATEGORIA DESEA SABER LOS STOCK?: ";
    for(int i=0;i<cantidadCategorias;i++){
        cout<<"ID: #: "<<vecNumCategorias[i].getNumeroCategoria()<<endl;
        cout<<"NOMBRE: "<<vecNumCategorias[i].getNombre()<<endl<<endl;
        cout<<"---------------------------------------------------------"<<endl;
    }

    int opcion;
    cout<<"ID DE CATEGORIA: ";
    cin>>opcion;

    int cantidadProductos = _productArchi.getCantidadRegistro();
    Producto *vecProductos = new Producto [cantidadProductos];
    _productArchi.LeerTodos(vecProductos,cantidadProductos);

    system("pause");
    system("cls");

    for(int i =0; i<cantidadProductos;i++){
        if(vecProductos[i].getCategoria() == vecNumCategorias[opcion].getNombre()){
            cout<<"CODIGO DEL PRODUCTO: "<<vecProductos[i].getIdProducto()<<endl;
            cout<<"NOMBRE DEL PRODUCTO: "<< vecProductos[i].getNombre()<<endl;
            cout<<"STOCK: "<<vecProductos[i].getStock()<<endl<<endl;
            cout<<"----------------------------------------------------------------------"<<endl;
        }
    }
    delete[]vecNumCategorias;
    delete[]vecProductos;
}
void ProductoManager::AjustarStock(){
    string codigo;

    cout<<"INGRESAR CODIGO DE PRODUCTO: ";
    codigo = CargarCadena();

    int tam = 13;
    if(!_validar.ValidarTamanios(codigo,tam)){
        cout<<"CODIGO INEXISTENTE" <<endl;
        cout<<"SUGERENCIA: REVISE HABERLO CARGADO ANTES"<<endl;
        return;
    }
    int pos = _productArchi.buscarIdProducto(codigo);
    Producto registro = _productArchi.leer(pos);

    if(!registro.getEstado()){
        cout<<"PRODUCTO INACTIVO"<<endl;
        return;
    }
    cout<<"NOMBRE: "<<registro.getNombre()<<endl;
    cout<<"STOCK ACTUAL: "<<registro.getStock()<<endl<<endl;
    float stockNuevo;
    cout<<"INGRESE NUEVO STOCK: ";
    cin>>stockNuevo;
    system("pause");
    system("cls");
    cout<<"MOTIVO: "<<endl;
    string motivo = MotivosAjustes();

    registro.setStock(stockNuevo);
    registro.setMotivoStock(motivo);

    bool ok = _productArchi.guardar(pos,registro);
    if(ok){
            system("cls");
        cout<<"CODIGO DE PRODUCTO: "<<registro.getIdProducto()<<endl;
        cout<<"NOMBRE: "<<registro.getNombre()<<endl;
        cout<<"STOCK: "<<registro.getStock()<<endl;
        cout<<"MOTIVO DE AJUSTE DE STOCK: "<<registro.getMotivo()<<endl<<endl;
        cout<<"SE MODIFICO CORRECTAMENTE!!"<<endl;
    }else{
        cout<<"OCURRIO UN PROBLEMA"<<endl;
    }

}
float ProductoManager::CalcularPrecioVenta(float precioCompra){
    float precioBase = precioCompra + (precioCompra * 0.3);
    float PrecioVenta = precioBase +(precioBase * 0.21);

    return PrecioVenta;
}

void ProductoManager::Mostrar(Producto registro){
    cout<<"--DATOS DEL PRODUCTO"<<endl;
    cout<<"CUIT DEL PROVEEDOR: "<<registro.getCuitProveedor()<<endl;
    cout<<"ID/CODIGO: "<<registro.getIdProducto()<<endl;
    cout<<"NOMBRE: "<<registro.getNombre()<<endl;
    cout<<"CATEGORIA: "<<registro.getCategoria()<<endl;
    cout<<"PRECIO DE COMPRA: "<<registro.getPrecioCompra()<<endl;
    cout<<"PRECIO DE VENTA: "<<registro.getPrecioVenta()<<endl;
    cout<<"STOCK: "<<registro.getStock()<<endl;
}

void ProductoManager::OrdenarNombre(Producto *vec,int tam){
    for(int i=0; i < tam; i++){
        bool intercambio = false;
        for(int j=0; j < tam -1 -i; j++){
            if(vec[j].getNombre() > vec[j+1].getNombre()){
                Producto aux = vec[j];
                vec[j] = vec[j+1];
                vec[j+1] = aux;
                intercambio = true;
            }
        }
        if(!intercambio){
            break;
        }
    }
}
void ProductoManager::OrdenarPrecioVenta(Producto *vec, int tam){
    for(int i=0; i < tam; i++){
        bool intercambio = false;
        for(int j=0; j < tam -1 -i; j++){
            if(vec[j].getPrecioVenta() > vec[j+1].getPrecioVenta()){
                Producto aux = vec[j];
                vec[j] = vec[j+1];
                vec[j+1] = aux;
                intercambio = true;
            }
        }
        if(!intercambio){
            break;
        }
    }
}
void ProductoManager::OrdenarPlu(Producto *vec, int tam){
    for(int i=0; i < tam; i++){
        bool intercambio = false;
        for(int j=0; j < tam -1 -i; j++){
            if(vec[j].getIdProducto() > vec[j+1].getIdProducto()){
                Producto aux = vec[j];
                vec[j] = vec[j+1];
                vec[j+1] = aux;
                intercambio = true;
            }
        }
        if(!intercambio){
            break;
        }
    }

}

string ProductoManager::MotivosAjustes(){
   string vecMotivos[5] = {"Error de carga inicial",
                            "Perdida/roto/vencido",
                            "Robo",
                            "Inventario fisico",
                            "Devoluciones internas"};

    cout<<"--OPCIONES MOTIVOS"<<endl;
    for(int i=0;i<5;i++){
        cout<<i+1<<" "<<vecMotivos[i]<<endl;
    }
    int opcion;
    cout<<endl<<"OPCION: ";
    cin>>opcion;

    while(opcion < 1 || opcion > 5 ){
        cout<<"--OPCIONES MOTIVOS"<<endl;
        for(int i=0;i<5;i++){
        cout<<i+1<<" "<<vecMotivos[i]<<endl;
        }
        int opcion;
        cout<<endl<<"OPCION: ";
        cin>>opcion;
    }

    return vecMotivos[opcion-1];

}

float ProductoManager::getPrecioVenta(string codigo){

    float precioVenta;
    Producto registro;

    int pos = _productArchi.buscarIdProducto(codigo);
    if(pos < 0){
            precioVenta = 0.0;
        return precioVenta;
    }

    registro = _productArchi.leer(pos);
    precioVenta = registro.getPrecioVenta();

    return precioVenta;
}

float ProductoManager::getStockActual(string codigo){

    float stock;
    Producto registro;

    int pos = _productArchi.buscarIdProducto(codigo);

    if(pos < 0){
        stock = 0.0;
    }

    registro = _productArchi.leer(pos);
    stock = registro.getStock();

    return stock;

}

bool ProductoManager::descontarStock(string codigo,int cantidad){
    int pos = _productArchi.buscarIdProducto(codigo);
    if(pos < 0) return false;

    Producto registro = _productArchi.leer(pos);
    if(!registro.getEstado()) return false;

    if(registro.getStock() < cantidad) return false;

    registro.setStock(registro.getStock() - cantidad);

    return _productArchi.guardar(pos,registro);

}

bool ProductoManager::restaurarStock(string codigo, float cantidad){
    int pos = _productArchi.buscarIdProducto(codigo);
    if(pos < 0) return false;

    Producto registro = _productArchi.leer(pos);
    if(!registro.getEstado()) return false;

    registro.setStock(registro.getStock() + cantidad);

    return _productArchi.guardar(pos,registro);
}
