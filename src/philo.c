/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 04:32:23 by cberganz          #+#    #+#             */
/*   Updated: 2022/01/30 14:10:39 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_all(t_root *root)
{
	int	i;

	pthread_mutex_destroy(&root->print);
	i = 0;
	while (i < root->number_of_philo)
	{
		pthread_mutex_destroy(&root->philos[i].eating);
		pthread_mutex_destroy(&root->forks[i]);
		i++;
	}
	free(root->forks);
	free(root->philos);
}

int	main(int argc, char *argv[])
{
	t_root			root;

	if (parse_args(argc, argv, &root))
		return (EXIT_FAILURE);
	if (create_mutex(&root, root.number_of_philo))
		return (EXIT_FAILURE);
	if (create_threads(&root, root.number_of_philo, &philo_life))
		return (EXIT_FAILURE);
	philo_master(&root);
	join_threads(&root, root.number_of_philo, NULL);
	free_all(&root);
	return (EXIT_SUCCESS);
}
