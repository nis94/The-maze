#include "Queue.h"



Queue::Queue(int mazeHeight, int mazeWidth)
{
	m_size = mazeHeight * mazeWidth;	//	Determine size of queue. We need to cover all the board, and while the algorithm of solving a maze might add the same point twice, if we haven't visited it yet, we also remove points, so a queue of this size won't fill up, given the maximum dimensions here.
	m_pArr = new Point[m_size]; 
	if (!m_pArr) // Check allocation
		exit(1);

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
		exit(EMPTY_QUEUE);	
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

Point Queue::DeQueue()	//	Remove and return head.
{
	if (isEmpty())
		exit(EMPTY_QUEUE);

	Point& res = m_pArr[head];	//	Take the head.
	head = addOne(head);	//	Advance head index.
	return res;
}