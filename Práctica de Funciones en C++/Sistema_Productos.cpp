#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip> // Libreria para alineacion simetrica de columnas

// 1. FUNCION INLINE: Calcula el precio aplicando un porcentaje de descuento
inline double calcularDescuento(double precio, double porcentaje) {
    return precio * (1.0 - porcentaje / 100.0);
}

class Producto {
private:
    std::string nombre;
    double precio;
    int cantidad;

public:
    // Constructor de la clase
    Producto(std::string n = "Sin nombre", double p = 0.0, int c = 0)
        : nombre(n), precio(p), cantidad(c) {}

    // 3. FUNCIONES CONSTANTES: Permiten consultar atributos sin modificar el objeto
    std::string getNombre() const {
        return nombre;
    }

    double getPrecio() const {
        return precio;
    }

    int getCantidad() const {
        return cantidad;
    }

    void mostrarDatos() const {
        std::cout << std::left << std::setw(18) << nombre
                  << " | $" << std::right << std::setw(8) << std::fixed << std::setprecision(2) << precio
                  << " | " << std::right << std::setw(8) << cantidad << "\n";
    }

    // 5. SOBRECARGA DEL OPERADOR +: Combina dos productos sumando precios y cantidades
    Producto operator+(const Producto& otro) const {
        std::string nombreCombinado = nombre + " + " + otro.nombre;
        double precioSumado = precio + otro.precio;
        int cantidadTotal = cantidad + otro.cantidad;
        return Producto(nombreCombinado, precioSumado, cantidadTotal);
    }

    // 2. FUNCION FRIEND: Accede a atributos privados para comparar precios
    friend void compararPrecios(const Producto& p1, const Producto& p2);

    // RETO ADICIONAL: Sobrecarga del operador << para imprimir en formato de tabla alineada
    friend std::ostream& operator<<(std::ostream& os, const Producto& p) {
        os << std::left << std::setw(18) << p.nombre
           << " | $" << std::right << std::setw(8) << std::fixed << std::setprecision(2) << p.precio
           << " | " << std::right << std::setw(8) << p.cantidad;
        return os;
    }
};

// Implementacion de la funcion amiga
void compararPrecios(const Producto& p1, const Producto& p2) {
    std::cout << std::left << std::setw(12) << p1.nombre << " vs " << std::setw(12) << p2.nombre << " -> ";
    if (p1.precio > p2.precio) {
        std::cout << p1.nombre << " es mas caro\n";
    } else if (p2.precio > p1.precio) {
        std::cout << p2.nombre << " es mas caro\n";
    } else {
        std::cout << "Ambos tienen el mismo precio\n";
    }
}

// Funcion auxiliar para imprimir el encabezado de las tablas
void imprimirEncabezadoTabla() {
    std::cout << std::left << std::setw(18) << "PRODUCTO"
              << " | " << std::right << std::setw(9) << "PRECIO"
              << " | " << std::right << std::setw(8) << "CANTIDAD" << "\n";
    std::cout << std::string(42, '-') << "\n";
}

int main() {
    std::vector<Producto> inventario = {
        Producto("Laptop", 1200.0, 5),
        Producto("Mouse", 25.0, 20),
        Producto("Teclado", 45.0, 15),
        Producto("Monitor", 300.0, 8),
        Producto("Audifonos", 80.0, 12)
    };

    std::cout << "==========================================" << "\n";
    std::cout << "          SISTEMA DE PRODUCTOS            " << "\n";
    std::cout << "==========================================" << "\n\n";

    // Demostracion del RETO ADICIONAL y FUNCION CONST: Impresion simetrica con operador <<
    std::cout << "--- LISTA DE PRODUCTOS EN INVENTARIO ---\n";
    imprimirEncabezadoTabla();
    for (const auto& prod : inventario) {
        std::cout << prod << "\n";
    }
    std::cout << std::string(42, '-') << "\n\n";

    // Demostracion de FUNCION INLINE
    std::cout << "--- CALCULO DE DESCUENTO (Funcion Inline) ---\n";
    double precioOriginal = inventario[0].getPrecio();
    double porcentajeDescuento = 15.0;
    double precioFinal = calcularDescuento(precioOriginal, porcentajeDescuento);
    
    std::cout << std::left << std::setw(22) << "Producto:" << inventario[0].getNombre() << "\n";
    std::cout << std::left << std::setw(22) << "Precio Original:" << "$" << std::fixed << std::setprecision(2) << precioOriginal << "\n";
    std::cout << std::left << std::setw(22) << "Descuento:" << porcentajeDescuento << "%\n";
    std::cout << std::left << std::setw(22) << "Precio Con Descuento:" << "$" << precioFinal << "\n\n";

    // Demostracion de FUNCION FRIEND
    std::cout << "--- COMPARACION DE PRECIOS (Funcion Friend) ---\n";
    compararPrecios(inventario[0], inventario[3]);
    compararPrecios(inventario[1], inventario[4]);
    std::cout << "\n";

    // Demostracion de LAMBDA: Filtrar productos por precio menor a un limite
    double limitePrecio = 100.0;
    std::cout << "--- FILTRADO CON LAMBDA (Productos menores a $" << limitePrecio << ") ---\n";
    imprimirEncabezadoTabla();
    auto filtrarPorPrecio = [limitePrecio](const Producto& p) {
        if (p.getPrecio() < limitePrecio) {
            std::cout << p << "\n";
        }
    };
    std::for_each(inventario.begin(), inventario.end(), filtrarPorPrecio);
    std::cout << std::string(42, '-') << "\n\n";

    // Demostracion de SOBRECARGA DEL OPERADOR +
    std::cout << "--- COMBINACION DE PRODUCTOS (Operador +) ---\n";
    Producto combo = inventario[1] + inventario[2]; // Combinar Mouse + Teclado
    imprimirEncabezadoTabla();
    std::cout << combo << "\n";
    std::cout << std::string(42, '-') << "\n";

    return 0;
}