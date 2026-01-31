#include "VentaManager.h"
#include <iostream>


using namespace std;
VentaManager::VentaManager(){
}
string VentaManager::CargarCadena(){
    string texto;
    if(cin.peek()=='\n'){
        cin.ignore();
    }
    getline(cin,texto);
    return texto;
}

void VentaManager::NuevaVenta(string usuario){
     Fecha fecha;
    _fecha = fecha.ObteneFechaActual();
    int idVenta = _venArchi.getIdNuevo();
    string legajo = usuario;
    string nombreCajero = _usuMan.getMostrarNombreCajero(usuario);

    DetalleVenta* detalles = new DetalleVenta[100];
    int cantidadDetalles = 0;
    float total = 0.0;

    system("cls");
    cout<<"--------------------------------------- NUEVA VENTA -------------------------------------------"<<endl;
    cout<<"-----------------------------------------------------------------------------------------------"<<endl;
    cout<<"||FECHA: "<<_fecha.toString()<<endl;
    cout<<"------------------------------------------------------------------------------------------------"<<endl;
    cout<<"|| VENDEDOR: "<<nombreCajero<<" || "<<"TRNS: "<<idVenta<<" ||"<<endl;
    cout<<"------------------------------------------------------------------------------------------------"<<endl<<endl;

    string dni;
    int tamDni = 8;
     while (true) {
        cout << "- INGRESE DNI DEL CLIENTE (0 para cancelar): ";
        dni = CargarCadena();
        if (dni == "0") {
            cout << "** VENTA CANCELADA **" << endl;
            system("pause");
            return;
        }
        if (!_validar.ValidarTamanioExactos(dni, tamDni)) {
            cout << "** ERROR: DNI DEBE CONTENER 8 DIGITOS **" << endl;
            continue;
        }
        break;
    }

    Cliente registro;

    if (existeCliente(dni)) {
        int pos = _cliArchi.buscarDni(dni);
        registro = _cliArchi.leer(pos);
        cout << "CLIENTE: " << registro.getNombreCompleto() << endl;
    } else {
        cout << "CLIENTE: " << dni << endl;
    }

    cout << endl;

    while (true) {
        int tamCodigo = 13;
        cout << endl << "- Codigo del producto (0 para terminar, -1 para cancelar venta, -2 para eliminar producto): ";
        string codigo = CargarCadena();

        if (codigo == "0") break;
        if (codigo == "-1") { /// camcelamos y devolvenmos el stock con for
            for (int i = 0; i < cantidadDetalles; i++) {
                _produMan.restaurarStock(detalles[i].getIdProducto(), detalles[i].getCantidad());
            }
            delete[] detalles;
            cout << "** VENTA CANCELADA - STOCK RESTAURADO **" << endl;
            system("pause");
            return;
        }
        if (codigo == "-2") { ///para eliminar pedimos el indice de producto y declaramos objeto eliminar que contanga
            if(cantidadDetalles == 0){ ///lo que contiene el vector en esa posicion a eliminar
                cout << "** NO HAY PRODUCTOS AGREGADOS **" << endl;
                system("pause");
                continue;
            }

            int numProducto;
            cout << "Ingrese el numero del producto a eliminar (1-" << cantidadDetalles << "): ";
            cin >> numProducto;

            if(numProducto < 1 || numProducto > cantidadDetalles){
                cout << "** NUMERO INVALIDO **" << endl;
                system("pause");
                continue;
            }

            int indice = numProducto - 1;
            DetalleVenta detalleEliminar = detalles[indice];

            if(_produMan.restaurarStock(detalleEliminar.getIdProducto(), detalleEliminar.getCantidad())){
                float subtotalEliminar = detalleEliminar.getCantidad() * detalleEliminar.getPrecioVenta();
                total -= subtotalEliminar;

                for(int i = indice; i < cantidadDetalles - 1; i++){
                    detalles[i] = detalles[i + 1];
                }
                cantidadDetalles--;

                string nombreProdu = _produMan.Buscar(detalleEliminar.getIdProducto());
                if(nombreProdu == ""){
                    nombreProdu = detalleEliminar.getIdProducto();
                }
                cout << "** PRODUCTO '" << nombreProdu << "' ELIMINADO - STOCK RESTAURADO **" << endl;
            } else {
                cout << "** ERROR AL RESTAURAR STOCK **" << endl;
            }
            system("pause");
            continue;
        }

        if (!_validar.ValidarTamanioExactos(codigo, tamCodigo)) {
            cout << "** ERROR: CODIGO INVALIDO **" << endl;
            continue;
        }

        string nombre = _produMan.Buscar(codigo);
        if (nombre == "") {
            cout << "** EAN INEXISTENTE **" << endl;
            continue;
        }

        int stockActual = _produMan.getStockActual(codigo);
        cout << "PRODUCTO: " << nombre << " | STOCK DISPONIBLE: " << stockActual << " |" << endl;
        cout << "Cantidad: ";

        int cantidad;
        cin >> cantidad;

        if (cantidad <= 0) {
            cout << "** ERROR: LA CANTIDAD DEBE SER MAYOR A 0 **" << endl;
            system("pause");
            continue;
        }

        if (cantidad > stockActual) {
            cout << "** STOCK INSUFICIENTE **" << endl;
            cout<<"--------------------------------------------------------------"<<endl;
            continue;
        }

        float precio = _produMan.getPrecioVenta(codigo);
        float subtotal = cantidad * precio;
        total += subtotal;

        if (!_produMan.descontarStock(codigo, cantidad)) {
            cout << "** ERROR AL DESCONTAR STOCK **" << endl;
            continue;
        }

        cout<<"Subtotal: "<<subtotal<<endl;

        if(cantidadDetalles >= 100){
            cout << "** ERROR: MAXIMO 100 PRODUCTOS POR VENTA **" << endl;
            system("pause");
            continue;
        }
        cout<<"-----------------------------------------------------------------------------------------"<<endl;
        DetalleVenta detVenta;
        int idDetalle = _detVenArchi.getIdNuevo();
        detVenta = DetalleVenta(idDetalle,idVenta,codigo,cantidad,precio);
        detalles[cantidadDetalles] = detVenta;
        cantidadDetalles++;
    }

    Venta ven;
    ven = Venta(idVenta,legajo,dni,_fecha,total);
    bool okVenta = _venArchi.guardar(ven);

    bool okDetalle = true;
    for (int i = 0; i < cantidadDetalles; i++) {
        if (!_detVenArchi.guardar(detalles[i])){
            okDetalle = false;
            break;
        }
    }

    delete[] detalles;

    if (okVenta && okDetalle) {
        cout << "** VENTA REGISTRADA CORRECTAMENTE **" << endl;
        MostrarTicket(idVenta);
    } else {
        cout << "** ERROR AL REGISTRAR LA VENTA **" << endl;
    }

    system("pause");
}

