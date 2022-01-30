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
	pthread_mutex_lock(&philo->is_eating);
	if (philo->id == 1)
		pthread_mutex_lock(&philo->root->philos[philo->root->number_of_philo - 1].is_eating);
	else
		pthread_mutex_lock(&philo->root->philos[philo->id - 2].is_eating);
	if (philo->id == philo->root->number_of_philo)
		pthread_mutex_lock(&philo->root->philos[0].is_eating);
	else
		pthread_mutex_lock(&philo->root->philos[philo->id].is_eating);
	pthread_mutex_lock(philo->right);
	print_message(philo, FORK);
	pthread_mutex_lock(philo->left);
	print_message(philo, FORK);
}

void philo_do_eat(t_philo *philo)
{
	philo->last_eat = get_time();
	print_message(philo, EAT);
	usleep(philo->root->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->is_eating);
	if (philo->id == 1)
		pthread_mutex_unlock(&philo->root->philos[philo->root->number_of_philo - 1].is_eating);
	else
		pthread_mutex_unlock(&philo->root->philos[philo->id - 2].is_eating);
	if (philo->id == philo->root->number_of_philo)
		pthread_mutex_unlock(&philo->root->philos[0].is_eating);
	else
		pthread_mutex_unlock(&philo->root->philos[philo->id].is_eating);
	pthread_mutex_unlock(philo->right);
	pthread_mutex_unlock(philo->left);
	philo->eat_count++;
}

void philo_do_sleep(t_philo *philo)
{
	print_message(philo, SLEEP);
	usleep(philo->root->time_to_sleep * 1000);
}

void philo_do_think(t_philo *philo)
{
	print_message(philo, THINK);
}
