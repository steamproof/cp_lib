template <typename T>
inline T floor_div(T a, T b) {
    assert(b != 0);
    if (b < 0) {
        a = -a;
        b = -b;
    }
    if (a >= 0) {
        return a / b;
    }
    return - ((-a + b - 1) / b);
}

template <typename T>
inline T ceil_div(T a, T b) {
    assert(b != 0);
    if (b < 0) {
        a = -a;
        b = -b;
    }
    if (a <= 0) {
        return a / b;
    }
    return (a + b - 1) / b;
}
