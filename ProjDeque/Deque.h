#pragma once

#include <iostream> //TODO Does not make sense here
#include <cassert>

using namespace std; //TODO considered a bad practice in header files

template <class T>
class Deque
{
private:
	int capacity = 3; //TODO move from int -> size_t
	int start = -1;
	int size = 0;
	T* buffer = nullptr;

	const int resizeNumber = 2;
	void resize();
	int getTailIndex();
	void freeDynamicMemory();
	// void assignArray( TODO );

	void copyFrom(const Deque& other);
	static T* clone(const T* buffer, size_t size, size_t from, size_t to);

public:
	Deque();
	Deque(int capacity = 3);
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

template<class T>
inline void Deque<T>::copyFrom(const Deque& other)
{
	T* newBuffer = createBuffer(
		other.capacity,
		other.start,
		other.start + other.size,
		other.buffer + other.start,
	);

	capacity = other.capacity;
	start = other.start;
	size = other.size;

	delete[] buffer;
	buffer = newBuffer;
}

template <typename T>
static T* createBuffer(size_t size, size_t initFrom, size_t initTo, const T* initValues)
{
	assert(initValues);
	assert(size > 0);

	T* newBuffer = new T[size];

	try {
		for (size_t i = initFrom; i < initTo; ++i, ++initValues)
			newBuffer[i] = *initValues;
	}
	catch (...) {
		delete[] newBuffer;
		return;
	}

	return newBuffer;
}

template <class T>
Deque<T>::Deque() {
	buffer = new T[capacity]; //may throw!!!
}

template <class T>
Deque<T>::Deque(int capacity)
	: capacity(capacity)
{
	if (capacity < 1) {
		this->capacity = 3;
	}

	this->buffer = new T[this->capacity];
}

template <class T>
Deque<T>::Deque(const Deque& other)
{
	copyFrom(other);
}

template <class T>
Deque<T>& Deque<T>::operator=(const Deque<T>& other)
{
	if (this != &other) {
		copyFrom(other);
	}
	return *this;
}

template <class T>
void Deque<T>::resize()
{
	int newCapacity = size ? resizeNumber * size : 2;
	int offset = size / 2;
	int newStart = offset;

	T* newBuffer = createBuffer(
		newCapacity,
		(newCapacity - capacity) / 2,
		start + size,
		buffer + start,
	);
	
	this->start = newStart;
	this->capacity = newCapacity;

	delete[]buffer;
	buffer = newBuffer;
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
	buffer[start] = newElem;
	++size;
}

template <class T>
T Deque<T>::removeFirst() {
	T removedElement;
	if (size == 0) {
		cout << "There is nothing to remove ...";
		return NULL;
	}

	removedElement = buffer[start];
	--size;
	if (size == 0) {
		start = -1;
	}
	else {
		start += 1;
	}

	return removedElement;
}

//TODO Handle the case when the container is empty
//TODO Pick a proper error-handling method
template <class T>
T Deque<T>::getFirst() {
	if (size == 0) {
		cout << "Unsuccessfull try to get first element of deque... Empty deque!" << endl;
		return NULL;
	}
	return buffer[start];
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
	buffer[newTailIndex] = newElem;

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
	removedElement = buffer[tailIndex];
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
	return buffer[tailIndex];
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
		cout << buffer[index] << " ";
	}
	cout << " -- some meta data --> start = " << start << " size = " 
		<< size << " capacity = " << capacity << endl;
}

template <class T>
void Deque<T>::freeDynamicMemory() {
	delete[]this->buffer;
}