/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_do.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 12:15:42 by cberganz          #+#    #+#             */
/*   Updated: 2022/02/02 13:47:31 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_do_take_fork(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right);
		print_message(philo, FORK);
		pthread_mutex_lock(philo->left);
		print_message(philo, FORK);
	}
	else
	{
		pthread_mutex_lock(philo->left);
		print_message(philo, FORK);
		if (philo->root->number_of_philo != 1)
		{
			pthread_mutex_lock(philo->right);
			print_message(philo, FORK);
		}
		else
			my_usleep(philo->root->time_to_die);
	}
}

void	philo_do_eat(t_philo *philo)
{
	print_message(philo, EAT);
	pthread_mutex_lock(&philo->eating);
	philo->last_eat = get_time();
	philo->eat_count++;
	if (philo->root->number_of_meals > 0
		&& philo->eat_count >= philo->root->number_of_meals)
	{
		pthread_mutex_lock(&philo->root->eat_enough_mut);
		philo->eat_enought = 1;
		pthread_mutex_unlock(&philo->root->eat_enough_mut);
	}
	pthread_mutex_unlock(&philo->eating);
	my_usleep(philo->root->time_to_eat);
	pthread_mutex_unlock(philo->right);
	if (philo->root->number_of_philo != 1)
		pthread_mutex_unlock(philo->left);
}

void	philo_do_sleep(t_philo *philo)
{
	print_message(philo, SLEEP);
	my_usleep(philo->root->time_to_sleep);
}

void	philo_do_think(t_philo *philo)
{
	print_message(philo, THINK);
}
