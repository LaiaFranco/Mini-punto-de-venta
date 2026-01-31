#include "DetalleVenta.h"
#include<cstring>

DetalleVenta::DetalleVenta(){
    _idDetalle = 0;
    _idVenta = 0;
    strcpy(_idProducto,"");
    _cantidad = 0.0;
    _PrecioVenta = 0.0;
}
DetalleVenta::DetalleVenta(int id,int idVenta,std::string idProducto,float cantidad,float precioVenta){
    setIdDetalle(id);
    setIdVenta(idVenta);
    setIdProducto(idProducto);
    setCantidad(cantidad);
    setPrecioVenta(precioVenta);
}

int DetalleVenta::getIdDetalle(){
return _idDetalle;}
int DetalleVenta::getIdVenta(){
return _idVenta;}
std::string DetalleVenta::getIdProducto(){
return _idProducto;}
float DetalleVenta::getCantidad(){
return _cantidad;}
float DetalleVenta::getPrecioVenta(){
return _PrecioVenta;}

void DetalleVenta::setIdDetalle(int id){
    _idDetalle = id;
}
void DetalleVenta::setIdVenta(int id){
    _idVenta = id;
}
void DetalleVenta::setIdProducto(std::string id){
    strncpy(_idProducto,id.c_str(),14);
    _idProducto[14] = '\0';
}
void DetalleVenta::setCantidad(float cantidad){
    _cantidad = cantidad;
}
void DetalleVenta::setPrecioVenta(float precio){
    _PrecioVenta = precio;
}
