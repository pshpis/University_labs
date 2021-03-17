#include <stdio.h>
#include "header.h"

int main(void){
    struct PentaAngle figure;
    figure = read_figure();
    printf("%lf ", perimetr(figure));
}
