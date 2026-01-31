#pragma once
#include<string>
#include "Fecha.h"

class Venta{
public:
    Venta();
    Venta(int numero,std::string legajo,std::string dni,Fecha fecha,float total);

    int getNumTransaccion();
    std::string getLegajoEmpleado();
    std::string getDniCliente();
    Fecha getFecha();
    float getTotal();

    void setNumTransaccion(int numero);
    void setLegajoEmpleado(std::string legajo);
    void setDniCliente(std::string dni);
    void setFecha(Fecha fecha);
    void setTotal(float total);

    void Mostrar();

private:
   int _numeroTransaccion;
   char _legajoEmpleado[10];
   char _dniCliente[10];
   Fecha _fecha;
   float _total;

};
