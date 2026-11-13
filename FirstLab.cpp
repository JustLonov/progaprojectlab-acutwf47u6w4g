#include <iostream>
#include <iomanip>
#include <Windows.h>

// Задание 1: вывод размеров типов данных
void PrintBitSizes() {
    std::cout << std::left << std::setw(17) << "тип" << std::setw(12) << "байт" << "комментарий" << std::endl;
    std::cout << std::string(50, '-') << std::endl;
    std::cout << std::left << std::setw(14) << "bool" << std::setw(8) << sizeof(bool) << "0 или 1" << std::endl;
    std::cout << std::left << std::setw(14) << "char" << std::setw(8) << sizeof(char) << "по стандарту - ровно 1 байт" << std::endl;
    std::cout << std::left << std::setw(14) << "short int" << std::setw(8) << sizeof(short int) << "минимум 2 байта" << std::endl;
    std::cout << std::left << std::setw(14) << "int" << std::setw(8) << sizeof(int) << "-" << std::endl;
    std::cout << std::left << std::setw(14) << "long int" << std::setw(8) << sizeof(long int) << "4 (Win) | 8 (Linux x64)" << std::endl;
    std::cout << std::left << std::setw(14) << "float" << std::setw(8) << sizeof(float) << "IEEE 754 binary32" << std::endl;
    std::cout << std::left << std::setw(14) << "double" << std::setw(8) << sizeof(double) << "IEEE 754 binary64" << std::endl;
    std::cout << std::left << std::setw(14) << "long double" << std::setw(8) << sizeof(long double) << "x87: 80 бит" << std::endl;
}

// Задание 2: вывод двоичного представления целого числа с визуальным обозначением
void PrintBinVis(unsigned long long bits, int amount, bool haveSign) {
    int start = amount - 1;
    if (haveSign) {
        std::cout << ((bits >> (amount - 1)) & 1) << " | ";
        start = amount - 2;
    }
    for (int i = start; i >= 0; i--) {
        std::cout << ((bits >> i) & 1);
        if (i % 4 == 0 && i > 0) std::cout << "  ";
    }
    std::cout << std::endl;
}

// Задание 3: вывод двоичного представления дробного (float) числа с визуальным обозначением (знаковый бит, поле порядка, мантисса)
void PrintFloatBits(float f) {
    unsigned int bits = 0;
    std::memcpy(&bits, &f, sizeof(bits));

    unsigned int sign = (bits >> 31) & 1;
    unsigned int field = (bits >> 23) & 0xFF;
    unsigned int mant = bits & 0x7FFFFF;

    std::cout << sign << " | ";

    for (int i = 7; i >= 0; i--) {
        std::cout << ((field >> i) & 1);
    }
    std::cout << " | ";
    for (int i = 22; i >= 0; i--) {
        std::cout << ((mant >> i) & 1);
    }
    std::cout << std::endl;
}

// Задание 4: вывод двоичного представления дробного (double) числа с визуальным обозначением (знаковый бит, поле порядка, мантисса)
void PrintDoubleBits(double f) {
    unsigned long long bits = 0;
    std::memcpy(&bits, &f, sizeof(bits));

    unsigned long long sign = (bits >> 63) & 1;
    unsigned long long field = (bits >> 52) & 0x7FF;
    unsigned long long mant = bits & 0xFFFFFFFFFFFFF;

    std::cout << sign << " | ";
    for (int i = 10; i >= 0; i--) {
        std::cout << ((field >> i) & 1);
    }
    std::cout << " | ";
    for (int i = 51; i >= 0; i--) {
        std::cout << ((mant >> i) & 1);
    }
    std::cout << std::endl;
}

// Задание 5: реализация изменения произвольного бита в введеном числе
// Это старое: 
//unsigned long long PrintSetBits(unsigned long long bits, int n) {
//    return bits | (1ULL << n);
//}
//unsigned long long PrintRemoveBits(unsigned long long bits, int n) {
//    return bits ^ (((bits >> n) & 1) << n);
//}
//unsigned long long PrintSwapBits(unsigned long long bits, int n) {
//    return bits ^ (0xFFFFFFFFFFFFFFFF);
//}

