/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 04:32:23 by cberganz          #+#    #+#             */
/*   Updated: 2022/02/07 17:34:20 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	free_all(t_root *root)
{
//	int	i;

	sem_close(root->forks_sem);	
	sem_close(root->print_sem);	
//	i = 0;
//	while (i < root->number_of_philo)
//	{
//		pthread_mutex_destroy(&root->philos[i].eating);
//		pthread_mutex_destroy(&root->forks[i]);
//		i++;
//	}
//	if (root->forks)
//		free(root->forks);
//	if (root->philos)
//		free(root->philos);
}

int	main(int argc, char *argv[])
{
	t_root			root;

	if (parse_args(argc, argv, &root))
		return (EXIT_FAILURE);
	if (init_sem(&root))
		return (EXIT_FAILURE);
	if (create_forks(&root, root.number_of_philo))
		return (EXIT_FAILURE);
	free_all(&root);
	return (EXIT_SUCCESS);
}
