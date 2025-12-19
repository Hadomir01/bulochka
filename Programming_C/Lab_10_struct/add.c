#include "new_head.h"

circ* simulate_circles(int n) {
    circ* c = malloc(n*sizeof(circ));
    if (c == NULL) {
        return NULL;
    }
    for (int i = 0; i<n; i++){
        printf("Введите характеристики окружности %d (центр по Ox, Oy, радиус)\n", i+1);
        scanf("%d %d %d", &c[i].x0, &c[i].y0, &c[i].R);
    }
    for (int i = 0; i<n; i++) {
        printf("Окружность %d: x0 = %d, y0 = %d, R = %d\n", 
               i+1, c[i].x0, c[i].y0, c[i].R);
    }
    return c;
}

double len_circle(circ* c) {
    return 2*pi*c->R;
}

void intersection(circ* c) {
    if (c == NULL) { 
        return;
    }
    float ox = 0;
    float oy = 0;

    if (abs(c->y0) <= c->R) {
        ox = 1;
    } 
    if (abs(c->x0) <= c->R) {
        oy = 1;
    }
    if (abs(c->y0) == c->R) {
        ox = 0.5;
    } 
    if (abs(c->x0) == c->R) {
        oy = 0.5;
    }
    
    if (ox == 1 && oy == 1) {
        printf("пересекает Ox и Oy\n");
    } else if (ox == 1) {
        printf("пересекает Ox\n");
    } else if (oy == 1) {
        printf("пересекает Oy\n");
    } else if (ox == 0.5 && oy == 0.5) {
        printf("касается с Ox и Oy\n");
    } else if (ox == 0.5) {
        printf("касается с Ox\n");
    } else if (oy == 0.5) {
        printf("касается с Oy\n");
    } else {
        printf("не пересекает оси / не касается осей\n");
    }
}
