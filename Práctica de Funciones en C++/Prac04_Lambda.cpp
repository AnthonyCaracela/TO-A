#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    // Vector con 10 números de prueba (cumple indicación inicial)
    std::vector<int> numeros = {12, 5, 8, 19, 24, 3, 17, 30, 1, 10};

    // LAMBDA 1: Imprimir elementos del vector (Lambda reusable de despliegue)
    auto imprimirVector = [](const std::vector<int>& vec) {
        for (int n : vec) {
            std::cout << n << " ";
        }
        std::cout << "\n";
    };
    std::cout << "--- VECTOR ORIGINAL ---\n";
    imprimirVector(numeros);
    std::cout << "\n";

    // LAMBDA 2: Contar los números pares (Sintaxis sin capturas / Predicado)
    auto esPar = [](int n) {
        return n % 2 == 0;
    };
    int cantidadPares = std::count_if(numeros.begin(), numeros.end(), esPar);
    std::cout << "1. Cantidad de numeros pares: " << cantidadPares << "\n";

    // LAMBDA 3: Calcular la suma total (Captura por referencia [&sumaTotal])
    int sumaTotal = 0;
    auto sumar = [&sumaTotal](int n) {
        sumaTotal += n;
    };
    std::for_each(numeros.begin(), numeros.end(), sumar);
    std::cout << "2. Suma total del vector: " << sumaTotal << "\n";

    // LAMBDA 4: Mostrar números mayores que un valor dado (Captura por valor [limite])
    int limite = 10;
    std::cout << "3. Numeros mayores que " << limite << ": ";
    auto mostrarMayores = [limite](int n) {
        if (n > limite) {
            std::cout << n << " ";
        }
    };
    std::for_each(numeros.begin(), numeros.end(), mostrarMayores);
    std::cout << "\n\n";

    // LAMBDA 5: Ordenar de mayor a menor con std::sort (Reto adicional)
    auto comparadorDescendente = [](int a, int b) {
        return a > b;
    };
    std::sort(numeros.begin(), numeros.end(), comparadorDescendente);
    std::cout << "--- RETO ADICIONAL: VECTOR ORDENADO (MAYOR A MENOR) ---\n";
    imprimirVector(numeros);
    return 0;
}