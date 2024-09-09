import time

def multiplicar_matrices(A, B):
    """Realiza la multiplicación de dos matrices A y B usando el método iterativo (Naive)"""     
    filas_A = len(A)           # Número de filas en la matriz A.
    columnas_A = len(A[0])     # Número de columnas en la matriz A.
    filas_B = len(B)           # Número de filas en la matriz B.
    columnas_B = len(B[0])     # Número de columnas en la matriz B.

    # Verificación de compatibilidad de las matrices para la multiplicación.
    if columnas_A != filas_B:
        print("Las matrices no son multiplicables")
        return 0
    
    # Crear una matriz para guardar la respuesta inicializada con ceros.
    C = [[0] * columnas_B for _ in range(filas_A)]    
    
    # Multiplicación de matrices utilizando un enfoque iterativo.
    for i in range(filas_A):
        for j in range(columnas_B):
            for k in range(columnas_A):
                C[i][j] += A[i][k] * B[k][j]  # Acumula el producto de los elementos correspondientes.
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
A, B = leer_matrices("dataset_Matrix_1000x1000 por 1000x1000.txt")

print("Multiplying...\n")
start = time.time()  # Registrar el tiempo de inicio.
resultado = multiplicar_matrices(A, B)  # Llamar a la función de multiplicación de matrices.
end = time.time()    # Registrar el tiempo de finalización.
elapsed_seconds = end - start  # Calcular el tiempo transcurrido.
print("Multiplication complete, elapsed time: ", elapsed_seconds, " seconds.\n")

# Guardar el resultado de la multiplicación en un archivo de salida.
result = open("iteration_result.txt", "w")
result.write(str(resultado))
result.close()
