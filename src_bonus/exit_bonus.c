#include "philo_bonus.h"

/*
**	Print error message, call free_all() and exit with exit_code.
**	The set of exit codes and error messages is specified in header file.
*/

void	ft_exit(int exit_code, t_root *root)
{
	printf("%s\n", error_messages[exit_code]);
	free_parent(root);
	exit(exit_code);
}

/*
**	This function clear the parent process memory before exit.
**	Unlink named semaphores and close them.
**	Close named semaphores using sem_close() function.
**	sem_close() function performs error return if a semaphore does not exist.
**	Free memory allocated with malloc().
*/

void	free_parent(t_root *root)
{
	sem_unlink("/forks_sem");
	sem_unlink("/print_sem");
	sem_unlink("/taking_fork_sem");
	sem_unlink("/eating_sem");
	sem_unlink("/finish_sem");
	sem_close(root->forks_sem);	
	sem_close(root->print_sem);
	sem_close(root->taking_fork_sem);
	sem_close(root->eating_sem);
	sem_close(root->finish_sem);
	if (root->philo)
		free(root->philo);
	if (root->threads)
		free(root->threads);
	if (root->forks_pid)
		free(root->forks_pid);
}

/*
**	This function clear a child process memory before exit.
**	Join the thread running philo_life() function.
**	Close named semaphores using sem_close() function.
**	sem_close() function performs error return if a semaphore does not exist.
**	Free memory allocated with malloc().
*/

void	free_child(t_root *root)
{
	if (pthread_join(root->thread, NULL))
		ft_exit(PTHREAD_JOIN_ERR, root);
	sem_close(root->forks_sem);
	sem_close(root->taking_fork_sem);
	sem_close(root->print_sem);
	sem_close(root->eating_sem);
	sem_close(root->finish_sem);
	if (root->philo)
		free(root->philo);
	if (root->threads)
		free(root->threads);
	if (root->forks_pid)
		free(root->forks_pid);
}

