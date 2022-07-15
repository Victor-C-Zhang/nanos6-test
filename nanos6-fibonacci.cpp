#include "nanos6-fibonacci.h"

long nanos6_fibonacci(long index) {
	if (index <= 1) {
		return index;
	}
	
	long result1, result2;
	
	#pragma oss task shared(result1) label("fibonacci")
	result1 = nanos6_fibonacci(index-1);
	
	#pragma oss task shared(result2) label("fibonacci")
	result2 = nanos6_fibonacci(index-2);
	
	#pragma oss taskwait
	return result1 + result2;
}


