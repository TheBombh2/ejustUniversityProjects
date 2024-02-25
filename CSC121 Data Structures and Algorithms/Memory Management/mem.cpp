#include <iostream>
#include "mem.hpp"


// Return the allocated segment. If no place found, return nullptr
Segment* allocate(Segment** head, unsigned int pid, unsigned int size) 
{
	//First head inserted [Hole, start = 0, size = 50]
	Segment* Temp = (*head);
	bool found = false;
	while (Temp != nullptr || (*head)->next == nullptr) {
		if (Temp->pid == -1 && Temp->size >= size) {
			found = true;
			break;
		}
		else {
			Temp = Temp->next;
		}
	}

	if (found == false) {
		return nullptr;
	}
	if ((*head)->next == nullptr) {
		Segment* New = new(Segment);
		New->next = Temp;
		New->prev = nullptr;
		New->size = size;
		New->pid = pid;
		New->start = Temp->start;
		Temp->start = New->start + New->size;
		Temp->size -= New->size;
		Temp->prev = New;
		(*head) = New;
		if (Temp->size == 0) {
			New->next = nullptr;
			delete Temp;
		}
		

		return New;
	}








	Segment* TempPre = (*head);
	while (TempPre->next != Temp) {
		TempPre = TempPre->next;
	}

	Segment* New = new(Segment);
	New->size = size;
	New->start = TempPre->start + TempPre->size;
	New->pid = pid;
	Temp->size = Temp->size - New->size;
	
	if (Temp->size == 0) {
		New->next = Temp->next;
		New->prev = Temp->prev;
		TempPre->next = New;
		delete Temp;
		return New;
	}
	New->prev = Temp->prev;
	Temp->prev = New;
	TempPre->next = New;
	Temp->start = New->start + New->size;
	New->next = Temp;
	

	return New;


}

// Free all segments allocated to process
void deallocate(Segment* head, unsigned int pid) {
	Segment* Temp = head;


	
	bool RightCheck = false;
	bool LeftCheck = false;

	bool found = false;
	while (Temp->next != nullptr) {

		if (head->pid == -1 && head->next->pid == -1) {

			head->size += head->next->size;
			head->next = head->next->next;
			head->next->start = head->size + head->start;

		}


		if (Temp->pid == pid) 
		{

			if (Temp->prev == nullptr) {
				Temp->size += Temp->next->size;
				if (Temp->next->next != nullptr) {
					Temp->next->next->start = Temp->start + Temp->size;
				}Temp->next = Temp->next->next;
				Temp->pid = -1;
				continue;
			}

			found = true;

			if (Temp->next == nullptr ) {
				Temp->pid = -1;
				continue;
			}
			else 
			{

				if(Temp->next != nullptr){
				if (Temp->next->pid == -1) {
					RightCheck = true;
					

				}}

				if (Temp->prev != nullptr){
					if (Temp->prev->pid == -1) {
						LeftCheck = true;
						
					}
					
					
				}










				if (RightCheck) {

					Temp->size += Temp->next->size;
					if (Temp->next->next != nullptr) {
						Temp->next->next->start = Temp->start + Temp->size;
					}Temp->next = Temp->next->next;
					Temp->pid = -1;
					
					continue;
				}

				if (LeftCheck) {
					Temp->prev->size += Temp->size;
					Temp->next->start = Temp->prev->size + Temp->prev->start;
					Temp->prev->next = Temp->next;
					delete Temp;
						
					continue;

				}

				if (!LeftCheck && !RightCheck) {
					Temp->pid = -1;
					continue;
				}






			}



		}

		Temp = Temp->next;
	}



	if (found == false) {
		return;
	}


}

// For debugging/testing
// You can use this to print a list as follow: dump(std::cout, list_head)
//
// DO NOT EDIT
void dump(std::ostream& o, Segment* head) {
	while (head != nullptr) {
		o << "(" << (( head->pid == -1 )? "H":"P") << ", " << head->start << ", " << head->size << ") " << "--> ";
		head = head->next;
	}
	o << "NULL";
}

#ifndef GRADING // Don't delete

int main() {
	// You don't need to write anything here, but you can use it to try out your program
	Segment* Mem = new(Segment);
	Mem->size = 50;
	Mem->next = nullptr;
	Mem->prev = nullptr;
	Mem->start = 0;
	Mem->pid = -1;
	Segment* Head = Mem;
	allocate(&Head, 1, 5);
	allocate(&Head, 0, 3);
	allocate(&Head, 2, 6);
	allocate(&Head, 3, 4);
	allocate(&Head, 0, 2);
	allocate(&Head, 4, 6);
	allocate(&Head, 5, 3);
	dump(std::cout, Head);
	std::cout << "\n";

	deallocate(Head, 0);
	dump(std::cout, Head);
	std::cout << "\n";

	deallocate(Head, 1);
	dump(std::cout, Head);
	std::cout << "\n";

	deallocate(Head, 3);
	dump(std::cout, Head);
	std::cout << "\n";

	deallocate(Head, 2);
	dump(std::cout, Head);
	std::cout << "\n";





	return 0;
}

#endif // Don't delete
