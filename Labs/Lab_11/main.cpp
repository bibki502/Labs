#include<iostream>
#include<vector>
#include<list>
#include<deque>
#include<string>
#include<iterator>
#include<fstream>
#include<algorithm> //содержит функции для работы с последовательностями
#include<numeric> //для суммирования всех чисел 

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");

    //1.Оптимизация списка товаров:
    cout<<"=====PRICES====="<<endl;
    vector<int> prices;
    int N;

    cout<<"How many prices do you want to enter?"<<endl;
    cin>> N;

    cout<<"Enter prices: "<<endl;
    for (int i=0; i<N; i++) {
        int ent_price;
        cin>> ent_price;
        prices.push_back(ent_price);
    }

    sort(prices.begin(), prices.end(), greater<int>()); //сортировка по убыванию

    //среднее значение
    float sum=accumulate(prices.begin(), prices.end(), 0.0);
    float average;
    if (prices.size()>0){
        average=sum/prices.size();
    } else {
        average=0;
    }

    cout<<"Average="<<average<<endl;

    //удаление цен, ниже среднего

    for (auto it=prices.begin(); it!=prices.end();) {
        if (*it<average) {
            it=prices.erase(it);
        } else{
            it++;
        }
    }

    for (auto it=prices.begin(); it!=prices.end();) {
        cout<<*it<<" "; 
        it++;   
    }

    cout<<endl;

    //2.Управление инвентарём
    cout<<"=====INVENTORY====="<<endl;
    list<string> inventory;
    string command;
    string item;

    cout<<"Commands: add [item], del [item], show the list, exit. Enter your commnd"<< endl;

    while (true)
    {
        cin>>command;

        if (command=="add") {
            cin>>item;
            auto it=back_inserter(inventory);
            *it=item;
        } else if (command=="del") {
            cin>>item;
            auto it=find(inventory.begin(), inventory.end(), item);

            if (it!=inventory.end()){
                inventory.erase(it);
            } else {
                cout<<"There is no such item"<<endl;
            }


        } else if (command=="show"){
            for (auto it=inventory.begin(); it!=inventory.end(); it++) {
                cout<<*it<<endl;
            }
        } else if (command=="exit"){
            break;
        }
    }
    
    //3.Редактор журнала

    list<string> journal;
    string line;
    string filename= "journal.txt";

    //загрузка файла
    ifstream inFile(filename);
    if (inFile.is_open()) {
        while (getline(inFile, line)){
            journal.push_back(line);
        }
        inFile.close();
    } else {
        cout<<"No file"<<endl;
    }

    //редактирование файла
    int choice=0;
    while (choice != 4) {
        cout << "\n=====MAGAZINE EDITOR=====" << endl;
        cout << "1. Show all entries" << endl;
        cout << "2. Add new entry" << endl;
        cout << "3. Edit an existing line" << endl;
        cout << "4. Save and exit" << endl;
        cout << "Select action: ";
        cin >> choice;
        cin.ignore(); //очистка буфера после ввода числа

        if (choice == 1) {
            int i = 1;
            for (auto it = journal.begin(); it != journal.end(); ++it) {
                cout << i++ << ". " << *it << endl;
            }
        } 
        else if (choice == 2) {
            cout << "Enter post text: ";
            getline(cin, line);
            journal.push_back(line);
        } 
        else if (choice == 3) {
            int lineNum;
            cout << "Enter the line number to edit: ";
            cin >> lineNum;
            cin.ignore();

            auto it = journal.begin();
            advance(it, lineNum - 1); //сдвиг итератора на нужную позицию

            if (it != journal.end()) {
                cout << "Previous text: " << *it << endl;
                cout << "Enter new text: ";
                getline(cin, line);
                *it = line;
            }
        }
    }

    //сохранение файла
    ofstream outFile(filename);
    for (auto it = journal.begin(); it != journal.end(); ++it) {
        outFile << *it << endl;
    }
    outFile.close();

    //4. Синхронизация данных

    vector<int> vec={17, 8, 67, 76};
    deque<int> deq;
    cout<<"=====Copy====="<<endl;
    cout<<"The vector:"<<endl;
    for (auto it=vec.begin(); it!=vec.end(); it++) {
        cout<<*it<<" ";
    }
    cout<<endl;

    cout<<"Copy the vector to the queue"<<endl;
    copy (vec.begin(), vec.end(), back_inserter(deq)); //копирование вектора в очередь

    cout<<"The queue:"<<endl;
    for (auto it = deq.begin(); it != deq.end(); ++it) {
        cout<<*it<<" ";
    }

    cout<<endl;

    cout<<"Let's add numbers to the queue:"<<endl;
    deq.push_front(89);
    deq.push_back(77);
    for (auto it = deq.begin(); it != deq.end(); ++it) {
        cout<<*it<<" ";
    }
    cout<<endl;

    vec.clear();
    cout<<"Copy the queue to the vector"<<endl;

    copy(deq.begin(), deq.end(), back_inserter(vec)); //копирование очереди в вектор

    cout<<"The vector:"<<endl;
    for (auto it=vec.begin(); it!=vec.end(); it++) {
        cout<<*it<<" ";
    }

    cout<<endl;

    //5.Реверсивное отображение данных
    //для выполнения этого задания взяла список инвентаря из 4 задания
    cout<<"=====Reversible data display====="<<endl;
    cout<<"Inventory:"<<endl;
    for (auto it=inventory.begin(); it!=inventory.end(); it++) {
        cout<<*it<<" ";
    }
    cout<<endl;
    cout<<"Output in reverse order:"<<endl;

    for(auto it=inventory.rbegin(); it!=inventory.rend(); it++){
        cout<<*it<<" ";
    }
    cout<<endl;


    return 0;

}
