#pragma once

#include "mem.hpp"

struct RawSegment {
	int pid;
	unsigned int start;
	unsigned int size;
};

Segment* mk_segments(RawSegment* segs, int size);

bool comp_list(Segment* list1, Segment* list2, int size);
