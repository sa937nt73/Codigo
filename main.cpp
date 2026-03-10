#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

/*
Función que calcula sin(x) usando la serie de Taylor

Serie:
sin(x) = x - x^3/3! + x^5/5! - x^7/7! + ...

Siguiendo el pseudocódigo:

term = x
sum  = x
eps  = 10^-8

do
    term = -term * x * x / ((2*n)*(2*n+1))
    sum  = sum + term
while abs(term/sum) > eps

La función retorna:
- suma aproximada de sin(x)
- número de iteraciones realizadas
*/

pair<float,int> sin_series(float x, float eps = 1e-8f)
{
    // Inicialización según el pseudocódigo
    float term = x;   // primer término de la serie
    float suma = x;   // suma acumulada
    int n = 1;        // índice de la serie
    int imax = 1;     // contador de iteraciones

    /*
    Iteración del algoritmo

    En cada paso se calcula el siguiente término usando
    el anterior (relación recursiva) para evitar calcular
    factoriales y potencias directamente.
    */

    while (fabsf(term/suma) > eps)
    {
        // cálculo del siguiente término de la serie
        term = -term * x * x / ((2*n)*(2*n+1));

        // se agrega el nuevo término a la suma acumulada
        suma += term;

        // avanzar al siguiente índice
        n++;
        imax++;
    }

    // retorna la aproximación y el número de iteraciones
    return {suma, imax};
}

int main()
{
    // valores de x para evaluar la serie
    vector<float> x_vals = {0.1f, 0.5f, 1.0f, 2.0f, 3.0f, 6.0f, 10.0f};

    // impresión del encabezado de la tabla
    cout << setw(8) << "x"
         << setw(8) << "imax"
         << setw(15) << "sum"
         << setw(20) << "error relativo" << endl;

    /*
    Para cada valor de x:
    1. calcular la serie
    2. comparar con el valor real sin(x)
    3. calcular el error relativo
    */

    for(float x : x_vals)
    {
        auto result = sin_series(x);

        float suma = result.first;   // aproximación obtenida
        int imax = result.second;    // número de iteraciones

        // valor real usando la función matemática
        float real = sinf(x);

        // cálculo del error relativo
        float error = fabsf(suma - real) / fabsf(real);

        // imprimir fila de la tabla
        cout << setw(8) << x
             << setw(8) << imax
             << setw(15) << suma
             << setw(20) << scientific << error
             << endl;
    }

    return 0;
}