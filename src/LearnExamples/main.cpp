#include <iostream> /* Input - output streams*/
#include <string> // adding a string dattype
#include <limits> // add new limits function in project
#include <cmath> // add math functions
#include <cstdint> // add case constructions


void Hello(){
    std::string name;
    /* cin - читает всё до первого пробела */
    /* getline - читает всю строку целиком, т.е. использует std::cin столько раз, пока пробелы не закончатся. */
    std::cout << "Hello 2, what`s your name?";
    std::getline(std::cin, name);
    std::cout << "\nHello, " << name << "!\n";
}

void Datatypes(){
                                     // Clang, sizeof datatypes
    char ch_symb = 'a';              // 1
    bool bool_var = true;            // 1
    short int si_num = 1;            // 2
    int i_num = 42;                  // 4
    long int li = 24332;             // 8 
    long long int lli = 23432232324; // 8
    float f_num = 23.23;             // 4
    double d_num = 2323.34343;       // 8
    long double ld_num = 32e15;      // 16
    
    std::cout << sizeof(char) << " " << sizeof(int) << "\n";

    // unsigned int - it is positive int numbers that have size of 4 bytes (16 bit)
    // That`s work and for a any num dattypes.
    // Simply example: unsigned long, unsigned long long, unsigned short and e.t.c

    // Min and Max value of any dttypes (their limits), you can take for using new library: <limits>
    // For int datatype:
    std::cout << "minimum value for int datatype: " << std::numeric_limits<unsigned long long int>::min() << "\n"
              << "maximum value for int datatype: " << std::numeric_limits<unsigned long long int>::max() << "\n"; // Ya ebal...

    // Divide static_cast (int a for double a or float a):
    int a = 6, b = 4;
    double q = static_cast<double>(a) / b; // 1.5
    // double q = a * 1.0 / b;

    // ASCII ariphmetic operations:
    char c = 'A';
    c += 25; // Increase ASCII code on a 25
    std::cout << c << "\n"; // Z

    // String concatenation:
    {
        std::string a = "Hello, ";
        std::string b = "world!\n";
        std::string c = a + b; // Hello, world!
    }
    

    // Automatical variable initialization:
    {
        auto x = 42;        // int
        auto pi = 3.14159;  // double
    }

}

void DoubleConversion(){
    double delta = 1e-5; // like as 0.00001

    double x = 0.1, y = 0.2;
    double sum = x + y;

    if (std::abs(sum - 0.3) < delta){ // numb as abs comparsion with delta = 1e-5
        std::cout << "EQUAL ";
    } else {
        std::cout << "NOT EQUAL ";
    }

    std::cout << sum << "\n";
}

void Ifelseprogramm(bool is = true){
    if (is){
        int64_t a, b;
        char operation;
        std::cin >> a >> operation >> b;

        int64_t result = 0;
        if (operation == '+') {
            result = a + b;
        } else if (operation == '-'){
            result = a - b;
        } else if (operation == '*'){
            result = a * b;
        } else if (operation == '/' || operation == ':'){
            result = a / b;
        } else if (operation == '%') {
            result = a % b;
        }

        std::cout << result << "\n";
    }
}

void SwithCaseProgramm(bool is = true){
    if (is){
        int64_t a, b;
        char operation;
        std::cin >> a >> operation >> b;

        int64_t result;
        switch (operation) {
            case '+':
                result = a + b;
                break;
            case '-':
                result = a - b;
                break;
            case '*':
                result = a * b;
                break;
            case '/':
            case ':':
                result = a / b;
                break;
            case '%':
                result = a % b;
                break;
            
            default:
                result = 0;
        }

        std::cout << result << "\n";
    }
}

void GoToProgram(bool is = true){
    if (is){
        again:             // Это метка, произвольное имя с двоеточием

        std::cout << "How old are you?\n";
        int age;
        std::cin >> age;

        if (age < 0 || age >= 128) {
            std::cout << "Wrong age...\n";
            goto again;                    // Безусловный переход на метку
        }

        std::cout << "Your age is " << age << ".\n";
    }
}

void Cycles(bool is = true){
    if (is){

        // While cycle
        {
            std::cout << "While, Table quadras of first 10 number" << "\n";
            int n = 1;
            while (n <= 10) {
                std::cout << n << "\t" << n * n << "\n";
                ++n;
            }
        }
        // Do-While cycle
        {
            std::cout << "Do-While, Table quadras of first 10 number" << "\n";
            int n = 1;
            do {
                std::cout << n << "\t" << n * n << "\n";
                ++n;
            } while (n <= 10);
        }
        // For cycle
        {
            std::cout << "For, Table quadras of first 10 number" << "\n";
            for (int i = 1; i <= 10; i++){
                std::cout << i << "\t" << i * i << "\n";
            }
        }
        // range-based for cycle
        {
            std::string line;
            std::getline(std::cin, line);
            for (char symbol : line) {
                std::cout << symbol << "\t" << static_cast<int>(symbol) << "\n";
            }
        }
    }
}

void ReadingInFile(bool is = true){
    if (is){
        std::string word, text;
        while (std::cin >> word){
            text += word + " ";
        }
        std::cout << text;
    }
}

void CyclesAndIfConstructions(){
    
    // Use if-else constructions for realise this programm
    Ifelseprogramm(false);
    // Use switch-case construction for realise same too program
    SwithCaseProgramm(false);
    // There is works as the same too, but writed defference

    // goto operation:
    GoToProgram(false);

    // Any cycles
    Cycles(false);

    // break and continue operators
    while (true){
        // ...
        if (true){
            break; // exit of infinity cycle
        }
    }

    ReadingInFile(false);

    double res;
    float d = 0.25;
    res = 0.06152234375*d + 0.234375*d + 0.4833984375*d + 0.75*d + 0.9521484375*d + 0.984375*d + 0.7177734375*d;
    std::cout << res;


}

int main(){
    std::cout << "Hello world!\n"; /* Cout is a character output*/
    /* \n is a code: 0A or 0D 0A*/
    // Hello();
    // Datatypes();
    // DoubleConversion();
    CyclesAndIfConstructions();
}