// Целые числа
long long PrintEditBits(long long bits, int n, int keyword) {
    switch (keyword) {
    // Установка
    case 0:
        return bits | (1ULL << n);
        break;
    // Удаление
    case 1:
        return bits ^ (((bits >> n) & 1) << n);
        break;
    // Инверсия
    case 2:
        return bits ^= (1ULL << n);
        break;
    }
}

// Float
float PrintEditBitsFloat(float bits, int n, int keyword) {
    unsigned int bitss = 0;
    std::memcpy(&bitss, &bits, sizeof(bitss));
    switch (keyword) {
    // Установка
    case 0:
        bitss |= (1ULL << n);
        break;
    // Удаление
    case 1:
        bitss ^= (((bitss >> n) & 1) << n);
        break;
    // Инверсия
    case 2:
        bitss ^= (1ULL << n);
        break;
    }
    float result = 0;
    std::memcpy(&result, &bitss, sizeof(result));
    return result;
}

double PrintEditBitsDouble(double bits, int n, int keyword) {
    unsigned long long bitss = 0;
    std::memcpy(&bitss, &bits, sizeof(bitss));
    switch (keyword) {
        // Установка
    case 0:
        bitss |= (1ULL << n);
        break;
        // Удаление
    case 1:
        bitss ^= (((bitss >> n) & 1) << n);
        break;
        // Инверсия
    case 2:
        bitss ^= (1ULL << n);
        break;
    }
    double result = 0;
    std::memcpy(&result, &bitss, sizeof(result));
    return result;
}

// Индивидуальное Задание 6: инверсия знака
// Целочисленное
long long PrintInvIntSign(long long bits) {
    bits ^= (1ULL << 31);
    return bits;
}
// Float
float PrintInvFloatSign(float bits) {
    unsigned long long bitss = 0;
    std::memcpy(&bitss, &bits, sizeof(bitss));
    bitss ^= (1ULL << 31);
    float result = 0;
    std::memcpy(&result, &bitss, sizeof(result));
    return result;
}
// Double
double PrintInvDoubleSign(double bits) {
    unsigned long long bitss = 0;
    std::memcpy(&bitss, &bits, sizeof(bitss));
    bitss ^= (1ULL << 63);
    double result = 0;
    std::memcpy(&result, &bitss, sizeof(result));
    return result;
}

