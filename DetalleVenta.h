#pragma once
#include<string>

class DetalleVenta{
public:

    DetalleVenta();
    DetalleVenta(int id,int idVenta,std::string idProducto,float cantidad,float precioVenta);

    int getIdDetalle();
    int getIdVenta();
    std::string getIdProducto();
    float getCantidad();
    float getPrecioVenta();

    void setIdDetalle(int id);
    void setIdVenta(int id);
    void setIdProducto(std::string id);
    void setCantidad(float cantidad);
    void setPrecioVenta(float precio);


private:
    int _idDetalle;
    int _idVenta;
    char _idProducto[15];
    float _cantidad;
    float _PrecioVenta;

};
