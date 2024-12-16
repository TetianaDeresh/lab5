#include <iostream>
#include <cstdint>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <sstream>

using namespace std;

bool isPrime(int64_t number);
int64_t getD(int64_t e, int64_t f);
int64_t modExp(int64_t base, int64_t exp, int64_t mod);
int64_t gcd(int64_t a, int64_t b);

void generateKeys(int64_t &n, int64_t &e, int64_t &d);
void encryptMessage(const string &message, int64_t n, int64_t e);
void decryptMessage(const string &encrypted, int64_t n, int64_t d);

int main() {
    srand(time(nullptr));

    int64_t n = 0, e = 0, d = 0;
    int choice;

    do {
        cout << "\n1. Generate Keys\n2. Encrypt Message\n3. Decrypt Message\n4. Exit\nChoose an option: ";
        cin >> choice;
        cin.ignore(); // Clear newline from buffer

        if (choice == 1) {
            generateKeys(n, e, d);
            cout << "Public Key: (n = " << n << ", e = " << e << ")\n";
            cout << "Private Key: (n = " << n << ", d = " << d << ")\n";
        } else if (choice == 2) {
            cout << "Enter public key (n and e): ";
            cin >> n >> e;
            cin.ignore();

            string message;
            cout << "Enter message to encrypt: ";
            getline(cin, message);

            encryptMessage(message, n, e);
        } else if (choice == 3) {
            cout << "Enter private key (n and d): ";
            cin >> n >> d;
            cin.ignore();

            string encrypted;
            cout << "Enter encrypted message (space-separated numbers): ";
            getline(cin, encrypted);

            decryptMessage(encrypted, n, d);
        } else if (choice == 4) {
            cout << "Exiting program." << endl;
        } else {
            cout << "Invalid option." << endl;
        }
    } while (choice != 4);

    return 0;
}

bool isPrime(int64_t number) {
    if (number <= 1) return false;
    for (int64_t i = 2; i * i <= number; ++i) {
        if (number % i == 0) return false;
    }
    return true;
}

int64_t getD(int64_t e, int64_t f) {
    e = e % f;
    for (int64_t d = 1; d < f; ++d) {
        if ((e * d) % f == 1) return d;
    }
    return 1;
}

int64_t modExp(int64_t base, int64_t exp, int64_t mod) {
    int64_t result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) result = (result * base) % mod;
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    return result;
}

int64_t gcd(int64_t a, int64_t b) {
    while (b != 0) {
        int64_t temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

void generateKeys(int64_t &n, int64_t &e, int64_t &d) {
    int64_t p = 0, q = 0;

    while (!isPrime(p)) p = rand() % 100 + 50;
    while (!isPrime(q) || p == q) q = rand() % 100 + 50;

    n = p * q;
    int64_t f = (p - 1) * (q - 1);

    e = 3;
    while (gcd(e, f) != 1) e += 2;

    d = getD(e, f);
}

void encryptMessage(const string &message, int64_t n, int64_t e) {
    cout << "Encrypted message: ";
    for (char c : message) {
        int64_t m = static_cast<int64_t>(c);
        int64_t encrypted = modExp(m, e, n);
        cout << encrypted << " ";
    }
    cout << endl;
}

void decryptMessage(const string &encrypted, int64_t n, int64_t d) {
    stringstream ss(encrypted);
    int64_t encryptedValue;

    cout << "Decrypted message: ";
    while (ss >> encryptedValue) {
        int64_t decrypted = modExp(encryptedValue, d, n);
        cout << static_cast<char>(decrypted);
    }
    cout << endl;
}
