/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_do_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 12:15:42 by cberganz          #+#    #+#             */
/*   Updated: 2022/02/07 17:36:10 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philo_do_take_fork(t_root *root)
{
		sem_wait(root->forks_sem);
		print_message(root, FORK);
		if (root->number_of_philo != 1)
		{
				sem_wait(root->forks_sem);
				print_message(root, FORK);
		}
		else
				my_usleep(root->time_to_die);
}

void	philo_do_eat(t_root *root)
{
		print_message(root, EAT);
		pthread_mutex_lock(&root->eating);
		root->last_eat = get_time();
		root->eat_count++;
		if (root->number_of_meals > 0
			&& root->eat_count >= root->number_of_meals)
			root->eat_enought = 1;
		pthread_mutex_unlock(&root->eating);
		my_usleep(root->time_to_eat);
		sem_post(root->forks_sem);
		sem_post(root->forks_sem);
}

void	philo_do_sleep(t_root *root)
{
		print_message(root, SLEEP);
		my_usleep(root->time_to_sleep);
}

void	philo_do_think(t_root *root)
{
		print_message(root, THINK);
}
