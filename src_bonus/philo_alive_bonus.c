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
	{
		philo->root->eat_enough_count++;
		if (philo->root->eat_enough_count >= philo->root->number_of_philo)
		{
			philo->root->eat_enought = 1;
			sem_post(philo->root->end_sem);
		}
	}
	return (NULL);
}

void	free_child(t_root *root)
{
	my_usleep(root->time_to_die);
	if (pthread_join(root->thread, NULL))
		ft_exit(PTHREAD_JOIN_ERR);
	sem_close(root->forks_sem);
	sem_close(root->taking_fork_sem);
	sem_close(root->end_sem);
	sem_close(root->print_sem);
	if (root->philo)
		free(root->philo);
	if (root->threads)
		free(root->threads);
	if (root->forks_pid)
		free(root->forks_pid);
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
			free_child(root);
			exit(1);
		}
		if (root->eat_enought)
		{
			free_child(root);
			exit(2);
		}
		my_usleep(5);
	}
	return (NULL);
}

void	*philo_life(void *arg)
{
	t_root	*root;

	root = (t_root *)arg;
	while (root->finish != 1 && root->eat_enought != 1)
	{
		philo_do_take_fork(root);
		philo_do_eat(root);
		philo_do_sleep(root);
		philo_do_think(root);
	}
	return (NULL);
}
