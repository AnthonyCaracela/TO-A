# Tecnología-de-Objetos

En este repositorio se encontrarán las actividades desarrolladas del curso de Tecnología de Objetos.

- Práctica de Manejo de Errores y Excepciones
- Práctica de Funciones Inline, Friend, Constantes, Lambda y Sobrecarga de Operadores

---

# Práctica 4: Funciones Lambda – Operaciones con vectores

Archivo: `Práctica de Funciones en C++/Prac04_Lambda.cpp`

## 1. ¿Qué se pedía?

Usar funciones lambda para procesar datos de un vector de forma rápida. El enunciado pedía:

1. Crear un `vector<int>` con al menos 10 números.
2. Usar una lambda para contar los números pares.
3. Usar una lambda para calcular la suma total.
4. Usar una lambda para mostrar los números mayores que un valor dado.
5. Reto adicional: ordenar el vector con `std::sort` y una lambda personalizada.

### Requisitos del enunciado y cómo se cumplen

| Requisito | ¿Cumplido? | Dónde se cumple |
|---|---|---|
| Vector con al menos 10 números | Sí | `numeros` tiene 10 elementos |
| Contar los números pares | Sí | Lambda 2 (`esPar`) con `std::count_if` |
| Calcular la suma total | Sí | Lambda 3 (`sumar`) con `std::for_each` |
| Mostrar los mayores que un valor dado | Sí | Lambda 4 (`mostrarMayores`), con `limite = 10` |
| Reto: ordenar con `std::sort` y lambda | Sí | Lambda 5 (`comparadorDescendente`) |
| Mostrar el vector (apoyo) | Sí | Lambda 1 (`mostrarVector`) |

## 2. ¿Qué es una lambda?

Una lambda es una función **sin nombre** que se escribe en el mismo lugar donde se va a usar. Sirve para cosas cortas y rápidas, como filtrar, recorrer o ordenar datos.

Su forma general es:

```
[captura](parámetros) { cuerpo }
```

- **`[captura]`**: las variables de afuera que la lambda puede usar.
  - `[]` no usa nada de afuera.
  - `[limite]` usa una **copia** de la variable (captura por valor).
  - `[&sumaTotal]` usa la **variable original** y puede cambiarla (captura por referencia).
- **`(parámetros)`**: los datos que recibe, igual que una función normal.
- **`{ cuerpo }`**: lo que hace la lambda.

### Tipos de captura (comparación)

| Tipo | Sintaxis | La lambda usa... | ¿Puede cambiar la variable original? | Ejemplo en esta práctica |
|---|---|---|---|---|
| Sin captura | `[]` | Solo lo que recibe por parámetro | No aplica | `mostrarVector`, `esPar`, `comparadorDescendente` |
| Por valor | `[limite]` | Una **copia** de la variable | No | `mostrarMayores` |
| Por referencia | `[&sumaTotal]` | La variable **original** | Sí | `sumar` |

## 3. Código completo

```cpp
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
```

## 4. Explicación paso a paso

### Diagrama de flujo del programa

```mermaid
flowchart TD
    A([Inicio]) --> B[Crear el vector con 10 números]
    B --> C[Lambda 1: mostrar el vector inicial]
    C --> D[Lambda 2: contar los pares con count_if]
    D --> E[Lambda 3: sumar todos con for_each]
    E --> F[Lambda 4: mostrar los mayores al límite con for_each]
    F --> G[Lambda 5: ordenar de mayor a menor con sort]
    G --> H[Lambda 1: mostrar el vector ordenado]
    H --> I([Fin])
```

### Librerías usadas

| Librería | Para qué se usa |
|---|---|
| `<iostream>` | Mostrar datos en pantalla con `std::cout`. |
| `<vector>` | Poder usar `std::vector`, una lista de datos que puede cambiar de tamaño. |
| `<algorithm>` | Usar `std::count_if`, `std::for_each` y `std::sort`, que reciben lambdas. |

