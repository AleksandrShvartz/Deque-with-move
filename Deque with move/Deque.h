#pragma once
#include <iostream>
template <class T>
class Deque;
template<class T>
std::ostream& operator <<(std::ostream&, const Deque<T>&);
template<class T>
class Deque {		 
	struct Node{
		Node(const T&, Node*, Node*);
		T data;
		Node* next;
		Node* prev;
	};
private:
	Node* first;
	Node* last;
	unsigned int size;
public:
	Deque<T>();
	void pushFront(const T&);
	void pushBack(const T&);
	T popFront();
	T popBack();
	Deque<T>(const Deque<T>&);
	Deque<T> operator=(const Deque<T>&);
	Deque( Deque<T>&&);
	Deque<T> operator=( Deque<T>&&);
	
	friend std::ostream& operator<< <>(std::ostream&,const Deque<T>&);
	~Deque();
};

template<class T>
inline Deque<T>::Deque():first(nullptr),last(nullptr),size(0)
{

}

template<class T>
inline Deque<T>::Deque(const Deque<T>& deque)
{
	size = 0;
	first = nullptr;
	last = nullptr;
	Node* iter = deque.first;
	for (unsigned i = 0; i != deque.size; ++i) {
		pushBack(iter->data);
		iter = iter->next;
	}
}

template<class T>
inline void Deque<T>::pushFront(const T& newData)
{
	first = new Node(newData,nullptr,first);
	if (size == 0)
		last = first;
	size++;
}

template<class T>
inline void Deque<T>::pushBack(const T& newData)
{
	last = new Node(newData, last, nullptr);
	if (size == 0)
		first = last;
	size++;
}

template<class T>
inline T Deque<T>::popFront()
{
	if (size > 0) {
		T t = first->data;
		Node* tmp = first->next;
		delete first;
		if (tmp != nullptr)
			tmp->prev = nullptr;
		else
			last = nullptr;
		first = tmp;
		size--;
		return t;
	}
	else throw "Size = 0";
}

template<class T>
inline T Deque<T>::popBack()
{
	if (size > 0) {
		T t = last->data;
		Node* tmp = last->prev;
		delete last;
		if (tmp != nullptr)
			tmp->next = nullptr;
		else
			first = nullptr;
		last = tmp;
		size--;
		return t;
	}
	else throw "Size = 0";
}

template<class T>
inline Deque<T> Deque<T>::operator=(const Deque<T>& deque)
{
	while (size)
	{
		popBack();
	}
	first = nullptr;
	last = nullptr;
	Node* iter = deque.first;
	for (unsigned i = 0; i != deque.size; ++i) {
		pushBack(iter->data);
		iter = iter->next;
	}
	return *this;
}

template<class T>
inline Deque<T>::Deque( Deque<T>&& deque)
{
	first = deque.first;
	last = deque.last;
	size = deque.size;
	deque.first = nullptr;
	deque.last = nullptr;	
	deque.size = 0;
}

template<class T>
inline Deque<T> Deque<T>::operator=( Deque<T>&& deque)
{
	while (size)
		popBack();
	first = deque.first;
	last = deque.last;
	size = deque.size;
	deque.first = nullptr;
	deque.last = nullptr;
	deque.size = 0;
	return *this;
}

template<class T>
inline Deque<T>::~Deque()
{
	Node* tmp;
	while (first != nullptr)
	{
		tmp = first;
		first = first->next;
		delete tmp;
	}
}

template<class T>
inline Deque<T>::Node::Node(const T& data, Node* prev, Node* next)
{
	this->data = std::move(data);
	this->prev = prev;
	this->next = next;

	if (prev == nullptr && next == nullptr) {
	  
	}
	else if (prev == nullptr) {
		next->prev = this;
	}
	else if (next == nullptr) {
		prev->next = this;
	}
	else throw "wrong argument";
}
template<class T>
inline std::ostream& operator<<<>(std::ostream& out, const Deque<T>& deque)
{
	auto tmp = deque.first;
	unsigned length = deque.size;
	while (length--) {
		out << tmp->data;
		tmp = tmp->next;
	}
	return out;
	// TODO: insert return statement here
}