void VentaManager::MostrarTicket(int idventa){
    system("cls");
    cout << "---------------------------------------------------------" << endl;
    cout << "                          TICKET                 " << endl;
    cout << "---------------------------------------------------------" << endl;

    Venta ven = _venArchi.leer(idventa-1); ///lee por el id
    cout << "FECHA: " << ven.getFecha().toString()<<"  ";
    cout << "NUMERO DE TRANSACCION: "<< ven.getNumTransaccion() << endl;
    cout << "LEGAJO VENDEDOR: " << ven.getLegajoEmpleado() << endl;
    cout << "CLIENTE: " << ven.getDniCliente() << endl;
    cout << "---------------------------------------------------------" << endl;
    cout << "PRODUCTO            CANT   PRECIO   SUBTOTAL" << endl;
    cout << "---------------------------------------------------------" << endl;

    int cantidad = _detVenArchi.getCantidadRegistro();
    for(int i = 0; i<cantidad; i++){
        DetalleVenta detalle = _detVenArchi.leer(i);
        if(detalle.getIdVenta() == idventa){
            string nombreProdu = _produMan.Buscar(detalle.getIdProducto());
            float subtotal = detalle.getCantidad() * detalle.getPrecioVenta();

            if(nombreProdu == ""){
                nombreProdu = detalle.getIdProducto();
            }

            if(nombreProdu.length() > 20){
                nombreProdu = nombreProdu.substr(0, 17) + "...";
            }

            cout << nombreProdu;
            int espacios = 20 - nombreProdu.length();
            if(espacios < 1) espacios = 1;
            for(int j = 0; j < espacios; j++) cout << " ";
            cout << (int)detalle.getCantidad() << "   "
                 << detalle.getPrecioVenta() << "      "
                 << subtotal << endl;

        }
    }
    cout << "---------------------------------------------------------" << endl;
    cout << "TOTAL:                              $" << ven.getTotal() << endl;
    cout << "---------------------------------------------------------" << endl<<endl;
    cout << "GRACIAS POR SU COMPRA!" << endl;


}

