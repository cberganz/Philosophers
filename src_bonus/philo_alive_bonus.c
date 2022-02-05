/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_alive_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 12:31:45 by cberganz          #+#    #+#             */
/*   Updated: 2022/02/05 16:06:34 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

uint8_t	ate_enought(t_root *root) // to modify
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (root->eat_enought == 1)
		count++;
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
		pthread_mutex_lock(&root->eating);
		if (get_time() > (root->last_eat + root->time_to_die))
		{
			print_message(&root, DIE);
			pthread_mutex_unlock(&root->eating);
			return ;
		}
		if (ate_enought(root))  // find way to print only once and close all processes
		{
			print_message(&root, EAT_ENOUGHT);
			pthread_mutex_unlock(&root->eating);
			return ;
		}
		pthread_mutex_unlock(&root->eating);
	}
}

void	*philo_life(void *arg)
{
	t_philo	*root;

	root = (t_root *)arg;
	while (1)
	{
		philo_do_take_fork(root);
		philo_do_eat(root);
		philo_do_sleep(root);
		philo_do_think(root);
		if (root->finish == 1) // To remove ?
			break ;
	}
	return (NULL);
}
