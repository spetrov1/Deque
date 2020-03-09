// ProjDeque.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "Deque.h"


int main()
{
    using std::cout;
    using std::endl;

    Deque<int> d(1);
    d.addFirst(5);
    d.print();


    /// Capacity is 4, it has to be 1 ???

    
    // Some manual tests

    Deque<double> deq = Deque<double>(1);
    deq.addFirst(5);
    deq.print();
    
    deq.addLast(15);
    deq.print();

    double el;
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

    cout << "Hello world! " << endl;

    

}
