#ifndef QUEUE_INT_H
#define QUEUE_INT_H
#define MAX_SIZE 20
#include <Arduino.h>
#include "GPIO.h"

class QueueInt {
private:
  int front;
  int rear;

  int arr[MAX_SIZE];

public:
    QueueInt() : front(-1), rear(-1) {}
    
    int doesExist(int element) {
        if (isEmpty()) {
            return -1;
        }

        for (int i = front; i <= rear; i++) {
            if (arr[i] == element) {
                return i;
            }
        }
        return -1;
    }

    int getElement(int index) {
        return arr[index];
    }


    bool isEmpty() {
        return (front == -1 || front > rear);
    }

    bool isFull() {
        return (rear == MAX_SIZE - 1);
    }

    int getHead() {
      return arr[front];
    }

    int itemCount() {
      if (front == -1) { // queue is empty
        return 0;
      }
      return rear - front + 1;
    }

    void enqueue(int val) {
        if (isFull()) {
            //cout << "Queue is full" << endl;
            return;
        }
        if (isEmpty())
            front = 0;
        arr[++rear] = val;
    }

    int dequeue() {
        if (isEmpty()) {
            //cout << "Queue is empty" << endl;
            return -1;
        }
        int val = arr[front++];
        if (front > rear)  // Reset queue after last element is dequeued
            front = rear = -1;
        return val;
    }

    // NOT TESTED
    String toString() {
        String result = "";
        if (isEmpty()) {
            return "/EMPTY/";
        }
        for (int c=front; c <= rear; c++) {
            result += String(arr[c])+", ";
        }
        return result;
    }
};

#endif