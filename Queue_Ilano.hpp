/*
Author: Gabriel Ilano
Date: 2/21/24
Description: Queue implementation
*/

#ifndef QUEUE_ILANO_HPP
#define QUEUE_ILANO_HPP
#include <stdexcept>

template<typename T>
class QNode {
private:
    T item;
    QNode* next;

public:
    T getItem() { //getter for item
        return item; 
    }
    
    QNode* getNext() {  //getter for next
        return next; 
    }
    
    void setNext(QNode* nextNode) { //setter for next
        next = nextNode; 
    }

    QNode(T newItem) { //constructor
        item = newItem;
        next = nullptr;
    }
};

template<typename T>
class Queue {
private:
    int count;
    QNode<T>* head; // Corrected to be a pointer to QNode<T>

public:
    Queue() { //constructor
        count = 0;
        head = nullptr;
    }

    ~Queue() { //destructor
        empty();
    }

    void enqueue(T item) { //adds item to tail of queue
        QNode<T>* newNode = new QNode<T>(item);
        if (head == nullptr) { //if first item in queue
            head = newNode;
        } else {
            QNode<T>* curr = head;
            while (curr->getNext() != nullptr) { //iterates to end of list
                curr = curr->getNext();
            }
            curr->setNext(newNode); //sets at end of list
        }
        count++;
    }

    void dequeue() { //removes item at front of queue
        if (head != nullptr) {
            QNode<T>* temp = head;
            head = head->getNext();
            delete temp;
            count--;
        }
    }

    T front() { //returns item at front of queue
        if(head != nullptr) { // Check if head is not null before accessing
            return head->getItem();
        }
        // Handle the case when the queue is empty. It's up to you to decide how to handle this.
        throw std::runtime_error("Queue is empty");
        return T(); //return default constructor
    }

    int size() { //returns number of items in queue
        return count;
    }

    void empty() { //deletes all items within queue
        while (head != nullptr) {//goes until end of queue
            QNode<T>* temp = head;
            head = head->getNext(); //goes to next item
            delete temp;
        }
        count = 0; 
    }

    bool isEmpty() { //returns true if queue is empty
        return count == 0;
    }
};

#endif
