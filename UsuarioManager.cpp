#include "UsuarioManager.h"
#include <iostream>

using namespace std;
UsuarioManager::UsuarioManager(){
}
string UsuarioManager::CargarCadena(){
    string texto;
    if(cin.peek()=='\n'){
        cin.ignore();
    }
    getline(cin,texto);
    return texto;
}
void UsuarioManager::InicializarSistema(){
    int cantidadRegistros = _UserArchi.getCantidadRegistro();
    if(cantidadRegistros ==0){
        cout<<endl<<endl<<"||       No hay usuarios registrados en el sistema... ||"<<endl;
        cout<<"||       Debe crear el primer usuario Administrador.  ||" <<endl<<endl;
        system("pause");
        system("cls");
        cout<<"    Hola Administrador del sistema!!."<<endl;
        cout<<"    A continuacion le dejamos los pasos para registrarse"<<endl;
        cout<<"    Esperamos disfrute la experiencia prueba beta de nustro sistema de gestion..."<<endl;
        system("pause");
        system("cls");
        CrearUsuario();
    }


}
string UsuarioManager::getObtenerRol(){

    int opcion;

    cout<<"== OPCIONES DE ROLES"<<endl;
    cout<<endl<<"1.ADMINISTRADOR"<<endl;
    cout<<"2.VENDEDOR"<<endl;

    cout<<endl;
    cout<<"Opcion: ";
    cin>> opcion;

    return vecRoles[opcion-1];
}

void UsuarioManager::CrearUsuario(){
    Usuario user;
    string legajo;
    string usuario,contrasenia,rol;
    Persona persona;
    int dia,mes,anio;
    int edad;
    std::string nombre, apellido,dni,direccion,telefono,mail;
    bool estado;

    cout<<"---CREAR NUEVO USUARIO"<<endl;
    legajo = _UserArchi.getLegajoNuevo();
    cout<<"NOMBRE: ";
    nombre = CargarCadena();
    cout<<"APELLIDO: ";
    apellido = CargarCadena();
    cout<<"DNI: ";
    dni = CargarCadena();
    if(_validar.ValidarTamDni(dni)){
        cout<<"DNI INCORRECTO."<<endl;
        return;
    }
    if(_UserArchi.ValidarDni(dni)){
        cout<<"DNI ya existente..."<<endl;
        return;
    }
    cout<<"LEGAJO: "<<legajo<<endl;
    cout<<"FECHA DE NACIMINETO "<<endl;
    cout<<"DIA: ";
    cin>>dia;
    cout<<"MES: ";
    cin>>mes;
    cout<<"ANIO: ";
    cin>>anio;
    if(!_fecha.validarFecha(dia,mes,anio)){
        cout<<"Fecha inexistente..."<<endl;
        return;
    }
    edad = _fecha.ObtenerEdad(dia,mes,anio);
    cout<<"EDAD: "<<edad<<endl;
    cout<<"DIRECCION: ";
    direccion = CargarCadena();
    cout<<"TELEFONO: ";
    telefono = CargarCadena();
    cout<<"MAIL: ";
    mail = CargarCadena();

    persona = Persona(nombre,apellido,dni,direccion,telefono,mail,Fecha(dia,mes,anio),edad,true);
    system("pause");
    system("cls");
    cout<<"---DEFINIR NOMBRE DE USUARIO Y CONTRASENIA"<<endl;
    cout<<"USUARIO: "<<legajo;
    usuario = legajo;

    cout<<endl<<"CONTRASENIA(solo 6 caracteres): ";
    contrasenia = CargarCadena();
    while(contrasenia.size() != 6){
        cout<<"ERROR.La contrasenia debe contener 6 digitos (numeros o letras)..."<<endl;

        cout<<endl<<"CONTRASENIA(solo 6 caracteres): ";
        contrasenia = CargarCadena();
        if(contrasenia.size() == 6){
            break;
        }
    }
    system("pause");
    system("cls");

    string contrasenia2;

    cout<<"REPETIR CONTRASENIA: ";
    contrasenia2 = CargarCadena();
    if(contrasenia == contrasenia2){
        cout<<"Contrasenia establecida correctamente!!"<<endl;
                system("pause");

    }else {
        for(int i=0;i<3;i++){
                cout<<"Contrasenia incorrecta"<<endl;
                cout<<"REPETIR CONTRASENIA: ";
                contrasenia2 = CargarCadena();

                if(contrasenia == contrasenia2){
                cout<<"Contrasenia establecida correctamente!!"<<endl;
                break;

                }
        if(i==2){
            system("cls");
            system("pause");
            cout<<"Vuelva a intentarlo mas tarde..."<<endl;
            return;
            }
        system("pause");
        system("cls");

    }
    }

    cout<<"ROL: "<<endl;
    rol =  getObtenerRol();

    user = Usuario(legajo,usuario,contrasenia,rol,persona);
    if(_UserArchi.guardar(user)){
       system("cls");
        MostrarUsuario(user);
        cout<<endl;
        cout<<"Se guardo correctamente.."<<endl;
    }else{
        cout<<"Hubo un error, no se pudo guardar.."<<endl;
    }

}

