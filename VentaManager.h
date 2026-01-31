#pragma once
#include <string>
#include "Fecha.h"
#include "Producto.h"
#include "ProductoArchivo.h"
#include "ProductoManager.h"
#include "Usuario.h"
#include "UsuarioManager.h"
#include "UsuarioArchivo.h"
#include "Cliente.h"
#include "ClienteManager.h"
#include "Venta.h"
#include "VentaArchivo.h"
#include "DetalleVenta.h"
#include "DetalleVenArchivo.h"
#include "Validador.h"


class VentaManager{
    public:
        VentaManager();
        void NuevaVenta(std::string usuario);
        void MostrarTicket(int idVenta);
        void ListarTodasLasVentas();
        void ConsultarPorNumTransaccion();
        void AnularVenta();

        void ReporteProductoMasVendido();
        void ReporteVentasPorDiaOMes();
        void ReporteVendedorMasTransacciones();
        void ReporteRecaudacion();

    protected:
        std::string CargarCadena();
        bool existeCliente(std::string dni);


    private:
        ProductoManager _produMan;
        UsuarioManager _usuMan;
        VentaArchivo _venArchi;
        DetalleVenArchivo _detVenArchi;
        ClienteManager _clienMan;
        ClienteArchivo _cliArchi;
        Fecha _fecha;
        Validador _validar;

};
