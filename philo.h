/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 04:28:26 by cberganz          #+#    #+#             */
/*   Updated: 2022/01/28 12:27:56 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_philo
{
	int				id;
	int				eat_count;
	pthread_t		thread;
	pthread_mutex_t	*right;
	pthread_mutex_t	*left;
	struct s_root	*root;
	struct timeval	die_time;
}	t_philo;

typedef struct s_root
{
	int				number_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_meals;
	int				finish;
	pthread_mutex_t	*forks;
	t_philo			*philos;	
}	t_root;

/*
**	Parsing
*/

int8_t	parse_args(int argc, char **args, t_root *root);

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

#endif
		
