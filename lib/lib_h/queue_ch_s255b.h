#ifndef QUEUE_CH_S255B_H	
#define QUEUE_CH_S255B_H

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define MAX_QUEUE_SIZE 256 //8-bits

typedef struct
{	
	char items[MAX_QUEUE_SIZE];
	uint8_t head;
	uint8_t tail;
} queue_ch;


void init_queue(queue_ch *q);
bool is_empty(queue_ch *q);
bool is_full(queue_ch *q);
int enqueue(queue_ch *q, char ch);
int dequeue(queue_ch *q);
int peek(queue_ch *q);
int print_queuq(queue_ch *q);

#endif