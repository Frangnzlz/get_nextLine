*This project has been created as part of the 42 curriculum by Frangnzlz.*

# get_next_line

## Descripción

**get_next_line** es un proyecto del Common Core de 42 School. Su objetivo es desarrollar una función capaz de leer un descriptor de archivo línea por línea, devolviendo una línea en cada llamada.

A diferencia de los métodos tradicionales de lectura, que pueden cargar un archivo completo en memoria, `get_next_line()` utiliza la función `read()` para leer datos en bloques. El contenido restante se almacena entre llamadas para que la siguiente ejecución pueda continuar exactamente donde terminó la anterior.

Este proyecto permite profundizar en conceptos fundamentales de la programación en C, como los descriptores de archivo, las variables estáticas, la gestión dinámica de memoria, la manipulación de cadenas y la gestión de buffers.

### Características

**Parte obligatoria:**

- Lee desde un descriptor de archivo.
- Devuelve una línea por cada llamada.
- Permite configurar el tamaño del buffer mediante `BUFFER_SIZE`.
- Conserva los datos pendientes entre llamadas utilizando una variable estática.
- Gestiona archivos que terminan o no con un salto de línea.
- Devuelve `NULL` cuando no quedan datos por leer o se produce un error.

**Parte bonus:**

- Permite leer desde varios descriptores de archivo simultáneamente.
- Mantiene un almacenamiento independiente para cada descriptor.
- Permite alternar entre diferentes descriptores sin perder los datos almacenados previamente.

## Algoritmo

El algoritmo utilizado en `get_next_line()` se basa en la lectura incremental y el almacenamiento persistente de datos mediante un buffer.

En lugar de leer todo el archivo de una sola vez, la función lee bloques de tamaño fijo y los almacena hasta encontrar una línea completa.

### 1. Almacenamiento persistente

Se utiliza una variable estática para conservar los datos entre diferentes llamadas a la función.

Esto es necesario porque cada llamada a `get_next_line()` debe recordar los datos que se han leído anteriormente, pero que todavía no se han devuelto.

En la implementación bonus, este almacenamiento se adapta para gestionar varios descriptores de archivo de forma independiente.

### 2. Lectura de datos

La función `read()` lee hasta `BUFFER_SIZE` bytes del descriptor de archivo recibido.

Los datos obtenidos se concatenan con el contenido almacenado anteriormente hasta que se cumple alguna de las siguientes condiciones:

- Se encuentra un carácter de salto de línea (`\n`).
- Se alcanza el final del archivo (EOF).
- Se produce un error durante la lectura.

### 3. Extracción de una línea

Cuando hay suficiente información almacenada, el algoritmo busca el primer carácter de salto de línea.

A continuación, extrae el contenido desde el principio del buffer hasta el carácter `\n`, incluyéndolo si está presente.

Si se alcanza el final del archivo y todavía queda contenido sin un salto de línea, ese contenido se devuelve como última línea.

### 4. Conservación de los datos restantes

Después de extraer una línea, el contenido devuelto se elimina del buffer almacenado.

Los caracteres restantes se conservan para la siguiente llamada a la función.

De esta manera, no se pierde información y las llamadas consecutivas continúan leyendo desde la posición correcta.

### 5. Final del archivo y gestión de errores

Cuando ya no quedan datos por leer, la función devuelve `NULL`.

Si se produce un error, la memoria reservada dinámicamente debe gestionarse correctamente para evitar fugas de memoria.

### Justificación del algoritmo

Este enfoque se ha seleccionado porque permite leer archivos de manera incremental sin necesidad de reservar memoria para almacenar todo su contenido.

Sus principales ventajas son:

- **Eficiencia de memoria:** únicamente se almacena la información necesaria en cada momento.
- **Flexibilidad:** permite trabajar con diferentes tamaños de buffer.
- **Persistencia:** las variables estáticas permiten conservar los datos pendientes entre llamadas.
- **Simplicidad:** separar la lectura, la extracción de líneas y la gestión del buffer facilita la comprensión y el mantenimiento del código.
- **Múltiples descriptores:** la implementación bonus amplía el mismo principio mediante buffers independientes para cada descriptor.

Por estos motivos, este algoritmo es adecuado para cumplir el objetivo del proyecto: implementar una lectura línea por línea y trabajar con conceptos fundamentales de gestión de memoria y operaciones de bajo nivel en C.

