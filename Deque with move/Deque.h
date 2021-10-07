#pragma once
#include <iostream>
template <class T>
class Deque;
/// <summary>
/// �������� ������ 
/// </summary>
/// <typeparam name="T">��������� ��������</typeparam>
/// <param name="out">����� ������</param>
/// <param name="deque">������� �� ������� �������� ��������</param>
/// <returns>������ �� ����� ������</returns>
template<class T>
std::ostream& operator <<(std::ostream& out, const Deque<T>& deque);
/// <summary>
/// ��������� ����� ������� � ���������� \param T
/// </summary>
/// <typeparam name="T">��� �������� ���������</typeparam>
template<class T>
class Deque {		 
	/// ���������� ����� ����.
	/**
	������ � ���� ������ ���� \param T � ������ ��������� �� 
	���������� � ��������� �������. 
	*/
	struct Node{
		/// <summary>
		/// �����������, ����������� ������� ����� ����� �������������.
		/// </summary>
		/// <param name="newData">������������ ������ ����</param>
		/// <param name="prev">�������� �� ���������� ������� </param>
		/// <param name="next">�������� �� ��������� �������</param>
		Node(const T& newData, Node* prev, Node* next);
		/// <summary>
		///  �����������, ����������� ������� ����� ����� �������������, �������������� 
		/// move ���������.
		/// </summary>
		/// <param name="newData">������������ ������ ����</param>
		/// <param name="prev">�������� �� ���������� ������� </param>
		/// <param name="next">�������� �� ��������� �������</param>
		Node(T&& newData, Node* prev, Node* next);
		/// <summary>
		/// ������ ����.
		/// </summary>
		T data;
		/// <summary>
		/// ��������� �� ��������� �������.
		/// </summary>
		Node* next;
		/// <summary>
		/// ��������� �� ���������� �������.
		/// </summary>
		Node* prev;
	};
private:
	Node* first;
	Node* last;
	unsigned int size;
public:
	/// <summary>
	/// ������� ����������� ��������� ������ ������� ���������� �������� ���� \param T 
	/// </summary>
	Deque<T>();
	/// <summary>
	/// ��������� ������� � ������ �������.
	/// </summary>
	/// <param name="newData">����������� �������</param>
	void pushFront(const T& newData);
	/// <summary>
	/// ��������� rvalue ������� � ������ �������.
	/// </summary>
	/// <param name="newData">����������� �������</param>
	void pushFront(T&& newData);
	/// <summary>
	/// ��������� ������� � ����� �������.
	/// </summary>
	/// <param name="newData">����������� �������</param>
	void pushBack(const T& newData);
	/// <summary>
	/// ��������� rvalue ������� � ����� �������.
	/// </summary>
	/// <param name="newData">����������� �������</param>
	void pushBack(T&& newData);
	/// <summary>
	/// "�������" ������� �� ������ �������
	/// \throw 	size=0
	/// </summary>
	/// <returns>������ ������� �������</returns>
	T popFront();
	/// <summary>
	 /// "�������" ������� �� ����� �������
	 /// \throw 	size=0
	 /// </summary>
	 /// <returns>��������� ������� �������</returns>
	T popBack();
	/// <summary>
	/// ����������� �����������.
	/// </summary>
	/// <param name="deque">������� �� ������� ���������� ��������</param>
	Deque<T>(const Deque<T>& deque);
	/// <summary>
	/// �������� ������������. 
	/// </summary>
	/// <param name="deque">������� �� ������� ���������� ��������</param>
	/// <returns>������� ������� �� �������� </returns>
	Deque<T> operator=(const Deque<T>& deque);
	/// <summary>
	/// Move-����������� �����������.
	/// </summary>
	/// <param name="deque">������� �� ������� ���������� ��������</param>
	Deque( Deque<T>&& deque);
	/// <summary>
	/// Move-�������� ������������.
	/// </summary>
	/// <param name="deque">������� �� ������� ���������� ��������</param>
	/// <returns>������� ������� �� ��������</returns>
	Deque<T> operator=( Deque<T>&& deque);
	/// <summary>
	/// ����������� �� 	\param std::initializer_list
	/// </summary>
	/// <param name="list">������ �������������</param>
	Deque<T>(const std::initializer_list<T>& list);
	/// <summary>
	/// �������� ������ 
	/// </summary>
	/// <typeparam name="T">��������� ��������</typeparam>
	/// <param name="out">����� ������</param>
	/// <param name="deque">������� �� ������� �������� ��������</param>
	/// <returns>������ �� ����� ������</returns>
	friend std::ostream& operator<< <>(std::ostream&,const Deque<T>&);
	///����������
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
inline Deque<T>::Deque(const std::initializer_list<T>& list)
{
	size = 0;
	first = nullptr;
	last = nullptr;
	for (auto elem : list)
		pushFront(elem);
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
inline void Deque<T>::pushFront( T&& newData)
{
	first = new Node(std::move(newData), nullptr, first);
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
inline void Deque<T>::pushBack(T&& newData)
{
	last = new Node(std::move(newData), last, nullptr);
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
	this->data = data;
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
inline Deque<T>::Node::Node( T&& data, Node* prev, Node* next)
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
		out << tmp->data<<" ";
		tmp = tmp->next;
	}
	return out;
	// TODO: insert return statement here
}


