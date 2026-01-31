#include "Venta.h"
#include<cstring>
#include<iostream>

Venta::Venta()
:_numeroTransaccion(0),_fecha(Fecha()),_total(0.0){
    strcpy(_legajoEmpleado,"");
    strcpy(_dniCliente,"");
}
Venta::Venta(int numero,std::string legajo,std::string dni,Fecha fecha,float total){
    setNumTransaccion(numero);
    setLegajoEmpleado(legajo);
    setDniCliente(dni);
    setFecha(fecha);
    setTotal(total);
}

int Venta::getNumTransaccion(){
return _numeroTransaccion;}
std::string Venta::getLegajoEmpleado(){
return _legajoEmpleado;}
std::string Venta::getDniCliente(){
return _dniCliente;}
Fecha Venta::getFecha(){
return _fecha;}
float Venta::getTotal(){
return _total;}

void Venta::setNumTransaccion(int numero){
    _numeroTransaccion = numero;
}
void  Venta::setLegajoEmpleado(std::string legajo){
    if(legajo.size() <= 10){
    strncpy(_legajoEmpleado,legajo.c_str(),9);
    _legajoEmpleado[9] = '\0';
    }
}
void Venta::setDniCliente(std::string dni){
    if(dni.size() <= 10){
    strncpy(_dniCliente,dni.c_str(),9);
    _dniCliente[9] = '\0';
    }
}
void Venta::setFecha(Fecha fecha){
    _fecha = fecha;
}
void Venta::setTotal(float total){
    _total = total;
}
void Venta::Mostrar(){
    std::cout<<"--DATOS DE LA VENTA"<<std::endl;
    std::cout<<"FECHA"<<getFecha().toString()<<std::endl;
    std::cout<<"TRANSANCCION: "<<getNumTransaccion()<<std::endl;
    std::cout<<"ATENDIDO POR: "<<getLegajoEmpleado()<<std::endl;
    std::cout<<"CLIENTE DNI:"<<getDniCliente()<<std::endl;
    std::cout<<"TOTAL:"<<getTotal()<<std::endl;
}
