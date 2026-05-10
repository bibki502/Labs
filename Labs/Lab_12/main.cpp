#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

#include "Reverse_Iterator_1.h"
#include "Time_iterator_2.h"
#include "Filtering_iterator_3.h"
#include "Transformation_iterator_4.h"
#include "Multi-iterator_5.h"

using namespace std;

int main() {
    // 1.Пользовательский обратный итератор для обхода истории изменений
    cout << "=== 1. Reverse Iterator ===" <<endl;
    vector<string> versions = {"v1.0: Start", "v1.1: Fix", "v2.0: Release"};
    
    MyReverseIterator<vector<string>::iterator> rev_it(versions.end());
    MyReverseIterator<vector<string>::iterator> rev_end(versions.begin());

    for (; rev_it != rev_end; ++rev_it) {
        cout << "History: " << *rev_it <<endl;
    }
    cout <<endl;


    //2.Итератор временного интервала
    cout << "=== 2. Interval Iterator ===" << endl;
    std::vector<int> hours = {1, 2, 7, 14, 19, 18, 23};
    
    //ищем часы в интервале от 1 до 5
    IntervalIterator<std::vector<int>::iterator, int> int_it(hours.begin(), hours.end(), 1, 5);
    IntervalIterator<std::vector<int>::iterator, int> int_end(hours.end(), hours.end(), 1, 5);

    for (; int_it != int_end; ++int_it) {
        cout << "Log event at: " << *int_it << ":00" << endl;
    }
    cout <<endl;


    //3.Итератор фильтрации по пользовательскому критерию:
    cout << "=== 3. Filter Iterator ===" <<endl;
    struct Task {string name; int priority; };
    vector<Task> tasks = {{"Lab 11", 5}, {"Lab 12", 10}, {"Coffee", 1}, {"Exam", 9}};
    
    auto isCritical = [](const Task& t) { return t.priority >= 9; };
    
    FilterIterator<vector<Task>::iterator, Task> filt_it(tasks.begin(), tasks.end(), isCritical);
    FilterIterator<vector<Task>::iterator, Task> filt_end(tasks.end(), tasks.end(), isCritical);

    for (; filt_it != filt_end; ++filt_it) {
        cout << "Critical Task: " << (*filt_it).name << " (P: " << (*filt_it).priority << ")" <<endl;
    }
    cout <<endl;


    //4.Итератор трансформации данных
    cout << "=== 4. Transform Iterator ===" <<endl;
    vector<double> prices_rub = {1000.0, 2500.0, 5000.0};
    double usd_rate = 92.5;
    
    auto toUsd = [usd_rate](const double& rub) { return rub / usd_rate; };
    
    TransformIterator<vector<double>::iterator, double, double> trans_it(prices_rub.begin(), toUsd);
    TransformIterator<vector<double>::iterator, double, double> trans_end(prices_rub.end(), toUsd);

    cout <<fixed <<setprecision(2);
    for (; trans_it != trans_end; ++trans_it) {
        cout << "Price: $" << *trans_it <<endl;
    }
    cout <<endl;


    //5.Мульти-итератор для объединения данных из различных источников
    cout << "=== 5: Multi Iterator ===" <<endl;
    vector<string> emails = {"sasha@hse.ru"};
    vector<string> phones = {"+7-999-000"};

    MultiIterator<vector<string>::iterator> multi_it(emails.begin(), emails.end(), phones.begin(), phones.end(), true);
    MultiIterator<vector<string>::iterator> multi_end(emails.begin(), emails.end(), phones.begin(), phones.end(), false);

    for (; multi_it != multi_end; ++multi_it) {
        cout << "Contact: " << *multi_it <<endl;
    }

    return 0;
}