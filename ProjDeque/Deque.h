#pragma once
#include <iostream>
using namespace std;

template <class T>
class Deque
{
private:
	int capacity;
	int start;
	int size;
	T* array;

	const int resizeNumber = 2;
	void resize();
	int getTailIndex();

	// void assignArray( TODO );
public:
	Deque();
	Deque(int capacity);
	Deque(const Deque&);
	Deque& operator=(const Deque&);

	void addFirst(T elem);
	T removeFirst();
	T getFirst();

	void addLast(T elem);
	T removeLast();
	T getLast();

	void print(); // just to test
};

template <class T>
Deque<T>::Deque() {
	capacity = 3;
	start = -1;
	size = 0;
	array = new T[capacity];
}

template <class T>
Deque<T>::Deque(int capacity) {
	if (capacity < 1) {
		this->capacity = 3;
	}
	else {
		this->capacity = capacity;
	}
	this->start = -1;
	this->size = 0;
	this->array = new T[this->capacity];
}

template <class T>
Deque<T>::Deque(const Deque& other) {
	this->capacity = other.capacity;
	this->start = other.start;
	this->size = other.size;
	this->array = new T[capacity];
	
	int tailIndex = getTailIndex();
	for (int i = start; i <= tailIndex; ++i) {
		array[i] = other.array[i];
	}
}

template <class T>
Deque<T>& Deque<T>::operator=(const Deque<T>& other) {
	if (this != &other) {
		this->capacity = other.capacity;
		this->start = other.start;
		this->size = other.size;
		this->array = new T[other.capacity];
		int tailIndex = getTailIndex();
		for (int i = start; i <= tailIndex; ++i) {
			this->array[i] = other.array[i];
		}
	}
	return *this;
}

template <class T>
void Deque<T>::resize() {
	int newCapacity = resizeNumber * size;
	int offset = size / 2;
	int newStart = offset;

	T* temp = array;
	// Try to isolate the assigning in other function
	array = new T[newCapacity];
	for (int i = 0; i < size; ++i) {
		array[newStart + i] = temp[start + i];
	}

	this->start = newStart;
	this->capacity = newCapacity;
}

template <class T>
void Deque<T>::addFirst(T newElem) {
	if (start == 0) {
		this->resize(); // start is modified
	}
	if (start == -1) { // or size == 0
		start = this->capacity / 2;
	} else {
		start = start - 1;
	}
	array[start] = newElem;
	++size;
}

template <class T>
T Deque<T>::removeFirst() {
	T removedElement;
	if (size == 0) {
		cout << "There is nothing to remove ...";
		return NULL;
	}

	removedElement = array[start];
	--size;
	if (size == 0) {
		start = -1;
	}
	else {
		start += 1;
	}

	return removedElement;
}

template <class T>
T Deque<T>::getFirst() {
	if (size == 0) {
		cout << "Unsuccessfull try to get first element of deque... Empty deque!" << endl;
		return NULL;
	}
	return array[start];
}


template <class T>
void Deque<T>::addLast(T newElem) {
	int tailIndex = getTailIndex();
	int newTailIndex;

	if (tailIndex == capacity - 1) { // no more tail
		resize();					  // then extend it
		newTailIndex = getTailIndex();
	}
	else if (tailIndex == -1) { // empty deque
		start = capacity / 2;
		newTailIndex = start - 1;
	}
	else {
		newTailIndex = tailIndex;
	}
	++newTailIndex;
	array[newTailIndex] = newElem;

	++size;
}


template <class T>
T Deque<T>::removeLast() {
	T removedElement;
	int tailIndex = getTailIndex();
	if (size == 0) {
		cout << "There is nothing to remove ..." << endl;
		return NULL;
	}
	removedElement = array[tailIndex];
	--size;

	if (size == 0) {
		start = -1;
	}

	return removedElement;
}

template <class T>
T Deque<T>::getLast() {
	int tailIndex = getTailIndex();
	if (size == 0) {
		cout << "Unsuccessfull try to get last element of deque... Empty deque!" << endl;
		return NULL;
	}
	return array[tailIndex];
}


template <class T>
int Deque<T>::getTailIndex() {
	if (size == 0) {
		return -1;
	}
	return start + size - 1;
}


template <class T>
void Deque<T>::print() {
	if (size == 0) {
		cout << "Empty deque..." << endl;
		return;
	}
	int tailIndex = getTailIndex();
	for (int index = start; index <= tailIndex; ++index) {
		cout << array[index] << " ";
	}
	cout << " -- some meta data --> start = " << start << " size = " 
		<< size << " capacity = " << capacity << endl;
}
