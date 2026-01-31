#include "Descuento.h"
#include<cstring>


Descuento::Descuento()
:_idDescuento(0),_porcentaje(0.0),_montoFijo(0.0),_estado(false){
    strcpy(_descripcion,"");
}
Descuento::Descuento(int id,std::string descripcion,float porcentaje,float montoFijo, bool dias[7],bool estado){
    setIdDescuento(id);
    setDescripcion(descripcion);
    setPorcentaje(porcentaje);
    setMontoFijo(montoFijo);
    setDiasSemana(dias);
    setEstado(estado);
}


int Descuento::getIdDescuento(){
return _idDescuento;}
std::string Descuento::getDescripcion(){
return _descripcion;}
float Descuento::getPorcentaje(){
return _porcentaje;}
float Descuento::getMontoFijo(){
return _montoFijo;}
bool Descuento::getEstado(){
return _estado;}

void Descuento::setIdDescuento(int id){
    _idDescuento = id;
}
void Descuento::setDescripcion(std::string descripcion){
    if(sizeof(descripcion) <= 100){
        strncpy(_descripcion,descripcion.c_str(),99);
        _descripcion[99] = '\0';
    }
}
void Descuento::setPorcentaje(float porcentaje){
    _porcentaje = porcentaje;
}
void Descuento::setMontoFijo(float monto){
    _montoFijo = monto;
}
void Descuento::setDiasSemana(bool v[7]){
    for(int i=0;i<7;i++){
        _diasSemana[i] = v[i];
    }
}
void Descuento::setEstado(bool estado){
    _estado = estado;
}

bool Descuento::aplicarDia(Fecha dia){
    int diaSemana = dia.ObtenerDiaDeLaSemana();

    return _diasSemana[diaSemana];
}
float Descuento::aplicar(float precioOrginal,Fecha diaActual){
    if(!_estado) return precioOrginal;
    if(!aplicarDia(diaActual)) return precioOrginal;

    float precioFinal = precioOrginal;

    if(_porcentaje > 0){
        precioFinal -= precioOrginal*(_porcentaje/100.0f);
    }
    if(_montoFijo > 0){
        precioFinal -= _montoFijo;
    }
    if(precioFinal < 0)precioFinal = 0;

    return precioFinal;
}

void Descuento::Mostrar(){
    const char *nombreDias[7] = {"Dom","Lun","Mar","Mie","Jue","Vie","Sab"};

    std::cout<<"--DESCUENTO"<<std::endl<<std::endl;
    std::cout<<"ID: "<<getIdDescuento()<<std::endl;
    std::cout<<"DESCRIPCION: "<<getDescripcion()<<std::endl;
    std::cout<<"PORCENTAJE: "<<getPorcentaje()<<"%"<<std::endl;
    std::cout<<"MONTO FIJO: "<<getMontoFijo()<<std::endl;
    std::cout<<"ESTADO: "<<getEstado()<<std::endl;
    std::cout<<"DIAS APLICABLES: ";
    for(int i=0;i<7;i++){
        if(_diasSemana[i])std::cout<<nombreDias[i]<<",";
    }
    std::cout<<std::endl;
}
