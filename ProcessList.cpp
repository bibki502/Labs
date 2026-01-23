#include "ProcessList.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

//Деструктор - очищение всей памяти 
ProcessList::~ProcessList(){
    ListNode* currentNode= head;

    while (currentNode!=nullptr)
    {
        ListNode* next=currentNode->getNext();
        delete currentNode;
        currentNode=next;
    }
    
}

bool ProcessList::insert(const PCB& newPCB){
    ListNode* newNode=new ListNode(newPCB); //создаём новый узел

    //Проверка на существующий узел
    ListNode* current=head;
    while (current!=nullptr)
    {
        if(current->getData().processID==newPCB.processID){
            cout<<"Attempt to insert existing elements"<<endl;
            return false;
        }

        current=current->getNext();
    }
    

    //Если список пуст или вставляем в наало
    if(head==nullptr || newPCB.processID<head->getData().processID){ 
       newNode->setNext(head);
       head=newNode;
       cout<<"PCB"<<newPCB.processID<<" added"<<endl;
       return true;
    }
    
    //Ищем место для вставки нового узла
    ListNode* currentNode=head;
    while (currentNode->getNext()!=nullptr && currentNode->getNext()->getData().processID<newPCB.processID)
    {
        currentNode=currentNode->getNext();
    }

    //Вставляем новый узел (current)
    newNode->setNext(currentNode->getNext()); //указатель в узле newNode меняем на указатель следующего
    currentNode->setNext(newNode); //указатель в currentNode меняем на указатель на newNode 

    cout<<"PCB "<<newPCB.processID<<" added"<<endl;
    return true;
    
}

bool ProcessList::remove(int pid){
    //Если список пустой
    if (head==nullptr){
        cout<<"The List is empty"<<endl;
        return false;
    }

    //Если удаляем первый элемент
    if(head->getData().processID==pid){
        ListNode* remoteNode=head;
        head=head->getNext();
        delete remoteNode;
        cout<<"PCB"<<pid<<" was deleted"<<endl;
        return true;
    }

    //Ищем узел, который нужно удалить
    ListNode* current=head;
    while (current->getNext()!=nullptr && current->getNext()->getData().processID!=pid)
    {
        current=current->getNext();
    }

    //Если не нашли
    if (current->getNext()==nullptr)
    {
        cout<<"PCB "<<pid<<" was not found"<<endl;
        return false;
    }

    //Если нашли, удаляем
    ListNode* toDelete=current->getNext();
    current->setNext(toDelete->getNext());
    delete toDelete;

    cout<<"PCB"<<pid<<"was deleted"<<endl;
    return true;    
}

void ProcessList::printList(){
    if(head==nullptr){
        cout<<"List is empty"<<endl;
    }

    cout<<"------PCB List------"<<endl;

    ListNode* current=head;

    while (current!=nullptr)
    {
        cout<<"ID: "<<current->getData().processID<<endl;
        cout<<"Name: "<<current->getData().processName<<endl;
        cout<<"Status: "<<current->getData().processStatus<<endl;
        cout<<"Command counter: "<<current->getData().commandCounter<<endl;

        cout<<"Registers={";
        for (int i = 0; i < current->getData().cpuRegisters.size(); i++)
        {
            cout<<current->getData().cpuRegisters[i]<<", ";
        }

        cout<<"}"<<endl;

        current=current->getNext();
    }
    
    cout<<"-----------"<<endl;
}