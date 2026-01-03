template <typename T>
ostream& operator<<(ostream& os, const vector<T>& v) {
    os << "{";
    string sep;
    for (const auto& x : v) {
        os << sep << x;
        sep = ", ";
    }
    os << "}";
    return os;
}
