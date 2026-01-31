#include "SubMenu.h"
#include <iostream>

using namespace std;
SubMenu::SubMenu(){

}

int SubMenu::SubMenuModificar(){
    int opcion;
    system("cls");
    cout<<"QUE DESEA MODIFICAR? "<<endl;
    cout<<"1.ROL"<<endl;
    cout<<"2.TELEFONO"<<endl;
    cout<<"3.DIRECCION"<<endl;
    cout<<"4.MAIL"<<endl;

    cout<<endl<<"OPCION: ";
    cin>>opcion;

    return opcion;
}
int SubMenu::SubMenuModificarCliente(){

    int opcion;
    while(true){
    system("cls");
    cout<<"QUE DESEA MODIFICAR? "<<endl;
    cout<<"1.TELEFONO"<<endl;
    cout<<"2.DIRECCION"<<endl;
    cout<<"3.MAIL"<<endl;
    cout<<"0.SALIR"<<endl;

    cout<<endl<<"OPCION: ";
    cin>>opcion;
    if(opcion >=0 && opcion <=3){
        return opcion;
        break;
    }
    continue;
    }
}
int SubMenu::SubMenuListar(){
    int opcion;
    while(true){
    system("cls");
    cout<<"LISTADO ORDENADO POR: "<<endl;
    cout<<"1.POR APELLIDO"<<endl;
    cout<<"2.POR NOMBRE"<<endl;
    cout<<"3.POR EDAD"<<endl;
    cout<<"0.SALIR"<<endl;

    cout<<endl<<"-Opcion: ";
    cin>>opcion;

    if(opcion >= 0 && opcion <= 3){
        return opcion;
        break;

    }
    continue;

    }
}

int SubMenu::SubMenuModificarCat(){
    int opcion;
    system("pause");
    system("cls");
    cout<<"QUE DESEA MODIFICAR? "<<endl;
    cout<<"1.NOMBRE DE CATEGORIA"<<endl;
    cout<<"2.DESCRIPCION DE CATEGORIA" <<endl;
    cout<<"0.NO DESEO MODIFICAR NADA/SALIR"<<endl;

    cout<<endl<<"-Opcion: ";
    cin>>opcion;

    return opcion;
}

int SubMenu::SubMenuModificarProducto(){
    int opcion;
    system("cls");
    cout<<"QUE DESEA MODIFICAR?" <<endl;
    cout<<"1. CUIT DE PROVEEDOR" <<endl;
    cout<<"2. CATEGORIA DEL PRODUCTO"<<endl;
    cout<<"3. PRECIO DE COMPRA"<<endl;
    cout<<"4. PRECIO DE VENTA"<<endl;
    cout<<"0. SALIR" <<endl;
    cout<<endl<<"OPCION: ";
    cin>>opcion;

    return opcion;
}

int SubMenu::SubMenuModificarProveedor(){
    int opcion;
    system("cls");
    cout<<"QUE DESEA MODIFICAR?"<<endl;
    cout<<"1. NOMBRE"<<endl;
    cout<<"2. DIRECCION"<<endl;
    cout<<"3. TELEFONO"<<endl;
    cout<<"4. EMAIL"<<endl;
    cout<<"0. SALIR"<<endl;
    cout<<endl<<"OPCION: ";
    cin>>opcion;
    
    return opcion;
}

int SubMenu::SubMenuListarProducto(){
    int opcion;
    while(true){
    system("cls");
    cout<<"LISTADO ORDENADO POR: "<<endl;
    cout<<"1. POR NOMBRE"<<endl;
    cout<<"2. POR PRECIO DE VENTA" <<endl;
    cout<<"3. POR PLU/CODIGO" <<endl;
    cout<<"0. SALIR" <<endl<<endl;

    cout<<"OPCION: ";
    cin>>opcion;
    if(opcion >= 0 && opcion <=3){
            return opcion;
            break;

    }
    continue;

    }
}
