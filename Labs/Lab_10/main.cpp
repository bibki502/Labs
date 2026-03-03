#include <vector>
#include <string>
#include <functional>
#include <iostream>
#include "MyPipeline.h"
using namespace std;

//Функции-шаги для чисел
int addFive(int x){return x+5;}
int multiplyByTwo (int x) {return x*2;}
int subtractThree (int x) {return x-3;}

//Функции-шаги для строк
string removeLast(string s) {
    if (!s.empty()) {
        s.pop_back(); // Удаляем последний символ
    }
    return s;
}
string duplicate(string s) { return s + s; }


int main(){

    //6.1. Демонстрация MyPipeline<int>
    cout<<"===  MyPipeline<int>  ==="<<endl;
    try
    {
        MyPipeline<int> intPipeline;
        //добавить минимум 3 шага
        intPipeline.addStep("Add 5", addFive);
        intPipeline.addStep("Multiply by 2", multiplyByTwo);
        intPipeline.addStep("Subtract 3", subtractThree);

        //вывести intPipeline через cout
        cout<<intPipeline<<endl;

        //вывести результат run для одного входного значения
        int value=5;
        cout<<"Value: "<<value<<endl;
        cout<<"Result: "<<intPipeline.run(value)<<endl;

        //вывести все элементы trace для того же входного значения
        vector<int> trace=intPipeline.trace(value);
        cout<<"Trace: ";
        for (int i = 0; i <trace.size(); i++) {
            int val = trace[i];
            cout << val << " ";
        }
        cout << endl;
    }
    catch(const exception& e)
    {
        cerr << e.what() << '\n';
    }
    
    //6.2. Демонстрация MyPipeline<std::string>
    cout<<"\n===  MyPipeline<string>  ==="<<endl;
    
    try
    {
        MyPipeline<string> strPipeline;
        //добавить минимум 3 шага
        strPipeline.addStep( "Remove last", removeLast);
        strPipeline.addStep("Double", duplicate);
        strPipeline.addStep( "Remove last", removeLast);

        //вывести результат run для одной входной строки
        string str="abcd";
        cout<<"String: "<<str<<endl;
        cout<<"Result: "<<strPipeline.run(str)<<endl;
    }
    catch(const exception& e)
    {
        std::cerr << e.what() << endl;
    }

    //6.3. Демонстрация исключения
    cout<<"\n===  Exceptions  ==="<<endl;

    try
    {
        MyPipeline<int> errorPipe;
        errorPipe.removeStep(100);
    }
    catch(const out_of_range& e)
    {
        cout<<"Caught expected error: " << e.what() << endl;
    }

    return 0;
}