// Вывод
void main() {
    SetConsoleOutputCP(65001);

    std::cout << "Задание 1:" << std::endl;
    PrintBitSizes();
    std::cout << std::endl;

    std::cout << "Задание 2:" << std::endl;
    std::cout << "-5: ";
    PrintBinVis((unsigned int)-5, 32, true);
    std::cout << std::endl;
    std::cout << "5: ";
    PrintBinVis(5, 32, true);
    std::cout << std::endl;
    std::cout << "3.5: ";
    PrintBinVis(3.5, 32, true);
    std::cout << std::endl;
    std::cout << "1.4e-45f: ";
    PrintBinVis(1.4e-45f, 32, true);
    std::cout << std::endl;

    std::cout << "Задание 3:" << std::endl;
    std::cout << "3.14: ";
    PrintFloatBits(3.14);
    std::cout << std::endl;
    std::cout << "1.4e-45f: ";
    PrintFloatBits(1.4e-45f);
    std::cout << std::endl;
    std::cout << "5: ";
    PrintFloatBits(5);
    std::cout << std::endl;
    std::cout << "-5: ";
    PrintFloatBits(-5);
    std::cout << std::endl;

    std::cout << "Задание 4:" << std::endl;
    std::cout << "3.14: ";
    PrintDoubleBits(3.14);
    std::cout << std::endl;
    std::cout << "1.4e-45f: ";
    PrintDoubleBits(1.4e-45f);
    std::cout << std::endl;
    std::cout << "5: ";
    PrintDoubleBits(5);
    std::cout << std::endl;
    std::cout << "-5: ";
    PrintDoubleBits(-5);
    std::cout << std::endl;

    std::cout << "Задание 5:" << std::endl;
    std::cout << "Установка бита:" << std::endl;
    std::cout << "5 было: ";
    PrintBinVis(5, 32, true);
    std::cout << "5 cтало: ";
    PrintBinVis(PrintEditBits(5, 7, 0), 32, true);
    std::cout << std::endl;
    std::cout << "-5 было: ";
    PrintBinVis((unsigned)-5, 32, true);
    std::cout << "-5 cтало: ";
    PrintBinVis(PrintEditBits((unsigned)-5, 12, 0), 32, true);
    std::cout << std::endl;
    std::cout << "3.5 float было: ";
    PrintFloatBits(3.5);
    std::cout << "3.5 float cтало: ";
    PrintFloatBits(PrintEditBitsFloat(3.5, 7, 0));
    std::cout << std::endl;
    std::cout << "3.5 double было: ";
    PrintDoubleBits(3.5);
    std::cout << "3.5 double cтало: ";
    PrintDoubleBits(PrintEditBitsDouble(3.5, 32, 0));
    std::cout << std::endl;
    std::cout << "Удаление бита:" << std::endl;
    std::cout << "5 было: ";
    PrintBinVis(5, 32, true);
    std::cout << "5 cтало: ";
    PrintBinVis(PrintEditBits(5, 0, 1), 32, true);
    std::cout << std::endl;
    std::cout << "-5 было: ";
    PrintBinVis((unsigned)-5, 32, true);
    std::cout << "-5 cтало: ";
    PrintBinVis(PrintEditBits((unsigned)-5, 12, 1), 32, true);
    std::cout << std::endl;
    std::cout << "3.5 float было: ";
    PrintFloatBits(3.5);
    std::cout << "3.5 float cтало: ";
    PrintFloatBits(PrintEditBitsFloat(3.5, 22, 1));
    std::cout << std::endl;
    std::cout << "3.5 double было: ";
    PrintDoubleBits(3.5);
    std::cout << "3.5 double cтало: ";
    PrintDoubleBits(PrintEditBitsDouble(3.5, 51, 1));
    std::cout << std::endl;
    std::cout << "Инверсия бита:" << std::endl;
    std::cout << "5 было: ";
    PrintBinVis(5, 32, true);
    std::cout << "5 cтало: ";
    PrintBinVis(PrintEditBits(5, 0, 2), 32, true);
    std::cout << std::endl;
    std::cout << "-5 было: ";
    PrintBinVis((unsigned)-5, 32, true);
    std::cout << "-5 cтало: ";
    PrintBinVis(PrintEditBits((unsigned)-5, 2, 2), 32, true);
    std::cout << std::endl;
    std::cout << "3.5 float было: ";
    PrintFloatBits(3.5);
    std::cout << "3.5 float cтало: ";
    PrintFloatBits(PrintEditBitsFloat(3.5, 22, 2));
    std::cout << std::endl;
    std::cout << "3.5 double было: ";
    PrintDoubleBits(3.5);
    std::cout << "3.5 double cтало: ";
    PrintDoubleBits(PrintEditBitsDouble(3.5, 51, 2));
    std::cout << std::endl;

    std::cout << "Задание 6:" << std::endl;
    std::cout << "5 было: ";
    PrintBinVis(5, 32, true);
    std::cout << "5 стало: ";
    PrintBinVis(PrintInvIntSign(5), 32, true);
    std::cout << std::endl;
    std::cout << "-5 было: ";
    PrintBinVis((unsigned)-5, 32, true);
    std::cout << "-5 стало: ";
    PrintBinVis(PrintInvIntSign((unsigned)-5), 32, true);
    std::cout << std::endl;
    std::cout << "3.5 float было: ";
    PrintFloatBits(3.5);
    std::cout << "3.5 float стало: ";
    PrintFloatBits(PrintInvFloatSign(3.5));
    std::cout << std::endl;
    std::cout << "-3.5 float было: ";
    PrintFloatBits(-3.5);
    std::cout << "-3.5 float стало: ";
    PrintFloatBits(PrintInvFloatSign(-3.5));
    std::cout << std::endl;
    std::cout << "3.5 double было: ";
    PrintDoubleBits(3.5);
    std::cout << "3.5 double стало: ";
    PrintDoubleBits(PrintInvDoubleSign(3.5));
    std::cout << std::endl;
    std::cout << "-3.5 double было: ";
    PrintDoubleBits(-3.5);
    std::cout << "-3.5 double стало: ";
    PrintDoubleBits(PrintInvDoubleSign(-3.5));

}