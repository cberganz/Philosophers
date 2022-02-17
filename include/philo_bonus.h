/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 04:28:26 by cberganz          #+#    #+#             */
/*   Updated: 2022/02/17 10:43:21 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>
# include <stdio.h>
# include <string.h>
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <limits.h>
# include <semaphore.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <sys/ipc.h>

typedef struct s_root
{
	int				number_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_meals;
	int				eat_enough_count;
	int				start_time;
	int				finish;
	sem_t			*forks_sem;
	sem_t			*print_sem;
	sem_t			*taking_fork_sem;
	sem_t			*end_sem;
	sem_t			*eating_sem;
	sem_t			*finish_sem;
	pid_t			*forks_pid;
	int				id;
	int				eat_count;
	int				last_eat;
	int				eat_enough;
	pthread_t		*threads;
	pthread_t		thread;
	pthread_mutex_t	eating;
	void			*philo;
}	t_root;

typedef struct s_philo
{
	int		i;
	t_root	*root;
}	t_philo;

/*
**	Messages
*/

# define DIE "died"
# define EAT_ENOUGH "All philosophers ate enough !"
# define FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"

/*
**	Arguments parsing and structures initialization.
*/

void	parse_arguments(int argc, char **args, t_root *root);

/*
**	Philo life and mastering.
*/

void	*philo_life(void *arg);
void	*parent_master(void *arg);
void	child_master(t_root *root);

/*
**	Process and threads utils.
*/	

void	create_forks(t_root *root, int nb);
void	create_threads(t_root *root, int nb);
void	join_threads(t_root *root, int nb);

/*
**	Utils.
*/

int		ft_atoi(const char *nptr);
int		get_time(void);
void	print_message(t_root *root, char *msg);
void	my_usleep(long int timetosleep);

/*
**	Processes clean exit.
*/

void	ft_exit(int exit_code, t_root *root);
void	free_parent(t_root *root);
void	free_child(t_root *root);

# define USAGE_ERR 2
# define USAGE "Usage : ./philo nb_philo t_die t_eat t_sleep [nb_meals]"
# define ARGS_ERR 3
# define ARGS "Error : Invalid arguments."
# define MALLOC_PHILO_ERR 4
# define MALLOC_PHILO "Error : malloc() t_philo structures."
# define MALLOC_THREADS_ERR 5
# define MALLOC_THREADS "Error : malloc() pthread_t *threads."
# define MALLOC_FORKSPID_ERR 6
# define MALLOC_FORKSPID "Error : malloc() pid_t *forks_pid."
# define FORKSSEM_OPEN_ERR 7
# define FORKSSEM_OPEN "Error : sem_open() on forks_sem."
# define PRINTSEM_OPEN_ERR 8
# define PRINTSEM_OPEN "Error : sem_open() on print_sem."
# define TAKINGFORKSEM_OPEN_ERR 9
# define TAKINGFORKSEM_OPEN "Error : sem_open() on taking_fork_sem."
# define EATINGSEM_OPEN_ERR 10
# define EATINGSEM_OPEN "Error : sem_open() on eating_sem."
# define FINISHSEM_OPEN_ERR 11
# define FINISHSEM_OPEN "Error : sem_open() on finish_sem."
# define PTHREAD_CREATE_CHILD_ERR 12
# define PTHREAD_CREATE_CHILD "Error : pthread_create() on child thread."
# define PTHREAD_CREATE_PARENT_ERR 13
# define PTHREAD_CREATE_PARENT "Error : pthread_create() on parent thread."
# define PTHREAD_JOIN_ERR 14
# define PTHREAD_JOIN "Error : pthread_join() on child thread."

static const char	**g_error_messages = ((const char *[15]){NULL, NULL, USAGE,
		ARGS, MALLOC_PHILO, MALLOC_THREADS, MALLOC_FORKSPID, FORKSSEM_OPEN,
		PRINTSEM_OPEN, TAKINGFORKSEM_OPEN, EATINGSEM_OPEN, FINISHSEM_OPEN
		PTHREAD_CREATE_CHILD, PTHREAD_CREATE_PARENT, PTHREAD_JOIN});

#endif	
