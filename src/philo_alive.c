#include "philo.h"

//		if (philo->root->number_of_meals > 0
//			&& philo->eat_count >= philo->root->number_of_meals)
//		{
//			print_log(philo, MSG_LIMIT);
//			pthread_mutex_unlock(&philo->m_eat);
//			return ((void *)0);
//		}

void	philo_master(t_root *root)
{
	int	i;

	i = 0;
	while (1)
	{
		pthread_mutex_lock(&root->philos[i].eating);
		if (get_time() > (root->philos[i].last_eat + root->time_to_die))
		{
			print_message(&root->philos[i], DIE);
			root->finish = 1;
			return ;
		}
		pthread_mutex_unlock(&root->philos[i].eating);
		i++;
		if (i >= root->number_of_philo)
			i = 0;
	}
}

void	*philo_life(void *philo)
{
	while (1)
	{
		philo_do_take_fork(philo);
		philo_do_eat(philo);
		philo_do_sleep(philo);
		philo_do_think(philo);
		if (((t_philo *)philo)->root->finish == 1)
			break ;	
	}
	return (philo);
}
