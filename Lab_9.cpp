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
        } else {
            return -1;
        }
    }
}

//Шаблонная функция groupStatus
template <typename T, typename KeyFunc, typename ValueFunc>
auto groupStatus(T arr[], int n, KeyFunc keyFunc, ValueFunc valueFunc)
{
    //Определение типа через decltupe
    using KeyType=decltype(keyFunc(arr[0]));
    using ValueType=decltype(valueFunc(arr[0]));

    // Cоздаём пустой вектор с группами
    vector<GroupInfo<KeyType, T, ValueType>> groups;
    
    //Проходимся по всему массиву
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


