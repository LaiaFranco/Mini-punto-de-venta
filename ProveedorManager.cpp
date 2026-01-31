#include "ProveedorManager.h"
#include<iostream>

using namespace std;
ProveedorManager::ProveedorManager(){
}
string ProveedorManager::CargarCadena(){
    string texto;
    if(cin.peek()=='\n'){
        cin.ignore();
    }
    getline(cin,texto);
    return texto;
}

void ProveedorManager::AgregarProveedor(){

    Proveedor registro;
    string cuit, nombre, direccion, telefono,email;
    bool estado;

    system("cls");

    cout<<"--AGREGAR PROVEEDOR"<<endl<<endl;
    cout<<"CUIT: ";
    cuit = CargarCadena();
    if(!_validador.ValidarCuit(cuit)){
        cout<<"CUIT INCORRECTO...Vuelva a intentar"<<endl;
        return;
    }
    int pos =_provArchi.buscarCuit(cuit);
    if(pos >= 0){
        cout<<"CUIT YA EXISTENTE"<<endl;
        return;
    }
    cout<<"NOMBRE: ";
    nombre = CargarCadena();
    cout<<"DIRECCION: ";
    direccion = CargarCadena();
    cout<<"TELEFONO: ";
    telefono = CargarCadena();
    cout<<"EMAIL: ";
    email = CargarCadena();

    registro = Proveedor(cuit,nombre,direccion,telefono,email,true);
    bool ok;
    ok = _provArchi.guardar(registro);
    if(ok){
        Mostrar(registro);
        cout<<endl;
        cout<<"Se guardo correctamente!!"<<endl;
    }

}

void ProveedorManager::Mostrar(Proveedor registro){
    system("pause");
    system("cls");
    cout<<"-DATOS DEL PROVEEDOR"<<endl<<endl;
    cout<<"CUIT: "<<registro.getCuit()<<endl;
    cout<<"NOMBRE: "<<registro.getNombre()<<endl;
    cout<<"DIRECCION: "<<registro.getDireccion()<<endl;
    cout<<"TELEFONO: "<<registro.getTelefono()<<endl;
    cout<<"E-MAIL: "<<registro.getEmail()<<endl;
}

void ProveedorManager::ModificarProveedor(int opcion){
    string cuit;
    Proveedor registro;
    bool ok;
    
    cout<<"INGRESE CUIT DEL PROVEEDOR: ";
    cuit = CargarCadena();
    
    int pos = _provArchi.buscarCuit(cuit);
    if(pos < 0){
        cout<<"** CUIT NO ENCONTRADO **"<<endl;
        return;
    }
    
    registro = _provArchi.leer(pos);
    if(!registro.getEstado()){
        cout<<"** PROVEEDOR INACTIVO **"<<endl;
        return;
    }
    
    Mostrar(registro);
    cout<<endl;
    
    switch(opcion){
    case 1:{
        system("pause");
        system("cls");
        string nombre;
        cout<<"NOMBRE NUEVO: ";
        nombre = CargarCadena();
        registro.setNombre(nombre);
        ok = _provArchi.guardar(pos, registro);
        if(ok){
            cout<<"** PROVEEDOR MODIFICADO CORRECTAMENTE **"<<endl;
            Mostrar(registro);
        }
        break;
    }
    case 2:{
        system("pause");
        system("cls");
        string direccion;
        cout<<"DIRECCION NUEVA: ";
        direccion = CargarCadena();
        registro.setDireccion(direccion);
        ok = _provArchi.guardar(pos, registro);
        if(ok){
            cout<<"** PROVEEDOR MODIFICADO CORRECTAMENTE **"<<endl;
            Mostrar(registro);
        }
        break;
    }
    case 3:{
        system("pause");
        system("cls");
        string telefono;
        cout<<"TELEFONO NUEVO: ";
        telefono = CargarCadena();
        registro.setTelefono(telefono);
        ok = _provArchi.guardar(pos, registro);
        if(ok){
            cout<<"** PROVEEDOR MODIFICADO CORRECTAMENTE **"<<endl;
            Mostrar(registro);
        }
        break;
    }
    case 4:{
        system("pause");
        system("cls");
        string email;
        cout<<"EMAIL NUEVO: ";
        email = CargarCadena();
        registro.setEmail(email);
        ok = _provArchi.guardar(pos, registro);
        if(ok){
            cout<<"** PROVEEDOR MODIFICADO CORRECTAMENTE **"<<endl;
            Mostrar(registro);
        }
        break;
    }
    }
}

void ProveedorManager::EliminarProveedor(){
    string cuit;
    char opcion;
    Proveedor registro;
    
    cout<<"INGRESE CUIT DEL PROVEEDOR: ";
    cuit = CargarCadena();
    
    int pos = _provArchi.buscarCuit(cuit);
    if(pos < 0){
        cout<<"** CUIT NO ENCONTRADO **"<<endl;
        return;
    }
    
    registro = _provArchi.leer(pos);
    Mostrar(registro);
    cout<<endl<<"ESTA SEGURO QUE DESEA ELIMINARLO? (S/N): ";
    cin>>opcion;
    
    if(opcion == 's' || opcion == 'S'){
        bool ok = _provArchi.eliminar(pos);
        if(ok){
            cout<<"** PROVEEDOR ELIMINADO CORRECTAMENTE **"<<endl;
        } else {
            cout<<"** ERROR AL ELIMINAR PROVEEDOR **"<<endl;
        }
    }
}

void ProveedorManager::ListarProveedores(){
    system("cls");
    int cantidad = _provArchi.getCantidadRegistro();
    
    if(cantidad == 0){
        cout<<"** NO HAY PROVEEDORES REGISTRADOS **"<<endl;
        system("pause");
        return;
    }
    
    int cantidadActivos = 0;
    for(int i = 0; i < cantidad; i++){
        Proveedor prov = _provArchi.leer(i);
        if(prov.getEstado()){
            cantidadActivos++;
        }
    }
    
    if(cantidadActivos == 0){
        cout<<"** NO HAY PROVEEDORES ACTIVOS **"<<endl;
        system("pause");
        return;
    }
    
    cout<<"==========================================="<<endl;
    cout<<"       LISTADO DE PROVEEDORES ACTIVOS     "<<endl;
    cout<<"==========================================="<<endl;
    
    for(int i = 0; i < cantidad; i++){
        Proveedor prov = _provArchi.leer(i);
        if(prov.getEstado()){
            Mostrar(prov);
            cout<<"-------------------------------------------"<<endl;
        }
    }
    system("pause");
}

void ProveedorManager::BuscarProveedor(){
    string cuit;
    
    cout<<"INGRESE CUIT DEL PROVEEDOR: ";
    cuit = CargarCadena();
    
    int pos = _provArchi.buscarCuit(cuit);
    if(pos < 0){
        cout<<"** PROVEEDOR NO ENCONTRADO **"<<endl;
        system("pause");
        return;
    }
    
    Proveedor registro = _provArchi.leer(pos);
    if(!registro.getEstado()){
        cout<<"** PROVEEDOR INACTIVO **"<<endl;
        system("pause");
        return;
    }
    
    system("cls");
    cout<<"--DATOS DEL PROVEEDOR BUSCADO"<<endl<<endl;
    Mostrar(registro);
    system("pause");
}

void ProveedorManager::MostrarParaProducto(Proveedor registro){
    cout<<"NOMBRE: "<<registro.getNombre()<<endl;
    cout<<"TELEFONO: "<<registro.getTelefono()<<endl;
}
