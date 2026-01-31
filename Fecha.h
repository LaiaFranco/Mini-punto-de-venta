#pragma once
#include <string>

class Fecha{

public:
    Fecha();
    Fecha(int dia,int mes, int anio);

    int getDia();
    int getMes();
    int getAnio();

    void setDia(int dia);
    void setMes(int mes);
    void setAnio(int anio);

    std::string toString();
    Fecha ObteneFechaActual();
    int ObtenerEdad(int dia,int mes,int anio);

    int ObtenerDiaDeLaSemana();

    bool validarFecha(int dia,int mes, int anio);
    bool esBiciesto(int anio);

private:
    int _dia;
    int _mes;
    int _anio;

};