void VentaManager::ListarTodasLasVentas(){
    system("cls");
    int cantidad = _venArchi.getCantidadRegistro();

    if(cantidad == 0){
        cout << "** NO HAY VENTAS REGISTRADAS **" << endl;
        system("pause");
        return;
    }

    cout << "===================================================" << endl;
    cout << "          LISTADO DE TODAS LAS VENTAS     " << endl;
    cout << "====================================================" << endl;
    cout << "TRANS    FECHA   LEGAJO   CLIENTE    TOTAL" << endl;
    cout << "----------------------------------------------------" << endl;

    for(int i = 0; i < cantidad; i++){
        Venta ven = _venArchi.leer(i);
        cout << ven.getNumTransaccion() << "   "
             << ven.getFecha().toString() << "   "
             << ven.getLegajoEmpleado() << "   "
             << ven.getDniCliente() << "   "
             << ven.getTotal() << endl;
    }
    cout << "===========================================" << endl;
    system("pause");
}

void VentaManager::ConsultarPorNumTransaccion(){
    system("cls");
    int numTransaccion;

    cout << "INGRESE NUMERO DE TRANSACCION: ";
    cin >> numTransaccion;

    if(numTransaccion <= 0){
        cout << "** ERROR: NUMERO DE TRANSACCION INVALIDO **" << endl;
        system("pause");
        return;
    }

    int pos = _venArchi.buscarId(numTransaccion);
    if(pos < 0){
        cout << "** TRANSACCION NO ENCONTRADA **" << endl;
        system("pause");
        return;
    }

    MostrarTicket(numTransaccion);
    system("pause");
}

void VentaManager::AnularVenta(){
    system("cls");
    int numTransaccion;

    cout << "INGRESE NUMERO DE TRANSACCION A ANULAR: ";
    cin >> numTransaccion;

    if(numTransaccion <= 0){
        cout << "** ERROR: NUMERO DE TRANSACCION INVALIDO **" << endl;
        system("pause");
        return;
    }

    int pos = _venArchi.buscarId(numTransaccion);
    if(pos < 0){
        cout << "** TRANSACCION NO ENCONTRADA **" << endl;
        system("pause");
        return;
    }

    Venta ven = _venArchi.leer(pos);
    cout << "TRANSACCION: " << ven.getNumTransaccion() << endl;
    cout << "FECHA: " << ven.getFecha().toString() << endl;
    cout << "TOTAL: $" << ven.getTotal() << endl;
    cout << "DESEA ANULAR ESTA VENTA? (1=SI, 0=NO): ";

    int confirmar;
    cin >> confirmar;

    if(confirmar != 1){
        cout << "** OPERACION CANCELADA **" << endl;
        system("pause");
        return;
    }

    int cantDetalles = _detVenArchi.getCantidadRegistro();
    for(int i = 0; i < cantDetalles; i++){
        DetalleVenta detalle = _detVenArchi.leer(i);
        if(detalle.getIdVenta() == numTransaccion){
            _produMan.restaurarStock(detalle.getIdProducto(), detalle.getCantidad());
        }
    }

    cout << "** VENTA ANULADA - STOCK RESTAURADO **" << endl;
    system("pause");
}

