#pragma once
#include<string>

class Categoria{
public:

    Categoria();
    Categoria(int numero, std::string nombre,std::string descripcion,bool estado);

    int getNumeroCategoria();
    std::string getNombre();
    std::string getDescripcion();
    bool getEstado();

    void setNumeroCategoria(int numero);
    void setNombre(std::string nombre);
    void setDescripcioon(std::string descripcion);
    bool setEstado(bool estado);

private:
    int _numeroCategoria;
    char _nombre[30];
    char _descripcion[100];
    bool _estado;

};
