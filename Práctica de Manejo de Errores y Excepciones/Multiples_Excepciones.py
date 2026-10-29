try:
    # Pedir dos números al usuario
    numerador = float(input("Introduce el primer número (numerador): "))
    denominador = float(input("Introduce el segundo número (denominador): "))
       # División
    resultado = numerador / denominador
    # Ingreso de datos correctos
    print(f"El resultado de la división es: {resultado}")
# No se ingresa el valor correcto
except ValueError:
    print("¡Error de tipo! Por favor, asegúrate de ingresar únicamente números válidos.")
# Division entre cero
except ZeroDivisionError:
    print("¡Error aritmético! No es posible dividir un número entre cero.")