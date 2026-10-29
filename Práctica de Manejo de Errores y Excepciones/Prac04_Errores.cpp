#include <iostream>
#include <stdexcept>
#include <limits>

int main() {
    double num1, num2;

    try {
        // 1. Pedir el primer número y verificar el tipo de dato ingresado
        std::cout << "Ingrese el primer número: ";
        if (!(std::cin >> num1)) {
            throw std::invalid_argument("Error de tipo: La entrada ingresada no es un número válido.");
        }

        // 2. Pedir el segundo número y verificar el tipo de dato ingresado
        std::cout << "Ingrese el segundo número: ";
        if (!(std::cin >> num2)) {
            throw std::invalid_argument("Error de tipo: La entrada ingresada no es un número válido.");
        }

        // 3. Validar error aritmético (división por cero)
        if (num2 == 0) {
            throw std::runtime_error("Error aritmético: No está permitida la división entre cero.");
        }

        // Realizar la división si los datos son correctos
        double resultado = num1 / num2;
        std::cout << "Resultado de la división: " << resultado << std::endl;

    } catch (const std::invalid_argument& e) {
        // Captura errores de ingreso de datos (no numéricos)
        std::cout << "\n[EXCEPCIÓN DE ENTRADA] " << e.what() << std::endl;
    } catch (const std::runtime_error& e) {
        // Captura errores aritméticos (división entre cero)
        std::cout << "\n[EXCEPCIÓN ARITMÉTICA] " << e.what() << std::endl;
    } catch (const std::exception& e) {
        // Captura genérica para cualquier otra excepción no contemplada
        std::cout << "\n[EXCEPCIÓN GENÉRICA] " << e.what() << std::endl;
    }

    return 0;
}