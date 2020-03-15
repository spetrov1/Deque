// Deque.cpp : This file contains the 'main' function. Program execution begins and ends there.
//



#include <iostream>
#include <cassert>

#include <fstream>
#include <unordered_set>
// std::unordered_set<void*> allocatedMemory;
#include "Deque.h"


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

void f() {
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

// #include "Test.h"
// std::ofstream Test::out = std::ofstream("my_log_file", std::ios::trunc);
// int Test::i = 15;

/*
#include "UnorderedSet.h"
#include <unordered_set>
std::unordered_set<int> UnorderedSet::set;
int UnorderedSet::i = 0;
*/

// ? How we change this PRIVATE variable ?
// ? Why can not initialize it in private method of Deque?
template<typename T>
std::ofstream Deque<T>::logFileStream = std::ofstream("my_log_file", std::ios::trunc);
template <typename T>
std::unordered_set<void*> Deque<T>::allocatedMemory;

// template <typename T>
// void Deque<T>::redirectClog();




int main()
{   
    
    Deque<int>* a = new Deque<int>;
    Deque<int>* b = new Deque<int>[2];
    delete a;
    delete [] b;

    Deque<int>::printAllocatedMemoryAddresses();
    
}