Funciones de `<algorithm>` que reciben lambdas en este programa:

| Función | Qué hace | Lambda que recibe |
|---|---|---|
| `std::count_if` | Cuenta cuántos elementos cumplen una condición | `esPar` |
| `std::for_each` | Aplica una acción a cada elemento del vector | `sumar` y `mostrarMayores` |
| `std::sort` | Ordena el vector según el criterio que se le da | `comparadorDescendente` |

### El vector

```cpp
std::vector<int> numeros = {12, 5, 8, 19, 24, 3, 17, 30, 1, 10};
```

Se crea un vector con **10 números enteros**, que es el mínimo que pedía el enunciado. Todas las lambdas trabajan con estos datos.

### Lambda 1: `mostrarVector` (mostrar el vector)

```cpp
auto mostrarVector = [](const std::vector<int>& vec) {
    for (int n : vec) {
        std::cout << n << " ";
    }
    std::cout << "\n";
};
```

- **Qué hace:** recorre el vector y muestra cada número separado por un espacio.
- **Captura `[]`:** vacía, porque no necesita variables de afuera. Todo lo que usa lo recibe por parámetro.
- **Parámetro `const std::vector<int>& vec`:** recibe el vector **por referencia** (`&`), así no se hace una copia, y es **constante** (`const`), así la lambda no puede modificarlo.
- **Por qué se usa dos veces:** se escribe una sola vez y se reutiliza para mostrar el vector al inicio y al final (ya ordenado).

### Lambda 2: `esPar` (contar los pares)

```cpp
auto esPar = [](int n) {
    return n % 2 == 0;
};
int cantidadPares = std::count_if(numeros.begin(), numeros.end(), esPar);
```

- **Qué hace:** revisa si un número es par. Un número es par si al dividirlo entre 2 el residuo (`%`) es 0.
- **Retorna:** `true` si es par, `false` si no lo es.
- **`std::count_if`:** recorre todo el vector y **cuenta** cuántas veces la lambda devolvió `true`.
- **Pares encontrados:** 12, 8, 24, 30 y 10, por lo tanto el resultado es **5**.

Seguimiento de la lambda, número por número:

| Número | `n % 2` | ¿Es par? |
|---|---|---|
| 12 | 0 | Sí |
| 5 | 1 | No |
| 8 | 0 | Sí |
| 19 | 1 | No |
| 24 | 0 | Sí |
| 3 | 1 | No |
| 17 | 1 | No |
| 30 | 0 | Sí |
| 1 | 1 | No |
| 10 | 0 | Sí |
| **Total de pares** | | **5** |

### Lambda 3: `sumar` (suma total)

```cpp
int sumaTotal = 0;
auto sumar = [&sumaTotal](int n) {
    sumaTotal += n;
};
std::for_each(numeros.begin(), numeros.end(), sumar);
```

- **Qué hace:** va sumando cada número del vector en la variable `sumaTotal`.
- **Captura `[&sumaTotal]`:** el `&` significa captura **por referencia**. La lambda trabaja con la variable original, no con una copia, por eso puede ir acumulando la suma y el valor final se ve afuera.
- **`std::for_each`:** recorre todo el vector y le pasa cada número a la lambda.
- **Resultado:** 12 + 5 + 8 + 19 + 24 + 3 + 17 + 30 + 1 + 10 = **129**.

Cómo va cambiando `sumaTotal` en cada paso:

| Paso | Número `n` | `sumaTotal` antes | `sumaTotal` después |
|---|---|---|---|
| 1 | 12 | 0 | 12 |
| 2 | 5 | 12 | 17 |
| 3 | 8 | 17 | 25 |
| 4 | 19 | 25 | 44 |
| 5 | 24 | 44 | 68 |
| 6 | 3 | 68 | 71 |
| 7 | 17 | 71 | 88 |
| 8 | 30 | 88 | 118 |
| 9 | 1 | 118 | 119 |
| 10 | 10 | 119 | **129** |

