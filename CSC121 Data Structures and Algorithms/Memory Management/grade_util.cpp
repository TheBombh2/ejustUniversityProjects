#include "grade_util.hpp"
#include "mem.hpp"

Segment* mk_segments(RawSegment* segs, int size) {
	if (size == 0)
		return nullptr;

	Segment** head = new Segment*;
	Segment** next_seg = head;
	Segment* last_seg = nullptr;

	for (RawSegment* p = segs+size-1; p >= segs; p--) {
		head = next_seg;
		Segment* new_seg = new Segment;
		new_seg->pid = p->pid;
		new_seg->start = p->start;
		new_seg->size = p->size;
		new_seg->next = last_seg;

		if (last_seg != nullptr) {
			last_seg->prev = new_seg;
		}

		*head = new_seg;

		next_seg = &((*head)->prev);
		last_seg = *head;
	}
	
	return *head;
}

bool comp_list(Segment* list1, Segment* list2, int size) {
	while ( (list1 != nullptr) && (list2 != nullptr) ) {
		if ( 
			list1->pid != list2->pid ||
			list1->start != list2->start ||
			list1->size != list2->size 
		   )
			return false;
		list1 = list1->next;
		list2 = list2->next;
	}
	return (list1 == nullptr) && (list2 == nullptr);
}


