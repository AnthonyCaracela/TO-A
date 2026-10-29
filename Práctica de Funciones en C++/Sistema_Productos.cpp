#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

// 1. FUNCION INLINE: Calcula el precio de un producto aplicando un porcentaje de descuento
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

    // 3. FUNCIONES CONSTANTES: Permiten consultar atributos sin modificar el estado del objeto
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
        std::cout << "Producto: " << nombre << " | Precio: $" << precio << " | Cantidad: " << cantidad << "\n";
    }

    // 5. SOBRECARGA DEL OPERADOR +: Combina dos productos sumando sus precios y sus cantidades
    Producto operator+(const Producto& otro) const {
        std::string nombreCombinado = nombre + " con " + otro.nombre;
        double precioSumado = precio + otro.precio;
        int cantidadTotal = cantidad + otro.cantidad;
        return Producto(nombreCombinado, precioSumado, cantidadTotal);
    }

    // 2. FUNCION FRIEND: Declaración de función amiga para acceder a atributos privados y comparar precios
    friend void compararPrecios(const Producto& p1, const Producto& p2);

    // RETO ADICIONAL: Sobrecarga del operador << para imprimir el producto en formato legible
    friend std::ostream& operator<<(std::ostream& os, const Producto& p) {
        os << "[" << p.nombre << " | Precio: $" << p.precio << " | Stock: " << p.cantidad << " unidades]";
        return os;
    }
};

// Implementacion de la función amiga
void compararPrecios(const Producto& p1, const Producto& p2) {
    std::cout << "Comparando " << p1.nombre << " con " << p2.nombre << ":\n";
    if (p1.precio > p2.precio) {
        std::cout << p1.nombre << " es mas caro que " << p2.nombre << "\n";
    } else if (p2.precio > p1.precio) {
        std::cout << p2.nombre << " es mas caro que " << p1.nombre << "\n";
    } else {
        std::cout << "Ambos productos tienen el mismo precio\n";
    }
}

int main() {
    // Creación del vector con inventario de productos
    std::vector<Producto> inventario = {
        Producto("Laptop", 1200.0, 5),
        Producto("Mouse", 25.0, 20),
        Producto("Teclado", 45.0, 15),
        Producto("Monitor", 300.0, 8),
        Producto("Audifonos", 80.0, 12)
    };

    std::cout << "=== SISTEMA DE PRODUCTOS ===\n\n";

    // Demostracion del RETO ADICIONAL y FUNCION CONST: Impresión con el operador << sobrecargado
    std::cout << "--- LISTA DE PRODUCTOS ---\n";
    for (const auto& prod : inventario) {
        std::cout << prod << "\n";
    }
    std::cout << "\n";

    // Demostracion de FUNCION INLINE
    std::cout << "--- CALCULO DE DESCUENTO (Funcion Inline) ---\n";
    double precioOriginal = inventario[0].getPrecio();
    double descuento = 15.0;
    double precioFinal = calcularDescuento(precioOriginal, descuento);
    std::cout << "Precio original de " << inventario[0].getNombre() << ": $" << precioOriginal << "\n";
    std::cout << "Precio final con " << descuento << "% de descuento: $" << precioFinal << "\n\n";

    // Demostracion de FUNCION FRIEND
    std::cout << "--- COMPARACION DE PRECIOS (Funcion Friend) ---\n";
    compararPrecios(inventario[0], inventario[3]);
    std::cout << "\n";

    // Demostracion de LAMBDA: Filtrar productos por precio menor a un umbral
    double limitePrecio = 100.0;
    std::cout << "--- FILTRADO CON LAMBDA (Productos con precio menor a $" << limitePrecio << ") ---\n";
    auto filtrarPorPrecio = [limitePrecio](const Producto& p) {
        if (p.getPrecio() < limitePrecio) {
            std::cout << p << "\n";
        }
    };
    std::for_each(inventario.begin(), inventario.end(), filtrarPorPrecio);
    std::cout << "\n";

    // Demostracion de SOBRECARGA DEL OPERADOR +
    std::cout << "--- COMBINACION DE PRODUCTOS (Operador +) ---\n";
    Producto combo = inventario[1] + inventario[2]; // Combinar Mouse + Teclado
    std::cout << "Producto resultante de la suma:\n" << combo << "\n";

    return 0;
}