bool VentaManager::existeCliente(string dni){

    int pos = _cliArchi.buscarDni(dni);
    if(pos < 0){
        return false;
    }
    return true;
}

void VentaManager::ReporteProductoMasVendido(){
    system("cls");
    cout << "===========================================" << endl;
    cout << "     REPORTE: PRODUCTO MAS VENDIDO        " << endl;
    cout << "===========================================" << endl;

    int cantDetalles = _detVenArchi.getCantidadRegistro();
    if(cantDetalles == 0){
        cout << "** NO HAY VENTAS REGISTRADAS **" << endl;
        system("pause");
        return;
    }

    struct ProductoVendido{
        string codigo;
        float cantidadTotal;
        string nombre;
    };

    ProductoVendido* productos = new ProductoVendido[1000];
    int cantidadProductos = 0;

    for(int i = 0; i < cantDetalles; i++){
        DetalleVenta detalle = _detVenArchi.leer(i);
        string codigo = detalle.getIdProducto();
        float cantidad = detalle.getCantidad();

        bool encontrado = false;
        for(int j = 0; j < cantidadProductos; j++){
            if(productos[j].codigo == codigo){
                productos[j].cantidadTotal += cantidad;
                encontrado = true;
                break;
            }
        }

        if(!encontrado){
            if(cantidadProductos >= 1000){
                cout << "** ERROR: DEMASIADOS PRODUCTOS DIFERENTES **" << endl;
                delete[] productos;
                system("pause");
                return;
            }
            ProductoVendido nuevo;
            nuevo.codigo = codigo;
            nuevo.cantidadTotal = cantidad;
            nuevo.nombre = _produMan.Buscar(codigo);
            if(nuevo.nombre == ""){
                nuevo.nombre = codigo;
            }
            productos[cantidadProductos] = nuevo;
            cantidadProductos++;
        }
    }

    if(cantidadProductos == 0){
        cout << "** NO HAY PRODUCTOS VENDIDOS **" << endl;
        delete[] productos;
        system("pause");
        return;
    }

    ProductoVendido masVendido = productos[0];
    for(int i = 1; i < cantidadProductos; i++){
        if(productos[i].cantidadTotal > masVendido.cantidadTotal){
            masVendido = productos[i];
        }
    }

    delete[] productos;

    cout << "PRODUCTO: " << masVendido.nombre << endl;
    cout << "CODIGO: " << masVendido.codigo << endl;
    cout << "CANTIDAD TOTAL VENDIDA: " << masVendido.cantidadTotal << endl;
    cout << "===========================================" << endl;
    system("pause");
}

