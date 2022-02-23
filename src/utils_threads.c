/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 04:27:51 by cberganz          #+#    #+#             */
/*   Updated: 2022/02/23 15:17:12 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_philo(t_root *root, int nb)
{
	root->philos[nb].id = nb + 1;
	root->philos[nb].eat_count = 0;
	root->philos[nb].eat_enough = 0;
	root->philos[nb].last_eat = get_time();
	root->philos[nb].root = root;
	root->philos[nb].right = &root->forks[nb];
	if (nb != 0)
		root->philos[nb].left = &root->forks[nb - 1];
	else
		root->philos[nb].left = &root->forks[root->number_of_philo - 1];
	pthread_mutex_init(&root->philos[nb].eating, NULL);
}

/*
**	Create nb threads and initialize t_philo stuctures for each.
**	Return 0 if everything worked as expected.
**	Return -1 on malloc() error.
**	Return -2 and free the pthread_t array on pthread_create() error.
*/

int8_t	create_threads(t_root *root, int nb, void *(*func_ptr)(void *))
{
	root->philos = malloc(nb * sizeof(t_philo));
	if (!root->philos)
	{
		printf("Malloc() error at create_threads().\n");
		free(root->forks);
		return (-1);
	}
	while (--nb >= 0)
	{
		init_philo(root, nb);
		if (pthread_create(&root->philos[nb].thread, NULL, func_ptr,
				(void *)&root->philos[nb]))
		{
			free(root->philos);
			free(root->forks);
			printf("Error at create_threads() while creating threads.\n");
			return (-2);
		}
	}
	return (0);
}

/*
**	Function that join nb threads and free the t_philo array.
**	If ret is not set to NULL, return a void** pointer to the threads returns.
**	Return NULL and free the t_philo array on pthread_join() error.
**	The array returned is NULL terminated so it require nb + 1 sized.
*/

int8_t	join_threads(t_root *root, int nb)
{
	while (--nb >= 0)
	{
		if (pthread_join(root->philos[nb].thread, NULL))
		{
			printf("Error while joining threads.\n");
			return (-1);
		}
	}
	return (0);
}

/*
**	Create nb mutex and setup the forks array with the mutex created.
**	Return 0 if everything worked as expected.
**	Return -1 in case of malloc() error while allocating the array.
*/

int8_t	create_mutex(t_root *root, int nb)
{
	root->forks = malloc(nb * sizeof(pthread_mutex_t));
	if (!root->forks)
	{
		printf("Malloc() error at create_mutex().\n");
		return (-1);
	}
	while (--nb >= 0)
		pthread_mutex_init(&root->forks[nb], NULL);
	pthread_mutex_init(&root->print, NULL);
	pthread_mutex_init(&root->finish_mut, NULL);
	pthread_mutex_init(&root->eat_enough_mut, NULL);
	return (0);
}
