#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

// Функція для обчислення (a^b) % p
long long mod_exp(long long a, long long b, long long p) {
    long long result = 1;
    a = a % p;
    while (b > 0) {
        if (b % 2 == 1) {
            result = (result * a) % p;
        }
        a = (a * a) % p;
        b = b / 2;
    }
    return result;
}

// Функція для перевірки простоти числа за алгоритмом Міллера — Рабіна
bool miller_rabin(long long p, int k) {
    // Якщо p <= 1, то воно не просте
    if (p <= 1) return false;
    // Якщо p = 2 або p = 3, то воно просте
    if (p == 2 || p == 3) return true;

    // Розкладаємо p - 1 на 2^s * d
    long long d = p - 1;
    int s = 0;
    while (d % 2 == 0) {
        d /= 2;
        s++;
    }

    // Виконуємо k раундів
    for (int i = 0; i < k; i++) {
        // Вибираємо випадкове число a від 2 до p - 2
        long long a = 2 + rand() % (p - 3);

        // Обчислюємо x = a^d % p
        long long x = mod_exp(a, d, p);
        
        if (x == 1 || x == p - 1) continue;

        bool is_composite = true;
        // Повторюємо операцію x = x^2 % p для s - 1 разів
        for (int j = 0; j < s - 1; j++) {
            x = mod_exp(x, 2, p);
            if (x == p - 1) {
                is_composite = false;
                break;
            }
        }
        if (is_composite) return false;
    }

    return true;  // Якщо не було знайдено складеного числа
}

int main() {
    srand(time(0));  // ініціалізація генератора випадкових чисел

    long long p;
    int k;

    // Вводимо число та кількість раундів
    std::cout << "Enter a number p > 3: ";
    std::cin >> p;
    std::cout << "Enter the number of rounds k: ";
    std::cin >> k;

    // Перевіряємо, чи є число простим
    if (miller_rabin(p, k)) {
        double probability = 1 - std::pow(4, -k);
        std::cout << "The number " << p << " is prime (with high probability)." << std::endl;
        std::cout << "The probability of primality is approximately: " << probability << std::endl;
    } else {
        std::cout << "The number " << p << " is composite." << std::endl;
    }

    return 0;
}
