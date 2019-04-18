#include <bits/stdc++.h>
using namespace std;

template<class T>
struct pt {
    T x, y;
    pt(T x = 0, T y = 0) : x(x), y(y) {}
    bool operator< (pt o) const {return (x < o.x || (x == o.x && y < o.y)); }
    bool operator== (pt o) const {return (x == o.x && y == o.y);}
    pt operator+ (pt o) const {return pt(x + o.x, y + o.y);}
    pt operator- (pt o) const {return pt(x - o.x, y - o.y);}
    pt operator* (T l) const {return pt(l*x, l*y);}
    pt operator/ (T l) const {return pt(x/l, y/l);}
    T dot(pt o) { return x*o.x + y*o.y; }
    T cross(pt o) { return x*o.y - y*o.x; }
    T cross(pt a, pt b) { return (a - *this).cross(b - *this); }
    T normsq(pt o) { return x*x +y*y; }
    double norm(pt o) { return hypot(x, y); }
};
int main() {

}