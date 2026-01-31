#include "CategoriaManager.h"
#include<iostream>

using namespace std;
CategoriaManager::CategoriaManager(){
}
string CategoriaManager::CargarCadena(){
    string texto;
    if(cin.peek()=='\n'){
        cin.ignore();
    }
    getline(cin,texto);
    return texto;
}
void CategoriaManager::AgregarCategoria(){
    Categoria registro;
    int numeroCategoria;
    string nombre, descripcion;

    while(true){
    numeroCategoria = _catArch.getIdNuevo();
    cout<<"--CARGAR CATEGORIA"<<endl<<endl;
    cout<<"NUMERO DE CATEGORIA: #"<<numeroCategoria<<endl;
    cout<<"NOMBRE (ej -> 'Lacteos'): ";
    nombre = CargarCadena();
    int opcion =_catArch.existeCategoria(nombre);

    if(opcion == 0){
        cout<<"ESA CATEGORIA YA EXISTE"<<endl;
        return;
    }else if(opcion == 1){
        cout<<"CATEGORIA EXISTENTE, PERO INACTIVA/ELIMINADA"<<endl;
        return;
    }

    cout<<"DESCRIPCION (ej ->'Leche, yogures, quesos y mantecas frescas o procesadas'): ";
    descripcion = CargarCadena();


    registro = Categoria(numeroCategoria,nombre,descripcion,true);

    if(_catArch.guardar(registro)){
        system("pause");
        system("cls");
        Mostrar(registro);
        cout<<endl;
        cout<<"Se guardo exitosamente!!"<<endl;
        break;

    }else{
        cout<<"Ocurrio un error...Vuelva a intentar"<<endl;
        break;
    }
    }

}
void CategoriaManager::ModificarCategoria(int opcion){
    Categoria registro;
    int numCategoria;
    bool ok;
    int pos;
    if(opcion > 0 && opcion <=2){
    cout<<"INGRESE ID/NUMERO DE CATEGORIA: ";
    cin>>numCategoria;

     pos = _catArch.buscarId(numCategoria);
    if(pos < 0){
        cout<<"ID INEXISTENTE"<<endl;
        return;
    }
    registro = _catArch.leer(pos);
    }
    switch(opcion){
    case 1:{
        system("pause");
        system("cls");
        string nombre;
        cout<<"INRGESAR NUEVO NOMBRE PARA LA CATEGORIA: ";
        nombre = CargarCadena();
        registro.setNombre(nombre);
        ok =  _catArch.guardar(pos,registro);
        MostrarActualizacion(ok,registro);
        break;
    }
    case 2:{
        system("pause");
        system("cls");
        string descripcion;
        cout<<"INRGESAR NUEVA DESCRIPCION PARA LA CATEGORIA: ";
        descripcion = CargarCadena();
        registro.setDescripcioon(descripcion);
        ok =  _catArch.guardar(pos,registro);
        MostrarActualizacion(ok,registro);
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

void CategoriaManager::Mostrar(Categoria registro){
    std::cout<<"--DATOS DE LA CATEGORIA"<<std::endl<<std::endl;
    std::cout<<"NUMERO: "<<registro.getNumeroCategoria()<<std::endl;
    std::cout<<"NOMBRE: "<<registro.getNombre()<<std::endl;
    std::cout<<"DESCRIPCION: "<<registro.getDescripcion()<<std::endl;
}

void CategoriaManager::MostrarActualizacion(bool ok, Categoria reg){
    if(ok){
        system("pause");
        system("cls");
        cout<<"ACTUALIZACION..."<<endl;
        Mostrar(reg);
    }else{
        system("pause");
        system("cls");
        cout<<"NO SE PUDO ADCTUALIZAR CORRECTAMENTE"<<endl;
    }

}
void CategoriaManager::EliminarCategoria(){
     Categoria registro;
    int numCategoria;
    bool ok;

    cout<<"INGRESE ID/NUMERO DE CATEGORIA: ";
    cin>>numCategoria;

    int pos = _catArch.buscarId(numCategoria);
    if(pos < 0){
        cout<<"ID INEXISTENTE"<<endl;
        return;
    }

    registro = _catArch.leer(pos);

    system("pause");
    system("cls");
    Mostrar(registro);

    char opcion;
    cout<<endl<<"Desea eliminar esta categoria? (S/N) ";
    cin>>opcion;
    if(opcion == 's' or opcion == 'S'){
        system("pause");
        system("cls");
        registro.setEstado(false);
        ok =  _catArch.guardar(pos,registro);
        MostrarActualizacion(ok,registro);
        cout<<"SE HA ELIMINADO CORRECTAMENTE" <<endl;
    }
}

void CategoriaManager::ListarCategorias(){

    int cantidad = _catArch.getCantidadRegistro();
    Categoria *vecCategoria = new Categoria[cantidad];

    _catArch.LeerTodos(vecCategoria,cantidad);

    for(int i=0;i<cantidad;i++){
            if(vecCategoria[i].getEstado()){
                Mostrar(vecCategoria[i]);
                cout<<"--------------------------------------------"<<endl;
            }
    }
}
