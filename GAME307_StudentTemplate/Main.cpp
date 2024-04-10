#include <iostream>
#include "GameManager.h"

int memoryAllocated, memoryDeallocated;

void* operator new(size_t count) {


	memoryAllocated += count;
	return malloc(count);

}

void operator delete(void* ptr, size_t sz) {


	memoryDeallocated += sz;

	free(ptr);

}
int main(int argc, char* args[]) { /// Standard C-style entry point, you need to use it

	GameManager *ptr = new GameManager();
	bool status  = ptr->OnCreate();
	if (status == true) {
		ptr->Run();
	} else if (status == false) {
		std::cerr << "Fatal error occured. Cannot start this program" << std::endl;
	}
	delete ptr;

	int memoryRemaining = memoryAllocated - memoryDeallocated;


	std::cout << "Total Memory Allocated: " << memoryAllocated << std::endl;
	std::cout << "Total Memory Deallocated: " << memoryDeallocated << std::endl;
	std::cout << "Total Memory Not Deallocated: " << memoryRemaining << std::endl;


	return 0;

}
