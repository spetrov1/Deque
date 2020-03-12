#pragma once

/// Add documentation

template <class T>
class Deque
{
private:
	size_t capacity = 0;
	size_t size = 0;
	size_t headIndex = 0;
	T* buffer = nullptr;

	const short resizeCoeff = 2;

	void resize();
	void copyFrom(const Deque&);
	void deleteDynamicMemory();
public:
	Deque(size_t capacity = 0);
	Deque(const Deque&);
	Deque& operator=(const Deque&);
	~Deque();

	void addFirst(T newElem);
	T removeFirst(); // TODO throw exception
	void getFirst() const; // TODO, throw exception

	void addLast(T newElem);
	T removeLast();
	void getLast(); // TODO throw exception

	void print() const {
		if (isEmpty()) 
			return;

		size_t tailIndex = getTailIndex();

		for (size_t i = headIndex; i <= tailIndex ; ++i) {
			std::cout << buffer[i] << " ";
		} 
		std::cout << "some meta data ... headIndex = " << headIndex <<
			" ,size = " << size << " ,capacity = " << capacity << std::endl;
	}

	size_t getTailIndex() const;
	bool isEmpty() const;
	bool notAllocatedMemory() const;
	void allocateSomeMemory();
	void turnToNotActiveMode();
};

template <typename T>
Deque<T>::~Deque() {
	deleteDynamicMemory();
}

template <typename T>
void Deque<T>::deleteDynamicMemory() {
	delete[] buffer;
}

template <typename T>
Deque<T>& Deque<T>::operator=(const Deque& other) {
	if (this != &other) {
		deleteDynamicMemory();
		copyFrom(other);
	}
	return *this;
}

/// Copy constructor
template <typename T>
Deque<T>::Deque(const Deque& other) {
	copyFrom(other);
}

/// Function used in copy constructor and operator=
/// 
/// Clone other deque to this deque
template <typename T>
void Deque<T>::copyFrom(const Deque& other) {
	this->buffer = new T[other.capacity]; // may throw ?

	size_t firstElementIndex = other.headIndex;
	size_t lastElementIndex = other.headIndex + other.size - 1;
	for (size_t i = firstElementIndex; i <= lastElementIndex; ++i) {
		this->buffer[i] = other.buffer[i];
	}

	this->capacity = other.capacity;
	this->size = other.size;
	this->headIndex = other.headIndex;
}

/// Capacity == 0 (default) ... unallocated memory for the deque's buffer
///
/// ELSE allocates memory for the buffer and set appropriate position for head
template <typename T>
Deque<T>::Deque(size_t capacity) {
	if (capacity == 0) 
		return;
	buffer = new T[capacity]; // may throw bad_aloc
	this->capacity = capacity;
	headIndex = capacity / 2;
}

/// If yet not allocated memory for buffer ... allocate memory and add element
/// Resize if there is no space for adding to head
/// ELSE just adds new head to deque
template <typename T>
void Deque<T>::addFirst(T newElem) {
	assert(newElem != NULL);

	if (notAllocatedMemory()) {
		allocateSomeMemory();
	}
	else if (isEmpty()) { // empty && allocatedSomeMemoryYet
		headIndex = capacity / 2; // TODO Head is expected to be on right position, so it is not needed maybe 
	}
	else if (!isEmpty()) {
		if (headIndex == 0) {
			resize();
		}
		--headIndex;     // We have head element and we skip it
						 // Prepare for the new head
	}
	buffer[headIndex] = newElem;
	++size;
}

/// Removes from head of the deque and returns it
/// If deque is empty ... NULL is returned
/// If there is only one element ... deque is setToNotActiveMode (deletes the allocated memory)
template <typename T>
T Deque<T>::removeFirst() {
	T removedElement;
	
	if (isEmpty()) {
		// or throw exception?
		return NULL;
	}
	removedElement = buffer[headIndex];
	++headIndex;
	--size;
	if (headIndex == 0) {
		turnToNotActiveMode(); // default init values for deque
	}

	return removedElement;
}

/// If not allocated memory for deque's buffer ... allocate some memory and adds newElem
/// If no space for adding to tail ... resize and add newElem
/// ELSE just adds newElem
template <typename T>
void Deque<T>::addLast(T newElem) {
	assert(newElem);
	size_t newTailIndex;

	if (notAllocatedMemory()) {
		allocateSomeMemory();
		newTailIndex = headIndex;
	}
	else if (isEmpty()) { // empty but yet allocated memory
		headIndex = capacity / 2; // Not needed maybe
		newTailIndex = headIndex;
	}
	else { // is not empty deque
		newTailIndex = getTailIndex();
		if (newTailIndex == capacity - 1) {
			resize();
			newTailIndex = getTailIndex(); // tail index after resize
		}
		++newTailIndex;
	}
	assert(newTailIndex); // is it okay ?

	buffer[newTailIndex] = newElem;
	++size;
}

/// Removes element from tail and returns it
/// If deque's empty, NULL is returned
/// If there is only one element, returns it and set deque to notActiveMode(deletes allocated memory)
template <typename T>
T Deque<T>::removeLast() {
	T removedElement;
	size_t tailIndex;
	if (isEmpty()) {
		// TODO throw exception ?
		return NULL;
	}
	tailIndex = getTailIndex();
	removedElement = buffer[tailIndex];
	--size;
	if (size == 0) {
		turnToNotActiveMode();
	}
	return removedElement;
}

/// Allocates 2 * larger memory for deque's buffer
/// 
/// Saves 'old' elements in the middle of the new buffer
template <typename T>
void Deque<T>::resize() {
	int newCapacity = resizeCoeff * size;
	int offset = size / 2;
	int newHeadIndex = offset;
	T* temp = buffer;

	if (size == 1) {
		newCapacity = 3; // TODO name constant 3
		offset = newCapacity / 2;
		newHeadIndex = offset;
	}

	// Try to isolate the assigning in other function
	buffer = new T[newCapacity]; // TODO may throw bad_alloc
	for (size_t i = 0; i < size; ++i) {
		buffer[newHeadIndex + i] = temp[headIndex + i];
	}

	headIndex = newHeadIndex;
	capacity = newCapacity;
}

/// Returns index of the tail
template <typename T>
size_t Deque<T>::getTailIndex() const {
	assert(size > 0); // or throw exception ?

	return headIndex + size - 1;
}

template <typename T>
bool Deque<T>::isEmpty() const {
	return size == 0;
}

/// Deque is in notActiveMode (not allocated memory for buffer)
template <typename T>
bool Deque<T>::notAllocatedMemory() const {
	return !buffer; // && capacity == 0 && size == 0 && headIndex == 0
}

/// Allocate memory for deque initialized with default constructor
///
/// Allocate memory for deque which is in notActiveMode
template <typename T>
void Deque<T>::allocateSomeMemory() {
	const short defaultMemoryAllocation = 3;
	buffer = new T[defaultMemoryAllocation]; // may throw bad_aloc exc ?

	capacity = defaultMemoryAllocation;
	headIndex = capacity / 2;
	size = 0; // Not needed maybe. It is expected to be this value
}

/// Deletes the allocated memory
///
/// Set all the private members to their default values
template <typename T>
void Deque<T>::turnToNotActiveMode() {
	delete[] buffer;
	capacity = size = headIndex = 0;
	buffer = nullptr;
}