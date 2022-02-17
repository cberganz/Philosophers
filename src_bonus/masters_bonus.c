/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   masters_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 12:31:45 by cberganz          #+#    #+#             */
/*   Updated: 2022/02/17 11:06:21 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/*
**	Launched by the main process as a thread. Wait for a child process to exit.
**	It has to be launched once for each child process.
**	If the child exit code is 1 (case 256), every other child is killed.
**	If the child exit code is 2 (case 512), eat_enough_count is incremented.
*/

void	*parent_master(void *arg)
{
	t_philo		*philo;
	int			stat;
	int			i;

	philo = (t_philo *)arg;
	waitpid(philo->root->forks_pid[philo->i], &stat, WEXITSTATUS(stat));
	if (stat == 256)
	{
		i = 0;
		while (i < philo->root->number_of_philo)
		{
			if (i != philo->i)
				kill(philo->root->forks_pid[i], SIGKILL);
			i++;
		}
	}
	else if (stat == 512)
	{
		sem_wait(philo->root->eating_sem);
		philo->root->eat_enough_count++;
		if (philo->root->eat_enough_count >= philo->root->number_of_philo)
			philo->root->eat_enough = 1;
		sem_post(philo->root->eating_sem);
	}
	return (NULL);
}

/*
**	Launched by the main thread of a child process to check for his philosopher
**	death or eat_enough.
**	Variables are protected by eating semaphore when the philosopher is eating.
**	If the philosopher died, performs a clean exit whith exit code 1.
**	If the philosopher ate enough, performs a clean exit whith exit code 2.
**	parent_master() function then handle the exit statut.
*/

void	child_master(t_root *root)
{
	int		i;

	i = 0;
	while (1)
	{
		sem_wait(root->eating_sem);
		sem_wait(root->finish_sem);
		if (get_time() >= (root->last_eat + root->time_to_die))
		{
			sem_post(root->eating_sem);
			sem_post(root->finish_sem);
			print_message(root, DIE);
			free_child(root);
			exit(1);
		}
		sem_post(root->finish_sem);
		if (root->eat_enough)
		{
			sem_post(root->eating_sem);
			free_child(root);
			exit(2);
		}
		sem_post(root->eating_sem);
	}
}
