/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_alive.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 12:31:45 by cberganz          #+#    #+#             */
/*   Updated: 2022/02/23 15:16:56 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

uint8_t	they_ate_enough(t_root *root)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	pthread_mutex_lock(&root->eat_enough_mut);
	while (i < root->number_of_philo)
	{
		if (root->philos[i].eat_enough == 1)
			count++;
		i++;
	}
	pthread_mutex_unlock(&root->eat_enough_mut);
	if (count >= root->number_of_philo)
		return (1);
	return (0);
}

void	philo_master(t_root *root)
{
	int	i;

	i = 0;
	while (1)
	{
		pthread_mutex_lock(&root->philos[i].eating);
		if (get_time() > (root->philos[i].last_eat + root->time_to_die))
		{
			print_message(&root->philos[i], DIE);
			pthread_mutex_unlock(&root->philos[i].eating);
			return ;
		}
		if (they_ate_enough(root))
		{
			print_message(&root->philos[i], EAT_ENOUGH);
			pthread_mutex_unlock(&root->philos[i].eating);
			return ;
		}
		pthread_mutex_unlock(&root->philos[i].eating);
		i++;
		if (i >= root->number_of_philo)
			i = 0;
	}
}

void	*philo_life(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		my_usleep(10);
	while (1)
	{
		philo_do_take_fork(philo);
		philo_do_eat(philo);
		philo_do_sleep(philo);
		philo_do_think(philo);
		pthread_mutex_lock(&philo->root->finish_mut);
		if (philo->root->finish == 1)
		{
			pthread_mutex_unlock(&philo->root->finish_mut);
			break ;
		}
		pthread_mutex_unlock(&philo->root->finish_mut);
	}
	return (NULL);
}
