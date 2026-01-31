#include "ClienteManager.h"
#include <cstring>
#include <iostream>
#include<limits>

using namespace std;
ClienteManager::ClienteManager(){
}

string ClienteManager::CargarCadena(){
    string texto;
    if(cin.peek()=='\n'){
        cin.ignore();
    }
    getline(cin,texto);
    return texto;
}

void ClienteManager::AgregarCliente(){
    Cliente registro;
    int id,dia,mes,anio;
    int edad;
    std::string nombre, apellido,dni,direccion,telefono,mail;
    bool estado;

    id = _cArchi.getIdNuevo();
    cout<<"NOMBRE: ";
    nombre = CargarCadena();
    cout<<"APELLIDO: ";
    apellido = CargarCadena();
    cout<<"DNI: ";
    dni = CargarCadena();
    if(_cArchi.ValidarDni(dni)){
        cout<<"DNI INCORRECTO.Numero ya registrado..."<<endl;
        return;
    }
    cout<<"FECHA DE NACIMINETO "<<endl;
    cout<<"DIA: ";
    cin>>dia;
    cout<<"MES: ";
    cin>>mes;
    cout<<"ANIO: ";
    cin>>anio;
    if(!_fecha.validarFecha(dia,mes,anio)){
        cout<<"Fecha inexistente..."<<endl;
        return;
    }
    edad = _fecha.ObtenerEdad(dia,mes,anio);
    cout<<"EDAD: "<<edad<<endl;
    cout<<"DIRECCION: ";
    direccion = CargarCadena();
    cout<<"TELEFONO: ";
    telefono = CargarCadena();
    cout<<"MAIL: ";
    mail = CargarCadena();

    registro = Cliente(nombre,apellido,dni,direccion,telefono,mail,Fecha(dia,mes,anio),edad,true,id);

    if(_cArchi.guardar(registro)){
            system("cls");
            MostrarCliente(registro);
        cout<<"Se guardo exitosamente!."<<endl;
    }else{
        cout<<"Ocurrio un error, no se pudo guardar correctamente."<<endl;
        cout<<"Vuelvalo a intentar mas tarde..."<<endl;
    }
}

void ClienteManager::EliminarCliente(){
    int id;
    char eliminado;
    Cliente cliente;

    cout<<"--- ELIMINAR CLIENTE "<<endl;
    cout<<"Ingresar id de cliente a eliminar: ";
    cin>>id;

    cliente = _cArchi.leer(id -1);
    cout<<"Datos del cliente: "<<endl;
    MostrarCliente(cliente);
    cout<<endl<<"Eliminar? S/N: ";
    cin>>eliminado;

    if(eliminado == 's' or eliminado == 'S'){
        cliente.setEstado(false);
    }else{
        cliente.setEstado(true);
    }

    if(_cArchi.eliminar(id-1)){
        cout<<"La tarea fue eliminada correctamente..."<<endl;
    }else{
        cout<<"Hubo un error en la eliminacion..."<<endl;
    }

}
void ClienteManager::Modificar(int opcion){
    string dni;
    bool ok;
    Cliente registro;

    if(opcion == 0){
        system("cls");
        cout<<"Saliendo..."<<endl;
        return;
    }


    cout<<"INGRESAR DNI DEL CLIENTE: ";
    dni = CargarCadena();

    int pos = _cArchi.buscarDni(dni);
    if(pos < 0){
        cout<<"DNI INEXISTENTE EN LA BASE DE DATOS..."<<endl;
        cout<<"OPCION 1 (ALTA CLIENTE)"<<endl;
        return;
    }
    registro = _cArchi.leer(pos);
    if(!registro.getEstado()){
            cout<<"CLIENTE NO ACTIVO"<<endl;
            cout<<"SI DESEA ACTIVARLO, DIRIJASE A CONFIGURACION"<<endl;
            return;
    }

    system("pause");
    system("cls");
    MostrarCliente(registro);
    cout<<endl;
    switch(opcion){
    case 1: {
        system("cls");
        string telefono;
        cout<<"--MODIFICAR TELEFONO"<<endl<<endl;
        cout<<"NUMERO TELEFONO NUEVO: ";
        telefono = CargarCadena();
        registro.setTelefono(telefono);
        ok = _cArchi.guardar(pos,registro);
        if(ok){
                system("cls");
            MostrarCliente(registro);
            cout<<"FUE ACTUALIZADO CORRECTAMENTE!!"<<endl;
        }
        break;
    }
    case 2:{
        system("cls");
        string direccion;
        cout<<"--MODIFICAR DIRECCION"<<endl<<endl;
        cout<<"DIRECCION NUEVA: ";
        direccion = CargarCadena();
        registro.setDireccion(direccion);
        ok = _cArchi.guardar(pos,registro);
        if(ok){
                system("cls");
            MostrarCliente(registro);
            cout<<"FUE ACTUALIZADO CORRECTAMENTE!!"<<endl;
        }
        break;
        }
    case 3: {
        system("cls");
        string mail;
        cout<<"--MODIFICAR MAIL"<<endl<<endl;
        cout<<"DIRECCION DE MAIL NUEVA: ";
        mail = CargarCadena();
        registro.setMail(mail);
        ok = _cArchi.guardar(pos,registro);
        if(ok){
                system("cls");
            MostrarCliente(registro);
            cout<<"FUE ACTUALIZADO CORRECTAMENTE!!"<<endl;
        }
        break;
    }
    }

}



