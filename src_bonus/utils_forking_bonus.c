/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_forking_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 04:27:51 by cberganz          #+#    #+#             */
/*   Updated: 2022/02/05 16:06:36 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_philo(t_root *root, int nb)
{
	root->id = nb + 1;
	root->eat_count = 0;
	root->eat_enought = 0;
	root->last_eat = get_time();
	pthread_mutex_init(&root->eating, NULL);
}

/*
**	Create nb threads and initialize t_philo stuctures for each.
**	Return 0 if everything worked as expected.
**	Return -1 on malloc() error.
**	Return -2 and free the pthread_t array on pthread_create() error.
*/

int8_t	create_forks(t_root *root, int nb, void *(*func_ptr)(void *))
{
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
			if (pthread_create(&root->thread, NULL, func_ptr, root)
				|| pthread_detach(main->thread))
			{
				printf("Error at create_forks()");
				return (-1);
			}
			philo_life(root);
		}
	}
	return (0);
}

int	init_sem(t_root *root)
{
	sem_unlink("forks_sem");
	sem_unlink("print_sem");
	root->forks_sem = sem_open("forks_sem", IPC_CREAT, 0660, root->nbr_philo);
	if (root->forks_sem == SEM_FAILED)
		return (-1);
	root->print_sem = sem_open("print_sem", IPC_CREAT, 0660, 1);
	if (root->print_sem == SEM_FAILED)
		return (-1);
	return (0);
}
