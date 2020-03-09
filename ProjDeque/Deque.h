#pragma once

#include <iostream> //TODO Does not make sense here
#include <cassert>

// TODO documentation ---> comments to almost every method

using namespace std; //TODO considered a bad practice in header files

template <class T>
class Deque
{
private:
	size_t capacity = 3; //TODO move from int -> size_t
	size_t start = 0;
	size_t size = 0;
	T* buffer = nullptr;
	
	
	const short resizeCoeff = 2;
	void resize();
	size_t getTailIndex(); // return size_t maybe ?
	void freeDynamicMemory();
	void copyFrom(const Deque& other);
	static T* createBuffer(size_t size, size_t initFrom, size_t initTo, const T* initValues);

public:
	Deque(int capacity = -1);
	Deque(const Deque&);
	Deque& operator=(const Deque&);
	~Deque();
	bool isEmpty() const;

	void addFirst(T elem);
	T removeFirst();
	T getFirst() const;

	void addLast(T elem);
	T removeLast();
	T getLast() const;

	void print(); // just to test

	void setToEmptyState();
	void allocateSomeBufferMemory(); // It can throw exception ??
};


// Why inline ??
template<class T>
inline void Deque<T>::copyFrom(const Deque& other)
{
	T* newBuffer = createBuffer(
		other.capacity,
		other.start,
		other.start + other.size,
		other.buffer + other.start
	);

	capacity = other.capacity;
	start = other.start;
	size = other.size;

	delete[] buffer;
	buffer = newBuffer;
}

// static for the class or just for the file ?
template <typename T>
T* Deque<T>::createBuffer(size_t size, size_t initFrom, size_t initTo, const T* initValues)
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

		return nullptr;    // Not sure if it is right ?
	}

	return newBuffer;
}

template <class T>
Deque<T>::Deque(int capacity)
	: capacity(capacity)
{
	if (capacity < 1) {
		setToEmptyState();
		return;
	}

	try {
		buffer = new T[this->capacity];
	}
	catch (...) { // Or Overflow_Error, BadAlloc ... which one ??
		setToEmptyState();
	}
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
Deque<T>::~Deque() {
	freeDynamicMemory();
}

template <class T>
void Deque<T>::resize()
{
	// int newCapacity = size ? resizeNumber * size : 2;
	size_t newCapacity = size * resizeCoeff; // size > 0 always
	size_t offset = size / 2;
	size_t newStart = offset;

	T* newBuffer = createBuffer(
		newCapacity,
		(newCapacity - capacity) / 2, // == (size / 2) ??
		start + size,
		buffer + start
	);
	
	start = newStart;
	capacity = newCapacity;

	delete[] buffer;
	buffer = newBuffer;
}

template <class T>
void Deque<T>::addFirst(T newElem) {
	if (isEmpty()) {
		allocateSomeBufferMemory();
		start = capacity / 2;
	}
	else if (start == 0) {
		resize(); // start is modified
	}
	else {
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
		// TODO set to empty state
	}
	else {
		start += 1;
	}

	return removedElement;
}

//TODO Handle the case when the container is empty
//TODO Pick a proper error-handling method
template <class T>
T Deque<T>::getFirst() const {
	if (isEmpty()) {
		cout << "Unsuccessfull try to get first element of deque... Empty deque!" << endl;
		return NULL;
	}
	return buffer[start];
}


template <class T>
void Deque<T>::addLast(T newElem) {
	size_t tailIndex = getTailIndex();
	size_t newTailIndex;

	// TODO check if empty state
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
	size_t tailIndex = getTailIndex();
	if (size == 0) {
		cout << "There is nothing to remove ..." << endl;
		return NULL;
	}
	removedElement = buffer[tailIndex];
	--size;

	if (size == 0) {
		start = -1;
		// TODO set to empty state
	}

	return removedElement;
}

template <class T>
T Deque<T>::getLast() const {
	int tailIndex = getTailIndex();
	if (size == 0) {
		cout << "Unsuccessfull try to get last element of deque... Empty deque!" << endl;
		return NULL;
	}
	return buffer[tailIndex];
}


template <class T>
size_t Deque<T>::getTailIndex() {
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
	size_t tailIndex = getTailIndex();
	for (size_t index = start; index <= tailIndex; ++index) {
		cout << buffer[index] << " ";
	}
	cout << " -- some meta data --> start = " << start << " size = " 
		<< size << " capacity = " << capacity << endl;
}

template <class T>
void Deque<T>::freeDynamicMemory() {
	delete[] buffer;
}

template <class T>
bool Deque<T>::isEmpty() const {
	return size == 0;
}

template <class T>
void Deque<T>::allocateSomeBufferMemory() {
	short defaultCapacity = 4;
	buffer = new T[defaultCapacity]; // can throw exception ?
	capacity = defaultCapacity; // problem assigning short to size_t ???
}

template <class T>
void Deque<T>::setToEmptyState() {
	capacity = 0;
	size = 0;
	start = 0;
	buffer = nullptr;
}