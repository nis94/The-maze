#include "Node.h"

Node::Node(const Point& p, Node* ptr) : m_point(p.getX(), p.getY()) 
{
	this->m_next = ptr;
}

Node::Node(const Node& n) : m_point(n.m_point)
{
	this->m_next = n.m_next;
}

Node::~Node() //d'tor
{
	// delete this->m_next;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Node::setPoint(Point& p)
{
	m_point = p;
	return true;
}

bool Node::setNext(Node* next)
{
	m_next = next;
	return true;
}




////////////////////////////////////////////////////////////////////////////////////////////////////////
void Node::insertAfter(Node* new_node)
{
	new_node->m_next = this->m_next;
	this->m_next = new_node;
}
Node* Node::deleteAfter(void)
{
	Node *temp = this->m_next;
	if (this->m_next == nullptr) { return nullptr; }
	this->m_next = temp->m_next;
	return temp;
}
