#ifndef NANOS6_HELPERS_H
#define NANOS6_HELPERS_H

#include <pthread.h>


typedef struct {
	pthread_mutex_t _mutex;
	pthread_cond_t _cond;
	int _signaled;
} condition_variable_t;


#define COND_VAR_INIT {PTHREAD_MUTEX_INITIALIZER, PTHREAD_COND_INITIALIZER, 0}


void condition_variable_callback(void *untyped_arg);
void wait_condition_variable(condition_variable_t *cond_var);


#endif /* NANOS6_HELPERS_H */

