#ifndef _GEN_STACK_HPP_
#define _GEN_STACK_HPP_

#include <iostream>
#include <string>

using namespace std;

template <class T>
class GenStack {
    private:
        int mSize;
        unsigned int numElements;
        unsigned int top;
        T *myStack;
        

    public:
        GenStack();
        GenStack(int maxSize);
        ~GenStack();

        bool push(T);
        T pop();
        T stackTop();

        bool isEmpty();
        bool isFull();
        int stackCount();
        unsigned int getSize();
        void resize();
        void displayStack();
};

template <class T>
GenStack<T>::GenStack() {
    myStack = new T[128];
    mSize = 128;
    numElements = 0;
    top = -1;
} 

template <class T>
GenStack<T>::GenStack(int maxSize) {
    myStack = new T[maxSize];
    mSize = maxSize;
    numElements = 0;
    top = -1;
} 

template <class T>
GenStack<T>::~GenStack() {
    delete myStack;
}

template <class T>
bool GenStack<T>::push(T item) {
    if (isFull()) {
        resize();
    }
    myStack[++top] = item;
    numElements++;

    return true;
}

template <class T>
void GenStack<T>::resize() {
    size_t newSize = mSize * 2;
    T* tempArray = new T[newSize];

    for(int i = 0; i < mSize; ++i) {
        tempArray[i] = myStack[i];
    }

    mSize = newSize;
    delete [] myStack;
    myStack = tempArray;
}

template <class T>
T GenStack<T>::pop() {
    if(isEmpty()){
        throw "Empty Stack Exception";
        exit(1);
    }
    numElements--;
    return myStack[top--];
}

template <class T>
bool GenStack<T>::isEmpty() {
    return numElements == 0;
}

template <class T>
bool GenStack<T>::isFull() {
    return numElements == mSize;
}

template <class T>
T GenStack<T>::stackTop() {
    if(isEmpty()) {
        return '\0';
    }
    return myStack[top];
}

template <class T>
unsigned int GenStack<T>::getSize() {
    return numElements;
}

template <class T>
void GenStack<T>::displayStack() {
    if (isEmpty()) {
        cout << "Stack is Empty\n";
    } else {
        cout << "Stack Size: " << numElements << endl;
        cout << "Stack top: " << myStack[top] << endl;
        for (int i = 0; i < numElements; ++i) {
            cout << "S[" << i << "]: " << myStack[i];
            if (i != numElements - 1) {
                cout << " | ";
            }
        }
        cout << endl;
    }
}

#endif