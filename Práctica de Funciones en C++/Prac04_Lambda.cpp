#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> numeros = {12, 5, 8, 19, 24, 3, 17, 30, 1, 10};

    // Lambda 1: Imprime los elementos de un vector recibido por referencia constante
    auto mostrarVector = [](const std::vector<int>& vec) {
        for (int n : vec) {
            std::cout << n << " ";
        }
        std::cout << "\n";
    };

    std::cout << "Resultado Lambda 1 - Vector inicial:\n";
    mostrarVector(numeros);

    // Lambda 2: Comprueba si un numero es par retornando un valor booleano
    auto esPar = [](int n) {
        return n % 2 == 0;
    };
    int cantidadPares = std::count_if(numeros.begin(), numeros.end(), esPar);
    std::cout << "\nResultado Lambda 2 - Cantidad de numeros pares:\n" << cantidadPares << "\n";

    // Lambda 3: Captura la variable sumaTotal por referencia y acumula el valor de cada elemento
    int sumaTotal = 0;
    auto sumar = [&sumaTotal](int n) {
        sumaTotal += n;
    };
    std::for_each(numeros.begin(), numeros.end(), sumar);
    std::cout << "\nResultado Lambda 3 - Suma total de elementos:\n" << sumaTotal << "\n";

    // Lambda 4: Captura por valor la variable limite e imprime los elementos que la superan
    int limite = 10;
    std::cout << "\nResultado Lambda 4 - Elementos mayores al limite indicado:\n";
    auto mostrarMayores = [limite](int n) {
        if (n > limite) {
            std::cout << n << " ";
        }
    };
    std::for_each(numeros.begin(), numeros.end(), mostrarMayores);
    std::cout << "\n";

    // Lambda 5: Compara dos elementos y retorna verdadero si el primero es mayor para ordenar de forma descendente
    auto comparadorDescendente = [](int a, int b) {
        return a > b;
    };
    std::sort(numeros.begin(), numeros.end(), comparadorDescendente);

    std::cout << "\nResultado Lambda 5 - Vector ordenado de mayor a menor:\n";
    mostrarVector(numeros);

    return 0;
}