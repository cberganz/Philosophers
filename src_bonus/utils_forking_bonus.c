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

static void	init_philo(t_root *root, int nb)
{
	root->id = nb + 1;
	root->eat_count = 0;
	root->eat_enought = 0;
	root->last_eat = get_time();
}

/*
**	Create nb threads and initialize t_philo stuctures for each.
**	Return 0 if everything worked as expected.
**	Return -1 on malloc() error.
**	Return -2 and free the pthread_t array on pthread_create() error.
*/

int8_t	create_forks(t_root *root, int nb)
{
	pthread_mutex_init(&root->eating, NULL);
	root->forks_pid = malloc(nb * sizeof(pid_t));
	if (!root->forks_pid)
	{
		printf("Malloc() error at create_forks().\n");
		return (-1);
	}
	while (--nb >= 0)
	{
		root->forks_pid[nb] = fork();
		if (root->forks_pid[nb] == 0)
		{
			init_philo(root, nb);
			if (pthread_create(&root->thread, NULL, &philo_master, root)
				|| pthread_detach(root->thread))
			{
				printf("Error at create_forks()");
				return (-1);
			}
			if (philo_life(root)) // Doit etre mis en dehors du while car le process enfant ne connait pas les autres
				kill_processes(root, root->number_of_philo);
		}
		my_usleep(5);
	}
	return (0);
}

void	kill_processes(t_root *root, int nb)
{
	while (--nb >= 0)
		kill(root->forks_pid[nb], SIGKILL);
}

int	init_sem(t_root *root)
{
	sem_unlink("forks_sem");
	sem_unlink("print_sem");
	root->forks_sem = malloc(sizeof(sem_t));
	if (!root->forks_sem)
		return (-1);
	root->forks_sem = sem_open("forks_sem", O_CREAT, 0660, root->number_of_philo);
	if (root->forks_sem == SEM_FAILED)
		return (-1);
	root->print_sem = malloc(sizeof(sem_t));
	if (!root->print_sem)
		return (-1);
	root->print_sem = sem_open("print_sem", O_CREAT, 0660, 1); //IPC_CREAT
	if (root->print_sem == SEM_FAILED)
		return (-1);
	return (0);
}
