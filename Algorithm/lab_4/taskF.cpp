#include <bits/stdc++.h>

using namespace std;

#define int int64_t

double eps = 1e-6;
double first_el;
int n;

bool eq(double a, double b){
    return abs(a - b) < eps;
}

double get_res(double sec_el){
    double last2_el = first_el, last1_el = sec_el;

    for (int i = 2; i < n; i ++){
        double temp = last1_el;
        last1_el = 2 * last1_el - last2_el + 2;
        last2_el = temp;
    }
    return last1_el;
}

bool is_ok(double sec_el){
    double last2_el = first_el, last1_el = sec_el;
    int cnt = 0;

    for (int i = 2; i < n; i ++){
        double temp = last1_el;
        last1_el = 2 * last1_el - last2_el + 2;
        last2_el = temp;

        if (eq(last1_el, 0)) cnt ++;
        if (last1_el < -eps) return false;
    }

    if (cnt <= 1) return true;
    return false;
}

int32_t main(){
    freopen("garland.in", "r", stdin);
    freopen("garland.out", "w", stdout);

    cin.tie(0);
    cout.tie(0);
    cout.precision(10);
    ios::sync_with_stdio(false);

    cin >> n >> first_el;


    double max_sec_el = first_el, min_sec_el = 0;

    while (max_sec_el - min_sec_el > eps){
        double mid = (max_sec_el + min_sec_el) / 2;
        if (!is_ok(mid)){
            min_sec_el = mid;
            continue;
        }
        else {
            max_sec_el = mid;
            continue;
        }
    }


//    cout << max_sec_el << " " << min_sec_el << endl;

    cout << get_res((max_sec_el + min_sec_el) / 2) << endl;
}
