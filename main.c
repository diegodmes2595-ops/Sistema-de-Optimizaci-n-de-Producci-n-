#include <stdio.h>
#include "productos.h"

int main(void) {
    /* Arreglos paralelos para los datos de los productos */
    char nombres[MAX_PRODUCTOS][MAX_NOMBRE];
    int  cantidades[MAX_PRODUCTOS];
    int  tiempos[MAX_PRODUCTOS];
    int  recursos[MAX_PRODUCTOS];
    int  n = 0;  /* Contador de productos ingresados */

    /* Limites de la fabrica */
    int tiempo_max   = 0;
    int recursos_max = 0;

    int opcion;
    int tiempo_total, recursos_total, puede;

    printf("=================================================\n");
    printf("  SISTEMA DE OPTIMIZACION DE PRODUCCION\n");
    printf("  Fabrica de Componentes Electronicos\n");
    printf("=================================================\n");
    printf("\n  Ingrese los limites de la fabrica:\n");
    printf("  Tiempo maximo de produccion disponible (min): ");
    scanf("%d", &tiempo_max);
    printf("  Cantidad maxima de recursos disponibles: ");
    scanf("%d", &recursos_max);

    do {
        printf("\n-------------------------------------------------\n");
        printf("  MENU PRINCIPAL\n");
        printf("-------------------------------------------------\n");
        printf("  1. Ingresar producto\n");
        printf("  2. Mostrar productos registrados\n");
        printf("  3. Calcular tiempo total de fabricacion\n");
        printf("  4. Calcular recursos totales necesarios\n");
        printf("  5. Verificar factibilidad de produccion\n");
        printf("  6. Editar producto\n");
        printf("  7. Eliminar producto\n");
        printf("  0. Salir\n");
        printf("-------------------------------------------------\n");
        printf("  Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {

            case 1:
                ingresar_producto(nombres, cantidades, tiempos, recursos, &n);
                break;

            case 2:
                mostrar_productos(nombres, cantidades, tiempos, recursos, n);
                break;

            case 3:
                if (n == 0) {
                    printf("\n  [!] No hay productos registrados.\n");
                } else {
                    tiempo_total = calcular_tiempo_total(cantidades, tiempos, n);
                    printf("\n  Tiempo total de fabricacion requerido: %d minutos\n",
                           tiempo_total);
                }
                break;

            case 4:
                if (n == 0) {
                    printf("\n  [!] No hay productos registrados.\n");
                } else {
                    recursos_total = calcular_recursos_total(cantidades, recursos, n);
                    printf("\n  Recursos totales necesarios: %d unidades\n",
                           recursos_total);
                }
                break;

            case 5:
                if (n == 0) {
                    printf("\n  [!] No hay productos registrados.\n");
                } else {
                    tiempo_total   = calcular_tiempo_total(cantidades, tiempos, n);
                    recursos_total = calcular_recursos_total(cantidades, recursos, n);
                    puede = verificar_factibilidad(tiempo_total, recursos_total,
                                                  tiempo_max, recursos_max);

                    printf("\n  --- Verificacion de Factibilidad ---\n");
                    printf("  Tiempo requerido  : %d min  (disponible: %d min)\n",
                           tiempo_total, tiempo_max);
                    printf("  Recursos requeridos: %d      (disponibles: %d)\n",
                           recursos_total, recursos_max);

                    if (puede) {
                        printf("  RESULTADO: La fabrica SI puede cumplir con la demanda.\n\n");
                    } else {
                        printf("  RESULTADO: La fabrica NO puede cumplir con la demanda.\n");
                        if (tiempo_total > tiempo_max)
                            printf("  -> Excede el tiempo disponible en %d minutos.\n",
                                   tiempo_total - tiempo_max);
                        if (recursos_total > recursos_max)
                            printf("  -> Excede los recursos disponibles en %d unidades.\n",
                                   recursos_total - recursos_max);
                        printf("\n");
                    }
                }
                break;

            case 6:
                if (n == 0) {
                    printf("\n  [!] No hay productos registrados.\n");
                } else {
                    editar_producto(nombres, cantidades, tiempos, recursos, n);
                }
                break;

            case 7:
                if (n == 0) {
                    printf("\n  [!] No hay productos registrados.\n");
                } else {
                    eliminar_producto(nombres, cantidades, tiempos, recursos, &n);
                }
                break;

            case 0:
                printf("\n  Saliendo del sistema. Hasta luego.\n\n");
                break;

            default:
                printf("\n  [!] Opcion invalida. Intente nuevamente.\n");
        }

    } while (opcion != 0);

    return 0;
}
