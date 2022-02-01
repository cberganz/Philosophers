/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_do.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 12:15:42 by cberganz          #+#    #+#             */
/*   Updated: 2022/01/30 15:30:15 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void philo_do_take_fork(t_philo *philo)
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
		my_usleep(10);
		pthread_mutex_lock(philo->left);
		print_message(philo, FORK);
		pthread_mutex_lock(philo->right);
		print_message(philo, FORK);
	}
}

void philo_do_eat(t_philo *philo)
{
	print_message(philo, EAT);
	pthread_mutex_lock(&philo->eating);
	philo->last_eat = get_time();
	pthread_mutex_unlock(&philo->eating);
	my_usleep(philo->root->time_to_eat);
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(philo->right);
		pthread_mutex_unlock(philo->left);
	}
	else
	{
		pthread_mutex_unlock(philo->left);
		pthread_mutex_unlock(philo->right);
	}
	philo->eat_count++;
}

void philo_do_sleep(t_philo *philo)
{
	print_message(philo, SLEEP);
	my_usleep(philo->root->time_to_sleep);
}

void philo_do_think(t_philo *philo)
{
	print_message(philo, THINK);
}
