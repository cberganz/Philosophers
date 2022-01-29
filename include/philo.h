/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 04:28:26 by cberganz          #+#    #+#             */
/*   Updated: 2022/01/29 16:57:16 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
//# include <time.h>

typedef struct s_philo
{
	int				id;
	int				eat_count;
	int				last_eat;
	pthread_t		thread;
	pthread_mutex_t	*right;
	pthread_mutex_t	*left;
	struct s_root	*root;
}	t_philo;

typedef struct s_root
{
	int				number_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_meals;
	int				start_time;
	int				finish;
	pthread_mutex_t	end;
	pthread_mutex_t	print;
	pthread_mutex_t	*forks;
	t_philo			*philos;	
}	t_root;

/*
**	Messages
*/

# define DIE "died"
# define EAT_ENOUGHT "TO CHANGE"
# define FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"

/*
**	Parsing
*/

int8_t	parse_args(int argc, char **args, t_root *root);

/*
**	Philo life
*/

void philo_do_take_fork(t_philo *philo);
void philo_do_eat(t_philo *philo);
void philo_do_sleep(t_philo *philo);
void philo_do_think(t_philo *philo);
void philo_do_die(t_philo *philo);

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

int	ft_atoi(const char *nptr);
int	get_time(void);
void	print_message(t_philo *philo, char *msg);

#endif
		
