#ifndef NEW_HEAD_H
#define NEW_HEAD_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define pi 3.14

typedef struct Circle {
    int x0; // центр окружности по Ox
    int y0; // центр окружности по Oy
    int R; // радиус окружности
} circ;

circ* simulate_circles(int n);
double len_circle(circ* c);
void intersection(circ* c);

#endif