#include <iostream>

#include "mem.hpp"
#include "grade_util.hpp"

const int ALLOCATE_TC = 7;
const int DEALLOCATE_TC = 4;

std::pair<unsigned int, unsigned int> alloc_in[ALLOCATE_TC] = {{1, 5}, {0, 3}, {2, 6}, {3, 4}, {0, 2}, {4, 6}, {5, 3}};

unsigned int dealloc_in[DEALLOCATE_TC] = {0, 1, 3, 2};

RawSegment alloc_out[ALLOCATE_TC][10] = { 
	{{1, 0, 5}, {-1, 5, 45}}, 
	{{1, 0, 5}, {0, 5, 3}, {-1, 8, 42}},
	{{1, 0, 5}, {0, 5, 3}, {2, 8, 6}, {-1, 14, 36}},
	{{1, 0, 5}, {0, 5, 3}, {2, 8, 6}, {3, 14, 4}, {-1, 18, 32}},
	{{1, 0, 5}, {0, 5, 3}, {2, 8, 6}, {3, 14, 4}, {0, 18, 2}, {-1, 20, 30}},
	{{1, 0, 5}, {0, 5, 3}, {2, 8, 6}, {3, 14, 4}, {0, 18, 2}, {4, 20, 6}, {-1, 26, 24}},
	{{1, 0, 5}, {0, 5, 3}, {2, 8, 6}, {3, 14, 4}, {0, 18, 2}, {4, 20, 6}, {5, 26, 3}, {-1, 29, 21}} 
};

int alloc_out_sz[ALLOCATE_TC] = {2, 3, 4, 5, 6, 7, 8};

RawSegment dealloc_out[DEALLOCATE_TC][10] = {
	{{1, 0, 5}, {-1, 5, 3}, {2, 8, 6}, {3, 14, 4}, {-1, 18, 2}, {4, 20, 6}, {5, 26, 3}, {-1, 29, 21}},
	{{-1, 0, 8}, {2, 8, 6}, {3, 14, 4}, {-1, 18, 2}, {4, 20, 6}, {5, 26, 3}, {-1, 29, 21}},
	{{-1, 0, 8}, {2, 8, 6}, {-1, 14, 6}, {4, 20, 6}, {5, 26, 3}, {-1, 29, 21}},
	{{-1, 0, 20}, {4, 20, 6}, {5, 26, 3}, {-1, 29, 21}}
};

int dealloc_out_sz[DEALLOCATE_TC] = {8, 7, 6, 4};

double test_allocate() {
	double grade = 0;

	Segment* head = new Segment{.pid = -1, .start = 0, .size = 50, .prev = nullptr, .next = nullptr};
	Segment* correct_head;


	for (int i = 0; i < ALLOCATE_TC; i++) {
		allocate(&head, alloc_in[i].first, alloc_in[i].second);

		correct_head = mk_segments(alloc_out[i], alloc_out_sz[i]);
		bool test_passed = comp_list(correct_head, head, alloc_out_sz[i]);
		if (!test_passed) {
			std::cout << "Error in test case ALLOCATE_" << i << "\n";
			std::cout << "\tExpected list:\n\t\t";
			dump(std::cout, correct_head);
			std::cout << "\n\tGot:\n\t\t";
			dump(std::cout, head);
			std::cout << "\n";
		}

		grade += test_passed;
	}
	return (grade/ALLOCATE_TC);
}

double test_deallocate() {
	double grade = 0;

	Segment* head = mk_segments(alloc_out[ALLOCATE_TC-1], alloc_out_sz[ALLOCATE_TC-1]);
	Segment* correct_head;

	for (int i = 0; i < DEALLOCATE_TC; i++) {
		correct_head = mk_segments(dealloc_out[i], dealloc_out_sz[i]);

		deallocate(head, dealloc_in[i]);
		bool test_passed = comp_list(correct_head, head, dealloc_out_sz[i]);
		if (!test_passed) {
			std::cout << "Error in test case DEALLOCATE_" << i << "\n";
			std::cout << "\tExpected list:\n\t\t";
			dump(std::cout, correct_head);
			std::cout << "\n\tGot:\n\t\t";
			dump(std::cout, head);
			std::cout << "\n";
		}
		grade += test_passed;
	}
	return (grade/DEALLOCATE_TC);
}

int main() {
	double allocate_score = test_allocate();
	double deallocate_score = test_deallocate();

	std::cout << "Allocate score = " << 100*allocate_score << "%\n";

	std::cout << "Deallocate score = " << 100*deallocate_score << "%\n";

	std::cout << "Total (out of 100) = " << (allocate_score+deallocate_score)*50 << "%\n";
}
