/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 04:32:23 by cberganz          #+#    #+#             */
/*   Updated: 2022/01/29 17:31:11 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_checker(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
	//	pthread_mutex_lock(&philo->m_eat);
//		if (philo->root->number_of_meals > 0
//			&& philo->eat_count >= philo->root->number_of_meals)
//		{
//			print_log(philo, MSG_LIMIT);
//			pthread_mutex_unlock(&philo->m_eat);
//			return ((void *)0);
//		}
		if (get_time() > (philo->last_eat + philo->root->time_to_die))
		{
			print_message(philo, DIE);
			pthread_mutex_unlock(&philo->root->end);
//			pthread_mutex_unlock(&philo->m_eat);
			return ((void *)0);
		}
	//	pthread_mutex_unlock(&philo->m_eat);
		usleep(1000);
	}
}

void	*philo_life(void *philo)
{
	pthread_t	checker;

	if (pthread_create(&checker, 0, ft_checker, philo)
	|| pthread_detach(checker))
		return ((void *)1);
	while (1)
	{
		philo_do_take_fork(philo);
		philo_do_eat(philo);
		philo_do_sleep(philo);
		philo_do_think(philo);
	//	if (((t_philo *)philo)->root->finish == 1)
	//		break ;	
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
//	join_threads(&root, root.number_of_philo, NULL); // Handle error return
	pthread_mutex_lock(&root.end);
	destroy_mutex(root.forks, root.number_of_philo);
	return (EXIT_SUCCESS);
}
