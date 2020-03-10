// ProjDeque.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cassert>
#include "Deque.h"

int main()
{

    using std::cout;
    using std::endl;

    /*
    Deque<int> d2(1);
    d2.addFirst(-1);
    d2.print();

    d2.addFirst(-2);
    d2.print();
    */

    
    Deque<int> d2(1);
    d2.addLast(1);
    d2.addLast(15);
    d2.print();


    Deque<int> d1(2);

    d1.addFirst(5);
    d1.addLast(-5);
    d1.addFirst(-6);
    d1.addFirst(150);
    d1.print();

   

    d1.addFirst(15);
    d1.addFirst(18);
    d1.print();

    
    // Some manual tests

    Deque<double> deq = Deque<double>(1);
    deq.addFirst(5);
    deq.print();
    
    deq.addLast(15);
    deq.print();

    int el;
    while( (el = deq.removeLast()) ) {
        cout << el << " ";
    }

    deq.addLast(-5);
    deq.addLast(1);
    cout << deq.removeFirst() << endl << deq.removeLast() << endl;

    deq.addFirst(-15);
    deq.print();

    Deque<double> deq2;
    deq2 = deq;

    deq2.print();

    deq2.addLast(15.5);
    deq2.removeFirst();
    deq2.addFirst(1.5);
    deq2.print();

    
    
}
