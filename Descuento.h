#pragma once
#include<string>
#include<iostream>
#include "Fecha.h"

class Descuento{
public:
    Descuento();
    Descuento(int id,std::string descripcion,float porcentaje,float montoFijo, bool dias[7],bool estado);


    int getIdDescuento();
    std::string getDescripcion();
    float getPorcentaje();
    float getMontoFijo();
    bool getEstado();


    void setIdDescuento(int id);
    void setDescripcion(std::string descripcion);
    void setPorcentaje(float porcentaje);
    void setMontoFijo(float monto);
    void setDiasSemana(bool v[7]);
    void setEstado(bool estado);

    bool aplicarDia(Fecha dia);
    float aplicar(float precioOrginal,Fecha diaActual);

    void Mostrar();


private:
    int _idDescuento;
    char _descripcion [100];
    float _porcentaje;
    float _montoFijo;
    bool _diasSemana[7];
    bool _estado;


};
