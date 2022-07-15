#include "nanos6-helpers.h"


/* Signal the condition variable */
void condition_variable_callback(void *untyped_arg)
{
	condition_variable_t *cond_var = (condition_variable_t *) untyped_arg;

	pthread_mutex_lock(&cond_var->_mutex);
	cond_var->_signaled = 1;
	pthread_cond_signal(&cond_var->_cond);
	pthread_mutex_unlock(&cond_var->_mutex);
}


/* Wait for the condition variable to be signaled */
void wait_condition_variable(condition_variable_t *cond_var)
{
	pthread_mutex_lock(&cond_var->_mutex);
	while (cond_var->_signaled == 0) {
		pthread_cond_wait(&cond_var->_cond, &cond_var->_mutex);
	}
	pthread_mutex_unlock(&cond_var->_mutex);
}

