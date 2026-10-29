#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <exception>
#include <algorithm>

using namespace std;

class EdadInvalidaException : public exception {
public:
    const char* what() const noexcept override {
        return "Edad fuera de rango (debe estar entre 0 y 120).";
    }
};

class NotaInvalidaException : public exception {
public:
    const char* what() const noexcept override {
        return "Nota fuera de rango (debe estar entre 0 y 20).";
    }
};

class AlumnoNoEncontradoException : public exception {
    string mensaje;
public:
    explicit AlumnoNoEncontradoException(int codigo)
        : mensaje("No existe un alumno con el código " + to_string(codigo) + ".") {}
    const char* what() const noexcept override {
        return mensaje.c_str();
    }
};

class AlumnoDuplicadoException : public exception {
    string mensaje;
public:
    explicit AlumnoDuplicadoException(int codigo)
        : mensaje("Ya existe un alumno con el código " + to_string(codigo) + ".") {}
    const char* what() const noexcept override {
        return mensaje.c_str();
    }
};

class EntradaInvalidaException : public exception {
    string mensaje;
public:
    explicit EntradaInvalidaException(const string& detalle)
        : mensaje("Entrada inválida: " + detalle) {}
    const char* what() const noexcept override {
        return mensaje.c_str();
    }
};

class ArchivoNoEncontradoException : public exception {
    string mensaje;
public:
    explicit ArchivoNoEncontradoException(const string& nombre)
        : mensaje("No se pudo abrir el archivo '" + nombre + "'.") {}
    const char* what() const noexcept override {
        return mensaje.c_str();
    }
};

class ArchivoCorruptoException : public exception {
    string mensaje;
public:
    ArchivoCorruptoException(const string& nombre, int linea)
        : mensaje("El archivo '" + nombre + "' está corrupto (línea " + to_string(linea) + ").") {}
    const char* what() const noexcept override {
        return mensaje.c_str();
    }
};

struct Alumno {
    int codigo;
    string nombre;
    int edad;
    double nota;
};

int parsearEntero(const string& texto, const string& campo) {
    try {
        size_t pos = 0;
        int valor = stoi(texto, &pos);
        if (pos != texto.size()) {
            throw EntradaInvalidaException(campo + " debe ser un número entero.");
        }
        return valor;
    } catch (const invalid_argument&) {
        throw EntradaInvalidaException(campo + " debe ser un número entero.");
    } catch (const out_of_range&) {
        throw EntradaInvalidaException(campo + " está fuera del rango permitido.");
    }
}

double parsearDecimal(const string& texto, const string& campo) {
    try {
        size_t pos = 0;
        double valor = stod(texto, &pos);
        if (pos != texto.size()) {
            throw EntradaInvalidaException(campo + " debe ser un número.");
        }
        return valor;
    } catch (const invalid_argument&) {
        throw EntradaInvalidaException(campo + " debe ser un número.");
    } catch (const out_of_range&) {
        throw EntradaInvalidaException(campo + " está fuera del rango permitido.");
    }
}

void validarEdad(int edad) {
    if (edad < 0 || edad > 120) {
        throw EdadInvalidaException();
    }
}

void validarNota(double nota) {
    if (nota < 0.0 || nota > 20.0) {
        throw NotaInvalidaException();
    }
}

void validarNombre(const string& nombre) {
    if (nombre.empty()) {
        throw EntradaInvalidaException("el nombre no puede estar vacío.");
    }
    if (nombre.find(';') != string::npos) {
        throw EntradaInvalidaException("el nombre no puede contener ';'.");
    }
}

class RegistroAlumnos {
    vector<Alumno> alumnos;

    vector<Alumno>::iterator buscarIterador(int codigo) {
        return find_if(alumnos.begin(), alumnos.end(),
                       [codigo](const Alumno& a) { return a.codigo == codigo; });
    }

public:
    void agregar(const Alumno& nuevo) {
        validarNombre(nuevo.nombre);
        validarEdad(nuevo.edad);
        validarNota(nuevo.nota);
        if (buscarIterador(nuevo.codigo) != alumnos.end()) {
            throw AlumnoDuplicadoException(nuevo.codigo);
        }
        alumnos.push_back(nuevo);
    }

    const Alumno& buscar(int codigo) {
        auto it = buscarIterador(codigo);
        if (it == alumnos.end()) {
            throw AlumnoNoEncontradoException(codigo);
        }
        return *it;
    }

    void eliminar(int codigo) {
        auto it = buscarIterador(codigo);
        if (it == alumnos.end()) {
            throw AlumnoNoEncontradoException(codigo);
        }
        alumnos.erase(it);
    }

    void listar() const {
        if (alumnos.empty()) {
            cout << "No hay alumnos registrados.\n";
            return;
        }
        for (const auto& a : alumnos) {
            cout << "Código: " << a.codigo << " | Nombre: " << a.nombre
                 << " | Edad: " << a.edad << " | Nota: " << a.nota << "\n";
        }
    }

    void guardar(const string& nombreArchivo) const {
        ofstream salida(nombreArchivo);
        if (!salida.is_open()) {
            throw ArchivoNoEncontradoException(nombreArchivo);
        }
        for (const auto& a : alumnos) {
            salida << a.codigo << ';' << a.nombre << ';' << a.edad << ';' << a.nota << '\n';
        }
    }

