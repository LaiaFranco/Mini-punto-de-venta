#include<ctime>
#include "Fecha.h"

bool Fecha::esBiciesto(int anio){
    return (anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0);
}
bool Fecha::validarFecha(int dia,int mes,int anio){
    if (anio < 1900 || anio > 2100) return false;
        if (mes < 1 || mes > 12) return false;

        int diasMes;

        switch (mes) {
            case 1: case 3: case 5: case 7: case 8: case 10: case 12:
                diasMes = 31;
                break;
            case 4: case 6: case 9: case 11:
                diasMes = 30;
                break;
            case 2:
                if (esBiciesto(anio))
                    diasMes = 29;
                else
                    diasMes = 28;
                break;
            default:
                return false;
        }

        if (dia < 1 || dia > diasMes) return false;

        return true;
}


Fecha::Fecha()
:_dia(0),_mes(0),_anio(0){
}

Fecha::Fecha(int dia,int mes, int anio){
    setDia(dia);
    setMes(mes);
    setAnio(anio);
}

int Fecha::getDia(){
return _dia;}

int Fecha::getMes(){
return _mes;}

int Fecha::getAnio(){
    return _anio;
}

void Fecha::setDia(int dia){
    if(dia >= 1 and dia<=31){
        _dia = dia;
    }
}

void Fecha::setMes(int mes){
    if(mes >=1 and mes <=12){
        _mes = mes;
    }
}

void Fecha::setAnio(int anio){
    _anio = anio;
}

std::string Fecha::toString(){
    return std::to_string(_dia) + "/" + std::to_string(_mes) + "/" + std::to_string(_anio);
}

Fecha Fecha::ObteneFechaActual(){
    time_t t = time(nullptr);
    tm* tiempoLocal = localtime(&t);

    int dia = tiempoLocal->tm_mday;
    int mes = tiempoLocal->tm_mon + 1;
    int anio = tiempoLocal->tm_year + 1900;

    return Fecha(dia,mes,anio);
}
int Fecha::ObtenerEdad(int dia,int mes,int anio){

    Fecha hoy = ObteneFechaActual();
        int edad = hoy.getAnio() - anio;
        if (hoy.getMes()< mes || (hoy.getMes() == mes && hoy.getDia() < dia)) {
            edad--;
        }
        return edad;
}

int Fecha::ObtenerDiaDeLaSemana(){
    tm t = {};
    t.tm_mday = _dia;
    t.tm_mon = _mes - 1;
    t.tm_year = _anio - 1990;

    mktime(&t);

    return t.tm_wday;
}
