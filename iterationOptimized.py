import time

def multiplicar_matrices_optimizado(A, B):
    """ 
    Realiza la multiplicación de dos matrices A y B siguiendo el método iterativo (Naive),
    pero esta vez, utilizando una optimización al transponer la segunda matriz, 
    para mejorar la localidad de los datos y la eficiencia.
    """
    # Obtener dimensiones de las matrices A y B
    filas_A = len(A)           # Número de filas de la matriz A.
    columnas_A = len(A[0])     # Número de columnas de la matriz A.
    filas_B = len(B)           # Número de filas de la matriz B.
    columnas_B = len(B[0])     # Número de columnas de la matriz B.
    
    # Verificación de compatibilidad de las matrices para la multiplicación.
    if columnas_A != filas_B:
        print("Las matrices no son multiplicables.")
        return 0

    # Transponer la segunda matriz B para mejorar la localidad de los datos en acceso secuencial.
    B_T = [[B[j][i] for j in range(filas_B)] for i in range(columnas_B)]
    
    # Crear una matriz para guardar la respuesta inicializada con ceros.
    C = [[0] * columnas_B for _ in range(filas_A)]
    
    # Multiplicación de matrices usando la transposición para mejorar la localidad de acceso.
    for i in range(filas_A):
        for j in range(columnas_B):
            suma = 0
            # Acceso secuencial a los datos transpuestos para optimizar la caché.
            for k in range(columnas_A):
                suma += A[i][k] * B_T[j][k]  # Notar el acceso secuencial a B_T.
            C[i][j] = suma  # Asignar el valor calculado a la posición correspondiente.
    return C

def leer_matrices(ruta_archivo):
    """ Lee dos matrices desde un archivo y las retorna."""
    with open(ruta_archivo, 'r') as archivo:
        # Leer todas las líneas del archivo.
        lineas = archivo.readlines()
        
        # Obtener las dimensiones de las matrices A y B desde las dos primeras líneas.
        filas_A, columnas_A = map(int, lineas[0].split())
        filas_B, columnas_B = map(int, lineas[1].split())     

        # Crear la matriz A utilizando las dimensiones y los datos correspondientes.
        A = []
        for i in range(2, 2 + filas_A):
            A.append(list(map(int, lineas[i].split())))
        
        # Crear la matriz B utilizando las dimensiones y los datos correspondientes.
        B = []
        for i in range(3 + filas_A, 3 + filas_A + filas_B):
            B.append(list(map(int, lineas[i].split())))
    return A, B

# Leer las matrices A y B desde el archivo especificado.
A, B = leer_matrices("dataset_Matrix_3x2 por 2x4.txt")

print("Multiplying...\n")
start = time.time()  # Registrar el tiempo de inicio.
resultado = multiplicar_matrices_optimizado(A, B)  # Llamar a la función de multiplicación optimizada.
end = time.time()    # Registrar el tiempo de finalización.
elapsed_seconds = end - start  # Calcular el tiempo transcurrido.
print("Multiplication complete, elapsed time: ", elapsed_seconds, " seconds.\n")

# Guardar el resultado de la multiplicación en un archivo de salida.
result = open("iteration_optimized_result.txt", "w")
result.write(str(resultado))
result.close()
