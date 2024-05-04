#include "tdas/list.h"
#include "tdas/map.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_LINE_LENGTH 1024
#define MAX_FIELDS 100

typedef struct {

  char id[100];
  char title[100];
  List* genres;
  List* director;
  float rating;
  int year;

} Film; // Struct para los datos de los films

typedef struct { 

Map *peliID;
Map *peliDecade;
Map *peliGenre;
Map *peliDirector;

} typeListFilm; // Struct para la lista de los films

char **leer_linea_csv(FILE *archivo, char separador) { // Funcion para leer una linea del archivo csv

  static char linea[MAX_LINE_LENGTH];
  static char *campos[MAX_FIELDS];
  char *ptr, *start;
  int idx = 0;

  if (fgets(linea, MAX_LINE_LENGTH, archivo) == NULL) {
    return NULL; // No hay más líneas para leer
  }

  ptr = start = linea;
  while (*ptr) {
    if (idx >= MAX_FIELDS - 1)
      break;

    if (*ptr == '\"') { // Inicio de un campo entrecomillado
      start = ++ptr;    // Saltar la comilla inicial
      while (*ptr && !(*ptr == '\"' && *(ptr + 1) == separador))
        ptr++;
    } else { // Campo sin comillas
      start = ptr;
      while (*ptr && *ptr != separador)
        ptr++;
    }

    if (*ptr) {
      *ptr = '\0'; // Reemplazar comilla final o separador por terminación
      ptr++;
      if (*ptr == separador)
        ptr++;
    }

    // Quitar comilla final si existe
    if (*(ptr - 2) == '\"') {
      *(ptr - 2) = '\0';
    }

    campos[idx++] = start;
  }

  campos[idx] = NULL; // Marcar el final del array
  return campos;

}

int is_equal_str(void *key1, void *key2) { // Funcion para comparar dos strings
  
    return strcasecmp((char *) key1, (char *) key2) == 0;
  
}

int is_equal_int(void *key1, void *key2) { return *(int *)key1 == *(int *)key2; } // Funcion para comparar dos enteros

void limpiarPantalla() { system("clear"); } 

void presioneTeclaParaContinuar() { 

  puts("\nPresione Enter para continuar...");
  getchar(); 
  getchar(); 

}

void mostrarMenuPrincipal() {

  limpiarPantalla();
  puts("========================================");
  puts("     Base de Datos de Películas");
  puts("========================================\n");

  puts("1) Cargar Películas");
  puts("2) Buscar por id");
  puts("3) Buscar por director");
  puts("4) Buscar por género");
  puts("5) Buscar por década");
  puts("6) Buscar por rango de calificaciones");
  puts("7) Buscar por década y género");
  puts("8) Salir\n");

}

void fillGenreList(List *entryList, const char *entry) { // Función para crear lista de géneros

  char *entryCopy = strdup(entry); // Crear una copia de la entrada

  if (entryCopy == NULL) { // Si no se pudo crear la copia, mostrar un mensaje de error y salir
    
    perror("Memory allocation failed");
    return;
    
  }

  char *tempW = strtok(entryCopy, ", "); // Separar la entrada por comas y espacios

  while (tempW != NULL ) { // Recorrer la lista de géneros

    list_pushBack(entryList, strdup(tempW)); // Se agrega hace una copia de tempW y se agrega a la lista.
    tempW = strtok(NULL, ", "); // Obtener el siguiente género.
    
  } 
  
  free(entryCopy); // Liberar la memoria de la copia
  
}

