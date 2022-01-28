/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_do.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 12:15:42 by cberganz          #+#    #+#             */
/*   Updated: 2022/01/28 12:29:00 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void philo_do_taken_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->right);
	printf("timestamp_in_ms %d has taken a fork.\n", philo->id);		
	pthread_mutex_lock(philo->left);
	printf("timestamp_in_ms %d has taken a fork.\n", philo->id);		
}

void philo_do_eat(t_philo *philo)
{
	printf("timestamp_in_ms %d is eating.\n", philo->id);		
	usleep(philo->root->time_to_eat * 1000);
	philo->eat_count++;
}

void philo_do_sleep(t_philo *philo)
{
	printf("timestamp_in_ms %d is sleeping.\n", philo->id);
	usleep(philo->root->time_to_sleep * 1000);
}

void philo_do_think(t_philo *philo)
{
	printf("timestamp_in_ms %d is thinking.\n", philo->id);
}
