#include "Stack.h"
#include "Node.h"

#include <iostream>
using namespace std;

Stack::Stack()
{
	m_top = nullptr;
}

Stack::~Stack()
{
	makeEmpty();
}

void Stack::makeEmpty()
{
	Node* temp;
	while (this->m_top != nullptr)
	{
		temp = this->m_top;
		this->m_top = this->m_top->m_next;
		delete temp;
	}
}

bool Stack::isEmpty()
{
	return (this->m_top == nullptr);
}

void Stack::push(const Point& point)
{
	this->m_top = new Node(point, this->m_top);
}

Point Stack::pop()
{
	if (isEmpty()) { cout << "Error! Stack UnderFlow"; exit(1); }

	Node* temp = this->m_top;
	Point p = this->m_top->m_point;
	this->m_top = this->m_top->m_next;
	delete temp;
	return p;
}
const Point& Stack::top()
{
	return (this->m_top->m_point);
}
