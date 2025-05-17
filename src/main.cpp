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

// Базовый тип для функции плотности
typedef double (*MathFunc)(double);

// Структура для работы с функцией
struct Func {
    MathFunc fx;    // Указатель на выбранную функцию
    double x;       // Текущее значение аргумента
};

// Примеры различных плотностей распределения, задаются жёстко внутри кода, т.к. ввод со строки требует парсер, но это не в ходит в требования задания
static double formula_exp(double x) { return exp(-x); }                          // Экспоненциальное
static double formula_norm(double x) { return exp(-x*x/2); }                     // Нормальное
static double formula_uniform(double x) { return x >= 0 && x <= 1 ? 1.0 : 0.0; } // Равномерное

static double formula_example_one(double x) { return x - (x*x*x)/4; }            // Пример 1
static double formula_example_two(double x) { return 0.5 * sinl(x); }            // Пример 2   

// Ввод шага интегрирования и точности
int InputValues(float* values) {
    printf("Insert iteration and epsilon (ex: 0.01 0.001): ");
    return scanf("%f %f", &values[0], &values[1]) == 2;
}

// Ввод интервала для интегрирования, задаётся пользователем
int InputInterval(float* interval) {
    printf("Insert interval (ex: 0 2): ");
    return scanf("%f %f", &interval[0], &interval[1]) == 2;
}

// Выбор функции
int SelectFunction(MathFunc* func) {
    printf("\nSelect probability distribution:\n");
    printf("1. Exponential (e^-x)\n");
    printf("2. Normal (e^(-x^2/2))\n");
    printf("3. Uniform [0,1]\n");
    printf("4. Example 1 (x - (x*x*x)/4)\n");
    printf("5. Example 2 ((1/2) * sin(x))\n");
    printf("Your choice: ");
    
    int choice;
    if(scanf("%d", &choice) != 1) return 0;
    
    switch(choice) {
        case 1: *func = formula_exp; break;
        case 2: *func = formula_norm; break;
        case 3: *func = formula_uniform; break;
        case 4: *func = formula_example_one; break;
        case 5: *func = formula_example_two; break;
        default: return 0;
    }
    return 1;
}

void Integrate(Func f, float* interval, float iter, float eps) {
    double integrate = 0.0;
    double mode = 0.0;
    double x = interval[0];

    // Вычисление интеграла плотности
    while(x <= interval[1]) {
        f.x = x;
        double current = f.fx(f.x);
        
        if(current < 0.0) {
            printf("Negative function value!\n");
            return;
        }

        integrate += current * iter;

        if(current > mode) mode = current;
        x += iter;
    }

    // Проверка условия нормировки
    if(fabs(1.0 - integrate) > eps) {
        printf("Invalid function. Integral: %.6f\n", integrate);
        return;
    }
    printf("Valid function. Integral: %.6f\n", integrate);

    // Вычисление характеристик M(x), D(x)
    double M = 0.0, D = 0.0;
    for(x = interval[0]; x <= interval[1]; x += iter) {
        f.x = x;
        double val = f.fx(x) * iter;
        M += x * val;
        D += x * x * val;
    }
    D -= M * M;

    // Вывод результата
    printf("\nResults:\n");
    printf("M(x) = %.6f\n", M);
    printf("D(x) = %.6f\n", D);
    printf("Mode = %.6f\n", mode);
}

int main() {
    // Выбор функции распределения
    MathFunc selected_func;
    if(!SelectFunction(&selected_func)) {
        printf("Invalid function selection!\n");
        return 1;
    }

    // Инициализация структуры функции
    Func f = {selected_func, 0};

    // Ввод параметров
    float interval[2];
    if(!InputInterval(interval)) return 1;

    float values[2];
    if(!InputValues(values)) return 1;

    // Вычисление характеристик
    Integrate(f, interval, values[0], values[1]);
    return 0;
}