int UsuarioManager::Login(string usuario, string contrasenia){

    system ("pause");
    system ("cls");

    int cantidadReg = _UserArchi.getCantidadRegistro();
    Usuario *vecUsuarios = new Usuario[cantidadReg];

    _UserArchi.LeerTodos(vecUsuarios,cantidadReg);

    for(int i=0;i<cantidadReg; i++){
            if(vecUsuarios[i].getUsuario() == usuario && vecUsuarios[i].getContrasenia() == contrasenia && vecUsuarios[i].getPersona().getEstado()== true){
                if(vecUsuarios[i].getRol() == vecRoles[0]){
                    delete[]vecUsuarios;
                    return 1;
                }else if(vecUsuarios[i].getRol() == vecRoles[1]){
                    delete []vecUsuarios;
                    return 2;
                }
            }

    }
    return 0;
    delete[]vecUsuarios;

}


void UsuarioManager::MostrarUsuario(Usuario registro){
    cout<<"== DATOS DE USUARIO === "<<endl;
    cout<<"ROL: "<<registro.getRol()<<endl;
    cout<<"USUARIO: "<<registro.getUsuario();
    cout<<endl<<"CONSTRASENIA: "<<registro.getContrasenia()<<endl;

    cout<<endl<<"---DATOS PEROSNALES"<<std::endl;
    cout<<"LEGAJO: "<<registro.getLegajo()<<std::endl;
    cout<<"NOMBRE: "<<registro.getPersona().getNombre()<<std::endl;
    cout<<"APELLIDO: "<<registro.getPersona().getApellido()<<std::endl;
    cout<<"DNI: "<<registro.getPersona().getDni() <<std::endl;
    cout<<"EDAD: "<<registro.getPersona().getEdad()<<endl;
    cout<<"DIRECCION: "<<registro.getPersona().getDireccion()<<std::endl;
    cout<<"TELEFONO: "<<registro.getPersona().getTelefono()<<std::endl;
    cout<<"MAIL: "<<registro.getPersona().getMail()<<std::endl;

}
void UsuarioManager::EliminarUsuario(){
    string legajo;
    char opcion;
    bool ok;
    Usuario registro;

    cout<<"INGRESE LEGAJO: ";
    legajo = CargarCadena();
    int pos = _UserArchi.buscarLegajo(legajo);
    system("pause");
    system("cls");
    cout<<"ESTA SEGURO QUE DESEA ELIMINARLO? (S/N) :";
    cin>>opcion;
    if(opcion == 's' or opcion == 'S'){
            ok =  _UserArchi.eliminar(pos);
            registro = _UserArchi.leer(pos);
            MostrarActualizacion(ok,registro);
    }
}
void UsuarioManager::MostrarActualizacion(bool ok,Usuario registro){
    if(ok){
            system("pause");
            system("cls");
        cout<<"ACTUALIZACION"<<endl;
            cout<<"SE MODIFICO CORRECTAMENTE"<<endl;
            cout<<"---------"<<endl;
            MostrarUsuario(registro);
        }else{
            cout<<"ALGO SALIO MAL, NO SE PUDO MODIFICAR..."<<endl;
        }
}


