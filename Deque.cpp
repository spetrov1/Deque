// Deque.cpp : This file contains the 'main' function. Program execution begins and ends there.
//



#include <iostream>
#include <cassert>
#include "Deque.h"

// Not appropriate name of the file

// tests
/*
bool addFirstToDequeInitializedWithOneCapacity() {
    Deque<int> d(1);
    d.addFirst(1);

    // TODO
}

bool addFirstMultipleTimesDequeInitOneCapacity() {
    Deque<int> d(1);
    d.addFirst(1);
    d.print();

    d.addFirst(2);
    d.print();

    d.addFirst(15);
    d.print();

    // TODO
}

bool addFirstDequeNotAllocatedMemory() { // Initialized with default constructor
    Deque<int> deq;
    deq.addFirst(1);
    deq.print();

    // TODO
}

bool addFirstMultipleTimesDequeInitializedNotAllocatedMemory() {
    Deque<int> deq;
    deq.addFirst(1);
    deq.print();

    deq.addFirst(2);
    deq.print();

    deq.addFirst(3);
    deq.print();

    // TODO
}
bool addFirstToDequeInitializedWith4Capacity() {
    Deque<int> deq(4);
    deq.addFirst(1);

    // TODO
}

bool addFirstMultipleTimesToDequeInitializedWith4Capacity() {
    Deque<int> deq(4);
    deq.addFirst(1);
    deq.addFirst(2);
    deq.addFirst(3);
    deq.addFirst(4);

    // TODO
}

bool removeFromDequeWithOneSizeAndCapacity() {
    Deque<int> d(1);
    d.addFirst(1);
    d.removeFirst();

    // TODO
}
bool RemoveTheOneAndOnlyElementOfDequeAndAfterThatAddFirst() {
    Deque<int> d(1);
    d.addFirst(1);
    d.print();

    std::cout << d.removeFirst() << std::endl;

    d.print();

    d.addFirst(2);
    d.print();

    // TODO
}

bool removeTwoElementsFromDeque() {
    Deque<int> d(1);
    d.addFirst(1);
    d.addFirst(2);
    d.print();

    int el;
    while (el = d.removeFirst()) {
        std::cout << el << " ";
    }
    d.print();
}

bool addLastToDequeWithNotAllocatedMemory() {
    Deque<int> d;
    d.addLast(1);
    d.print();

    // TODO
}

bool addLastMultipleTimesToDequeWithNotAllocatedMemory() {
    Deque<int> d;
    d.addLast(1);
    d.addLast(2);
    d.addLast(3);

    d.print();

    // TODO
}

bool removeLastFromDequeOneElementSize() {
    Deque<int> d;
    d.addFirst(1);

    d.removeLast();

    // TODO
}

bool removeLastAndAfterThatAddSomeElements() {
    Deque<int> d;
    d.addFirst(1);
    d.removeLast();

    d.addLast(2);
    d.addFirst(1);
    d.addFirst(-100);
    d.addFirst(-200);
    d.print();

    // TODO
}

*/

int main()
{   
    Deque<int> d(2);
    d.addFirst(1);
    d.addLast(2);
    d.print();
    d.removeFirst();
    d.removeFirst();

    d.addLast(100);
    d.addLast(109);
    d.addFirst(9);
    d.addFirst(1);

    d.print();

    // test of operator=
    Deque<int> d2;
    d2 = d;
    d2.print();
    int el;
    while (el = d2.removeFirst()) {
        std::cout << el << " ";
    } 
    std::cout << '\n';
   
    d2.addLast(-100);
    d2.addFirst(55);
    d2.print();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
