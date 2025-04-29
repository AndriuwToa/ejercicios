#include <stdio.h>
#include <string.h>

#define NUM_EQUIPOS 4
#define MAX_NOMBRE 50

int nombreValido(char nombre[]) {
    int i = 0;
    while (nombre[i] != '\0') {
        char c = nombre[i];
        if (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))) {
            return 0;
        }
        i++;
    }
    return 1;
}

int main() {
    char nombres[NUM_EQUIPOS][MAX_NOMBRE];
    int puntos[NUM_EQUIPOS] = {0};
    int gf[NUM_EQUIPOS] = {0}; // goles a favor
    int gc[NUM_EQUIPOS] = {0}; // goles en contra
    int diff[NUM_EQUIPOS];     // diferencia de goles
    int marcador1, marcador2;
    int i, j;

    for (i = 0; i < NUM_EQUIPOS; i++) {
        printf("Nombre del equipo #%d: ", i + 1);
        do {
            fgets(nombres[i], MAX_NOMBRE, stdin);
            nombres[i][strcspn(nombres[i], "\n")] = '\0';
            if (!nombreValido(nombres[i])) {
                printf("ERROR: Nombre invalido. Solo letras sin espacios. Intente de nuevo: ");
            }
        } while (!nombreValido(nombres[i]));
    }

    printf("\n--- Ingreso de resultados de los partidos ---\n");
    for (i = 0; i < NUM_EQUIPOS - 1; i++) {
        for (j = i + 1; j < NUM_EQUIPOS; j++) {
            printf("\n%s vs %s\n", nombres[i], nombres[j]);

            printf("Goles de %s: ", nombres[i]);
            scanf("%d", &marcador1);

            printf("Goles de %s: ", nombres[j]);
            scanf("%d", &marcador2);

            gf[i] += marcador1;
            gc[i] += marcador2;

            gf[j] += marcador2;
            gc[j] += marcador1;

            if (marcador1 > marcador2) {
                puntos[i] += 3;
            } else if (marcador1 < marcador2) {
                puntos[j] += 3;
            } else {
                puntos[i] += 1;
                puntos[j] += 1;
            }
        }
    }

    // Calcular diferencia de goles
    for (i = 0; i < NUM_EQUIPOS; i++) {
        diff[i] = gf[i] - gc[i];
    }

    // Ordenar por puntos y diferencia de goles
    for (i = 0; i < NUM_EQUIPOS - 1; i++) {
        for (j = 0; j < NUM_EQUIPOS - 1 - i; j++) {
            int swap = 0;
            if (puntos[j] < puntos[j+1]) {
                swap = 1;
            } else if (puntos[j] == puntos[j+1] && diff[j] < diff[j+1]) {
                swap = 1;
            }
            if (swap) {
                int aux_puntos = puntos[j];
                puntos[j] = puntos[j+1];
                puntos[j+1] = aux_puntos;

                int aux_gf = gf[j];
                gf[j] = gf[j+1];
                gf[j+1] = aux_gf;

                int aux_gc = gc[j];
                gc[j] = gc[j+1];
                gc[j+1] = aux_gc;

                int aux_diff = diff[j];
                diff[j] = diff[j+1];
                diff[j+1] = aux_diff;

                char aux_nombre[MAX_NOMBRE];
                strcpy(aux_nombre, nombres[j]);
                strcpy(nombres[j], nombres[j+1]);
                strcpy(nombres[j+1], aux_nombre);
            }
        }
    }

    // Mostrar tabla de posiciones
    printf("\n--- Tabla de Posiciones ---\n");
    printf("Pos  Equipo               GF  GC  DIF  Pts\n");
    for (i = 0; i < NUM_EQUIPOS; i++) {
        printf("%-4d %-20s %-3d %-3d %-4d %-3d\n",
               i+1, nombres[i], gf[i], gc[i], diff[i], puntos[i]);
    }

    // Finalistas
    printf("\n--- Finalistas ---\n");
    printf("1. %s\n", nombres[0]);
    printf("2. %s\n", nombres[1]);

    return 0;
}