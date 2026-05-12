#include <stdio.h>
#include "productos.h"

/* Compara dos cadenas sin usar strcmp (lógica propia) */
static int cadenas_iguales(char *a, char *b) {
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0') {
        if (a[i] != b[i]) return 0;
        i++;
    }
    return a[i] == '\0' && b[i] == '\0';
}

/* Copia cadena sin usar strcpy (lógica propia) */
static void copiar_cadena(char *dest, char *src) {
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

/* Ingresa un nuevo producto al final del arreglo */
void ingresar_producto(char nombres[][MAX_NOMBRE], int *cantidades,
                       int *tiempos, int *recursos, int *n) {
    if (*n >= MAX_PRODUCTOS) {
        printf("\n  [!] Limite alcanzado. No se pueden ingresar mas de %d productos.\n",
               MAX_PRODUCTOS);
        return;
    }

    printf("\n  Nombre del producto: ");
    scanf(" %49[^\n]", nombres[*n]);

    printf("  Cantidad demandada (unidades): ");
    scanf("%d", &cantidades[*n]);

    printf("  Tiempo de fabricacion por unidad (minutos): ");
    scanf("%d", &tiempos[*n]);

    printf("  Recursos requeridos por unidad: ");
    scanf("%d", &recursos[*n]);

    (*n)++;
    printf("\n  [OK] Producto ingresado correctamente.\n");
}

/* Calcula el tiempo total de fabricacion para cubrir la demanda */
int calcular_tiempo_total(int *cantidades, int *tiempos, int n) {
    int total = 0;
    int i;
    for (i = 0; i < n; i++) {
        total += cantidades[i] * tiempos[i];
    }
    return total;
}

/* Calcula el total de recursos necesarios para cubrir la demanda */
int calcular_recursos_total(int *cantidades, int *recursos, int n) {
    int total = 0;
    int i;
    for (i = 0; i < n; i++) {
        total += cantidades[i] * recursos[i];
    }
    return total;
}

/* Retorna 1 si la fabrica puede cumplir la demanda, 0 si no puede */
int verificar_factibilidad(int tiempo_total, int recursos_total,
                           int tiempo_max, int recursos_max) {
    return (tiempo_total <= tiempo_max && recursos_total <= recursos_max) ? 1 : 0;
}

/* Busqueda lineal propia: retorna indice del producto o -1 si no existe */
int buscar_producto(char nombres[][MAX_NOMBRE], int n, char *nombre_buscado) {
    int i;
    for (i = 0; i < n; i++) {
        if (cadenas_iguales(nombres[i], nombre_buscado)) {
            return i;
        }
    }
    return -1;
}

/* Edita los datos de un producto buscado por nombre */
void editar_producto(char nombres[][MAX_NOMBRE], int *cantidades,
                     int *tiempos, int *recursos, int n) {
    char nombre_buscado[MAX_NOMBRE];
    int idx;

    printf("\n  Nombre del producto a editar: ");
    scanf(" %49[^\n]", nombre_buscado);

    idx = buscar_producto(nombres, n, nombre_buscado);

    if (idx == -1) {
        printf("\n  [!] Producto \"%s\" no encontrado.\n", nombre_buscado);
        return;
    }

    printf("\n  Producto encontrado: %s\n", nombres[idx]);
    printf("  Nuevo nombre (actual: %s): ", nombres[idx]);
    scanf(" %49[^\n]", nombres[idx]);

    printf("  Nueva cantidad (actual: %d): ", cantidades[idx]);
    scanf("%d", &cantidades[idx]);

    printf("  Nuevo tiempo por unidad (actual: %d min): ", tiempos[idx]);
    scanf("%d", &tiempos[idx]);

    printf("  Nuevos recursos por unidad (actual: %d): ", recursos[idx]);
    scanf("%d", &recursos[idx]);

    printf("\n  [OK] Producto actualizado correctamente.\n");
}

/* Elimina un producto buscado por nombre y desplaza el arreglo */
void eliminar_producto(char nombres[][MAX_NOMBRE], int *cantidades,
                       int *tiempos, int *recursos, int *n) {
    char nombre_buscado[MAX_NOMBRE];
    int idx, i;

    printf("\n  Nombre del producto a eliminar: ");
    scanf(" %49[^\n]", nombre_buscado);

    idx = buscar_producto(nombres, *n, nombre_buscado);

    if (idx == -1) {
        printf("\n  [!] Producto \"%s\" no encontrado.\n", nombre_buscado);
        return;
    }

    /* Desplazar elementos hacia la izquierda para cubrir el hueco */
    for (i = idx; i < (*n) - 1; i++) {
        copiar_cadena(nombres[i], nombres[i + 1]);
        cantidades[i] = cantidades[i + 1];
        tiempos[i]    = tiempos[i + 1];
        recursos[i]   = recursos[i + 1];
    }

    (*n)--;
    printf("\n  [OK] Producto \"%s\" eliminado correctamente.\n", nombre_buscado);
}

/* Muestra todos los productos registrados en formato de tabla */
void mostrar_productos(char nombres[][MAX_NOMBRE], int *cantidades,
                       int *tiempos, int *recursos, int n) {
    int i;
    if (n == 0) {
        printf("\n  [!] No hay productos registrados.\n");
        return;
    }
    printf("\n  %-25s %10s %10s %10s\n", "Nombre", "Cantidad", "Tiempo(m)", "Recursos");
    printf("  %-25s %10s %10s %10s\n",
           "-------------------------", "--------", "---------", "--------");
    for (i = 0; i < n; i++) {
        printf("  %-25s %10d %10d %10d\n",
               nombres[i], cantidades[i], tiempos[i], recursos[i]);
    }
    printf("\n");
}
