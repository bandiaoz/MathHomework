#include <bits/stdc++.h>

using namespace std;
using ll = long long;

template<class ele_t>
struct Matrix {
    int n, m;
    vector<vector<ele_t>> a;
    Matrix() {}
    Matrix(int _n, int _m) {
        n = _n;
        m = _m;
        a.assign(n, vector<ele_t>(m, 0));
    }
    Matrix(vector<vector<ele_t>> v) {
        n = v.size();
        m = n ? v[0].size() : 0;
        a = v;
    }
    inline Matrix t() {
        Matrix ans = Matrix(m, n);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                ans.a[j][i] = a[i][j];
            }
        }
        return ans;
    }
    inline void make_unit() {
        assert(n == m);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                a[i][j] = i == j;
            }
        }
    }
    inline Matrix operator+(const Matrix& b) {
        assert(n == b.n && m == b.m);
        Matrix ans = Matrix(n, m);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                ans.a[i][j] = a[i][j] + b.a[i][j];
            }
        }
        return ans;
    }
    inline Matrix operator-(const Matrix& b) {
        assert(n == b.n && m == b.m);
        Matrix ans = Matrix(n, m);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                ans.a[i][j] = a[i][j] - b.a[i][j];
            }
        }
        return ans;
    }
    inline Matrix operator*(const Matrix& b) {
        assert(m == b.n);
        Matrix ans = Matrix(n, b.m);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < b.m; j++) {
                for (int k = 0; k < m; k++) {
                    ans.a[i][j] = ans.a[i][j] + a[i][k] * b.a[k][j];
                }
            }
        }
        return ans;
    }
    inline Matrix operator*(const ele_t &k) {
        Matrix ans = *this;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                ans.a[i][j] *= k;
            }
        }
        return ans;
    }
    inline Matrix pow(long long k) {
        assert(n == m);
        Matrix ans(n, n), t = a;
        ans.make_unit();
        while (k) {
            if (k & 1) ans = ans * t;
            t = t * t;
            k >>= 1;
        }
        return ans;
    }
    friend Matrix operator*(const ele_t &k, const Matrix &b) {
        Matrix ans = b;
        for (int i = 0; i < ans.n; ++i) {
            for (int j = 0; j < ans.m; ++j) {
                ans.a[i][j] *= k;
            }
        }
        return ans;
    }
    inline void print() {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                cout << a[i][j] << " \n"[j == m - 1];
            }
        }
    }
    inline Matrix& operator+=(const Matrix& b) { return *this = (*this) + b; }
    inline Matrix& operator-=(const Matrix& b) { return *this = (*this) - b; }
    inline Matrix& operator*=(const Matrix& b) { return *this = (*this) * b; }
    inline Matrix& operator*=(const ele_t &k) { return *this = (*this) * k; }
    inline bool operator==(const Matrix& b) { return a == b.a; }
    inline bool operator!=(const Matrix& b) { return a != b.a; }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << fixed << setprecision(4);

    Matrix<double> A(vector<vector<double>>{{2, 1, 1, 0}, {1, 4, 0, 0}, {1, 0, 2, 0}, {0, 0, 0, 2}});
    Matrix<double> b(vector<vector<double>>{{1}, {2}, {0}, {1}});
    Matrix<double> c(vector<vector<double>>{{2}});

    Matrix<double> x(vector<vector<double>>{{1}, {1}, {1}, {1}});

    auto culGradient = [&](Matrix<double> x) {
        return A * x + b;
    };

    Matrix<double> gradient = culGradient(x);
    Matrix<double> d = -1 * gradient;

    double sigma = 1e-4;
    double beta = 1;
    double gamma = 0.5;

    auto f = [&](Matrix<double> x) {
        return 1.0 / 2 * x.t() * A * x + b.t() * x + c;
    };

    auto Armijo = [&]() {
        auto check = [&](int m) {
            Matrix lhs = f(x + beta * pow(gamma, m) * d);
            Matrix rhs = f(x) + sigma * beta * pow(gamma, m) * gradient.t() * d;
            return lhs.a[0][0] <= rhs.a[0][0];
        };

        int m = -1;
        for (int i = 1; ; ++i) {
            if (check(i)) {
                m = i;
                break;
            }
        }
        
        cout << "Using Armijo algorithm, ";
        cout << "m = " << m << ", ";
        cout << "the next x is (";
        Matrix nex = x + beta * pow(gamma, m) * d;
        for (int i = 0; i < nex.n; ++i) {
            cout << nex.a[i][0];
            if (i != nex.n - 1) {
                cout << ", ";
            }
        }
        cout << ")^t\n";
    };

    auto Goldstein = [&]() {
        auto check1 = [&](double lambda) {
            Matrix lhs = f(x + lambda * d);
            Matrix rhs = f(x) + sigma * lambda * gradient.t() * d;
            return lhs.a[0][0] <= rhs.a[0][0];
        };

        auto check2 = [&](double lambda) {
            Matrix lhs = f(x + lambda * d);
            Matrix rhs = f(x) + (1 - sigma) * lambda * gradient.t() * d;
            return lhs.a[0][0] > rhs.a[0][0];
        };

        double lambda = 1000;
        while (!check1(lambda) || !check2(lambda)) {
            lambda /= 2;
        }

        cout << "Using Goldstein algorithm, ";
        cout << "lambda = " << lambda << ", ";
        cout << "the next x is (";
        Matrix nex = x + lambda * d;
        for (int i = 0; i < nex.n; ++i) {
            cout << nex.a[i][0];
            if (i != nex.n - 1) {
                cout << ", ";
            }
        }
        cout << ")^t\n";
    };

    auto Wolfe = [&]() {
        double sigma_1 = 0.2, sigma_2 = 0.5;

        auto check1 = [&](double lambda) {
            Matrix lhs = f(x + lambda * d);
            Matrix rhs = f(x) + sigma_1 * lambda * gradient.t() * d;
            return lhs.a[0][0] <= rhs.a[0][0];
        };

        auto check2 = [&](double lambda) {
            Matrix lhs = culGradient(x + lambda * d).t() * d;
            Matrix rhs = sigma_2 * culGradient(x).t() * d;
            return lhs.a[0][0] >= rhs.a[0][0];
        };

        double lambda = 1000;
        while (!check1(lambda) || !check2(lambda)) {
            lambda /= 2;
        }

        cout << "Using Wolfe algorithm, ";
        cout << "lambda = " << lambda << ", ";
        cout << "the next x is (";
        Matrix nex = x + lambda * d;
        for (int i = 0; i < nex.n; ++i) {
            cout << nex.a[i][0];
            if (i != nex.n - 1) {
                cout << ", ";
            }
        }
        cout << ")^t\n";
    };

    Armijo();
    Goldstein();
    Wolfe();

    return 0;
}