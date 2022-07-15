//
// Created by victor on 7/14/22.
//

#include "big_allocation.h"
#include "hash_func.h"
#include <nanos6/cluster.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

// types to use
typedef unsigned int a_t;

int run_allocation() {
  long KB = 1024;
  long MB = 1024*KB;
  long GB = 1024*MB;

  printf("Got before alloc\n");
  long alloc_size = MB; // tune this param
  unsigned long N = alloc_size / sizeof(a_t);
  a_t* ptr = (a_t*)(nanos6_dmalloc(1024,
                                               nanos6_equpart_distribution, 0,
                                               NULL));

  printf("Got after alloc\n");
  long seed = time(NULL);
  // fill
#pragma oss task for inout(ptr[0;N])
  for (unsigned i = 0; i < N; ++i) {
    ptr[i] = XXPMS32(i, seed);
  }
#pragma oss taskwait

  // verify
//  std::mt19937_64 gen(seed);
  srand(seed);

  for (int i = 0; i < 10000; ++i) {
    unsigned long sample = rand() % N;
    if(ptr[i] != XXPMS32(sample, seed)) {
      nanos6_dfree(ptr, alloc_size);
      return 0;
    }
  }

  nanos6_dfree(ptr, alloc_size);
  return 1;
}

