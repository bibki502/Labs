#include <iostream>
#include <vector>
#include <string>
#include "ProcessList.h"
using namespace std;

int main(){

    //1.Создание списка процессов: Инициализация объекта класса ProcessList
    cout<<"------1.Creating a list of PCB------"<<endl;
    ProcessList PCBList;
    cout<<"ProcessList PCBList"<<endl;

    //2. Добавление элементов
    cout<<"-----2.Adding PCB------"<<endl;
    PCB pcb1(101, "Telegram", "Running", 200, {1,2,3,4});
    PCB pcb2(303, "Browser", "Stopped", 75, {10,20,30,40});
    PCB pcb3(202, "Game", "Waiting", 100, {15,25,35,50});

    //Вставка нескольких процессов в список
    cout<<"Add PCB1: ";
    if (PCBList.insert(pcb1)) cout<<"successfully"<<endl;

    cout<<"Add PCB2: ";
    if (PCBList.insert(pcb2)) cout<<"successfully"<<endl;
    
    cout<<"Add PCB3: ";
    if (PCBList.insert(pcb3)) cout<<"successfully"<<endl;

    //3. Вывод списка: Печать списка после вставок для проверки корректности добавления
    cout<<"------3.List after insertions------"<<endl;
    PCBList.printList();
    cout<<endl;

    //4. Удаление элементов: Удаление одного или нескольких процессов из списка
    cout<<"------4.Remove items----"<<endl;
    cout<<"Remove PCB ID=303"<<endl;
    if (PCBList.remove(303)) cout<<"successfully"<<endl;

    //5. Вывод списка: Печать списка после удалений для демонстрации изменений
    cout<<"------5.List after deletions------"<<endl;
    PCBList.printList();
    cout<<endl;

    //6. Попытки неудачной операции: Демонстрация попыток вставки существующих и удаления несуществующих элементов
    cout<<"------6.Failed operation attempts------"<<endl;
    PCB pcb4(202, "Game", "Waiting", 100, {15,25,35,50});
    if (!PCBList.insert(pcb4)){
        cout<<"Attempt to insert existing elements"<<endl;
    }

    if (!PCBList.remove(404)){
        cout<<"Attempt to delete non-existent elements"<<endl;
    }

    //7. Финальный вывод списка: Печать конечного состояния списка
    cout<<"------7.Final list output------"<<endl;
    PCBList.printList();

    return 0;

}