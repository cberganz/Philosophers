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
	waitpid(philo->root->forks_pid[philo->i], &stat, WEXITSTATUS(stat));
	sem_wait(philo->root->first_sem);
	if (stat == 256)
	{
		i = 0;
		while (i < philo->root->number_of_philo)
		{
			if (i != philo->i)
				kill(philo->root->forks_pid[i], SIGKILL);
			i++;
		}
		sem_post(philo->root->end_sem);
	}
	else if (stat == 512)
		return (NULL);
		//philo->root->eat_enough_count++;
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
		if (get_time() >= (root->last_eat + root->time_to_die))
		{
			print_message(root, DIE);
			exit(1);
		}
		if (root->number_of_meals > 0 && root->eat_count >= root->number_of_meals)
			exit(2);
		my_usleep(5);
	}
	return (NULL);
}

void	philo_life(t_root *root)
{
//	root->eating_sem = sem_open("eating_sem", O_CREAT, 0600, 1);
	//sem_init(root->eating_sem, 0, 1); // Pas autorisé
//	if (root->eating_sem == SEM_FAILED)
//		return ;
	while (1)
	{
		philo_do_take_fork(root);
		philo_do_eat(root);
		philo_do_sleep(root);
		philo_do_think(root);
	}
}
