# BUSCADOR DE PELÍCULAS

### DESCRIPCIÓN

Este sistema permite buscar películas dentro de una base de datos proveniente de archivos csv. Varias acciones pueden ser hechas por el usuario dentro del sistema, como cargar el archivo, buscar por ID, ver las películas por género, década, director y por otras variables. Esta herramienta tiene por objetivo poder visualizar de una manera más efectiva ciertos datos de las películas en bases de datos.

### COMO USAR

Para poder usar el sistema, usted debe hacer uso del Fork & Run a su derecha en la pantalla. Tras hacer eso, debe hacer uso del siguiente comando para poder hacer uso del buscador de películas.

````
./main
````

Trate de no tocar nada del código en main.c, ya que este puede hacer que el programa deje de funcionar como es debido.

## FUNCIONALIDADES

### FUNCIONA CORRECTAMENTE:

- Cargar las películas desde archivos csv.
- Buscar películas por su ID.
- Buscar películas por director, género o década.
- Buscar por década y género.

### PROBLEMAS CONOCIDOS:

- La opción para buscar por rango de calificaciones no se encuentra actualmente disponible, por lo que no podrá ser usado.
- Al buscar por década y género, al introducir el género en minúsculas o mayúsculas no afectará la búsqueda de películas. Sin embargo, esta comodidad **NO ESTÁ** implementada para la búsqueda de directores o géneros.
- Si introduce letras dentro de los campos en los cuales se pide año o década, el programa estará forzado a sacarlo del sistema.

## EJEMPLO DE USO

Para empezar, debemos a registrar a nuestro paciente:

````
REGISTRACIÓN DE PACIENTE

Ingrese nombre del paciente: Eduardo Cordero

Ingrese edad del paciente: 19

Ingrese síntoma del paciente: Fiebre
````

Esto deja a nuestro paciente, Eduardo, ingresado al sistema como paciente de prioridad baja. Si llegase el caso de que al ser revisado, el doctor requiera que el paciente sea movido de prioridad, uno puede hacer uso de la asignación de prioridad:

````
REASIGNACIÓN DE PRIORIDAD

Ingrese nombre del paciente: Eduardo Cordero

Ingrese antigua prioridad del paciente: BAJA

Ingrese nueva prioridad (1/2/3): 2
````

Debido a que la fiebre de Eduardo no paraba, el doctor decidió subirlo a prioridad media. Ahora Eduardo no tendrá que esperar mucho tiempo, pero el hospital tiene varios pacientes antes que nuestro personaje. La lista se puede ver mediante la impresión de la lista de espera:

````
Pacientes en espera:

PRIORIDAD ALTA (1):

No hay pacientes en espera.

PRIORIDAD MEDIA (2):

Nombre: Julia Torres
Edad: 42
Sintoma: Dolor estomacal
Hora de Ingreso: 15:59 

Nombre: Pablo Ibarra
Edad: 7
Síntoma: Falta de energía
Hora de Ingreso: 16:10

Nombre: Eduardo Cordero
Edad: 19
Síntoma: Fiebre
Hora de Ingreso: 16:42 

PRIORIDAD BAJA:

Nombre: Javiera Cortés
Edad: 16
Síntoma: Tos
Hora de Ingreso: 15:47

````

Para poder avanzar con los pacientes, el doctor llama a Julia Torres para que sea atendida:

````
ATENDIENDO AL PACIENTE

Nombre: Julia Torres
Edad: 42
Síntoma: Dolor estomacal
Hora de Ingreso: 15:59

El paciente ha sido atendido.

````

Ya con Julia atendida, si queremos ver la lista de espera de prioridad media, podemos hacer uso de la interfaz para exclusivamente esta lista:

````
LISTA POR PRIORIDAD

Elija la prioridad a mostrar (1/2/3): 2

PRIORIDAD MEDIA (2):

Nombre: Pablo Ibarra
Edad: 7
Síntoma: Falta de energía
Hora de Ingreso: 16:10

Nombre: Eduardo Cordero
Edad: 19
Síntoma: Fiebre
Hora de Ingreso: 16:42 

````

Para salir del sistema, haga uso de la última opción y estará fuera de la aplicación:

````
Saliendo del sistema de gestión hospitalaria...
Presione una tecla para continuar...
````

---

En caso de que haya problemas con el código, usted puede contactar al desarrollador de la aplicación mediante GitHub. Solamente haga uso de este código en el shell y contacte al desarrollador con todos los detalles posibles:

````
gcc tdas/*.c main.c -Wno-unused-result -o main
````