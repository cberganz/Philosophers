/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_forking_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 04:27:51 by cberganz          #+#    #+#             */
/*   Updated: 2022/02/23 15:16:40 by cberganz         ###   ########.fr       */
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
				ft_exit(PTHREAD_CREATE_CHILD_ERR, root);
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
		if (pthread_create(&philo[nb].root->threads[nb],
				NULL, parent_master, &philo[nb]))
			ft_exit(PTHREAD_CREATE_PARENT_ERR, root);
	}
}

void	join_threads(t_root *root, int nb)
{
	while (--nb >= 0)
	{
		if (pthread_join(root->threads[nb], NULL))
			printf("Error while joining threads.\n");
	}
}
