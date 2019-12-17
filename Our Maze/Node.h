#pragma warning(disable:4996)
#ifndef __NODE_H
#define __NODE_H
#include "Point.h"

class Node
{
	Point				m_point;
	Node*				m_next;

public:
	Node(const Point& p, Node* ptr = nullptr);
	Node(const Node& n);
	~Node();

public:
	inline bool			setPoint(Point& p);
	inline bool			setNext(Node* next);

	inline const Point&		getPoint()			const { return m_point; }
	inline const Node*		getNext()			const { return m_next; }

public:
	void				insertAfter(Node* new_node);
	Node*				deleteAfter(void); 

	friend class Stack; 
};
#endif // !__NODE_H