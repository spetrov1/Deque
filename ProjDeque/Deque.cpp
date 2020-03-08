#include "Deque.h"
 
deque::Deque::Deque() {
	capacity = 3;
	start = -1;
	size = 0;
	array = new double[capacity];
}
 
deque::Deque ::Deque(int capacity) {
	if (capacity < 1) {
		this->capacity = 3;
	}
	else {
		this->capacity = capacity;
	}
	this->start = -1;
	this->size = 0;
	this->array = new double[this->capacity];
}
 
deque::Deque::Deque(const Deque& other) {
	this->capacity = other.capacity;
	this->start = other.start;
	this->size = other.size;
	freeDynamicMemory();
	this->array = new double[capacity];

	int tailIndex = getTailIndex();
	for (int i = start; i <= tailIndex; ++i) {
		array[i] = other.array[i];
	}
}
 
deque::Deque& deque::Deque::operator=(const Deque & other) {
	if (this != &other) {
		this->capacity = other.capacity;
		this->start = other.start;
		this->size = other.size;
		freeDynamicMemory();

		this->array = new double[other.capacity];
		int tailIndex = getTailIndex();
		for (int i = start; i <= tailIndex; ++i) {
			this->array[i] = other.array[i];
		}
	}
	return *this;
}

void deque::Deque::resize() {
	int newCapacity = resizeNumber * size;
	int offset = size / 2;
	int newStart = offset;

	double* temp = array;
	// Try to isolate the assigning in other function
	array = new double[newCapacity];
	for (int i = 0; i < size; ++i) {
		array[newStart + i] = temp[start + i];
	}

	this->start = newStart;
	this->capacity = newCapacity;
}
 
void deque::Deque::addFirst(double newElem) {
	if (start == 0) {
		this->resize(); // start is modified
	}
	if (start == -1) { // or size == 0
		start = this->capacity / 2;
	}
	else {
		start = start - 1;
	}
	array[start] = newElem;
	++size;
}
 
double deque::Deque ::removeFirst() {
	double removedElement;
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
 
double deque::Deque::getFirst() {
	if (size == 0) {
		cout << "Unsuccessfull try to get first element of deque... Empty deque!" << endl;
		return NULL;
	}
	return array[start];
}
 
void deque::Deque::addLast(double newElem) {
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
 
double deque::Deque ::removeLast() {
	double removedElement;
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
 
double deque::Deque::getLast() {
	int tailIndex = getTailIndex();
	if (size == 0) {
		cout << "Unsuccessfull try to get last element of deque... Empty deque!" << endl;
		return NULL;
	}
	return array[tailIndex];
}
 
int deque::Deque ::getTailIndex() {
	if (size == 0) {
		return -1;
	}
	return start + size - 1;
}
 
void deque::Deque::print() {
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
 
void deque::Deque::freeDynamicMemory() {
	delete[]this->array;
}
