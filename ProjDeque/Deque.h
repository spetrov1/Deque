#ifndef DEQUE_H
#define DEQUE_H

#include <iostream>
using namespace std;

namespace deque {

	class Deque
	{
	private:
		int capacity;
		int start;
		int size;
		double* array;

		const int resizeNumber = 2;
		void resize();
		int getTailIndex();
		void freeDynamicMemory();
		// void assignArray(doubleODO );
	public:
		Deque();
		Deque(int capacity);
		Deque(const Deque&);
		Deque& operator=(const Deque&);

		void addFirst(double elem);
		double removeFirst();
		double getFirst();

		void addLast(double elem);
		double removeLast();
		double getLast();

		void print(); // just to test
	};

	class A {

	};
}

#endif