#include <iostream>
#include <cmath>

using namespace std;

double f1(double a){
    return(cos(a) + cos(2 * a) + cos(6 * a) + cos(7 * a));
}

double f2(double a){
    return(4 * cos(a / 2) * cos(5 * a / 2) * cos(4 * a));
}

int main (void)
{
    double num;
    cin >> num;

    num /= 360;
    num *= 2 * M_PI;

    double ans1 = f1(num);
    double ans2 = f2(num);

    printf("\n%f\n%f", ans1, ans2);
    return 0;
}