void UsuarioManager::ModificarUsuario(int opcion){
    string  legajo;
    bool ok;
    Usuario registro;

    cout<<"INGRESE LEGAJO DEL EMPLEADO: ";
    legajo = CargarCadena();

    int pos = _UserArchi.buscarLegajo(legajo);
    if(pos < 0){
        cout<<"EL LEGAJO INGRESADO NO EXISTE..."<<endl;
        return;
    }
    registro = _UserArchi.leer(pos);
    MostrarUsuario(registro);
    cout<<endl;
    switch(opcion){
    case 1:{
        system("pause");
        system("cls");
        string  rol;
        rol = getObtenerRol();
        registro.setRol(rol);
        ok =_UserArchi.guardar(pos,registro);
        MostrarActualizacion(ok,registro);
        break;
    }
    case 2:{
        system("pause");
        system("cls");
        string telefono;
        cout<<"TELEFONO NUEVO: ";
        telefono = CargarCadena();
        registro.getPersona().setTelefono(telefono);
        ok = _UserArchi.guardar(pos,registro);
        MostrarActualizacion(ok,registro);
        break;
    }
    case 3:{
        system("pause");
        system("cls");
        string direccion;
        cout<<"DIRECCION NUEVA: ";
        direccion = CargarCadena();
        registro.getPersona().setDireccion(direccion);
        ok = _UserArchi.guardar(pos,registro);
        MostrarActualizacion(ok,registro);
        break;
    }
    case 4:{
        system("pause");
        system("cls");
        string mail;
        cout<<"MAIL NUEVO: ";
        mail = CargarCadena();
        registro.getPersona().setMail(mail);
        ok = _UserArchi.guardar(pos,registro);
        MostrarActualizacion(ok,registro);
        break;
    }
    }
}
void UsuarioManager::ListarUsuarios(int opcion){
    int cantidadRegistros = _UserArchi.getCantidadRegistro();
    Usuario *vecRegistros = new Usuario[cantidadRegistros];


    _UserArchi.LeerTodos(vecRegistros,cantidadRegistros);

    int cantidaActivos = 0;
    for(int i=0;i<cantidadRegistros;i++){
        if(vecRegistros[i].getPersona().getEstado() == true){
            cantidaActivos++;
        }
    }

    Usuario *vecActivos = new Usuario[cantidaActivos];
    int contador = 0;
    for(int i=0;i<cantidadRegistros;i++){
            if(vecRegistros[i].getPersona().getEstado() == true){
                vecActivos[contador] = vecRegistros[i];
                contador++;
            }
    }
    switch(opcion){
    case 1: {
        OrdenarVecApellido(vecActivos,cantidaActivos);
    for(int i=0;i<cantidaActivos;i++){
        MostrarUsuario(vecActivos[i]);
        cout<<"-----------------"<<endl;
    }
    delete[]vecActivos;
    delete[]vecRegistros;
    break;
    }

    case 2:{
        OrdenarVecNombre(vecActivos,cantidaActivos);
        for(int i=0;i<cantidaActivos;i++){
            MostrarUsuario(vecActivos[i]);
            cout<<"______________________________"<<endl;
        }
        delete[]vecRegistros;
        delete []vecActivos;
        break;
    }
    case 3:{

    OrdenarVecEdad(vecActivos,cantidaActivos);
    for(int i=0;i<cantidaActivos;i++){
        MostrarUsuario(vecActivos[i]);
        cout<<"-----------------"<<endl;
    }

    delete[]vecRegistros;
    delete[]vecActivos;
    break;
    }
}
}

