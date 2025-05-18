/*
******************************************************************
*     C Mathematical method for probability calculations        *
*                                                                *
* Author: Alexander Dmitriyevich                                 *
* url: https://vk.com/sasha314                                   *
*                                                                *
******************************************************************
*/

#include <stdio.h>
#include <math.h>
#include <iostream>

// Базовый тип для функции плотности распределения
typedef double (*MathFunc)(double); // Создание указателя

struct Func {
    MathFunc fx;  // Указатель на функцию
    double x;     // Текущее значение аргумента
};

// Список доступных функций для указателя
static double Func_exp(double x){ return exp(-x); }
static double Func_norm(double x){ return exp(-x*x/2); }

// Функции примеры
static double Func_example_one(double x){ return x - (pow(x, 3))/4; }
static double Func_example_two(double x){ return 0.5 * sinl(x); }

// Ввод шага итерирования и точности
double InputValues(float* values){
    std::cout << "Insert iteration and epsilon (ex: 1e-2 1e-3): ";

    return scanf("%f %f", &values[0], &values[1]) == 2; // возвращает результат условия, 0 или 1
}

// Ввод интервала интегрирования (интервал определения функции распределения)
double InputInterval(float* interval){
    std::cout << "\nInsert interval (ex: 0 2): ";

    return scanf("%f %f", &interval[0], &interval[1]) == 2; // возвращает результат условия, 0 или 1
}

// Выбор функции распределения: Функция принимает адресс на указатель
int SelectFunction(MathFunc* func) {
    std::cout << "\n" << "Select probability distribution:" << "\n";
    std::cout << "1. Exponential (e^-x)" << "\n";
    std::cout << "2. Normal (e^(-x^2/2))" << "\n";
    std::cout << "3. Example 1 (x - (x*x*x)/4)" << "\n";
    std::cout << "4. Example 2 ((1/2) * sin(x))" << "\n";

    int choice;
    if (scanf("%d", &choice) != 1) return 1; // Если количество ввода не равно 1, то возвращает 1

    switch(choice) {
        case 1: *func = Func_exp; break;
        case 2: *func = Func_norm; break;
        case 3: *func = Func_example_one; break;
        case 4: *func = Func_example_two; break;
        default: return 0;
    }

    return 1;
}

void Integrate(Func f, float* interval, float iter, float eps) {
    double integrate = 0.0;
    double mode = 0.0;
    f.x = interval[0]; // 0 <- f.x, 1

    // Вычисление плотности вероятности функции на заданном интервале
    for ( f.x = interval[0]; f.x <= interval[1]; f.x += iter ){ // f.x <= 1 <- interval[1] {0, 1 <- [1]}
        double function = f.fx(f.x); // F(x) F - function, x - argument

        if (function < 0.0){
            std::cout << "Negative function value!" << "\n";
            return; // Выход из функции
        }

        integrate += function * iter;

        if(function > mode){
            mode = integrate; // Нахождение моды
        }
    }

    // Проверка сходимости
    if (abs(1.0 - integrate) > eps){
        std::cout << "Invalid function or interval. Integral: " << integrate << "\n";
        return; // Выход из функции
    }
    std::cout << "Function is valid, integral: " << integrate << "\n";

    // Вычисление M(x) и D(x):
    double M = 0.0, D = 0.0;
    for (f.x = interval[0]; f.x <= interval[1]; f.x += iter){
        M += f.x * f.fx(f.x) * iter;          // Вычисление M(x)
        D += pow(f.x, 2) * f.fx(f.x) * iter;  // Вычисление D(x)
    }
    D -= pow(M, 2);                           // Окончательное нахождение диспресии

    // Вывод:
    std::cout << "M(x) = " << M << "\n";
    std::cout << "D(x) = " << D << "\n";
    std::cout << "Mode = " << mode << "\n"; 
}

int main(){
    MathFunc select; // Указатель на функцию
    if(!SelectFunction(&select)){
        std::cout << "Invalid function selection!" << "\n";
        return 0;
    }

    Func f = {select, 0}; // Инициализация струткуры (функции)
    
    float values[2]; // Выделение памяти под статический массив типа float
    if(!InputValues(values)) return 1; // Если возвращён 0, то !0 = 1 и программа завершается

    float interval[2]; // Выделение памяти под статический массив типа float
    if(!InputInterval(interval)) return 1; // Если возвращён 0, то !0 = 1 и программа завершается
    
    Integrate(f, interval, values[0], values[1]); // Вычисление...
}