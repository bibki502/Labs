#include <iostream>
#include <vector>
#include <string>
using namespace std;

//Шаблонная структура GroupInfo
template <typename KeyType, typename ElemType, typename ValueType>
struct GroupInfo 
{
    KeyType key; //ключ группы
    int count; //количество элементов в группе
    ElemType minElem; //минимальный элемент группы
    ElemType maxElem; //максимальный элемент группы
    ValueType sum; //сумма значений valueFunc(x) по всем элементам группы
    double avg; //среднее значение valueFunc(x) по группе
};

//Шаблонная функция поиска существующей группы по ключу
template <typename KeyType, typename ElemType, typename ValueType>
int FindGroup(vector<GroupInfo<KeyType, ElemType, ValueType>>& groups, KeyType key) 
{
    for (int i=0; i<groups.size(); i++){
        if (groups[i].key==key){
            return i;
        }
        
    }
    return -1;
}

//Шаблонная функция groupStatus
template <typename T, typename KeyFunc, typename ValueFunc>
auto groupStatus(T arr[], int n, KeyFunc keyFunc, ValueFunc valueFunc)
{
    //Определение типа через decltupe
    using KeyType=decltype(keyFunc(arr[0]));
    using ValueType=decltype(valueFunc(arr[0]));

    //Создание пустого вектора с группами
    vector<GroupInfo<KeyType, T, ValueType>> groups;
    
    //Проход по всему массиву
    for(int i=0; i<n; i++)
    {
        T cur=arr[i];

        //Получение ключа и значения
        KeyType key=keyFunc(cur);
        ValueType value=valueFunc(cur);

        //Поиск группы с таким ключом
        int groupIndex=FindGroup(groups,key);

        if (groupIndex==-1) {

            //Создание новой группы
            GroupInfo <KeyType, T, ValueType> newGroup;
            newGroup.key=key;
            newGroup.count=1;
            newGroup.minElem=cur;
            newGroup.maxElem=cur;
            newGroup.sum=value;
            newGroup.avg=0.0;

            groups.push_back(newGroup);

        } else {

            //Обновление существующей группы
            auto& group=groups[groupIndex];

            group.count++;

            if (cur<group.minElem){
                group.minElem=cur;
            }

            if (cur>group.maxElem){
                group.maxElem=cur;
            }

            group.sum=group.sum+value;

        }

    }

    //Вычисление среднего значения
    for(int i = 0; i < groups.size(); i++) {

        //Преобразование sum к double перед делением с помощью static_cast<double>
        groups[i].avg=static_cast<double>(groups[i].sum)/groups[i].count;
    }

    return groups;

}

//Функия вывода
template<typename KeyType, typename ElemType, typename ValueType>
void printGroups(const vector<GroupInfo<KeyType, ElemType, ValueType>>& groups) {
    
    // Проход по всем группам
    for (int i = 0; i < groups.size(); i++) {
        
        cout << "Group with key: " << groups[i].key <<endl;
        cout << "Number of elements: " << groups[i].count <<endl;
        cout << "Min element: " << groups[i].minElem <<endl;
        cout << "Max element: " << groups[i].maxElem <<endl;
        cout << "Sum: " << groups[i].sum <<endl;
        cout << "Average value: " << groups[i].avg <<endl;
        cout <<endl;
    }
}


int main(){
    
    //Пример 1. Массив int
    cout<<"------Array int------"<<endl;

    int intArr[]={234, 174, 783, 192, 12};
    int intSize=sizeof(intArr)/sizeof(intArr[0]);

    cout << "Array: ";
    for (int i = 0; i < intSize; i++) {
        cout << intArr[i] << " ";
    }
    cout <<endl;

    //Лямбда для ключа (последняя цифра)
    auto intKeyFunc=[] (int x) {return x%10;};

    //Лямбда для значения (само число)
    auto intValueFunc=[] (int x) {return x;};

    auto intGroups = groupStatus(intArr, intSize, intKeyFunc, intValueFunc);
    printGroups(intGroups);

    //Пример 2. Массив double
    double doubleArr[] = {-5.5, 3.14, 15.7, 0.0, 8.2, -1.1, 20.5, 7.0};
    int doubleSize = sizeof(doubleArr) / sizeof(doubleArr[0]);

    cout << "Array: ";
    for (int i = 0; i < doubleSize; i++) {
        cout << doubleArr[i] << " ";
    }
    cout <<endl;

    ////Лямбда для ключа (интервал)
    auto doubleKeyFunc = [](double x) {
        if (x < 0) return 0;
        else if (x <= 10) return 1;
        else return 2;
    };

    //Лямбда для значения (само число)
    auto doubleValueFunc = [](double x) {return x;};
    auto doubleGroups = groupStatus(doubleArr, doubleSize, doubleKeyFunc, doubleValueFunc);
    printGroups(doubleGroups);

    //Пример 3. Массив string
    string stringArr[] = {"apple", "banana", "apricot", "berry", "avocado", "cherry"};
    int stringSize = sizeof(stringArr) / sizeof(stringArr[0]);

    cout << "Array: ";
    for (int i = 0; i < stringSize; i++) {
        cout << "\"" <<stringArr[i] << "\" ";
    }
    cout <<endl;

    // Лямбда для ключа (первая буква (char))
    auto stringKeyFunc = [](const string& s) {
        return s.empty() ? ' ' : s[0];  // если строка пустая, возвращается пробел
    };

    // Лямбда для значения (длина строки (size_t))
    auto stringValueFunc = [](const string& s) {
        return s.length();
    };

    auto stringGroups = groupStatus(stringArr, stringSize, stringKeyFunc, stringValueFunc);
    printGroups(stringGroups);

    return 0;

}