void UsuarioManager::BuscarUsuario(){
    string legajo;
    Usuario registro;
    cout<<"INGRESE LEGAJO DEL EMPLEADO A BUSCAR: "<<endl;
    legajo = CargarCadena();
    int pos =_UserArchi.buscarLegajo(legajo);

    while(pos < 0){
        cout<<"LEGAJO INEXISTENTE"<<endl;
        cout<<"INGRESE LEGAJO DEL EMPLEADO A BUSCAR: "<<endl;
        cin>>legajo;
        int pos =_UserArchi.buscarLegajo(legajo);
    }

    registro = _UserArchi.leer(pos);
    system("pause");
    system("cls");
    cout<<"DATOS CORRESPONDIENTES A"<<registro.getPersona().getNombre()<<" "<<registro.getPersona().getApellido()<<endl<<endl;
    MostrarUsuario(registro);


}

void UsuarioManager::OrdenarVecApellido(Usuario *vec,int tam){
     for(int i=0; i<tam; i++){
        bool intercambio = false;
        for(int j=0;j<tam - 1 -i;j++){
            if(vec[j].getPersona().getApellido() > vec[j+1].getPersona().getApellido()){
                Usuario aux = vec[j];
                vec[j] = vec[j+1];
                vec[j+1] = aux;
                intercambio = true;
            }
        }
        if(!intercambio){
            break;
        }
    }
}
void UsuarioManager::OrdenarVecNombre(Usuario vec[],int tam){
     for(int i=0; i<tam; i++){
        bool intercambio = false;
        for(int j=0;j<tam - 1 -i;j++){
            if(vec[j].getPersona().getNombre() > vec[j+1].getPersona().getNombre()){
                Usuario aux = vec[j];
                vec[j] = vec[j+1];
                vec[j+1] = aux;
                intercambio = true;
            }
        }
        if(!intercambio){
            break;
        }
    }
}
void UsuarioManager::OrdenarVecEdad(Usuario vec[],int tam){
    for(int i=0; i<tam; i++){
        bool intercambio = false;
        for(int j=0;j<tam - 1 -i;j++){
            if(vec[j].getPersona().getEdad() > vec[j+1].getPersona().getEdad()){
                Usuario aux = vec[j];
                vec[j] = vec[j+1];
                vec[j+1] = aux;
                intercambio = true;
            }
        }
        if(!intercambio){
            break;
        }
    }
}
string  UsuarioManager::getMostrarNombreCajero(string legajo){

    Usuario registro;
    int pos = _UserArchi.buscarLegajo(legajo);
    registro = _UserArchi.leer(pos);

    return registro.getPersona().getNombreCompleto();

}

void UsuarioManager::CambiarContrasenia(string legajo){
    Usuario registro;
    string nuevaContrasenia, confirmarContrasenia;

    int pos = _UserArchi.buscarLegajo(legajo);
    if(pos < 0){
        cout << "** LEGAJO NO ENCONTRADO **" << endl;
        return;
    }

    registro = _UserArchi.leer(pos);
    MostrarUsuario(registro);

    cout << endl << "INGRESE NUEVA CONTRASENIA: ";
    nuevaContrasenia = CargarCadena();

    if(!_validar.ValidarContrasenias(nuevaContrasenia)){
        cout << "** CONTRASENIA INVALIDA **" << endl;
        return;
    }

    cout << "CONFIRMAR CONTRASENIA: ";
    confirmarContrasenia = CargarCadena();

    if(nuevaContrasenia != confirmarContrasenia){
        cout << "** LAS CONTRASENIAS NO COINCIDEN **" << endl;
        return;
    }

    registro.setContrasenia(nuevaContrasenia);
    bool ok = _UserArchi.guardar(pos, registro);

    if(ok){
        cout << "** CONTRASENIA CAMBIADA CORRECTAMENTE **" << endl;
    } else {
        cout << "** ERROR AL CAMBIAR CONTRASENIA **" << endl;
    }
}