    void cargar(const string& nombreArchivo) {
        ifstream entrada(nombreArchivo);
        if (!entrada.is_open()) {
            throw ArchivoNoEncontradoException(nombreArchivo);
        }
        vector<Alumno> temporal;
        string linea;
        int numeroLinea = 0;
        while (getline(entrada, linea)) {
            numeroLinea++;
            if (linea.empty()) {
                continue;
            }
            vector<string> campos;
            stringstream ss(linea);
            string campo;
            while (getline(ss, campo, ';')) {
                campos.push_back(campo);
            }
            if (campos.size() != 4) {
                throw ArchivoCorruptoException(nombreArchivo, numeroLinea);
            }
            try {
                Alumno a;
                a.codigo = parsearEntero(campos[0], "código");
                a.nombre = campos[1];
                a.edad = parsearEntero(campos[2], "edad");
                a.nota = parsearDecimal(campos[3], "nota");
                validarNombre(a.nombre);
                validarEdad(a.edad);
                validarNota(a.nota);
                for (const auto& existente : temporal) {
                    if (existente.codigo == a.codigo) {
                        throw ArchivoCorruptoException(nombreArchivo, numeroLinea);
                    }
                }
                temporal.push_back(a);
            } catch (const ArchivoCorruptoException&) {
                throw;
            } catch (const exception&) {
                throw ArchivoCorruptoException(nombreArchivo, numeroLinea);
            }
        }
        alumnos = temporal;
    }
};

string leerLinea(const string& mensaje) {
    cout << mensaje;
    string texto;
    if (!getline(cin, texto)) {
        throw EntradaInvalidaException("se cerró la entrada de datos.");
    }
    return texto;
}

void registrarAlumno(RegistroAlumnos& registro) {
    Alumno a;
    a.codigo = parsearEntero(leerLinea("Código: "), "código");
    a.nombre = leerLinea("Nombre: ");
    a.edad = parsearEntero(leerLinea("Edad: "), "edad");
    a.nota = parsearDecimal(leerLinea("Nota (0-20): "), "nota");
    registro.agregar(a);
    cout << "Alumno registrado correctamente.\n";
}

void buscarAlumno(RegistroAlumnos& registro) {
    int codigo = parsearEntero(leerLinea("Código a buscar: "), "código");
    const Alumno& a = registro.buscar(codigo);
    cout << "Código: " << a.codigo << " | Nombre: " << a.nombre
         << " | Edad: " << a.edad << " | Nota: " << a.nota << "\n";
}

void eliminarAlumno(RegistroAlumnos& registro) {
    int codigo = parsearEntero(leerLinea("Código a eliminar: "), "código");
    registro.eliminar(codigo);
    cout << "Alumno eliminado correctamente.\n";
}

int main() {
    const string archivo = "alumnos.txt";
    RegistroAlumnos registro;

    try {
        registro.cargar(archivo);
        cout << "Datos cargados desde '" << archivo << "'.\n";
    } catch (const ArchivoNoEncontradoException& e) {
        cout << "Aviso: " << e.what() << " Se iniciará con un registro vacío.\n";
    } catch (const ArchivoCorruptoException& e) {
        cout << "Aviso: " << e.what() << " Se iniciará con un registro vacío.\n";
    }

    bool salir = false;
    while (!salir) {
        cout << "\n===== SISTEMA DE REGISTRO DE ALUMNOS =====\n";
        cout << "1. Registrar alumno\n";
        cout << "2. Buscar alumno\n";
        cout << "3. Eliminar alumno\n";
        cout << "4. Listar alumnos\n";
        cout << "5. Guardar en archivo\n";
        cout << "6. Cargar desde archivo\n";
        cout << "0. Salir\n";

        try {
            int opcion = parsearEntero(leerLinea("Opción: "), "la opción");
            switch (opcion) {
                case 1: registrarAlumno(registro); break;
                case 2: buscarAlumno(registro); break;
                case 3: eliminarAlumno(registro); break;
                case 4: registro.listar(); break;
                case 5:
                    registro.guardar(archivo);
                    cout << "Datos guardados en '" << archivo << "'.\n";
                    break;
                case 6:
                    registro.cargar(archivo);
                    cout << "Datos cargados desde '" << archivo << "'.\n";
                    break;
                case 0: salir = true; break;
                default:
                    throw EntradaInvalidaException("opción no disponible en el menú.");
            }
        } catch (const EdadInvalidaException& e) {
            cout << "Error de edad: " << e.what() << "\n";
        } catch (const NotaInvalidaException& e) {
            cout << "Error de nota: " << e.what() << "\n";
        } catch (const AlumnoNoEncontradoException& e) {
            cout << "Error de búsqueda: " << e.what() << "\n";
        } catch (const AlumnoDuplicadoException& e) {
            cout << "Error de registro: " << e.what() << "\n";
        } catch (const ArchivoNoEncontradoException& e) {
            cout << "Error de archivo: " << e.what() << "\n";
        } catch (const ArchivoCorruptoException& e) {
            cout << "Error de archivo: " << e.what() << "\n";
        } catch (const EntradaInvalidaException& e) {
            if (cin.eof()) {
                cout << e.what() << "\n";
                salir = true;
            } else {
                cout << e.what() << "\n";
            }
        } catch (const exception& e) {
            cout << "Error inesperado: " << e.what() << "\n";
        }
    }

    cout << "Programa finalizado.\n";
    return 0;
}