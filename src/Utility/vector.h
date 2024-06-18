//custom vector implementation for our project
#pragma once
#include <initializer_list>

template <class T>
class vector
{
protected:
	const static int VECTOR_INITIAL_SIZE = 1;
	T* arr;
	//capacity is reserved memory in vector, size number of elements in vector
	int _capacity, _size;

	//copies content and resizes vector
	void resize()
	{
		_capacity *= 2;
		T* temp = new T[_capacity];

		//copy elements from arr to new array
		for (int x = 0; x < _size; x++)
			temp[x] = arr[x];

		//delete arr, temp becomes new arr
		delete[] arr;
		arr = temp;
	}

public:
	class Iterator;

	vector() : arr(new T[VECTOR_INITIAL_SIZE]), _capacity(VECTOR_INITIAL_SIZE), _size(0) {}
	vector(const vector& other) : arr(new T[other._capacity]), _capacity(other._capacity), _size(other._size)
	{
		for (int x = 0; x < _size; x++)
			arr[x] = other.arr[x];
	}
	vector(std::initializer_list<T> lst) : arr(new T[lst.size()]), _capacity(lst.size()), _size(0)
	{
		for(T l : lst)
			push_back(l);
	}
	
	~vector()
	{
		delete[] arr;
	}

	void push_back(T data)
	{
		//vector is full
		if (_size == _capacity)
			resize();
		arr[_size] = data;
		_size++;
	}

	void pop_back()
	{
		_size--;
	}

	int size() const
	{
		return _size;
	}

	void shrink_to_fit()
	{
		if(_size==0)
			_capacity=1;
		else
			_capacity = _size;
	}

	T& operator[](const unsigned int index) const
	{
		if (index < 0 || index >= _size)
			throw std::out_of_range("vector operator[] index is out of range");

		return arr[index];
	}

	Iterator begin() { return Iterator(arr); }
	Iterator end() { return Iterator(arr+_size); }
};


//custom vector iterator, makes programming easier, also required to use algorithm library
// you can find requirements here: https://cplusplus.com/reference/iterator/BidirectionalIterator/
template <class T>
class vector<T>::Iterator
{
	public:
		//we have to use it, c++ standard requires it, othwerwise algorithm library will not work
		using iterator_category = std::bidirectional_iterator_tag;
		using difference_type = std::ptrdiff_t;
		using value_type = T;
		using pointer = T*;
		using reference = T&;


		Iterator(pointer ptr) : _ptr(ptr){}

		Iterator& operator=(const Iterator& other) { _ptr = other._ptr; }
		bool operator==(const Iterator& a)const { return _ptr == a._ptr; }
		bool operator!=(const Iterator& a)const { return _ptr != a._ptr; }

		Iterator& operator++() { ++_ptr; return *this; }
		//postfix increment
		Iterator operator++(int) { Iterator tmp = this; ++(*this); return tmp; }
		Iterator& operator--() { --_ptr; return*this; }
		//postfix decrement
		Iterator& operator--(int) { Iterator tmp = this; --(*this); return tmp; }

		
		const reference operator*()const { return *_ptr; }
		reference operator*() { return *_ptr; }
		
		pointer operator->() { return _ptr; }
		const pointer operator->()const { return _ptr; }

	private:
		pointer _ptr;
};