void VentaManager::ReporteVentasPorDiaOMes(){
    system("cls");
    cout << "===========================================" << endl;
    cout << "   REPORTE: VENTAS TOTALES POR DIA O MES   " << endl;
    cout << "===========================================" << endl;

    int opcion;
    cout << "1. POR DIA" << endl;
    cout << "2. POR MES" << endl;
    cout << "OPCION: ";
    cin >> opcion;

    if(opcion != 1 && opcion != 2){
        cout << "** OPCION INVALIDA **" << endl;
        system("pause");
        return;
    }

    int cantVentas = _venArchi.getCantidadRegistro();
    if(cantVentas == 0){
        cout << "** NO HAY VENTAS REGISTRADAS **" << endl;
        system("pause");
        return;
    }

    if(opcion == 1){
        int dia, mes, anio;
        Fecha fecha;
        do{
            cout << "INGRESE DIA: ";
            cin >> dia;
            cout << "INGRESE MES: ";
            cin >> mes;
            cout << "INGRESE ANIO: ";
            cin >> anio;

            if(!fecha.validarFecha(dia, mes, anio)){
                cout << "** FECHA INVALIDA. INTENTE NUEVAMENTE **" << endl;
            }
        }while(!fecha.validarFecha(dia, mes, anio));

        float totalDia = 0;
        int cantidadVentas = 0;

        for(int i = 0; i < cantVentas; i++){
            Venta ven = _venArchi.leer(i);
            Fecha fechaVenta = ven.getFecha();
            if(fechaVenta.getDia() == dia && fechaVenta.getMes() == mes && fechaVenta.getAnio() == anio){
                totalDia += ven.getTotal();
                cantidadVentas++;
            }
        }

        cout << "===========================================" << endl;
        cout << "VENTAS DEL " << dia << "/" << mes << "/" << anio << endl;
        cout << "CANTIDAD DE VENTAS: " << cantidadVentas << endl;
        cout << "TOTAL: $" << totalDia << endl;
        cout << "===========================================" << endl;
    } else {
        int mes, anio;
        do{
            cout << "INGRESE MES (1-12): ";
            cin >> mes;
            if(mes < 1 || mes > 12){
                cout << "** MES INVALIDO. DEBE SER ENTRE 1 Y 12 **" << endl;
            }
        }while(mes < 1 || mes > 12);

        cout << "INGRESE ANIO: ";
        cin >> anio;

        if(anio < 1900 || anio > 2100){
            cout << "** ANIO FUERA DE RANGO VALIDO **" << endl;
            system("pause");
            return;
        }

        float totalMes = 0;
        int cantidadVentas = 0;

        for(int i = 0; i < cantVentas; i++){
            Venta ven = _venArchi.leer(i);
            Fecha fechaVenta = ven.getFecha();
            if(fechaVenta.getMes() == mes && fechaVenta.getAnio() == anio){
                totalMes += ven.getTotal();
                cantidadVentas++;
            }
        }

        cout << "===========================================" << endl;
        cout << "VENTAS DEL MES " << mes << "/" << anio << endl;
        cout << "CANTIDAD DE VENTAS: " << cantidadVentas << endl;
        cout << "TOTAL: $" << totalMes << endl;
        cout << "===========================================" << endl;
    }

    system("pause");
}

void VentaManager::ReporteVendedorMasTransacciones(){
    system("cls");
    cout << "===========================================" << endl;
    cout << "  REPORTE: VENDEDOR CON MAS TRANSACCIONES " << endl;
    cout << "===========================================" << endl;

    int cantVentas = _venArchi.getCantidadRegistro();
    if(cantVentas == 0){
        cout << "** NO HAY VENTAS REGISTRADAS **" << endl;
        system("pause");
        return;
    }

    struct VendedorTrans{
        string legajo;
        int cantidadTransacciones;
        float totalVendido;
    };

    VendedorTrans* vendedores = new VendedorTrans[100];
    int cantidadVendedores = 0;

    for(int i = 0; i < cantVentas; i++){
        Venta ven = _venArchi.leer(i);
        string legajo = ven.getLegajoEmpleado();

        bool encontrado = false;
        for(int j = 0; j < cantidadVendedores; j++){
            if(vendedores[j].legajo == legajo){
                vendedores[j].cantidadTransacciones++;
                vendedores[j].totalVendido += ven.getTotal();
                encontrado = true;
                break;
            }
        }

        if(!encontrado){
            if(cantidadVendedores >= 100){
                cout << "** ERROR: DEMASIADOS VENDEDORES DIFERENTES **" << endl;
                delete[] vendedores;
                system("pause");
                return;
            }
            VendedorTrans nuevo;
            nuevo.legajo = legajo;
            nuevo.cantidadTransacciones = 1;
            nuevo.totalVendido = ven.getTotal();
            vendedores[cantidadVendedores] = nuevo;
            cantidadVendedores++;
        }
    }

    if(cantidadVendedores == 0){
        cout << "** NO HAY VENDEDORES **" << endl;
        delete[] vendedores;
        system("pause");
        return;
    }

    VendedorTrans mejorVendedor = vendedores[0];
    for(int i = 1; i < cantidadVendedores; i++){
        if(vendedores[i].cantidadTransacciones > mejorVendedor.cantidadTransacciones){
            mejorVendedor = vendedores[i];
        }
    }

    delete[] vendedores;

    string nombreVendedor = _usuMan.getMostrarNombreCajero(mejorVendedor.legajo);

    cout << "VENDEDOR: " << nombreVendedor << endl;
    cout << "LEGAJO: " << mejorVendedor.legajo << endl;
    cout << "CANTIDAD DE TRANSACCIONES: " << mejorVendedor.cantidadTransacciones << endl;
    cout << "TOTAL VENDIDO: $" << mejorVendedor.totalVendido << endl;
    cout << "===========================================" << endl;
    system("pause");
}

