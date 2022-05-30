# taller1-paralela
En el siguiente repositorio encontrarán el taller 1 del ramo o asignatura **Computación Paralela y Distribuida**.

## Integrantes
* Martín Sobarzo
* Cristobal Abarca
* Rodrigo Ubilla

## Creación
Debe seguir los siguientes pasos para ejecutar el programa.

### Clonación:
```
$ git clone https://github.com/Meshdako/taller1-paralela.git
$ cd taller1-paralela
```
Una vez dentro del respositorio, podemos abrir dos terminales para ingresar a cada carpeta por separado.

### Ingresar
```
$ cd main_secuencial/main_openmp
```
*En la parte de $ cd escribimos solo una de las carpetas, no ambas al mismo tiempo.*

### Make
```
$ make
$ *time ./nombre_archivo
```
*Agregamos el símbolo del asterísco en el comando time, puesto que no es obligación el agregarlo al ejecutar el ./archivo*

Luego de ejecutar, solo debemos esperar a que en nuestra terminal aparezca lo siguiente:
```
$ Grabación hecha con éxito
```
En ese momento, podemos abrir el archivo .csv que se nos creó.

***

## Fallas en la implementación
Tal como se puede apreciar, solo la parte secuencial y paralela (OpenMP) fueron hechas y subidas al repositorio.

Sin embargo, la parte paralela de OpenMP no está hecha de manera eficiente, puesto que los tiempos registrados para la parte secuencial fueron cercanos a los 4:00 minutos y la parte paralela sobrepasa los 10:00 minutos, a pesar de estar ejecutándose cada hilo. No sabemos que es lo que sucede exactamente, a pesar de plantear y replantear la implementación de este.

Hicimos borradores a papel, borradores en *paint*, fuimos probando línea por línea y, aún así, no logramos hacer correr eficientemente la parte paralela. Por lo mismo, se nos vino el tiempo encima, lo cual nos impidió hacer la parte MPI del código.

**INVITAMOS** a la persona que sea, que nos pueda *echar una mano* para entender como debía hacerse y/o qué es lo que no está bien implementado en nuestro código.

# Muchas gracias.