void fillDirectorList(List *directorList, const char *entry) { // Función para crear lista de directores

  char *entryCopy = strdup(entry); // Crear una copia de la entrada
  
  if (entryCopy == NULL) { // Si no se pudo crear la copia, mostrar un mensaje de error y salir
    perror("Memory allocation failed");
    return;
  }

  char *tempDirector = strtok(entryCopy, ","); // Separar la entrada por comas
  
  while (tempDirector != NULL) { // Recorrer la lista de directores
      
    char *cleanedDirector = strdup(tempDirector); // Crear una nueva copia del director
        
    while (isspace(*cleanedDirector)) { // Eliminar espacios en blanco al inicio de la copia del director
        
      cleanedDirector++; // Avanzar al siguiente carácter
        
    }
      
    char *end = cleanedDirector + strlen(cleanedDirector) - 1; // Se obtiene el último cáracter de la copia del director
      
    while (end > cleanedDirector && isspace(*end)) { // Eliminar espacios en blanco al final de la copia del director
        
      *end-- = '\0'; // Eliminar el carácter
        
    }
      
    list_pushBack(directorList, cleanedDirector); // Agregar la copia limpia del director a la lista
    tempDirector = strtok(NULL, ","); // Obtener el siguiente director
      
  }
  
  free(entryCopy); // Liberar la memoria de la copia
  
}

void searchValue(Map *map, const char *value, Film *film) { // Función para buscar un valor en un mapa

  MapPair *pair = map_search(map, (void *) value); // Buscar el valor en el mapa

  if (pair != NULL) { // Si se encontró el valor

    List *attachedList = (List *) pair->value; // Obtener la lista asociada al valor

    if (attachedList != NULL) 
      list_pushBack(attachedList, film); // Agregar el puntero a la estructura Film a la lista asociada al valor

  } else { // Si no se encontró el valor

    List *newList = list_create(); // Crear una nueva lista
    list_pushBack(newList, film); // Agregar el puntero a la estructura Film a la lista
    map_insert(map, (void *) strdup(value), newList); // Insertar el valor y la lista en el mapa

  }
}

void processDirectorsAndGenre(Map *entryMapA, Map *entryMapB, Film *entryFilm) { // Función para procesar los directores y géneros

  void *aux = list_first(entryFilm->genres); // Obtener el primer género de la lista de géneros del película

  while (aux != NULL) { // Recorrer la lista de géneros

    searchValue(entryMapA, aux, entryFilm); // Buscar el género en el mapa de géneros
    aux = list_next(entryFilm->genres); // Obtener el siguiente género de la lista de géneros

  }

  
  void *temp = list_first(entryFilm->director); // Obtener el primer director de la lista de directores del película

  while (temp != NULL) { // Recorrer la lista de directores

    searchValue(entryMapB, temp, entryFilm); // Buscar el director en el mapa de directores
    temp = list_next(entryFilm->director); // Obtener el siguiente director de la lista de directores

  }
}

void processDecades(Map *decadeMap, Film *entryFilm) { // Función para procesar las décadas

  int decade = (entryFilm->year / 10) * 10; // Obtener la década del año de la película

  int *decadeKey = malloc(sizeof(int)); // Asignar memoria para la clave de la década
  *decadeKey = decade; // Asignar la clave de la década

  MapPair *tempPair = map_search(decadeMap, decadeKey); // Buscar la clave de la década en el mapa de décadas

  if (tempPair != NULL) { // Si se encontró la clave de la década

    List *decadeList = (List *) tempPair->value; // Obtener la lista asociada a la clave de la década
    list_pushBack(decadeList, entryFilm); // Agregar el puntero a la estructura Film a la lista asociada a la clave de la

  } else { // Si no se encontró la clave de la década

    List *newDecadeList = list_create(); // Crear una nueva lista
    list_pushBack(newDecadeList, entryFilm); // Agregar el puntero a la estructura Film a la lista
    map_insert(decadeMap, decadeKey, newDecadeList); // Insertar la clave de la década y la lista en el mapa de décadas

  }
}

void massInsertion(typeListFilm *data, Film *film) { // Función para insertar los datos de los films en los mapas

  map_insert(data->peliID, film->id, film); // Insertar el id del film en el mapa de ids
  processDirectorsAndGenre(data->peliGenre, data->peliDirector, film); // Procesar los directores y géneros del film
  processDecades(data->peliDecade, film); // Procesar año del film para ser agregados a sus respectivas décadas

}

