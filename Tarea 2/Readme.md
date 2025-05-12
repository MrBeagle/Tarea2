# Spotifind - Gestión de Canciones 

Este proyecto implementa una aplicación en C para gestionar canciones desde un archivo CSV. Permite buscar canciones por ID, género, artista o categoría de tempo, y organiza las canciones en estructuras de datos eficientes.

---

##  Cómo compilar y ejecutar la tarea

### Requisitos
- Un compilador de C (como `gcc`).
- Sistema operativo **Windows** (se utiliza `system("cls")` para limpiar la pantalla).
- Archivo CSV con datos de canciones.

### Pasos para compilar
1. Asegúrate de que todos los archivos del proyecto (`main.c`, `Map.c`, `List.c`, `Extra.c`, y sus respectivos headers) estén en el mismo directorio.
2. Abre una terminal en el directorio del proyecto.
3. Ejecuta el siguiente comando para compilar el programa:

   ```bash
   gcc -o spotifind main.c Map.c List.c Extra.c
   ```

4. Ejecuta el programa compilado con:

   ```bash
   ./spotifind
   ```

---

##  Opciones que funcionan correctamente y posibles problemas

### Opciones funcionales
- **Cargar Canciones (Opción 1):**
  - Permite cargar canciones desde un archivo CSV.
  - Asegúrate de que el archivo CSV tenga el formato correcto y que las columnas necesarias estén presentes.
  - Limita la carga a 10,000 canciones por restricciones de memoria.

- **Buscar por ID (Opción 2):**
  - Busca una canción específica por su ID.
  - Funciona correctamente si el ID existe en el archivo cargado.

- **Buscar por Género (Opción 3):**
  - Lista todas las canciones de un género específico.
  - Funciona correctamente si el género existe en el archivo cargado.

- **Buscar por Artista (Opción 4):**
  - Lista todas las canciones de un artista específico.
  - Funciona correctamente si el artista existe en el archivo cargado.

- **Buscar por Tempo (Opción 5):**
  - Lista canciones clasificadas como "lentas", "moderadas" o "rápidas".
  - Funciona correctamente si las canciones están clasificadas por tempo.

### Problemas conocidos
- **Error al cargar canciones:**
  - Si el archivo CSV tiene un formato incorrecto (por ejemplo, columnas faltantes o delimitadores diferentes), la carga puede fallar.
  - **Solución:** Asegúrate de que el archivo CSV tenga el formato esperado.

- **Errores de memoria:**
  - Si el archivo CSV contiene demasiadas canciones, el programa puede quedarse sin memoria.
  - **Solución:** Reduce el tamaño del archivo CSV o ajusta el límite de canciones en el código (`LIMITE`).

- **Limpieza de pantalla:**
  - La función `limpiarPantalla()` utiliza `system("cls")`, que solo funciona en Windows.
  - **Solución:** En sistemas no Windows, reemplaza `system("cls")` con una alternativa adecuada.

---

##  Ejemplo de interacción con la aplicación

### Archivo CSV de ejemplo (`canciones.csv`):
```
ID,Artista,Álbum,Canción,Tempo,Género
1,Artista1,Álbum1,Canción1,75.0,Pop
2,Artista2,Álbum2,Canción2,100.0,Rock
3,Artista3,Álbum3,Canción3,130.0,Electrónica
```

### Ejecución del programa

#### Menú principal:
```
--- Spotifind ---
1. Cargar Canciones
2. Buscar por ID
3. Buscar por Genero
4. Buscar por Artista
5. Buscar por Tempo
6. Salir
Seleccione una opcion:
```

#### Cargar canciones (Opción 1):
```
Ingrese la ruta del archivo CSV: "canciones.csv"
Canciones cargadas exitosamente.
```

#### Buscar por ID (Opción 2):
```
Ingrese el ID de la cancion a buscar: 1
Cancion encontrada:
ID: 1 | Artista: Artista1 | Album: Álbum1 | Cancion: Canción1 | Tempo: 75.00 | Genero: Pop
```

#### Buscar por género (Opción 3):
```
Ingrese el genero a buscar: Pop
ID: 1 | Artista: Artista1 | Album: Álbum1 | Cancion: Canción1 | Tempo: 75.00 | Genero: Pop
```

#### Salir (Opción 6):
```
Saliendo...
```
