# Repaso Ⅰ

## Declaración
Es posible declarar una función para solo indicar que existe en ese momento. Si es que uno usa una función no declarada, `c` advierte que usa una función no declarada, este caso está en `declaracion.c`, y la advertencia aparece incluso corriendo: `gcc -o main ./declaracion.c`.

Uno de los usos es para cuando se declara una struct que puede tener un puntero a si misma en su interior.

## Comandos de compilación
`gcc` posee argumentos adicionales para poder mostrar más posibles errores de código. Estos son:
|argumento|Descripción|
|-|-|
|`-Wall`| Advierte sobre acciones "questionables" que pueden ser arregladas fácilmente.|
|`-Wextra`| Advierte sobre ciertas acciones que no son de `-Wall`.|
|`-Wshadow`| Advierte cuando una declaración es sobreescrita por otra (por ejemplo redeclarar `i` en una función). |
|`-Wconversion`| Advierte sobre conversiones de valores no explícitas (por ejemplo entre float e int). |

La información fue sacada de la documentación de `gcc`: https://gcc.gnu.org/onlinedocs/gcc/Warning-Options.html

## Headers

Los headers son archivos `.h` en `c` y `.hpp` en `c++`. Estos archivos declaran lo que está expuesto a ser utilizado en otras funciones, pero también lo que es usado en el mismo archivo

## Extra: Uso de `&` en declaración de funciones en C++
Es común en `C` el pasar un puntero a una función, pero en `C++` se puede pasar implícitamente el valor de referencia. El ejemplo se encuentra en el archivo `utils/sort.cpp`.


## Problema de Igualar valores

Dado dos colecciones de valores $N$ y $K$ con $|K|\geq|N|$, deberás indicar si existe una colección $S$ de elementos de $K$ con $|S| = |N|$, tal que, dado $S=s_1, ..., s_{|N|}$ y  $N=n_1, ..., n_{|N|}$, entonces lo siguiente es verdad: 
$$s_1 + n_1 = s_2 + n_2 = ... = s_{|N|} + n_{|N|}$$

El valor que debe ser impreso en consola es el primer índice de $K$ tal que satsfaga el problema. Si no hay valor válido, se imprime $-1$.

#### Restricciones:
* $0\leq n_i<100$
* $0\leq k_i<100$
* $2\leq|N|\leq|K|<10^4$

#### Formato input
La primera línea posee la cantidad de problemas $P$.
Luego, $P$ veces se entrega primero los valores de `|N| |K|`, y sus siguientes dos líneas entregan los valores de $N$ y $K$, respectivamente.

#### Ejemplo

Input:
```
2
2 4
3 5
1 4 2 3
4 8
1 2 3 4
4 5 6 4 5 6 4 5
```

Output:
```
2
-1
```

#### Ejemplo 2
Problema: cuantas veces está un valor de N en K. imprimir por cada posición $i$ de N cuantas veces está $n_i$ en K


Input:
```
2
2 4
3 5
1 4 2 3
4 8
1 4 6 4
4 5 6 4 5 6 4 5
```

Output:
```
1 0
0 3 2 3
```