void ClienteManager::ListadoOpcion(int opcion){
    switch(opcion){
    case 1:{
        system("cls");
        cout<<"-- OPCION: ORDENADO POR APELLIDO"<<endl<<endl;
        listarPorApellido();
        break;
    }
    case 2:{
        system("cls");
        cout<<"-- OPCION: ORDENADO POR NOMBRE"<<endl<<endl;
        listarPorNombre();
        break;
    }
    case 3:{
        system("cls");
        cout<<"-- OPCION: ORDENADO POR EDAD"<<endl<<endl;
        listarPorEdad();
        break;
    }
    case 0:{
        cout<<"Saliendo..."<<endl;
        break;
    }
    }
}

void ClienteManager::listarPorApellido(){

  int cantidad = _cArchi.getCantidadRegistro();
    Cliente *clientes = new Cliente[cantidad];
    _cArchi.LeerTodos(clientes,cantidad);

    int cantidadActivos = 0;
    for(int i=0;i<cantidad;i++){
        if(clientes[i].getEstado()){
            cantidadActivos++;
        }
    }

    Cliente *clientesActivos = new Cliente[cantidadActivos];
    int contador =0;
    for(int i=0;i<cantidad;i++){
        if(clientes[i].getEstado()){
            clientesActivos[contador] = clientes[i];
            contador++;
        }
    }

    for(int i=0;i<cantidadActivos;i++){
        bool intercambio = false;
        for(int j=0;j<cantidadActivos - 1 -i;j++){
            if(clientesActivos[j].getApellido()> clientesActivos[j+1].getApellido()){
                Cliente aux = clientesActivos[j];
                clientesActivos[j] = clientesActivos[j+1];
                clientesActivos[j+1] = aux;
                intercambio = true;
            }
        }
        if(!intercambio){
            break;
        }
    }

    for(int i=0;i<cantidad;i++){
        MostrarCliente(clientesActivos[i]);
        cout<<"-----------------"<<endl;
    }

    delete[]clientes;
    delete[]clientesActivos;
}
void ClienteManager::listarPorNombre(){
    int cantidad = _cArchi.getCantidadRegistro();
    Cliente *clientes = new Cliente[cantidad];
    _cArchi.LeerTodos(clientes,cantidad);

    int cantidadActivos = 0;
    for(int i=0;i<cantidad;i++){
        if(clientes[i].getEstado()){
            cantidadActivos++;
        }
    }

    Cliente *clientesActivos = new Cliente[cantidadActivos];
    int contador =0;
    for(int i=0;i<cantidad;i++){
        if(clientes[i].getEstado()){
            clientesActivos[contador] = clientes[i];
            contador++;
        }
    }

    for(int i=0;i<cantidadActivos;i++){
        bool intercambio = false;
        for(int j=0;j<cantidadActivos - 1 -i;j++){
            if(clientesActivos[j].getNombre() > clientesActivos[j+1].getNombre()){
                Cliente aux = clientesActivos[j];
                clientesActivos[j] = clientesActivos[j+1];
                clientesActivos[j+1] = aux;
                intercambio = true;
            }
        }
        if(!intercambio){
            break;
        }
    }

    for(int i=0;i<cantidad;i++){
        MostrarCliente(clientesActivos[i]);
        cout<<"-----------------"<<endl;
    }
    delete[]clientes;
    delete[]clientesActivos;
}

