/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_do.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 12:15:42 by cberganz          #+#    #+#             */
/*   Updated: 2022/01/29 11:08:18 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void philo_do_take_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->right);
	printf("%d %d has taken a fork\n", get_time() - philo->root->start_time, philo->id);		
	pthread_mutex_lock(philo->left);
	printf("%d %d has taken a fork\n", get_time() - philo->root->start_time, philo->id);
}

void philo_do_eat(t_philo *philo)
{
	philo->last_eat = get_time();
	printf("%d %d is eating\n", get_time() - philo->root->start_time, philo->id);		
	usleep(philo->root->time_to_eat * 1000);
	pthread_mutex_unlock(philo->right);
	pthread_mutex_unlock(philo->left);
	philo->eat_count++;
}

void philo_do_sleep(t_philo *philo)
{
	printf("%d %d is sleeping\n", get_time() - philo->root->start_time, philo->id);
	usleep(philo->root->time_to_sleep * 1000);
}

void philo_do_think(t_philo *philo)
{
	printf("%d %d is thinking\n", get_time() - philo->root->start_time, philo->id);
}

void philo_do_die(t_philo *philo)
{
	philo->root->finish = 1;
	printf("%d %d died\n", get_time() - philo->root->start_time, philo->id);
}
