#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "map.h"
#include "extra.h"

// Estructura para almacenar pares clave-valor
typedef struct Pair {
    void *key;
    void *value;
} Pair;

// Estructura para representar una canción
typedef struct {
    char id[50];
    char artistas[100];
    char nombre_album[100];
    char nombre_cancion[100];
    float tempo;
    char genero_cancion[50];
} Cancion;

// Listas globales para clasificar canciones por tempo
List *listaLentas;
List *listaModeradas;
List *listaRapidas;

// Función para eliminar comillas de una cadena
void eliminarComillas(char *ruta) {
    char *inicio = ruta;
    char *fin = ruta + strlen(ruta) - 1;

    if (*inicio == '"' && *fin == '"') {
        memmove(ruta, ruta + 1, strlen(ruta));
        ruta[strlen(ruta) - 1] = '\0';
    }
}

// Función para cargar canciones desde un archivo CSV
void cargarCanciones(Map *mapaGeneros, Map *mapaIDs, Map *mapaArtistas, const char *nombreArchivo) {
    FILE *archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL) {
        perror("Error al abrir el archivo");
        return;
    }

    char **campos;
    int contador = 0;
    const int LIMITE = 10000; // Límite de canciones a cargar por limitaciones de mi equipo

    // Leer encabezados del archivo CSV
    campos = leer_linea_csv(archivo, ',');

    // Leer cada línea del archivo CSV
    while ((campos = leer_linea_csv(archivo, ',')) != NULL) {
        if (contador >= LIMITE) {
            break;
        }

        // Crear una nueva canción y asignar sus valores
        Cancion *cancion = (Cancion *)malloc(sizeof(Cancion));
        if (!cancion) continue;

        strcpy(cancion->id, campos[0]);
        strcpy(cancion->artistas, campos[2]);
        strcpy(cancion->nombre_album, campos[3]);
        strcpy(cancion->nombre_cancion, campos[4]);
        cancion->tempo = atof(campos[18]);
        strcpy(cancion->genero_cancion, campos[20]);

        // Clasificar la canción según su tempo
        if (cancion->tempo < 80.0) {
            pushBack(listaLentas, cancion);
        } else if (cancion->tempo <= 120.0) {
            pushBack(listaModeradas, cancion);
        } else {
            pushBack(listaRapidas, cancion);
        }

        // Agregar la canción al mapa de géneros
        List *listaGenero = searchMap(mapaGeneros, cancion->genero_cancion);
        if (!listaGenero) {
            listaGenero = createList();
            insertMap(mapaGeneros, cancion->genero_cancion, listaGenero);
        }
        pushBack(listaGenero, cancion);

        // Agregar la canción al mapa de IDs
        insertMap(mapaIDs, cancion->id, cancion);

        // Agregar la canción al mapa de artistas
        List *listaArtista = searchMap(mapaArtistas, cancion->artistas);
        if (!listaArtista) {
            listaArtista = createList();
            insertMap(mapaArtistas, cancion->artistas, listaArtista);
        }
        pushBack(listaArtista, cancion);

        contador++;
    }

    fclose(archivo);
    printf("Canciones cargadas exitosamente.\n");
}

// Función para buscar canciones por género
void buscarPorGenero(Map *mapaGeneros, const char *genero) {
    List *listaGenero = searchMap(mapaGeneros, genero);
    if (!listaGenero) {
        printf("No se encontraron canciones para el genero '%s'.\n", genero);
        return;
    }
    Cancion *cancion = firstList(listaGenero);
    while (cancion) {
        printf("ID: %s | Artista: %s | Album: %s | Cancion: %s | Tempo: %.2f | Genero: %s\n",
               cancion->id, cancion->artistas, cancion->nombre_album, cancion->nombre_cancion, cancion->tempo, cancion->genero_cancion);
        cancion = nextList(listaGenero);
    }
}

// Función para buscar canciones por ID
void buscarPorID(Map *mapaIDs, const char *id) {
    Cancion *cancion = searchMap(mapaIDs, id);
    if (cancion) {
        printf("Cancion encontrada:\n");
        printf("ID: %s | Artista: %s | Album: %s | Cancion: %s | Tempo: %.2f | Genero: %s\n",
               cancion->id, cancion->artistas, cancion->nombre_album, cancion->nombre_cancion, cancion->tempo, cancion->genero_cancion);
    } else {
        printf("No se encontro ninguna cancion con el ID '%s'.\n", id);
    }
}

