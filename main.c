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
    }
    return 1;
}

int main() {
    char nombres[NUM_EQUIPOS][MAX_NOMBRE];
    int puntos[NUM_EQUIPOS] = {0};
    int goles_favor[NUM_EQUIPOS] = {0};
    int goles_contra[NUM_EQUIPOS] = {0};
    int diferencia[NUM_EQUIPOS];
    int marcador1, marcador2;
    int i, j;

    for (i = 0; i < NUM_EQUIPOS; i++) {
        printf("Nombre del equipo #%d: ", i + 1);
        do {
            fgets(nombres[i], MAX_NOMBRE, stdin);
            nombres[i][strcspn(nombres[i], "\n")] = '\0'; 
            if (!nombreValido(nombres[i])) {
                printf("ERROR: Nombre inválido. Solo letras sin espacios. Intente de nuevo: ");
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

            goles_favor[i] += marcador1;
            goles_contra[i] += marcador2;

            goles_favor[j] += marcador2;
            goles_contra[j] += marcador1;

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

    for (i = 0; i < NUM_EQUIPOS; i++) {
        diferencia[i] = goles_favor[i] - goles_contra[i];
    }

    for (i = 0; i < NUM_EQUIPOS - 1; i++) {
        for (j = i + 1; j < NUM_EQUIPOS; j++) {
            if ((puntos[j] > puntos[i]) ||
                (puntos[j] == puntos[i] && diferencia[j] > diferencia[i])) {
                char temp[MAX_NOMBRE];
                strcpy(temp, nombres[i]);
                strcpy(nombres[i], nombres[j]);
                strcpy(nombres[j], temp);

                int aux;
                aux = puntos[i]; puntos[i] = puntos[j]; puntos[j] = aux;
                aux = goles_favor[i]; goles_favor[i] = goles_favor[j]; goles_favor[j] = aux;
                aux = goles_contra[i]; goles_contra[i] = goles_contra[j]; goles_contra[j] = aux;
                aux = diferencia[i]; diferencia[i] = diferencia[j]; diferencia[j] = aux;
            }
        }
    }

    printf("\n--- Equipos que jugarán la final ---\n");
    for (i = 0; i < 2; i++) {
        printf("%d. %s (Puntos: %d, GF: %d, GC: %d, GD: %d)\n",
               i + 1, nombres[i], puntos[i], goles_favor[i], goles_contra[i], diferencia[i]);
    }

    return 0;
}