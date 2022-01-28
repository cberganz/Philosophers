/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 04:32:23 by cberganz          #+#    #+#             */
/*   Updated: 2022/01/28 12:29:01 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_life(void *philo)
{
	printf("Hello from philosopher number %d. My right fork is %d, my left fork is %d\n", ((t_philo *)philo)->id, (int)((t_philo *)philo)->right, (int)((t_philo *)philo)->left);
}

int	main(int argc, char *argv[])
{
	t_root			root;
	pthread_t		*th_arr;
	pthread_mutex_t	*mutex_arr;

	if (parse_args(argc, argv, &root))
		return (EXIT_FAILURE);
	if (create_mutex(&root, root.number_of_philo))
		return (EXIT_FAILURE);
	if (create_threads(&root, root.number_of_philo, &philo_life))
		return (EXIT_FAILURE);
	join_threads(&root, root.number_of_philo, NULL);
	destroy_mutex(root.forks, root.number_of_philo);
	return (EXIT_SUCCESS);
}