// Función para buscar canciones por artista
void buscarPorArtista(Map *mapaArtistas, const char *artista) {
    List *listaArtista = searchMap(mapaArtistas, artista);
    if (!listaArtista) {
        printf("No se encontraron canciones para el artista '%s'.\n", artista);
        return;
    }
    Cancion *cancion = firstList(listaArtista);
    while (cancion) {
        printf("ID: %s | Artista: %s | Album: %s | Cancion: %s | Tempo: %.2f | Genero: %s\n",
               cancion->id, cancion->artistas, cancion->nombre_album, cancion->nombre_cancion, cancion->tempo, cancion->genero_cancion);
        cancion = nextList(listaArtista);
    }
}

// Función para buscar canciones por categoría de tempo
void buscarPorTempo(const char *categoria) {
    List *listaTempo = NULL;

    // Determinar la lista correspondiente según la categoría
    if (strcmp(categoria, "lentas") == 0) {
        listaTempo = listaLentas;
    } else if (strcmp(categoria, "moderadas") == 0) {
        listaTempo = listaModeradas;
    } else if (strcmp(categoria, "rapidas") == 0) {
        listaTempo = listaRapidas;
    } else {
        printf("Categoria invalida. Las categorias validas son: lentas, moderadas, rapidas.\n");
        return;
    }

    // Imprimir las canciones de la lista seleccionada
    Cancion *cancion = firstList(listaTempo);
    printf("Canciones %s:\n", categoria);
    while (cancion) {
        printf("ID: %s | Artista: %s | Album: %s | Cancion: %s | Tempo: %.2f | Genero: %s\n",
               cancion->id, cancion->artistas, cancion->nombre_album, cancion->nombre_cancion, cancion->tempo, cancion->genero_cancion);
        cancion = nextList(listaTempo);
    }
}

// Función para liberar la memoria utilizada por las estructuras
void liberarMemoria(Map *mapaGeneros, Map *mapaIDs, Map *mapaArtistas) {
    Cancion *cancion;

    // Liberar memoria de las listas de tempo
    while ((cancion = firstList(listaLentas)) != NULL) {
        popFront(listaLentas);
        free(cancion);
    }
    free(listaLentas);

    while ((cancion = firstList(listaModeradas)) != NULL) {
        popFront(listaModeradas);
        free(cancion);
    }
    free(listaModeradas);

    while ((cancion = firstList(listaRapidas)) != NULL) {
        popFront(listaRapidas);
        free(cancion);
    }
    free(listaRapidas);

    // Liberar memoria de los mapas
    Pair *par;
    while ((par = firstMap(mapaGeneros)) != NULL) {
        List *listaGenero = par->value;
        free(listaGenero); 
        eraseMap(mapaGeneros, par->key);
    }
    free(mapaGeneros);

    while ((par = firstMap(mapaIDs)) != NULL) {
        free(par->value); 
        eraseMap(mapaIDs, par->key);
    }
    free(mapaIDs);

    while ((par = firstMap(mapaArtistas)) != NULL) {
        List *listaArtista = par->value;
        free(listaArtista); 
        eraseMap(mapaArtistas, par->key);
    }
    free(mapaArtistas);
}

// Función principal del programa
int main() {
    // Crear mapas para almacenar canciones por género, ID y artista
    Map *mapaGeneros = createMap(10000);
    Map *mapaIDs = createMap(10000);
    Map *mapaArtistas = createMap(10000);

    // Inicializar listas de tempo
    listaLentas = createList();
    listaModeradas = createList();
    listaRapidas = createList();

    int opcion;
    char input[200];

    // Menú principal
    do {
        limpiarPantalla();
        printf("\n--- Spotifind ---\n");
        printf("1. Cargar Canciones\n");
        printf("2. Buscar por ID\n");
        printf("3. Buscar por Genero\n");
        printf("4. Buscar por Artista\n");
        printf("5. Buscar por Tempo\n");
        printf("6. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                printf("Ingrese la ruta del archivo CSV: ");
                scanf(" %[^\n]", input);
                eliminarComillas(input);
                cargarCanciones(mapaGeneros, mapaIDs, mapaArtistas, input);
                break;
            case 2:
                printf("Ingrese el ID de la cancion a buscar: ");
                scanf("%s", input);
                buscarPorID(mapaIDs, input);
                break;
            case 3:
                printf("Ingrese el genero a buscar: ");
                scanf("%s", input);
                buscarPorGenero(mapaGeneros, input);
                break;
            case 4:
                printf("Ingrese el nombre del artista: ");
                scanf(" %[^\n]", input);
                buscarPorArtista(mapaArtistas, input);
                break;
            case 5:
                printf("Ingrese la categoria de tempo (lentas, moderadas, rapidas): ");
                scanf(" %[^\n]", input);
                buscarPorTempo(input);
                break;
            case 6:
                printf("Saliendo...\n");
                liberarMemoria(mapaGeneros, mapaIDs, mapaArtistas);
                break;
            default:
                printf("Opcion no valida.\n");
        }
        presioneTeclaParaContinuar();
    } while (opcion != 6);

    return 0;
}