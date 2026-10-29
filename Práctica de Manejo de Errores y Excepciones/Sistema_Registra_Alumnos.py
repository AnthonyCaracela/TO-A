import json

#  Error Personalizado
class AlumnoNoEncontradoError(Exception):
    """Excepción lanzada cuando el alumno buscado no existe en el registro."""
    pass

# Cargar los datos desde un archivo JSON
def cargar_registro(nombre_archivo):
    try:
        with open(nombre_archivo, "r", encoding="utf-8") as archivo:
            return json.load(archivo)
    # Archivo no encontrado
    except FileNotFoundError:
        print(f"⚠️ El archivo '{nombre_archivo}' no existe. Se iniciará un registro vacío.")
        return {}
    # Archivo corrupto (JSON inválido)
    except json.JSONDecodeError:
        print(f"❌ El archivo '{nombre_archivo}' está corrupto. Se iniciará un registro vacío.")
        return {}

# Guardar los datos
def guardar_registro(nombre_archivo, datos):
    with open(nombre_archivo, "w", encoding="utf-8") as archivo:
        json.dump(datos, archivo, indent=4, ensure_ascii=False)


archivo_datos = "alumnos.json"
import os
if not os.path.exists(archivo_datos):
    datos_iniciales = {
        "Perez Quiroz, Andre": {"edad": 14},
        "Rivera Huarca, Rebeca": {"edad": 16},
        "Montes Palomino, Mauricio": {"edad": 17},
        "Peralta Delgado, Renzo": {"edad": 15},
        "Anco Ccacya, Beto": {"edad": 14}
    }
    with open(archivo_datos, "w", encoding="utf-8") as archivo:
        json.dump(datos_iniciales, archivo, indent=4, ensure_ascii=False)

registro = cargar_registro(archivo_datos)

while True:
    print("\n--- SISTEMA DE REGISTRO DE ALUMNOS ---")
    print("1. Agregar Alumno")
    print("2. Buscar Alumno")
    print("3. Salir")
    
    opcion = input("Selecciona una opción: ")
    
    if opcion == "1":
        # 4. Manejo de errores en entrada de datos
        nombre = input("Nombre del alumno: ").strip()
        if not nombre:
            print("❌ El nombre no puede estar vacío.")
            continue
            
        try:
            edad = int(input("Edad del alumno: "))
            if edad <= 0 or edad > 100:
                # Forzamos un ValueError si la edad no es lógica
                raise ValueError
        except ValueError:
            print("❌ Entrada inválida. La edad debe ser un número entero entre 1 y 100.")
            continue
            
        # Guardar en el diccionario
        registro[nombre] = {"edad": edad}
        guardar_registro(archivo_datos, registro)
        print(f"✅ Alumno {nombre} registrado con éxito.")
        
    elif opcion == "2":
        nombre_buscar = input("Nombre del alumno a buscar: ").strip()
        try:
            # Uso de la Excepción Personalizada
            if nombre_buscar not in registro:
                raise AlumnoNoEncontradoError(f"El alumno '{nombre_buscar}' no está en la base de datos.")
            
            # Si existe, muestra la información
            info = registro[nombre_buscar]
            print(f"🔍 Alumno encontrado -> Nombre: {nombre_buscar}, Edad: {info['edad']}")
            
        except AlumnoNoEncontradoError as error:
            print(f"❌ Error Personalizado: {error}")
            
    elif opcion == "3":
        print("¡Hasta luego!")
        break
    else:
        print("❌ Opción no válida. Intenta de nuevo.")