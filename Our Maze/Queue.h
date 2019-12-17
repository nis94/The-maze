#pragma warning(disable:4996)
#ifndef __QUEUE_H
#define __QUEUE_H

#include "Point.h"

const int FULL_QUEUE = -10;
const int EMPTY_QUEUE = -20;

class Queue
{
private:
	Point*		m_pArr;
	int			m_size;
	int			head, tail;

	int	addOne(int num) const;

public:
	//Constructors
	Queue(int mazeHeight, int mazeWidth); // Receive height and width to know how much space to allocate for the point array.
	~Queue();

public:
	void				MakeEmpty();
	bool				isEmpty()		const;
	bool				EnQueue(const Point& p);	//	Add p to end of queue.
	Point				DeQueue();					//	Remove from start of queue.
	const Point&		Front()			const;
};
#endif 