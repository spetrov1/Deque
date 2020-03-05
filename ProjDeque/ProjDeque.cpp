// ProjDeque.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Deque.h"


int main()
{
    Deque<int> deq = Deque<int>(1);
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
}
