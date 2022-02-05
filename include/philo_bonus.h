/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 04:28:26 by cberganz          #+#    #+#             */
/*   Updated: 2022/02/05 16:02:39 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>
# include <stdio.h>
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/time.h>

# include <signal.h>
# include <limits.h>
# include <sys/time.h>
# include <sys/sem.h>
# include <semaphore.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct s_root
{
	int				number_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_meals;
	int				start_time;
	uint8_t			finish;
	sem_t			forks_sem;
	sem_t			print_sem;
	pid_t			*forks_pid;
	int				id;
	int				eat_count;
	int				last_eat;
	int				eat_enought;
	pthread_t		thread;
	pthread_mutex_t	eating;
}	t_root;

/*
**	Messages
*/

# define DIE "died"
# define EAT_ENOUGHT "All philosophers ate enought !"
# define FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define USAGE "Usage : ./philo nb_philo t_die t_eat t_sleep [nb_meals]"

/*
**	Parsing
*/

int8_t	parse_args(int argc, char **args, t_root *root);

/*
**	Philo life
*/

void	*philo_life(void *philo);
void	philo_master(t_root *root);
void	philo_do_take_fork(t_philo *philo);
void	philo_do_eat(t_philo *philo);
void	philo_do_sleep(t_philo *philo);
void	philo_do_think(t_philo *philo);
void	philo_do_die(t_philo *philo);

/*
**	Thread utils
*/	

int8_t	create_threads(t_root *root, int nb, void *(*func_ptr)(void *));
void	**join_threads(t_root *root, int nb, void **ret);
int8_t	create_mutex(t_root *root, int nb);
void	destroy_mutex(pthread_mutex_t *forks, int nb);

/*
**	Utils
*/

int		ft_atoi(const char *nptr);
int		get_time(void);
void	print_message(t_philo *philo, char *msg);
void	my_usleep(long int timetosleep);

#endif	
