#include <stdio.h>
#include <math.h>

#ifndef header_was_declarated
#define header_was_declarated

struct Point{
    int x;
    int y;
};

double dist(struct Point a, struct Point b){
    return sqrt((double)(a.x - b.x) * (a.x - b.x) + (double)(a.y - b.y) * (a.y - b.y));
}


struct PentaAngle{
    struct Point points[5];
};

double perimetr(const struct PentaAngle* figure){
    double ans = 0;
    for (int i = 0; i < 5; i ++){
        if (i < 4){
            ans += dist(figure.points[i], figure.points[i + 1]);
        }
        else {
            ans += dist(figure.points[i], figure.points[0]);
        }
    }
    return ans;
}

struct Point read_point(){
    struct Point a;
    scanf("%d%d", &a.x, &a.y);
    return a;
}

struct PentaAngle read_figure(){
    struct PentaAngle figure;
    for (int i = 0; i < 5; i ++){
        figure.points[i] = read_point();
    }
    return figure;

};

#endif

