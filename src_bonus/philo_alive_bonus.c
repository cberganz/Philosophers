/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_alive_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 12:31:45 by cberganz          #+#    #+#             */
/*   Updated: 2022/02/07 17:47:21 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*parent_master(void *arg)
{
	t_philo	*philo;
	int			stat;
	int			i;

	philo = (t_philo *)arg;
	waitpid(philo->root->forks_pid[philo->id], &stat, WEXITSTATUS(stat));
	if (stat == 256)
	{
//		philo->main->dead = 1;
		i = 0;
		while (i < philo->root->number_of_philo)
		{
			if (i != philo->id)
				kill(philo->root->forks_pid[i], SIGKILL);
			i++;
		}
	}
	else if (stat == 512)
		philo->root->eat_enough_count++;
	philo->root->finish = 1;
	return (NULL);
}

void	*child_master(void *arg)
{
	int	i;
	t_root	*root;

	i = 0;
	root = (t_root *)arg;
	while (1)
	{
		pthread_mutex_lock(&root->eating);
		if (get_time() > (root->last_eat + root->time_to_die))
		{
			print_message(root, DIE);
			exit(1);
//			pthread_mutex_unlock(&root->eating);
//			return (NULL);
		}
		if (root->eat_count >= root->number_of_meals)
			exit(2);
//			pthread_mutex_unlock(&root->eating);
//			return (NULL);
		pthread_mutex_unlock(&root->eating);
	}
	return (NULL);
}

void	philo_life(t_root *root)
{
	while (1)
	{
		philo_do_take_fork(root);
		philo_do_eat(root);
		philo_do_sleep(root);
		philo_do_think(root);
		if (root->finish == 1) // To remove ?
			break ;
	}
}