void cargarPeliculas(typeListFilm *data) { // Función para cargar los datos de los films desde el archivo csv

  FILE *archivo = fopen("data/Top1500.csv", "r"); // Abrir el archivo csv en modo lectura
  if (archivo == NULL) { // Si no se pudo abrir el archivo, mostrar un mensaje de error y salir

    perror("Error al abrir el archivo");
    return;
    
  }

  char **campos; // Declarar un puntero a un array de punteros a caracteres
  campos = leer_linea_csv(archivo, ','); // Leer la primera línea del archivo csv y almacenar los campos en el array de

  while ((campos = leer_linea_csv(archivo, ',')) != NULL) { 

    Film *peli = (Film *) malloc(sizeof(Film)); // Asignar memoria para una estructura Film

    strcpy(peli->id, campos[1]); // Se transfiere el ID de la película al struct.
    strcpy(peli->title, campos[5]); // Se transfiere el título de la película al struct.

    peli->genres = list_create(); // Crear una lista para los géneros del film 
    peli->director = list_create(); // Crear una lista para los directores del film

    peli->year = atoi(campos[10]); // Se convierte el año string a año entero para ser almacenado en el struct.
    peli->rating = atof(campos[8]); // Se convierte el rating string a float rating para ser almacenado en el struct.

    fillGenreList(peli->genres, campos[11]); // Se pobla la lista de géneros del film
    fillDirectorList(peli->director, campos[14]); // Se pobla la lista de directores del film
    massInsertion(data, peli); // Insertar los datos del film en los mapas correspondientes

  }

  fclose(archivo); // Cerrar el archivo csv

  MapPair *pair = map_first(data->peliID); 

  while (pair != NULL) { 

    Film *peli = pair->value; // Obtener el puntero a la estructura Film asociada al id del film
    
    printf("ID: %s, Título: %s, Año: %d\n", peli->id, peli->title, peli->year); 
    pair = map_next(data->peliID); // Obtener el siguiente par del mapa de ids
    
  }
  printf("\nPelículas cargadas exitosamente.\n");
}

void buscarPorID(Map *peliID) { // Función para buscar un film por su id

  char id[10]; // Declarar un array de caracteres para almacenar el id ingresado por el usuario

  printf("Ingrese el id de la película: "); 
  scanf("%s", id); // Leer el id ingresado por el usuario

  MapPair *pair = map_search(peliID, id); // Buscar el id en el mapa de ids

  if (pair != NULL) { // Si se encontró el id

    Film *peli = pair->value; // Obtener el puntero a la estructura Film asociada al id del film
    
    void *aux = list_first(peli->genres); // Obtener el primer género de la lista de géneros del film
    void *temp = list_first(peli->director); // Obtener el primer director de la lista de directores del film

    printf("\nTítulo: %s\n", peli->title); 
    printf("\nGénero(s):\n\n"); 

    while (aux != NULL) { // Recorrer la lista de géneros del film

      printf("- %s\n", (char *) aux); // Mostrar cada género de la lista de géneros del film
      aux = list_next(peli->genres); // Obtener el siguiente género de la lista de géneros del film

    }

    printf("\nDirector(es):\n"); 

    while (temp != NULL) { // Recorrer la lista de directores del film

      printf("- %s\n", (char *) temp); // Mostrar cada director de la lista de directores del film
      temp = list_next(peli->director); // Obtener el siguiente director de la lista de directores del film

    }

    printf("\nRating: %.1f\n", peli->rating); 
    printf("\nAño: %d\n", peli->year); 

  } else
    printf("La película con id %s no existe\n", id); // Mostrar un mensaje de error si no se encontró el id
}

