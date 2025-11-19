#include <iostream>
#include <windows.h>
using namespace std;

//ввод массива
void inputData(float* p, int n){
    cout<<"Введите значения: ";
    for (int i=0; i<n; i++) {
        cin>>*(p+i);
    }
}

//вычисление среднего значения
float average(const float* p, int n){
    float sum=0;

    for (int i=0; i<n; i++) {
        sum=sum+*(p+i);
    }

    return sum/n;
}

//нахождение минимального значения
float minValue(const float* p, int n){
    float min=*p;
    for(int i=0; i<n; i++){
        if (*(p+i)<min){
            min=*(p+i);
        }
    }

    return min;
}

//нахождение максимального значения
float maxValue(const float* p, int n){
    float max=*p;
    for(int i=0; i<n; i++){
        if (*(p+i)>max){
            max=*(p+i);
        }
    }

    return max;
}

//нахождение значения выыше срднего
float* filterAboveAverage(float* p, int n, int& newCount){
    //находим среднее значение
    float sum=0;

    for (int i=0; i<n; i++) {
        sum=sum+*(p+i);
    }

    //считаем сколько элементов в массиве выше срднего
    for (int i=0; i<n; i++){
        if (*(p+i)>(sum/n)){
            newCount++;
        }
    }

    //создаём новый отфильтрованный массив нужного размера
    float* filtered=new float[newCount];

    //копируем в новый массив значения выше среднего
    int j=0;
    for(int i=0; i<n; i++) {
        if (*(p+i)>(sum/n)){
            *(filtered+j++)=*(p+i);
        }
        
    }

    return filtered;

}

int main(){
    while (true) {
        SetConsoleOutputCP(CP_UTF8);
        SetConsoleCP(CP_UTF8);

        int n;

        cout<<"\n\n=== Анализ сенсора ===\n";

        cout << "Введите количество измерений: ";
        cin >> n;

        if (n<0) {
            cout<<"Выход из пограммы\n";
            break;
        }

        if (n==0){
            cout<<"Значений нет\n";
            continue;
        }

        float* data=new float[n];

        inputData(data, n);

        //проверка фун-ии, вывод
        cout<< "Вы ввели: ";

        for (int i=0; i<n; i++){
            cout<< *(data+i)<<" ";
        }   

        //находим среднее значение
        float avrg=average(data, n);
        cout<<"\n\nСреднее значение: "<<avrg;

        //находим минимальное значение
        float min=minValue(data,n); 
        cout<<"\nМинимальное значение: "<<min;

        //находим максимальное значение
        float max=maxValue(data,n); 
        cout<<"\nМаксимальное значение: "<<max;

        //выводим значения выше среднего
        int newCount=0;
        float* filtered=filterAboveAverage(data, n, newCount);
        cout<<"\n\nЗначения выше среднего: \n";
        for (int j=0; j<newCount; j++){
            cout<<*(filtered+j)<<" ";
        }


        //обнуление массива и указателя на него
        delete [] data;
        data=nullptr;

    }

    return 0;

}