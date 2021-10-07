#include "Deque.h"
int main()
{
	Deque<int> a;
	a.pushFront(5);
	a.pushBack(3);
	a.pushFront(4);
	a.pushBack(2);
	std::cout << a<<std::endl;
	Deque<std::string> s;
	s.pushBack("abc\n");
	s.pushFront("e");
	std::cout << s;
	/*int b=a.popBack();
	int k = a.popFront();
	int o = a.popBack();
	int y = a.popFront();*/
	Deque<int>b;
	b = std::move(a);
	std::cout << b << std::endl;
	Deque<double> d = {1.0,2.0,3.5};
	std::cout << d;
	return 0;
}
