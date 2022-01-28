## PTHREADS ##

#PREREQUISITES

- Include : pthread.h
- Makefile : -pthread flag option

#WHAT

- Create a thread execute a fonction
- Create a variable pthread_t tname
- Invoque pthread_create(&tname, [attribute =NULL], &ft_ptr, [arg=null or to pass to ft_ptr])
- Invoque pthread_join(tname, NULL or pointer to received the return of the thread)
- pthread_create fonction return 0 if the thread has been created. Otherwise, you need to protect the call by placing it inside a if statement. Return an exit error if the thread has not been created or the join did not work as expected.

#DIFFERENCE THREAD AND PROCCESSES

- Processes :
	int pid = fork();
	if (pid == -1){
		return ERROR;
	}
	ACTIONS
	if (pid != 0){
		wait(NULL);
	}
	--> Will execute ACTIONS 2 times : one from main process, one from fork process with the id pid.
	--> Forking will create a copy of all current variables of the process.
- Pthread : 
	--> will execute ACTIONS 2 times with the same pid.
	--> Threading will use the same variables for all threads leading to issues when different threads are trying to access the same variable.

#RACE CONDITIONS

Race condition is what happen when different threads are trying to read and modify the same variable at the same time. It results in undeterminate behaviour.

#MUTEX

Mutex is one of the possible solutions to the race condition issue. A mutex is a sort of lock. it consist in a boolean variable define to 1 if a variable is locked or 0 if its not locked.
Here is a simple implementation of a mutex varible :

	pthread_mutex_t mutex;
	ft(){
		pthread_mutex_lock(&mutex);
		ACTIONS ON VARIABLE
		pthread_mutex_unlock(&mutex);
	}
	main (){
		pthread_t tname;

		pthread_mutex_init(&mutex, NULL);
		if (pthread_create(&tname, NULL, &ft, NULL) != 0){
			return ERROR;
		}
		if (pthread_join(tname, NULL) != 0){
			return ERROR;
		}
		pthread_mutex_destroy(&mutex);
	}

#CREATE THREADS IN A LOOP

	pthread_t threads[4];
	while (i < 4){
		if (pthread_create(threads + i, NULL, &ft, NULL) != 0){
			return ERROR;
		}
	}
	while (i < 4){
		if (pthread_join(threads[i], NULL) != 0){
			return ERROR;
		}
		
	}
--> Pay attention not joining the threads in the first while loop or thread n+1 will be creating only when the thread n is finished, wich is not the expected behaviour.

#GET RETURN VALUE FROM A THREAD

--> To get return value of a fonction executed by a thread, we use the second parameter of the pthread_join(pthread_t tname, void **thread_return) fonction.
--> The fonction called by a thread must be prototyped as : void *ft([args]). The thread return is a pointer to that void *ptr.

	void *ft(){
		int value;
		value = malloc(sizeof(int)); // Allocating because you cannot return a local variable.
		value = 6;
		return (void *)&value;
	}
	int main(){
		int	*res;
		...creating thread, etc.
		if (pthread_join(tname, (void **)&res) != 0){
			return ERROR;
		}
		// Nowhere, &res is &value : the pointers values are the same.
		free(res);
	}

#HOW TO PASS ARGUMENTS TO THREADS

	#include <stdio.h>
	#include <stdlib.h>
	#include <pthread.h>
	#include <unistd.h>

	int primes[10] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29 };

	void* routine(void* arg) {
	    sleep(1);
	    int index = *(int*)arg;
	    printf("%d ", primes[index]);
	    free(arg); // You need to free memory here to avoid deallocating memory before it has been used
	}

	int main(int argc, char* argv[]) {
	    pthread_t th[10];
	    int i;
	    for (i = 0; i < 10; i++) {
	        int* a = malloc(sizeof(int)); // (1) Here you need to allocate a because passing the same pointer to multiple threads give them a value changed dynamicaly changed in the main.
	        *a = i;
	        if (pthread_create(&th[i], NULL, &routine, a) != 0) {
	            perror("Failed to created thread");
	        }
	    }
	    for (i = 0; i < 10; i++) {
	        if (pthread_join(th[i], NULL) != 0) {
	            perror("Failed to join thread");
	        }
			// (2) You can also deallocate the pointer here if the routine function return that pointer
	    }
    	
    	return 0;
	}
	--> (1) Another better solution to avoid allocating memory here would be sending prime + i pointer to routine !
	--> (2) Also here arg is deallocated in the routine function. The best practice is to modify its value in order to use it as return value of the routine. That way you can free memory in the function it has been allocated. This practice prevent from many memory errors to make it easier handling them.
