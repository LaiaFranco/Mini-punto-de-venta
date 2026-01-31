#include "Categoria.h"
#include<cstring>
#include<iostream>

Categoria::Categoria()
:_numeroCategoria(0),_estado(false){
    strcpy(_nombre,"");
    strcpy(_descripcion,"");

}
Categoria::Categoria(int numero, std::string nombre,std::string descripcion,bool estado){
    setNumeroCategoria(numero);
    setNombre(nombre);
    setDescripcioon(descripcion);
    setEstado(estado);
}

int Categoria::getNumeroCategoria(){
return _numeroCategoria;}
std::string Categoria::getNombre(){
return _nombre;}
std::string Categoria::getDescripcion(){
return _descripcion;}
bool Categoria::getEstado(){
return _estado;}

void Categoria::setNumeroCategoria(int numero){
    _numeroCategoria = numero;
}
void Categoria::setNombre(std::string nombre){
    if(nombre.size() <= 30){
        strncpy(_nombre,nombre.c_str(),29);
        _nombre[29] = '\0';
    }
}
void Categoria::setDescripcioon(std::string descripcion){
    if(descripcion.size() <= 100){
        strncpy(_descripcion,descripcion.c_str(),99);
        _descripcion[99] = '\0';
    }
}
bool Categoria::setEstado(bool estado){
    _estado = estado;
}





