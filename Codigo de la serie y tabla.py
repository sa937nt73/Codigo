import numpy as np
import pandas as pd
import math

def sin_series(x, eps=1e-8): # Función que calcula el seno de x utilizando la serie de Taylor

    term = x
    suma = x
    n = 1
    imax = 1

    while abs(term/suma) > eps: # Ciclo que se repite hasta que el término actual es suficientemente pequeño en comparación con la suma acumulada
        term = -term * x * x / ((2*n)*(2*n+1))
        suma += term
        
        n += 1
        imax += 1

    return suma, imax


# valores de x
x_vals = np.array([0.1, 0.5, 1, 2, 3, 6, 10])

# vectores para guardar resultados
imax_vals = []
sum_vals = []
error_vals = []

for x in x_vals: # Tabla de resultados para cada valor de x

    suma, imax = sin_series(x)
    
    real = math.sin(x)
    
    error = abs(suma - real)/abs(real)

    imax_vals.append(imax)
    sum_vals.append(suma)
    error_vals.append(error)


# crear tabla
tabla = pd.DataFrame({
    "x": x_vals,
    "imax": imax_vals,
    "sum": sum_vals,
    "error relativo": error_vals
})

print(tabla)