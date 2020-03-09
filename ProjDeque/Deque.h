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
	size_t getTailIndex() const; // return size_t maybe ?
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
/// Help function for copy constructor
/// 
/// Help function for operator=
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
/// Return new buffer
///
/// Initialized with segment of values (initFrom ... initTo) from initValues
/// Return nullptr if problem assigning values
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

/// If not given parameter, deque is set to EmptyState
///
/// If capacity < 1, deque is set to EmptyState
/// ELSE just allocates capacity size for the deque
template <class T>
Deque<T>::Deque(int capacity)
	: capacity(capacity)
{
	if (capacity < 1) {
		setToEmptyState();
		return;
	}

	try {
		buffer = new T[capacity];
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


/// Allocate memory for bigger buffer
///
/// Assigning the 'old' values to the 'new' allocated buffer
template <class T>
void Deque<T>::resize()
{
	assert(size); // size is expected to be greater than 0

	size_t newCapacity = size * resizeCoeff; // size > 0 always when resize is invoked
	size_t offset = size / 2;
	size_t newStart = offset;

	// Should be checked if createBuffer returned nullptr ???
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

/// If empty deque, allocate some memory for buffer and ... add first element in deque
/// If start(head of deque) is 0 indexed, ... resize deque and add the new head of deque
/// ELSE just add new head of deque
template <class T>
void Deque<T>::addFirst(T newElem) {

	// TODO check if empty deque (size == 0)
	if (isEmpty()) { // this case only if deque is in empty state
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

/// If empty deque ... NULL is returned
/// Removes head of deque
/// Return head of deque
template <class T>
T Deque<T>::removeFirst() {
	T removedElement;
	if (isEmpty()) {
		cout << "There is nothing to remove ..."; // Is this message okay ???
		return NULL;
	}

	removedElement = buffer[start];
	--size;
	if (size == 0) {
		setToEmptyState();
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

/// If empty deque, allocate some memory for buffer and ... add first element in deque
/// If no more space for tail, ... resize deque and add the new elem to the tail of deque
/// ELSE just add new elem to the tail of deque
template <class T>
void Deque<T>::addLast(T newElem) {
	size_t tailIndex = getTailIndex();
	size_t newTailIndex;

	if (isEmpty()) {
		allocateSomeBufferMemory();
		start = capacity / 2;
		newTailIndex = start - 1;
	}
	else if (tailIndex == capacity - 1) { // no more tail
		resize();						  // then extend it
		newTailIndex = getTailIndex();
	}
	else {
		newTailIndex = tailIndex;
	}
	++newTailIndex;
	buffer[newTailIndex] = newElem;

	++size;
}

/// If empty deque, ... NULL returned
/// Removes last element(TAIL) of deque
/// Return last element(TAIL) of deque
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
		setToEmptyState();
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
size_t Deque<T>::getTailIndex() const {
	if (size == 0) {
		return -1; // TODO size_t can't be negative
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