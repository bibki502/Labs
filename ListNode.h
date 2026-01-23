#ifndef LISTNODE_H
#define LISTNODE_H

#include "PCB.h"
#include <string>
using namespace std;

class ListNode {
    private:
        PCB data; //текущий PCB
        ListNode* next; //указатель на следующий  PCB
    public:
        ListNode(const PCB& pcbData, ListNode* nextNode=nullptr){
            data=pcbData;
            next=nextNode;
        }
        
        //Геттеры
        PCB getData() const{
            return data;
        }

        ListNode* getNext() const{
            return next;
        }

        //Функция для установки нового значения 
        void setNext(ListNode* nextNode) { 
            next = nextNode; 
        }
};
#endif