void buscarPorDirector(Map *peliDirector) { // Función para buscar un film por su director
  
  char directorInput[100]; // Declarar un string para almacenar el nombre del director ingresado por el usuario

  printf("Ingrese el nombre del director: "); 
  scanf(" %99[^\n]", directorInput); // Leer el nombre del director ingresado por el usuario

  char cleanedDirector[100]; // Declarar un string para almacenar el nombre del director sin cáracteres extra
  strcpy(cleanedDirector, directorInput); // Se copia el nombre ingresado en el nuevo string
  
  while (isspace(cleanedDirector[0])) // Eliminar espacios en blanco al principio del string 
    memmove(cleanedDirector, cleanedDirector + 1, strlen(cleanedDirector)); // Mover cáracteres un index más adelante
  
  for (size_t i = strlen(cleanedDirector); isspace(cleanedDirector[i - 1]); --i) 
    cleanedDirector[i - 1] = '\0'; // Eliminar espacios en blanco al final del string limpio
  
  MapPair *directorPair = map_search(peliDirector, (void *) cleanedDirector); // Búsqueda del director en el mapa

  if (directorPair != NULL) { // Si se encontró el nombre del director
      
    List *movies = (List *) directorPair->value; // Obtener la lista de películas asociada al nombre del director
    void *aux = list_first(movies);
    
    printf("\nPelículas del director %s:\n\n", cleanedDirector);

    while (aux != NULL) { 
              
      Film *peli = (Film *) aux; // Se hace casting para conseguir el puntero a la estructura Film
              
      printf("- %s\n", peli->title); 
      aux = list_next(movies); // Se obtiene el siguiente elemento de la lista
              
    }
  } else 
      printf("No se encontró al director %s\n.", cleanedDirector); // Mensaje de error
}

void buscarPorGenero(Map *peliGenre) { // Función para buscar un film por su género

  char genre[100]; // Declarar un string para almacenar el género ingresado por el usuario

  printf("Ingrese el género de la película: "); 
  scanf("%s", genre); // Leer el género ingresado por el usuario

  MapPair *genrePair = map_search(peliGenre, genre); // Buscar el género en el mapa de géneros

  if (genrePair != NULL) { // Si se encontró el género

    List *movies = (List *) genrePair->value; // Obtener la lista de películas asociada al género
    void *aux = list_first(movies); // Obtener el primer elemento de la lista de películas

    printf("\nPelículas del género '%s':\n\n", genre); 

    while (aux != NULL) { // Se recorre la lista

      Film *peli = (Film *) aux; // Se hace casting para conseguir el puntero a la estructura Film

      printf("- %s\n", peli->title); 
      aux = list_next(movies); // Se obtiene el siguiente elemento de la lista

    }
  } else
    printf("El género '%s' no se encuentra en la base de datos\n", genre);
}

void buscarPorDecada(Map *peliDecade) { // Función para buscar un film por su década

  int tempDecade; // Declarar una variable para almacenar la década ingresada por el usuario

  printf("Ingrese la década de la película en fórmato completo (Ej: 1980): "); 
  scanf("%i", &tempDecade); // Leer la década ingresada por el usuario

  MapPair *decadePair = map_search(peliDecade, (void *) &tempDecade); // Buscar la década en el mapa de décadas

  if (decadePair != NULL) { // Si se encontró la década

    List *movies = (List *) decadePair->value; // Obtener la lista de películas asociada a la década
    void *aux = list_first(movies); // Obtener el primer elemento de la lista de películas

    printf("\nPelículas de la década de %i:\n\n", tempDecade); 

    while (aux != NULL) { // Se recorre la lista

      Film *peli = (Film *) aux; // Se hace casting para conseguir el puntero a la estructura Film

      printf("- %s\n", peli->title); 
      aux = list_next(movies); // Se obtiene el siguiente elemento de la lista

    }
  } else
    printf("La década %i no se encuentra en la base de datos\n", tempDecade);
}

