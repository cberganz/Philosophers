# Philosophers

| Project Name | philosophers |
| :-: | :-: |
| Description | An introduction to multithreading and forking using mutexes and semaphores |
| Technologies | <a href="#"><img alt="C" src="https://custom-icon-badges.demolab.com/badge/C-03599C.svg?logo=c-in-hexagon&logoColor=white&style=for-the-badge"></a> |
| External libraries | memset(), printf(), malloc(), free(), write(), usleep(), gettimeofday(), pthread_create(), pthread_detach(), pthread_join(), pthread_mutex_init(), pthread_mutex_destroy(), pthread_mutex_lock(), pthread_mutex_unlock() |
| Additional libraries for bonuses | fork(), kill(), exit(), waitpid(), sem_open(), sem_close(), sem_post(), sem_wait(), sem_unlink() |
| Final grade | 125/125 |

## Usage
```
git clone https://github.com/cberganz/Philosophers.git
cd Philosophers
make # or 'make bonus' forking version
./philo [number_of_philosophers] [time_to_die time_to_eat] [time_to_sleep] [number_of_times_each_philosopher_must_eat]
```

# PTHREADS
## PREREQUISITES

- Include : pthread.h
- Makefile : -pthread flag option

## WHAT

- Create a thread execute a fonction
- Create a variable pthread_t tname
- Invoque pthread_create(&tname, [attribute =NULL], &ft_ptr, [arg=null or to pass to ft_ptr])
- Invoque pthread_join(tname, NULL or pointer to received the return of the thread)
- pthread_create fonction return 0 if the thread has been created. Otherwise, you need to protect the call by placing it inside a if statement. Return an exit error if the thread has not been created or the join did not work as expected.

## DIFFERENCE THREAD AND PROCCESSES

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

## RACE CONDITIONS

Race condition is what happen when different threads are trying to read and modify the same variable at the same time. It results in undeterminate behaviour.

## MUTEX

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

## CREATE THREADS IN A LOOP

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

## GET RETURN VALUE FROM A THREAD

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

## HOW TO PASS ARGUMENTS TO THREADS

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

## SEMAPHORES

	#include <fcntl.h> // For O_* constants
	#include <sys/stat.h> // For mode constants
	#include <semaphore.h> 

	sem_t *sem_open(const char *name, int oflag, mode_t mode, unsigned int value)
	/*
	** oflag O_CREAT to create a new semaphore.
	** In case of creation, both mode and value args must be specified.
	*/

	int sem_close(sem_t *sem)
	/*
	** sem_close() closes the named semaphore referred to by sem, allowing any resources
	** that the system has allocated to the calling process for this semaphore to be freed.
	** return ) on success, -1 on error with errno set.
	*/

	int sem_post(sem_t *sem)
	/*
	** Link with -pthread
	** sem_post()  increments  (unlocks)  the semaphore pointed to by sem.
	** If the semaphore's value consequently becomes greater than zero, then 
	** another process or thread blocked in a sem_wait(3) call will be woken 
	** up and proceed to lock the semaphore.
	** returns 0 on success, -1 on error. In case of error, the value of the
	** semaphore is left unchaned and a errno setindicate the error.
	*/

	int sem_wait(sem_t *sem)
	/*
	** Decrement (locks) the semaphore pointed to by sem.
	** Return 0 on success, -1 and errno set on error.
	*/

	int sem_unlink(const char *name)
	/*
	** Link with -pthread
	** sem_unlink()  removes  the  named  semaphore referred to by name.
	** The semaphore name is removed immediately. The semaphore is destroyed 
	** once all other processes that have the semaphore open close it.
	** Returns 0 on success, -1 with errno set on error.
	*/

## FORK

	#include <sys/wait.h>
	pid_t waitpid(pid_t pid, int *stat_loc, int options)
	/*
	** wait for a child process to stop or terminate.
	*/

	#include <unistd.h>
	pid_t fork(void)
	/*
	** Create a new process
	** return -1 on error
	*/
