#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H
#include <iostream>
#include <cassert>
using namespace std;
const int SIZE = 10;

template <typename T>
class Array {
private:
	T* array;
	int size;
	int capacity;
	void copyArray(const Array&);
	void deleteArray();
public:
	Array();
	Array(int);
	~Array();
	Array(const Array&);
	Array& operator=(const Array&);
	void push(const T&);
	void pop();
	T& operator[](const int) const;
	int getSize() const;
};

template <typename T>
void Array<T>::copyArray(const Array<T>& other) {
	capacity = other.capacity;
	size = other.size;
	array = new T[capacity];
	assert(array != NULL);
	for (int i = 0; i < capacity; i++) {
		array[i] = other.array[i];
	}
}
template <typename T>
void Array<T>::deleteArray() {
	delete[] array;
}
template <typename T>
Array<T>::Array() : size(0), capacity(1), array(new T[1]) {
}
template <typename T>
Array<T>::Array(int newSize) : size(0), capacity(newSize), array(new T[newSize]) {
}
template <typename T>
Array<T>::~Array() {
	deleteArray();
}
template <typename T>
Array<T>::Array(const Array<T>& other) {
	copyArray(other);
}
template <typename T>
Array<T>& Array<T>::operator=(const Array<T>& other) {
	if (this != &other) {
		deleteArray();
		copyArray(other);
	}
	return *this;
}
template <typename T>
void Array<T>::push(const T& element) {
	if (size > capacity - 1) {
		T* tempArray = array;
		capacity += SIZE;
		array = new T[capacity];
		assert(array != NULL);
		for (int i = 0; i < size; i++) {
			array[i] = tempArray[i];
		}
		array[size] = element;
		size++;
		delete[] tempArray;
	}
	else if (size <= capacity - 1) {
		array[size] = element;
		size++;
	}
}
template <typename T>
void Array<T>::pop() {
	if (size != 0) size--;
}
template <typename T>
T& Array<T>::operator[](const int position) const {
	return array[position];
}
template <typename T>
int Array<T>::getSize() const {
	return size;
}

#endif
