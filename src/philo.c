/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 04:32:23 by cberganz          #+#    #+#             */
/*   Updated: 2022/01/29 11:08:17 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_life(void *philo)
{
	while (1)
	{
		philo_do_take_fork(philo);
		philo_do_eat(philo);
		philo_do_sleep(philo);
		philo_do_think(philo);
		if ((get_time() - ((t_philo *)philo)->last_eat) > ((t_philo *)philo)->root->time_to_die)
			philo_do_die(philo);
		if (((t_philo *)philo)->root->finish == 1)
			break ;	
	}
	return (philo);
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
	join_threads(&root, root.number_of_philo, NULL); // Handle error return
	destroy_mutex(root.forks, root.number_of_philo);
	return (EXIT_SUCCESS);
}