void ClienteManager::listarPorEdad(){

    int cantidad = _cArchi.getCantidadRegistro();
    Cliente *clientes = new Cliente[cantidad];
    _cArchi.LeerTodos(clientes,cantidad);

    int cantidadActivos = 0;
    for(int i=0;i<cantidad;i++){
        if(clientes[i].getEstado()){
            cantidadActivos++;
        }
    }

    Cliente *clientesActivos = new Cliente[cantidadActivos];
    int contador =0;
    for(int i=0;i<cantidad;i++){
        if(clientes[i].getEstado()){
            clientesActivos[contador] = clientes[i];
            contador++;
        }
    }

    for(int i=0;i<cantidadActivos;i++){
        bool intercambio = false;
        for(int j=0;j<cantidadActivos - 1 -i;j++){
            if(clientesActivos[j].getEdad() > clientesActivos[j+1].getEdad()){
                Cliente aux = clientesActivos[j];
                clientesActivos[j] = clientesActivos[j+1];
                clientesActivos[j+1] = aux;
                intercambio = true;
            }
        }
        if(!intercambio){
            break;
        }
    }

    for(int i=0;i<cantidad;i++){
        MostrarCliente(clientesActivos[i]);
        cout<<"-----------------"<<endl;
    }
    delete[]clientes;
    delete[]clientesActivos;
}

Cliente ClienteManager::buscarPorDni(){
    string dni;
    int tamDni = 8;

    cout<<"INGRESE DNI DEL CLIENTE: ";
    dni = CargarCadena();

    bool validacion = _validar.ValidarTamanioExactos(dni,tamDni);

    while(validacion == false){
       cout<<"INGRESE NUEVAMENTE EL DNI: ";
       dni = CargarCadena();
       validacion = _validar.ValidarTamDni(dni);
    }

    int pos = _cArchi.buscarDni(dni);

    if(pos < 0){
        return Cliente();
    }else{
    Cliente registro =_cArchi.leer(pos);
    return registro;
    }
}

void ClienteManager::buscar(){
    string dni;
    int tamDni = 8;
    Cliente registro;

    while(true){
        cout<<"INGRESE DNI DEL CLIENTE: ";
        dni = CargarCadena();
        if(!_validar.ValidarTamanioExactos(dni,tamDni)){
            cout<<"** DNI INCORRECTO **"<<endl;
            cout<<"Debe contener 8 caracteres"<<endl;
            continue;
        }
        int pos = _cArchi.buscarDni(dni);
        if(pos < 0){
            cout<<"CLIENTE NO REGISTRADO"<<endl;
            return;
        }

        registro = _cArchi.leer(pos);
        cout<<"--DATOS DEL CLIENTE BUSCADO"<<endl<<endl;
        MostrarCliente(registro);
        break;
    }

}

void ClienteManager::MostrarCliente(Cliente cliente){
    std::cout<<"ID: "<<cliente.getIdCliente()<<std::endl;
    std::cout<<"NOMBRE: "<<cliente.getNombre()<<std::endl;
    std::cout<<"APELLIDO: "<<cliente.getApellido()<<std::endl;
    std::cout<<"DNI: "<<cliente.getDni() <<std::endl;
    std::cout<<"EDAD: "<<cliente.getEdad()<<endl;
    std::cout<<"DIRECCION: "<<cliente.getDireccion()<<std::endl;
    std::cout<<"TELEFONO: "<<cliente.getTelefono()<<std::endl;
    std::cout<<"MAIL: "<<cliente.getMail()<<std::endl;
}
