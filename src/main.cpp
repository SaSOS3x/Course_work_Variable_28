/*
******************************************************************
*     C++ Mthematical method for calculate any mathematical      *
*               infinity vars for Probability theory             *
*                                                                *
* Author: Alexander Dmitriyevich                                 *
* url: https://vk.com/sasha314                                   *
*                                                                *
******************************************************************
*/

/*
**********************************************************************************
*                                                                                *
* For compile this application use this command:                                 *
* Windows: clang++ main.cpp -o main.exe                                          *
*                                                                                *
**********************************************************************************
*/

// Include librarities

#include <iostream>
#include <string>
#include <cmath>
#include <list>
#include <sstream>
#include <vector>
#include <stdexcept>
#include "exprtk.hpp"

struct func
{
    double x = 0;
    exprtk::expression<double> expression;               // function F(x)
    exprtk::parser<double> parser;                       // Parser

    bool set_function(const std::string& expr_str)       // Installing a function from a string (example, "x^2 + sin(x)")
    {
        exprtk::symbol_table<double> symbol_table;
        symbol_table.add_variable("x", x);               // Variable x
        expression.register_symbol_table(symbol_table);

        return parser.compile(expr_str, expression);     // Compile function
    }

    double calculate_Fx()                                // Calculate F(x)
    {
        return expression.value();
    }
};

std::vector<float> InputValues(){
    std::vector<float> numbers;
    std::string input;

    // Entering a line from the console
    std::cout << "Insert iteration (example: 1e-2) and Insert epsilo (example: 1e-2): ";
    std::getline(std::cin, input);

    // Splitting the string into numbers
    std::istringstream iss(input);
    float num;
    int count = 0;

    // Extract the first two numbers
    while (iss >> num && count < 2) {
        numbers.push_back(num);
        count++;
    }

    // Checking that there are enough numbers
    if (count < 2) {
        std::cout << "In the string less than two numbers!\n";
        return {0};
    }

    // Output vector
    std::cout << "Values: ";
    for (const auto& n : numbers) {
        std::cout << n << " ";
    }

    std::cout << "\n";

    return numbers;
}

std::vector<float> InputList(){
    std::vector<float> numbers;
    std::string input;

    // Entering a line from the console
    std::cout << "Insert interval, that function > 0: ";
    std::getline(std::cin, input);

    // Splitting the string into numbers
    std::istringstream iss(input);
    float num;
    int count = 0;

    // Extract the first two numbers
    while (iss >> num && count < 2) {
        numbers.push_back(num);
        count++;
    }

    // Checking that there are enough numbers
    if (count < 2) {
        std::cout << "In the string less than two numbers!\n";
        return {0};
    }

    // Output vector
    std::cout << "Vector: ";
    for (const auto& n : numbers) {
        std::cout << n << " ";
    }

    std::cout << "\n";

    return numbers;
}

double Integrate(std::vector<float> interval, float iter, double eps){
    /*
    ********************************************
    *                                          *
    * newfunc - is a struct object of function *
    *                                          *
    * interval - is a vector who has have a 2  *
    * numbers, example: [0, 2]                 *
    *                                          *
    * iter - is a iterate variable             *
    *                                          *
    * eps - is a epsilo                        *
    *                                          *
    ********************************************
    */

    func newfunc;

    std::string user_expr;
        
    // Function input from the user
    std::cout << "Enter the function (use 'x' as a variable): ";
    std::getline(std::cin, user_expr);

    // Setting the function
    if (!newfunc.set_function(user_expr))
    {
        std::cerr << "An error in the formula!\n";
        return 1;
    }

    // Set the variables
    newfunc.x = interval[0];
    double integrate = 0;
    double mode = 0;
    double func = 0;
    
    // Integrte function...
    while (std::abs(newfunc.x) < interval[1]) {
        func = newfunc.calculate_Fx();          // Calculate F(x)

        // Checking properties...
        if (func < 0){
            std::cout << "The distribution function cannot take negative values." << "\n";
            return 0;
        }

        integrate += func * iter;               // Integrate...
        std::cout << "integrate: " << integrate << " x: " << newfunc.x << "\n";

        // Checking a new mode
        if (mode < func){
            mode = func;
        }
        newfunc.x += iter;
    }
    
    // Checking properties...
    if (1 - std::abs(integrate) <= eps){
        std::cout << "This function is a correct in that interval, integrate: " << integrate << " epsilo: " << eps << "\n";
    } else {
        std::cout << "This function is a not correct in that interval, integrate: " << integrate << " epsilo: " << eps << "\n";
        return 0;
    }
    
    std::cout << "Calculate M(x)..." << "\n";

    newfunc.x = interval[0];                  // Ubdate x vriable in newfunc object -> func structure
    double Mintegrate = 0;

    // Clculate M(x)...
    while (std::abs(newfunc.x) < interval[1]) {
        Mintegrate += newfunc.x * newfunc.calculate_Fx() * iter;
        std::cout << "integrate: " << Mintegrate << " x: " << newfunc.x << "\n";
        newfunc.x += iter;
    }

    std::cout << "Calculate D(x)..." << "\n";

    newfunc.x = interval[0];                  // Ubdate x vriable in newfunc object -> func structure
    double Dintegrate = 0;

    // Calculate D(x)...
    while (std::abs(newfunc.x) < interval[1]) {
        Dintegrate += std::pow(newfunc.x, 2) * newfunc.calculate_Fx() * iter;
        std::cout << "integrate: " << Dintegrate << " x: " << newfunc.x << "\n";
        newfunc.x += iter;
    }
    
    Dintegrate = Dintegrate - std::pow(Mintegrate, 2);  // Finish the calculating

    std::cout << "M(x) = " << Mintegrate << "\n" << "D(x) = " << Dintegrate << "\n" << "mode = " << mode << "\n";
    
    return 0;
}

int main(){

    // Set the interval
    std::vector<float> interval = InputList();

    try {
        int value = interval.at(1);
    } catch (const std::out_of_range& e){
        std::cerr << "Error: " << "you don`t write a 2-nd number..." << "\n";
        return 1;
    }

    // Set the values
    std::vector<float> values = InputValues();

    try {
        int value = values.at(1);
    } catch (const std::out_of_range& e){
        std::cerr << "Error: " << "you don`t write a 2-nd number..." << "\n";
        return 1;
    }

    // Integrate...
    Integrate(interval, values[0], values[1]);
}
