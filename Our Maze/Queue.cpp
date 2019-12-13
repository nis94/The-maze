#include "Queue.h"



Queue::Queue(int mazeHeight, int mazeWidth)
{
	m_size = mazeHeight * mazeWidth;	//	Determine size of queue.
	m_pArr = new Point[m_size]; // PROBLEM: Make sure calculation for array size is correct.
	// Check allocation

	head = 0;
	tail = -1;
	EnQueue(Point(0, 1));	//	Initialize the queue with the entrance point at 0,1.
}


Queue::~Queue() // Destructor
{
	delete[]m_pArr;
}


int Queue::addOne(int num) const
{
	return((1 + num) % m_size);
}


void Queue::MakeEmpty()
{
	head = 0;
	tail = -1;
}

bool Queue::isEmpty() const
{
	if (addOne(tail) == head)
		return true;
	else
		return false;
}

const Point& Queue::Front() const	// Show the first item, without removing.
{
	if (isEmpty())
	{
		exit(EMPTY_QUEUE);	//	MAKE THIS BETTER
	}
	return (m_pArr[head]);
}

bool Queue::EnQueue(const Point& p)	//	Insert point to the end\tail
{
	if (addOne(addOne(tail)) == head)	//	Add 2 because of the dummy space.
	{
		exit(FULL_QUEUE);
	}
	tail = addOne(tail);
	m_pArr[tail] = p;
	return true;
}

Point& Queue::DeQueue()	//	Remove and return head.
{
	if (isEmpty())
		exit(EMPTY_QUEUE);

	Point& res = m_pArr[head];	//	Take the head.
	head = addOne(head);	//	Advance head index.
	return res;

	// QUESTION: can we save a constructor by first having some temp index, and then using a move constructor in the return line for res?
	// Instead of creating res before?
}