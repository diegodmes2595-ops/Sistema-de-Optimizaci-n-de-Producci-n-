#ifndef PRODUCTOS_H
#define PRODUCTOS_H

#define MAX_PRODUCTOS 5
#define MAX_NOMBRE    50

/* Prototipos del módulo de productos */

void ingresar_producto(char nombres[][MAX_NOMBRE], int *cantidades,
                       int *tiempos, int *recursos, int *n);

int  calcular_tiempo_total(int *cantidades, int *tiempos, int n);

int  calcular_recursos_total(int *cantidades, int *recursos, int n);

int  verificar_factibilidad(int tiempo_total, int recursos_total,
                            int tiempo_max, int recursos_max);

int  buscar_producto(char nombres[][MAX_NOMBRE], int n,
                     char *nombre_buscado);

void editar_producto(char nombres[][MAX_NOMBRE], int *cantidades,
                     int *tiempos, int *recursos, int n);

void eliminar_producto(char nombres[][MAX_NOMBRE], int *cantidades,
                       int *tiempos, int *recursos, int *n);

void mostrar_productos(char nombres[][MAX_NOMBRE], int *cantidades,
                       int *tiempos, int *recursos, int n);

#endif
