#pragma once 

#include <ostream>

struct Segment {
	int pid; // if pid = -1, then the Segment represents a hole, otherwise the Segment is allocated to the process with the pid
	unsigned int start;
	unsigned int size; // size in bytes
	Segment* prev;
	Segment* next;
};

Segment* allocate(Segment** head, unsigned int pid, unsigned int size);

void deallocate(Segment* head, unsigned int pid);

void dump(std::ostream& o, Segment* head);
