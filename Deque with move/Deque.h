#pragma once
#include <iostream>
template <class T>
class Deque;
/// <summary>
/// Оператор вывода 
/// </summary>
/// <typeparam name="T">Шаблонный параметр</typeparam>
/// <param name="out">поток вывода</param>
/// <param name="deque">Очередь из которой читаются элементы</param>
/// <returns>Ссылку на поток вывода</returns>
template<class T>
std::ostream& operator <<(std::ostream& out, const Deque<T>& deque);
/// <summary>
/// Шаблонный класс очереди с параметром \param T
/// </summary>
/// <typeparam name="T">тип хранимых элементов</typeparam>
template<class T>
class Deque {		 
	/// Внутренний класс узла.
	/**
	Хранит в себе данные типа \param T и хранит указатели на 
	предыдущий и следующий элемент. 
	*/
	struct Node{
		/// <summary>
		/// Конструктор, вставляющий элемент между двумя передаваемыми.
		/// </summary>
		/// <param name="newData">Передаваемые данные узла</param>
		/// <param name="prev">Указатеь на предыдущий элемент </param>
		/// <param name="next">Указатеь на следующий элемент</param>
		Node(const T& newData, Node* prev, Node* next);
		/// <summary>
		///  Конструктор, вставляющий элемент между двумя передаваемыми, поддерживающий 
		/// move семантику.
		/// </summary>
		/// <param name="newData">Передаваемые данные узла</param>
		/// <param name="prev">Указатеь на предыдущий элемент </param>
		/// <param name="next">Указатеь на следующий элемент</param>
		Node(T&& newData, Node* prev, Node* next);
		/// <summary>
		/// Данные узла.
		/// </summary>
		T data;
		/// <summary>
		/// Указатель на следующий элемент.
		/// </summary>
		Node* next;
		/// <summary>
		/// Указатель на предыдущий элемент.
		/// </summary>
		Node* prev;
	};
private:
	Node* first;
	Node* last;
	unsigned int size;
public:
	/// <summary>
	/// Базовый конструктор создающий пустую очередь содержащие элементы типа \param T 
	/// </summary>
	Deque<T>();
	/// <summary>
	/// Добавляет элемент в начало очереди.
	/// </summary>
	/// <param name="newData">Добавляемый элемент</param>
	void pushFront(const T& newData);
	/// <summary>
	/// Добавляет rvalue элемент в начало очереди.
	/// </summary>
	/// <param name="newData">Добавляемый элемент</param>
	void pushFront(T&& newData);
	/// <summary>
	/// Добавляет элемент в конец очереди.
	/// </summary>
	/// <param name="newData">Добавляемый элемент</param>
	void pushBack(const T& newData);
	/// <summary>
	/// Добавляет rvalue элемент в конец очереди.
	/// </summary>
	/// <param name="newData">Добавляемый элемент</param>
	void pushBack(T&& newData);
	/// <summary>
	/// "Вынимет" элемент из начала очереди
	/// \throw 	size=0
	/// </summary>
	/// <returns>первый элемент очереди</returns>
	T popFront();
	/// <summary>
	 /// "Вынимет" элемент из конца очереди
	 /// \throw 	size=0
	 /// </summary>
	 /// <returns>последний элемент очереди</returns>
	T popBack();
	/// <summary>
	/// Конструктор копирования.
	/// </summary>
	/// <param name="deque">очередь из которой копируются элементы</param>
	Deque<T>(const Deque<T>& deque);
	/// <summary>
	/// Оператор присваивания. 
	/// </summary>
	/// <param name="deque">очередь из которой копируются элементы</param>
	/// <returns>текущую очередь по значению </returns>
	Deque<T> operator=(const Deque<T>& deque);
	/// <summary>
	/// Move-конструктор копирования.
	/// </summary>
	/// <param name="deque">очередь из которой копируются элементы</param>
	Deque( Deque<T>&& deque);
	/// <summary>
	/// Move-оператор присваивания.
	/// </summary>
	/// <param name="deque">очередь из которой копируются элементы</param>
	/// <returns>текущую очередь по значению</returns>
	Deque<T> operator=( Deque<T>&& deque);
	/// <summary>
	/// Конструктор от 	\param std::initializer_list
	/// </summary>
	/// <param name="list">список инициализации</param>
	Deque<T>(const std::initializer_list<T>& list);
	/// <summary>
	/// Оператор вывода 
	/// </summary>
	/// <typeparam name="T">Шаблонный параметр</typeparam>
	/// <param name="out">поток вывода</param>
	/// <param name="deque">Очередь из которой читаются элементы</param>
	/// <returns>Ссылку на поток вывода</returns>
	friend std::ostream& operator<< <>(std::ostream&,const Deque<T>&);
	///Деструктор
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


