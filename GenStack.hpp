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

/**************************
 * GenStack()
 * Default constructor
 **************************/
template <class T>
GenStack<T>::GenStack() {
    myStack = new T[128];
    mSize = 128;
    numElements = 0;
    top = -1;
} 

/**************************
 * GenStack(int maxSize)
 * Overloaded constructor
 * adds a max size
 **************************/
template <class T>
GenStack<T>::GenStack(int maxSize) {
    myStack = new T[maxSize];
    mSize = maxSize;
    numElements = 0;
    top = -1;
} 

/**************************
 * ~GenStack()
 * destructor deletes the stack
 **************************/
template <class T>
GenStack<T>::~GenStack() {
    delete myStack;
}

/**************************
 * push(T item)
 * adds the item with template T to 
 * the top of the stack (end of the array)
 **************************/
template <class T>
bool GenStack<T>::push(T item) {
    if (isFull()) {
        resize();
    }
    myStack[++top] = item;
    numElements++;

    return true;
}

/**************************
 * resize()
 * resizes the array when the 
 * stack is full
 **************************/
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

/**************************
 * pop()
 * returns the top value of the stack 
 * and removes the value from the stack
 **************************/
template <class T>
T GenStack<T>::pop() {
    if(isEmpty()){
        throw "Empty Stack Exception";
        exit(1);
    }
    numElements--;
    return myStack[top--];
}

/**************************
 * isEmpty()
 * checks if the stack is empty
 **************************/
template <class T>
bool GenStack<T>::isEmpty() {
    return numElements == 0;
}

template <class T>
bool GenStack<T>::isFull() {
    return numElements == mSize;
}

/**************************
 * stackTop()
 * returns 
 **************************/
template <class T>
T GenStack<T>::stackTop() {
    if(isEmpty()) {
        return '\0';
    }
    return myStack[top];
}

/**************************
 * getSize()
 * return the size of the stack
 **************************/
template <class T>
unsigned int GenStack<T>::getSize() {
    return numElements;
}

/**************************
 * displayStack()
 * prints out the stack
 * mostly used for debugging
 **************************/
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