# BUSCADOR DE PELÍCULAS

### DESCRIPCIÓN

Este sistema permite buscar películas dentro de una base de datos proveniente de archivos csv. Varias acciones pueden ser hechas por el usuario dentro del sistema, como cargar el archivo, buscar por ID, ver las películas por género, década, director y por otras variables. Esta herramienta tiene por objetivo poder visualizar de una manera más efectiva ciertos datos de las películas en bases de datos.

### COMO USAR

Para poder usar el sistema, usted debe hacer uso del Fork & Run a su derecha en la pantalla. Tras hacer eso, debe hacer uso del siguiente comando para poder hacer uso del buscador de películas.

````
./tarea2
````

Trate de no tocar nada del código en tarea2.c, ya que este puede hacer que el programa deje de funcionar como es debido.


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
- Al pedirle los IDs de ciertas películas, si introduce cáracteres especiales podría forzar un error lo cual llevaría a un salida forzada del sistema.

## EJEMPLO DE USO

Para empezar, debemos acargar las películas mediante la primera opción:

````
...
ID: tt0119567, Título: The Lost World: Jurassic Park, Año: 1997
ID: tt0093773, Título: Predator, Año: 1987
ID: tt0356150, Título: EuroTrip, Año: 2004
ID: tt0018756, Título: Champagne, Año: 1928
ID: tt0143145, Título: The World Is Not Enough, Año: 1999
ID: tt0040982, Título: You Gotta Stay Happy, Año: 1948

Películas cargadas exitosamente.

Presione Enter para continuar...
````

Ya con las películas cargadas, podemos tomar una de las varias vehículas mediante su ID para ver toda su información con la segunda opción del menu:

````
Ingrese su opción: 2
Ingrese el id de la película: tt0119567

Título: The Lost World: Jurassic Park

Género(s):

- Action
- Adventure
- Sci-Fi

Director(es):
- Steven Spielberg

Rating: 6.5

Año: 1997

Presione Enter para continuar...
````

Sabemos que el director de esta película es Steven Spielberg, por lo que si queremos conocer más películas dirigidas por él, podemos usar la tercera opción:

````
Ingrese su opción: 3
Ingrese el nombre del director: Steven Spielberg

Películas del director Steven Spielberg:

- Schindler's List
- Saving Private Ryan
- Raiders of the Lost Ark
- Jaws
- E.T. the Extra-Terrestrial
- Jurassic Park
- Close Encounters of the Third Kind
- Catch Me If You Can
- Lincoln
- Minority Report
- Indiana Jones and the Last Crusade
- The Sugarland Express
- The Color Purple
- Munich
- The Terminal
- Hook
- Amistad
- The Lost World: Jurassic Park

Presione Enter para continuar...

````

Uno de los géneros de Lost World: Jurassic Park es Sci-Fi, así que busquemos más películas del mismo género:

````
Ingrese su opción: 4
Ingrese el género de la película: Sci-Fi

Películas del género 'Sci-Fi':

- Star Wars: Episode V - The Empire Strikes Back
- Star Wars
- A Clockwork Orange
- 2001: A Space Odyssey
- Blade Runner
- E.T. the Extra-Terrestrial
- Inception
- Jurassic Park

(...)

- Star Wars: Episode I - The Phantom Menace
- Mystery Men
- Vanilla Sky
- Bill & Ted's Excellent Adventure
- V for Vendetta
- The Absent Minded Professor
- A Scanner Darkly
- Dude, Where's My Car?
- Sphere
- The Day After Tomorrow
- Weird Science
- Spaceballs
- The Lost World: Jurassic Park
- Predator

Presione Enter para continuar...
````

Hay varias películas dentro del género SciFi, muchas para contar fácilmente. Si buscar por género no es lo tuyo, podemos buscar películas por década:

````
Ingrese su opción: 5
Ingrese la década de la película en fórmato completo (Ej: 1980): 1910

Películas de la década de 1910:

- The Birth of a Nation

Presione Enter para continuar...
````

Por último, si queremos ser aún más específicos con la lista de películas, podemos filtrar por género y década:

````
Ingrese su opción: 7
Ingrese el género de la película: Comedy
Ingrese la década de la película: 2010

Películas del género 'Comedy' de la década 2010:

- Midnight in Paris
- The Descendants
- The Artist
- Toy Story 3
- Beginners
- Another Year
- Crazy, Stupid, Love.
- Silver Linings Playbook
- Moonrise Kingdom
- Love & Other Drugs
- Bridesmaids
- Due Date
- Get Him to the Greek
- The Best Exotic Marigold Hotel
- Cyrus
- Hesher

Presione Enter para continuar...
````

Para salir del sistema, haga uso de la última opción y estará fuera de la aplicación:

````
Ingrese su opción: 8
Saliendo del sistema...

Presione Enter para continuar..
````

---

En caso de que haya problemas con el código, usted puede contactar al desarrollador de la aplicación mediante GitHub. Solamente haga uso de este código en el shell y contacte al desarrollador con todos los detalles posibles:

````
gcc tdas/*.c tarea2.c -Wno-unused-result -o tarea2
````