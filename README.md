# Parcial Infraestructura Paralelas y Distribuidas

## Codigo del Programa - 3743

## Kevin Jordan Alzate - 2228507


## Tiempos de Ejecucion
###  (Version Secuencial)

* 8.011s
* 8.197s
* 7.816s
* 7.659s
* 7.814s

_Tiempo Promedio: **7.88033s**_

###  (Primera Ejecucion Paralela)

* 7.351s
* 7.479s
* 7.416s
* 7.347s
* 7.489s


_Tiempo Promedio: **7.41533s**_

###  (Segunda Ejecucion Paralela)

* 7.532s
* 7.444s
* 7.524s
* 7.524s
* 7.522s


_Tiempo Promedio: **7.52333s**_

# Speedup
### Secuencial / Primera Ejecución Paralela 
_Speedup = 7.88033s/7.41533s = 1.0627_

## Analisis
___Se obtuvo un speedup de 1.0627 al comparar la ejecución secuencial con la paralela usando un número de hilos igual a los núcleos de la máquina. Este valor sugiere que el uso de múltiples hilos mejora el rendimiento, pero no de manera significativa, lo cual es un indicativo de que la paralelización no ha sido completamente efectiva en este caso.___
#
### Secuencial / Segunda Ejecución Paralela 

_Speedup = 7.88033s/7.52333s = 1.04745_

## Analisis
___El speedup fue de 1.04745 cuando se utilizó el doble de hilos. Aunque el valor es similar al de la primera ejecución, se observa una ligera disminución en el rendimiento en comparación con el uso del número de núcleos. Esto puede ser un indicativo de que el overhead de manejar más hilos supera las ganancias de rendimiento potenciales.___


#
## Eficiencia
### Contra Primera Ejecución Paralela 
_Eficiencia = 1.0627 / 6 = 0.17711  (17.7%)_



## Analisis
___Este valor de eficiencia fue de 0.17711, lo que indica que aproximadamente el 17.7% de la capacidad de los hilos se está utilizando efectivamente para el procesamiento. Esto sugiere que hay un considerable margen de mejora en la paralelización, posiblemente debido a la sobrecarga del sistema o a la forma en que se distribuyen las tareas entre los hilos.___
#

### Contra Segunda Ejecución Paralela
Eficiencia = 1.04745/ 12 =0.08728  (8.7%)


## Analisis
___La eficiencia fue de 0.08728, lo que implica que solo el 8.7% de la capacidad de los hilos se utiliza de manera efectiva. Este valor es bastante bajo y sugiere que el sistema no está aprovechando los hilos adicionales, lo que puede ser resultado de una carga de trabajo no equilibrada o de la gestión de hilos.___


# Conclusiones
__Los resultados obtenidos muestran que, aunque se logró cierta mejora en el rendimiento al aplicar paralelización, el speedup y la eficiencia son relativamente bajos. Para mejorar estos valores, se podrían explorar métodos adicionales de optimización del algoritmo, así como también una revisión de la estrategia de paralelización, considerando técnicas que puedan mejorar la distribución de la carga de trabajo entre los hilos.__
