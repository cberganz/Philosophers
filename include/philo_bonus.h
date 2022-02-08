/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 04:28:26 by cberganz          #+#    #+#             */
/*   Updated: 2022/02/07 16:35:47 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>
# include <stdio.h>
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <semaphore.h>
# include <sys/time.h>
# include <sys/wait.h>

typedef struct s_root
{
	int				number_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_meals;
	int				eat_enough_count;
	int				start_time;
	uint8_t			finish;
	sem_t			*forks_sem;
	sem_t			*print_sem;
	pid_t			*forks_pid;
	int				id;
	int				eat_count;
	int				last_eat;
	int				eat_enought;
	pthread_t		*threads;
	pthread_t		thread;
	pthread_mutex_t	eating;
}	t_root;

typedef struct s_philo
{
	int	id;
	t_root	*root;
}	t_philo;

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

void	philo_life(t_root *root);
void	*parent_master(void *arg);
void	*child_master(void *arg);
void	philo_do_take_fork(t_root *root);
void	philo_do_eat(t_root *root);
void	philo_do_sleep(t_root *root);
void	philo_do_think(t_root *root);

/*
**	Thread utils
*/	

int8_t	create_forks(t_root *root, int nb);
void	kill_processes(t_root *root, int nb);
int	init_sem(t_root *root);
int8_t	create_threads(t_root *root, int nb);

/*
**	Utils
*/

int		ft_atoi(const char *nptr);
int		get_time(void);
void	print_message(t_root *root, char *msg);
void	my_usleep(long int timetosleep);

#endif	
