/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_do.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 12:15:42 by cberganz          #+#    #+#             */
/*   Updated: 2022/01/29 16:48:28 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void philo_do_take_fork(t_philo *philo)
{
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