void buscarPorDecadaGenero(Map *peliGenre) { // Función para buscar un film por su género y década

  char genre[100]; // Declarar un string para almacenar el género ingresado por el usuario
  int tempDecade; // Declarar una variable para almacenar la década ingresada por el usuario

  printf("Ingrese el género de la película: ");
  scanf("%s", genre); 

  MapPair *genrePair = map_search(peliGenre, genre); // Buscar el género en el mapa de géneros

  if (genrePair != NULL) { 

    List *movies = (List *) genrePair->value; // Obtener la lista de películas asociada al género

    printf("Ingrese la década de la película: "); 
    scanf("%i", &tempDecade);
    
    void *aux = list_first(movies); // Obtener el primer elemento de la lista de películas
    bool flag = true; // Variable para mostrar mensaje especial si es que no se imprime nada

    printf("\nPelículas del género '%s' de la década %i:\n\n", genre, tempDecade); 

    while (aux != NULL) { // Se recorre la lista

      Film *peli = (Film *) aux; 

      if (peli->year >= tempDecade && peli->year < tempDecade + 10) {
        printf("- %s\n", peli->title); // Se muestra el título de la película
        flag = false; // Se encontró una película, por lo que no se debe hacer uso del mensaje especial  
      }
      aux = list_next(movies); // Se obtiene el siguiente elemento de la lista
    }

    if (flag) { // Si no se printeo ninguna película, se muestra un mensaje especial
      printf("La lista de '%s' de la década %i\n se encuentra vacía.", genre, tempDecade);
      return;
    }
  } else 
    printf("El género '%s' no se encuentra en la base de datos\n", genre);
}

int main() { 

  char opcion; // Declarar una variable para almacenar la opción elegida por el usuario
  typeListFilm storage; // Declarar una estructura para almacenar los datos de los films

  storage.peliID = map_create(is_equal_str); // Crear el mapa de ids
  storage.peliDecade = map_create(is_equal_int); // Crear el mapa de décadas
  storage.peliGenre = map_create(is_equal_str); // Crear el mapa de géneros
  storage.peliDirector = map_create(is_equal_str); // Crear el mapa de directores

  do {
    
    mostrarMenuPrincipal(); // Mostrar el menú principal
    printf("Ingrese su opción: "); // Pedir al usuario que ingrese una opción
    scanf(" %c", &opcion); // Leer la opción ingresada por el usuario

    switch (opcion) { // Seleccionar la opción elegida por el usuario
      
    case '1':
      cargarPeliculas(&storage); // Cargar las películas desde el archivo csv
      break;
    case '2':
      buscarPorID(storage.peliID); // Buscar un film por su id
      break;
    case '3':
      buscarPorDirector(storage.peliDirector); // Buscar un film por su director
      break;
    case '4':
      buscarPorGenero(storage.peliGenre); // Buscar un film por su género
      break;
    case '5': 
      buscarPorDecada(storage.peliDecade); // Buscar un film por su década
      break;
    case '6':
      printf("Esta opción no se encuentra disponible en la versión actual del sistema. Por favor, intente nuevamente más tarde.\n"); // 
      break;
    case '7':
      buscarPorDecadaGenero(storage.peliGenre); // Buscar un film por su género y década
      break;
    case '8':
      printf("Saliendo del sistema...\n"); // Salir del sistema
      break;
    default:
      printf("Opción inválida, porfavor inserte una nueva opción nuevamente"); // Mostrar un mensaje de error si la opción ingresada no es válida
      break;
    }
    presioneTeclaParaContinuar();

  } while (opcion != '8'); // Repetir el menú principal hasta que el usuario elija la opción de salir

  free(storage.peliID); // Liberar la memoria del mapa de ids
  free(storage.peliDecade); // Liberar la memoria del mapa de décadas
  free(storage.peliGenre); // Liberar la memoria del mapa de géneros
  free(storage.peliDirector); // Liberar la memoria del mapa de directores

}