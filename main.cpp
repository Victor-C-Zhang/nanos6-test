#include <nanos6/bootstrap.h>
#include <nanos6/library-mode.h>

#include <cstdio>
#include <cstdlib>
#include <iostream>

#include "big_allocation.h"


int main(int argc, char **argv) {
	std::cout << run_allocation() << std::endl;

	return 0;
}

