// Тест на простоту
// Определить является ли число простым, используя алгоритм Миллера-Рабина

#include <iostream>
using namespace std;

long long mul_mod(long long a, long long b, long long m) {
    return (a * b) % m;
}

long long pow_mod(long long base, long long power, long long mod){
    long long result = 1;
    while (power){
        if (power & 1){
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        power >>= 1;
    }
    return result;
}

bool is_prime(long long n) {
    if (n < 2){
        return false;
    }
    if (n % 2 == 0){
        return n == 2;
    }
    if (n < 9){
        return true;
    }

    long long t = n - 1;
    long long s = 0;
    while (t % 2 == 0){
        t /= 2;
        s++;
    }

    long long bases[7] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};

    for (long long a : bases){
        if (a >= n) continue;
        long long x = pow_mod(a, t, n);
        if (x == 1 || x == n - 1) continue;
        bool ok = false;
        for (long long i = 1; i < s; i++){
            x = mul_mod(x, x, n);
            if (x == n - 1) {
                ok = true;
                break;
            }
        }
        if (!ok){
            return false;
        }
    }

    return true;
}

int main(){
    long long n;
    cout << "Введите n = ";
    cin >> n;

    if (is_prime(n)){
        cout << "Число простое" << endl;
    } else {
        cout << "Число составное" << endl;
    }

    return 0;
}