## Instructions

### Requisitos

Para compilar y utilizar el proyecto se necesita:

- Un compilador de C, como `cc` o `gcc`.
- La biblioteca estándar de C.
- Un entorno Unix o compatible.
- Un descriptor de archivo válido desde el que leer.

### Compilación

**Parte obligatoria**

Para compilar la implementación obligatoria:

```bash
cc -Wall -Wextra -Werror \
get_next_line.c get_next_line_utils.c \
main.c -o get_next_line
```

**Parte bonus**

Para compilar la implementación bonus:

```bash
cc -Wall -Wextra -Werror \
get_next_line_bonus.c get_next_line_utils_bonus.c \
main.c -o get_next_line
```

### Tamaño del buffer

El tamaño del buffer se puede configurar durante la compilación utilizando el parámetro `-D`.

Por ejemplo, para compilar con un buffer de 100 bytes:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=100 \
get_next_line.c get_next_line_utils.c \
main.c -o get_next_line
```

Si no se especifica ningún tamaño durante la compilación, se utilizará el valor predeterminado definido en el header.

### Ejecución

Una vez compilado el programa, se puede ejecutar mediante:

```bash
./get_next_line
```

El archivo `main.c` utilizado en los ejemplos es un archivo de pruebas que debe proporcionar el descriptor de archivo a `get_next_line()`.

### Ejemplo de uso

Incluye el header correspondiente:

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
    int     fd;
    char    *line;

    fd = open("test.txt", O_RDONLY);
    if (fd < 0)
        return (1);

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }

    close(fd);
    return (0);
}
```

Cada llamada a `get_next_line(fd)` devuelve la siguiente línea disponible.

La cadena devuelta se reserva dinámicamente, por lo que debe liberarse utilizando `free()` después de utilizarla.

## Estructura del proyecto

```text
get_nextLine/
│
├── get_next_line.c
├── get_next_line.h
├── get_next_line_utils.c
│
├── get_next_line_bonus.c
├── get_next_line_bonus.h
└── get_next_line_utils_bonus.c
```

| Archivo | Descripción |
|---|---|
| `get_next_line.c` | Implementación principal de la función. |
| `get_next_line.h` | Header de la parte obligatoria. |
| `get_next_line_utils.c` | Funciones auxiliares para manipular cadenas y buffers. |
| `get_next_line_bonus.c` | Implementación bonus con soporte para varios descriptores. |
| `get_next_line_bonus.h` | Header de la parte bonus. |
| `get_next_line_utils_bonus.c` | Funciones auxiliares de la implementación bonus. |

## Resources

### Documentación y referencias

Los siguientes recursos permiten comprender mejor los conceptos utilizados durante el desarrollo del proyecto:

- [read() - Linux Manual Page](https://man7.org/linux/man-pages/man2/read.2.html): documentación sobre la lectura de datos desde descriptores de archivo.
- [open() - Linux Manual Page](https://man7.org/linux/man-pages/man2/open.2.html): documentación sobre la apertura de archivos.
- [malloc() - Linux Manual Page](https://man7.org/linux/man-pages/man3/malloc.3.html): documentación sobre la reserva dinámica de memoria.
- [free() - Linux Manual Page](https://man7.org/linux/man-pages/man3/free.3.html): documentación sobre la liberación de memoria.
- [Static Variables in C](https://en.cppreference.com/w/c/language/static_storage_duration.html): explicación sobre las variables estáticas y su duración de almacenamiento.
- [42 School](https://42.fr/): información sobre el currículo de 42.

### Uso de inteligencia artificial (IA)

Se han utilizado herramientas de inteligencia artificial como recurso de apoyo durante el desarrollo y la documentación del proyecto.

Su utilización se ha centrado en las siguientes tareas:

- Comprender y revisar los requisitos del proyecto.
- Aclarar conceptos relacionados con los descriptores de archivo, las variables estáticas y la gestión de buffers.
- Ayudar a explicar y documentar el algoritmo utilizado.
- Organizar y mejorar la estructura y redacción del README.

La inteligencia artificial se ha utilizado como herramienta de aprendizaje y apoyo documental. La implementación y comprensión del proyecto son responsabilidad del autor.