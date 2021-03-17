#include <stdio.h>
#include <stdlib.h>
#include <math.h>

enum Sweet{
    cake = 1,
    brownie,
    icecream,
    candy
};

struct Circle{
    int x0, y0, r;
    double square;
};

struct Circle set_square(struct Circle c){
    c.square = M_PI * c.r * c.r;
    return c;
}

union Keyboard{
    struct BitField{
        unsigned num_lock : 1;
        unsigned caps_lock : 1;
        unsigned scroll_lock : 1;
    };

};

int main(void){
    int sweet = candy;
    printf("%d\n", sweet);

    struct Circle c;
    scanf("%d %d %d", &c.x0, &c.y0, &c.r);
    c = set_square(c);
    printf("%lf\n", c.square);

    union Keyboard Status;
    scanf("%x", &Status);

    printf("%d%d%d", Status.num_lock, Status.caps_lock, Status.scroll_lock);

}
