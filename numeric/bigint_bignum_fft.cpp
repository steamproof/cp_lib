// base must be <= 1e4 for safe carry if using fft::multiply with int inputs
vector<int> multiply_bigint(vector<int> a, vector<int> b, int base = 10000) {
    while (!a.empty() && a.back() == 0) {
        a.pop_back();
    }
    while (!b.empty() && b.back() == 0) {
        b.pop_back();
    }
    if (a.empty() || b.empty()) {
        return {0};
    }

    vector<int> aa = a;
    vector<int> bb = b;
    auto c = fft::multiply(aa, bb);

    long long carry = 0;
    vector<int> res;
    res.reserve(c.size() + 3);
    for (int i = 0; i < (int) c.size(); i++) {
        long long cur = c[i] + carry;
        res.push_back((int) (cur % base));
        carry = cur / base;
    }
    while (carry > 0) {
        res.push_back((int) (carry % base));
        carry /= base;
    }
    while (res.size() > 1 && res.back() == 0) {
        res.pop_back();
    }
    return res;
}