void VentaManager::ReporteRecaudacion(){
    system("cls");
    cout << "===========================================" << endl;
    cout << "         REPORTE: RECAUDACION             " << endl;
    cout << "===========================================" << endl;

    int opcion;
    cout << "1. RECAUDACION DIARIA" << endl;
    cout << "2. RECAUDACION MENSUAL" << endl;
    cout << "3. RECAUDACION ANUAL" << endl;
    cout << "OPCION: ";
    cin >> opcion;

    if(opcion < 1 || opcion > 3){
        cout << "** OPCION INVALIDA **" << endl;
        system("pause");
        return;
    }

    int cantVentas = _venArchi.getCantidadRegistro();
    if(cantVentas == 0){
        cout << "** NO HAY VENTAS REGISTRADAS **" << endl;
        system("pause");
        return;
    }

    if(opcion == 1){
        int dia, mes, anio;
        Fecha fecha;
        do{
            cout << "INGRESE DIA: ";
            cin >> dia;
            cout << "INGRESE MES: ";
            cin >> mes;
            cout << "INGRESE ANIO: ";
            cin >> anio;

            if(!fecha.validarFecha(dia, mes, anio)){
                cout << "** FECHA INVALIDA. INTENTE NUEVAMENTE **" << endl;
            }
        }while(!fecha.validarFecha(dia, mes, anio));

        float total = 0;
        for(int i = 0; i < cantVentas; i++){
            Venta ven = _venArchi.leer(i);
            Fecha fechaVenta = ven.getFecha();
            if(fechaVenta.getDia() == dia && fechaVenta.getMes() == mes && fechaVenta.getAnio() == anio){
                total += ven.getTotal();
            }
        }

        cout << "===========================================" << endl;
        cout << "RECAUDACION DEL " << dia << "/" << mes << "/" << anio << endl;
        cout << "TOTAL: $" << total << endl;
        cout << "===========================================" << endl;
    } else if(opcion == 2){
        int mes, anio;
        do{
            cout << "INGRESE MES (1-12): ";
            cin >> mes;
            if(mes < 1 || mes > 12){
                cout << "** MES INVALIDO. DEBE SER ENTRE 1 Y 12 **" << endl;
            }
        }while(mes < 1 || mes > 12);

        cout << "INGRESE ANIO: ";
        cin >> anio;

        if(anio < 1900 || anio > 2100){
            cout << "** ANIO FUERA DE RANGO VALIDO **" << endl;
            system("pause");
            return;
        }

        float total = 0;
        for(int i = 0; i < cantVentas; i++){
            Venta ven = _venArchi.leer(i);
            Fecha fechaVenta = ven.getFecha();
            if(fechaVenta.getMes() == mes && fechaVenta.getAnio() == anio){
                total += ven.getTotal();
            }
        }

        cout << "===========================================" << endl;
        cout << "RECAUDACION DEL MES " << mes << "/" << anio << endl;
        cout << "TOTAL: $" << total << endl;
        cout << "===========================================" << endl;
    } else {
        int anio;
        cout << "INGRESE ANIO: ";
        cin >> anio;

        if(anio < 1900 || anio > 2100){
            cout << "** ANIO FUERA DE RANGO VALIDO **" << endl;
            system("pause");
            return;
        }

        float total = 0;
        for(int i = 0; i < cantVentas; i++){
            Venta ven = _venArchi.leer(i);
            Fecha fechaVenta = ven.getFecha();
            if(fechaVenta.getAnio() == anio){
                total += ven.getTotal();
            }
        }

        cout << "===========================================" << endl;
        cout << "RECAUDACION DEL ANIO " << anio << endl;
        cout << "TOTAL: $" << total << endl;
        cout << "===========================================" << endl;
    }

    system("pause");
}
