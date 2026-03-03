#ifndef PCB_H
#define PCB_H

#include <string>
#include <vector>
using namespace std;

struct PCB
{
    int processID; 
    string processName;
    string processStatus; //Статус процесса- Running, Waiting, Stopped
    int commandCounter; //Счетчик команд, указывающий на следующую исполняемую команду
    vector<int> cpuRegisters;

    //Конструктор по умолчанию (для поля PCB data в классе ListNode)
    PCB() : processID(0), processName(""), processStatus("Waiting"),
            commandCounter(0), cpuRegisters({0, 0, 0, 0}) {}

    //Конструктор с параметрами
    PCB(int id, string name, string status = "Waiting", int counter = 0, vector<int> registers = {0, 0, 0, 0}){
        processID=id;
        processName=name;
        processStatus=status;
        commandCounter=counter;
        cpuRegisters=registers;
    }
};
#endif