#include "queue_ch_s255b.h"

void init_queue(queue_ch *q)
{
	q->head = -1;	//last position that needs to be read/emptied
	q->tail = 0;	//next position that needs to be filled
}

bool is_empty(queue_ch *q)
{
	return (q->tail == q->head + 1);
}

bool is_full(queue_ch *q)
{
	return (q->tail == q->head);
}

int enqueue(queue_ch *q, char ch)
{
	if(is_full(q))
	{
		printf("queue_ch_s256b.c : queue_ch is full !!!"); //supressed for better CLI output
		return -1;
	}
	
	q->items[q->tail] = ch;
	q->tail++;
	return 0;
}

int dequeue(queue_ch *q)
{	
	if(is_empty(q))
	{
		printf("queue_ch_s256b.c : queue_ch is empty !!!"); //supressed for better CLI output
		return -1;
	}

	return (q->items[++q->head]);
}

int peek(queue_ch *q)
{
	if(is_empty(q))
	{
		printf("queue_ch_s256b.c : queue_ch is empty !!!"); //supressed for better CLI output
		return -1;
	}

	return (q->items[q->head + 1]);
}

int print_queuq(queue_ch *q)
{
	if(is_empty(q))
	{
		printf("queue_ch_s256b.c : queue_ch is empty !!!"); //supressed for better CLI output
		return -1;
	}
	
	printf("Current character queue : ");
	for(uint8_t i = q->head + 1; i< q->tail; i++)
	{
		printf("%c ", q->items[i]);
	}
	printf("\n");
	return 0;
}