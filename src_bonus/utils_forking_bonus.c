/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_forking_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 04:27:51 by cberganz          #+#    #+#             */
/*   Updated: 2022/02/07 17:49:58 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	create_forks(t_root *root, int nb)
{
	while (--nb >= 0)
	{
		root->forks_pid[nb] = fork();
		if (root->forks_pid[nb] == 0)
		{
			root->id = nb + 1;
			if (pthread_create(&root->thread, NULL, &philo_life, root))
				ft_exit(PTHREAD_CREATE_CHILD_ERR);
			child_master(root);
		}
	}
}

void	create_threads(t_root *root, int nb)
{
	t_philo	*philo;

	philo = (t_philo *)root->philo;
	while (--nb >= 0)
	{
		philo[nb].root = root;
		philo[nb].i = nb;
		if (pthread_create(&philo[nb].root->threads[nb], NULL, parent_master, &philo[nb]))
			ft_exit(PTHREAD_CREATE_PARENT_ERR);
	}
}

void	initialize_structures(t_root *root)
{
	sem_unlink("/forks_sem");
	sem_unlink("/print_sem");
	sem_unlink("/taking_fork_sem");
	sem_unlink("/eating_sem");
	root->last_eat = get_time();
	root->philo = malloc(root->number_of_philo * sizeof(t_philo));
	if (!root->philo)
		ft_exit(MALLOC_PHILO_ERR);
	root->threads = malloc(root->number_of_philo * sizeof(pthread_t));
	if (!root->threads)
		ft_exit(MALLOC_THREADS_ERR);
	root->forks_pid = malloc(root->number_of_philo * sizeof(pid_t));
	if (!root->forks_pid)
		ft_exit(MALLOC_FORKSPID_ERR);
	root->forks_sem = sem_open("/forks_sem", O_CREAT | O_EXCL, 0660, root->number_of_philo);
	if (root->forks_sem == SEM_FAILED)
		ft_exit(FORKSSEM_OPEN_ERR);
	root->print_sem = sem_open("/print_sem", O_CREAT | O_EXCL, 0660, 1);
	if (root->print_sem == SEM_FAILED)
		ft_exit(PRINTSEM_OPEN_ERR);
	root->taking_fork_sem = sem_open("/taking_fork_sem", O_CREAT | O_EXCL, 0600, 1);
	if (root->taking_fork_sem == SEM_FAILED)
		ft_exit(TAKINGFORKSEM_OPEN_ERR);
	root->eating_sem = sem_open("/eating_sem", O_CREAT | O_EXCL, 0600, 1);
	if (root->eating_sem == SEM_FAILED)
		ft_exit(EATINGSEM_OPEN_ERR);
}
