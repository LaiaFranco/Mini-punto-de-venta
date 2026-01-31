#include "Producto.h"
#include<cstring>

Producto::Producto(){
    strcpy(_idProducto,"");
    strcpy(_categoria,"");
    strcpy(_cuitProveedor,"");
    strcpy(_nombre,"");
    _precioCompra = 0.0;
    _precioVenta = 0.0;
    _stock = 0.0;
    _estado = false;
}

Producto::Producto(std::string id,std::string cuit,std::string nombre, std::string categoria,float precioCompra,float precioVenta,float stock, bool estado){
    setIdProducto(id);
    setCuitProveedor(cuit);
    setNombre(nombre);
    setCategoria(categoria);
    setPrecioCompra(precioCompra);
    setPrecioVenta(precioVenta);
    setStock(stock);
    setEstado(estado);
}

std::string Producto::getIdProducto(){
return _idProducto;}
std::string Producto::getCategoria(){
return _categoria;}
std::string Producto::getCuitProveedor(){
return _cuitProveedor;}
std::string Producto::getNombre(){
return _nombre;}
std::string Producto::getMotivo(){
return _MotivoStcok;}
float Producto::getPrecioCompra(){
return _precioCompra;}
float Producto::getPrecioVenta(){
return _precioVenta;}
float Producto::getStock(){
return _stock;}
bool Producto::getEstado(){
return _estado;}

void Producto::setIdProducto(std::string  id){
    if(id.size() <= 15){
        strncpy(_idProducto,id.c_str(),14);
        _idProducto[14] = '\0';
    }
}
void Producto::setCuitProveedor(std::string cuit){
    if(cuit.size() <= 13){
        strncpy(_cuitProveedor,cuit.c_str(),12);
        _cuitProveedor[12] = '\0';
    }
}
void Producto::setNombre(std::string nombre){
    if(nombre.size() <= 100){
        strncpy(_nombre,nombre.c_str(),100);
        _nombre[99] = '\0';
    }
}
void Producto::setCategoria(std::string categoria){
     if(categoria.size() <= 50){
     strncpy(_categoria,categoria.c_str(),50);
        _categoria[49] = '\0';
     }
}
void Producto::setMotivoStock(std::string motivo){
    if(motivo.size() <= 100){
        strncpy(_MotivoStcok,motivo.c_str(),100);
        _MotivoStcok[99] = '\0';
    }
}
void Producto::setPrecioCompra(float precioCompra){
    _precioCompra = precioCompra;
}
void Producto::setPrecioVenta(float precioVenta){
    _precioVenta = precioVenta;
}
void Producto::setStock(float stock){
    _stock = stock;
}
void Producto::setEstado(bool estado){
    _estado = estado;
}


