#ifndef PROCESSLIST_H
#define PROCESSLIST_H

#include <string>
#include "PCB.h"
#include "ListNode.h"
using namespace std;

class ProcessList{
    private:
        ListNode* head;
    public:
        //Конструктор
        ProcessList(): head(nullptr){};
        //Деструктор
        ~ProcessList();
    
        bool insert(const PCB& newPCB);
        bool remove(int pid);
        void printList();

        //Геттер метод 
        ListNode* getHead(){
            return head;
        };
};
#endif