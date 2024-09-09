import numpy as np
import time

def split(matrix):
    """
    Divide una matriz dada en cuatro submatrices (cuadrantes).
    Esta función es utilizada por el algoritmo de Strassen.
    """
    row, col = matrix.shape  # Obtener el número de filas y columnas de la matriz.
    row2, col2 = row // 2, col // 2  # Calcular la mitad de filas y columnas.
    return matrix[:row2, :col2], matrix[:row2, col2:], matrix[row2:, :col2], matrix[row2:, col2:]

def strassen(x, y):
    """
    Calcula el producto de dos matrices utilizando el algoritmo de Strassen mediante el enfoque de divide & conquer de forma recursiva.
    """
    # Caso base: si el tamaño de las matrices es 1x1, se realiza una multiplicación directa.
    if len(x) == 1:
        return x * y

    # Dividir las matrices en cuadrantes de forma recursiva hasta alcanzar el caso base.
    a, b, c, d = split(x)
    e, f, g, h = split(y)

    # Calcular los 7 productos recursivamente (p1, p2...p7).
    p1 = strassen(a, f - h) 
    p2 = strassen(a + b, h)	 
    p3 = strassen(c + d, e)	 
    p4 = strassen(d, g - e)	 
    p5 = strassen(a + d, e + h)	 
    p6 = strassen(b - d, g + h) 
    p7 = strassen(a - c, e + f) 

    # Calcular los valores de los 4 cuadrantes de la matriz final c.
    c11 = p5 + p4 - p2 + p6 
    c12 = p1 + p2		 
    c21 = p3 + p4		 
    c22 = p1 + p5 - p3 - p7 

    # Combinar los 4 cuadrantes en una sola matriz usando apilamiento horizontal y vertical.
    c = np.vstack((np.hstack((c11, c12)), np.hstack((c21, c22)))) 

    return c

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
A, B = leer_matrices("dataset_Matrix_1000x300 por 300x500.txt")

# Convertir las listas a matrices NumPy para facilitar operaciones.
MatrixA = np.array(A)
MatrixB = np.array(B)

# Asegurarse de que las matrices sean cuadradas y que su tamaño sea del orden n^2, agregando ceros si es necesario.
n = max(MatrixA.shape[0], MatrixA.shape[1], MatrixB.shape[0], MatrixB.shape[1])  # Obtener la dimensión máxima.
m = 1
while m < n:
    m *= 2  # Encontrar la potencia de 2 más cercana que sea mayor o igual a n.

# Rellenar las matrices con ceros para hacerlas cuadradas de tamaño m x m.
A = np.pad(MatrixA, ((0, m - MatrixA.shape[0]), (0, m - MatrixA.shape[1])), mode='constant')
B = np.pad(MatrixB, ((0, m - MatrixB.shape[0]), (0, m - MatrixB.shape[1])), mode='constant')

print("Multiplying...\n")
start = time.time()  # Registrar el tiempo de inicio.
resultado = strassen(A, B)  # Llamar a la función de Strassen para la multiplicación.
end = time.time()  # Registrar el tiempo de finalización.
elapsed_seconds = end - start  # Calcular el tiempo transcurrido.
print("Multiplication complete, elapsed time: ", elapsed_seconds, " seconds.\n")

# Guardar el resultado de la multiplicación en un archivo de salida.
result = open("strassen_result.txt", "w")
result.write(str(resultado))
result.close()
