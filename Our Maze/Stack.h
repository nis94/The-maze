#pragma warning(disable:4996)
#ifndef __STACK_H
#define __STACK_H

#include "Point.h"

class Node;

class Stack
{
private:
	Node* m_top;

public:
	Stack();
	~Stack();

	void makeEmpty();
	bool isEmpty();
	void push(const Point& point);
	Point pop();
	const Point& top(); 
};
#endif // !__STACK_H