### Lambda 4: `mostrarMayores` (mayores que un valor)

```cpp
int limite = 10;
auto mostrarMayores = [limite](int n) {
    if (n > limite) {
        std::cout << n << " ";
    }
};
std::for_each(numeros.begin(), numeros.end(), mostrarMayores);
```

- **Qué hace:** muestra solo los números que son mayores que `limite`.
- **Captura `[limite]`:** sin `&`, es captura **por valor**. La lambda guarda una **copia** de `limite` (que vale 10). Solo necesita leer ese valor, no cambiarlo.
- **Resultado:** los mayores que 10 son **12, 19, 24, 17 y 30**. El 10 no aparece porque no es mayor, es igual.

Seguimiento con `limite = 10`:

| Número `n` | ¿`n > 10`? | ¿Se muestra? |
|---|---|---|
| 12 | Sí | Sí |
| 5 | No | No |
| 8 | No | No |
| 19 | Sí | Sí |
| 24 | Sí | Sí |
| 3 | No | No |
| 17 | Sí | Sí |
| 30 | Sí | Sí |
| 1 | No | No |
| 10 | No (es igual, no mayor) | No |

### Lambda 5: `comparadorDescendente` (ordenar, reto adicional)

```cpp
auto comparadorDescendente = [](int a, int b) {
    return a > b;
};
std::sort(numeros.begin(), numeros.end(), comparadorDescendente);
```

- **Qué hace:** le dice a `std::sort` cómo comparar dos números. Devuelve `true` si `a` es mayor que `b`, así el mayor va primero.
- **Por qué es necesaria:** por defecto `std::sort` ordena de menor a mayor. Con esta lambda personalizada se ordena de **mayor a menor**.
- **Resultado:** `30 24 19 17 12 10 8 5 3 1`.

Vector antes y después de ordenar:

| Posición | Antes | Después |
|---|---|---|
| 1 | 12 | 30 |
| 2 | 5 | 24 |
| 3 | 8 | 19 |
| 4 | 19 | 17 |
| 5 | 24 | 12 |
| 6 | 3 | 10 |
| 7 | 17 | 8 |
| 8 | 30 | 5 |
| 9 | 1 | 3 |
| 10 | 10 | 1 |

## 5. Salida del programa

```
Resultado Lambda 1 - Vector inicial:
12 5 8 19 24 3 17 30 1 10 

Resultado Lambda 2 - Cantidad de numeros pares:
5

Resultado Lambda 3 - Suma total de elementos:
129

Resultado Lambda 4 - Elementos mayores al limite indicado:
12 19 24 17 30 

Resultado Lambda 5 - Vector ordenado de mayor a menor:
30 24 19 17 12 10 8 5 3 1 
```

## 6. Resumen de las lambdas

| Lambda | Captura | Qué hace | Se usa con | Resultado |
|---|---|---|---|---|
| `mostrarVector` | `[]` | Imprime el vector | Llamada directa | Muestra los 10 números |
| `esPar` | `[]` | Dice si un número es par | `std::count_if` | 5 pares |
| `sumar` | `[&sumaTotal]` (referencia) | Acumula la suma | `std::for_each` | 129 |
| `mostrarMayores` | `[limite]` (valor) | Muestra los mayores al límite | `std::for_each` | 12 19 24 17 30 |
| `comparadorDescendente` | `[]` | Compara para ordenar de mayor a menor | `std::sort` | 30 24 19 17 12 10 8 5 3 1 |

## 7. Cómo compilar y ejecutar

```
g++ Prac04_Lambda.cpp -o Prac04_Lambda
./Prac04_Lambda
```

## 8. Conclusión

Las lambdas permiten escribir funciones cortas justo donde se necesitan, sin tener que declarar una función aparte. En esta práctica se vio cómo usarlas para mostrar, contar, sumar, filtrar y ordenar datos de un vector, y cómo la **captura** (por valor o por referencia) controla qué variables de afuera puede usar cada lambda.