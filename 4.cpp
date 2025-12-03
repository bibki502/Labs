#include <iostream>
#include <windows.h>
#include <iomanip>
using namespace std;

//ввод массива
void inputData(float** data, int d, int h){
    cout<<"Введите значения\n";
    for (int i=0; i<d; i++) {
        cout<<"День"<<i+1<<": ";
        for (int j=0; j<h; j++){
            cin>>*(*(data+i)+j);
        }
    }
}

//вычисление среднего значения
float dayAverage(float* d, int h){
    float sum=0;

    for (int i=0; i<h; i++) {
        sum=sum+*(d+i);
    }

    return sum/h;
}

//нахождение общей средней температуры
float overallAverage(float** data, int d, int h){
    float total=0;

    for (int i=0; i<d; i++) {
        total=total+dayAverage(*(data+i),h);
    }

    return total/d;
}



//вывод тёплых дней
void showHotDays(float** data, int d, int h){
    float overall=overallAverage(data,d,h);
    cout<<"\nТёплые дни:\n";

    for (int i=0; i<d; i++) {
        float dayAvg=dayAverage(*(data+i),h);

        if (dayAvg>overall) {
            cout<<"День"<<i+1<<" (среднее="<<dayAvg<<")\n";
        }
    }

}

int main()
{
    while (true) {
        SetConsoleOutputCP(CP_UTF8);
        SetConsoleCP(CP_UTF8);

        int d;
        int h;

        cout<<"\n\n=== Анализ сенсора ===\n";

        cout << "Введите количество дней: ";
        cin >> d;
        cout << "Введите количество измерений в дне: ";
        cin >> h;

        if (d<0 || h<0) {
            cout<<"Выход из пограммы\n";
            break;
        }

        if (d==0 || h==0){
            cout<<"Значений нет\n";
            continue;
        }

        float** data= new float* [d];
        for (int i=0; i<d; i++){
            *(data+i)=new float[h];
        }

        inputData(data, d, h);

        //проверка фун-ии, вывод
        cout<<"Вы ввели значения:";
        for (int i=0; i<d; i++) {
            cout<<"\nДень"<<i+1<<": ";
            for (int j=0; j<h; j++){
                cout<<*(*(data+i)+j)<<" ";
            }
        }

        //нахождение обшей средней температуры
        float avrg=overallAverage(data, d, h);
        cout<<"\n\nОбщая средняя температура: "<<avrg;

        //вывод тёплых дней
        showHotDays(data, d, h);


        //освобождение памяти
        for (int i=0; i<d;i++){
            delete[] *(data+i);
        }
        delete [] data;
        data=nullptr;

    }

    return 0;

}
