/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 06:46:14 by cberganz          #+#    #+#             */
/*   Updated: 2022/01/29 17:31:10 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *nptr)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	while (nptr[i] == ' ' || (nptr[i] >= '\t' && nptr[i] <= '\r'))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = (result * 10) + (nptr[i] - '0');
		i++;
	}
	return (result * sign);
}

int	get_time(void)
{
	static struct timeval	time;
	int						ret;

	gettimeofday(&time, 0);
	ret = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (ret);
}
#include <string.h>
void	print_message(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->root->print);
	if (philo->root->finish == 0)
	{
		printf("%d %d %s\n", get_time() - philo->root->start_time, philo->id, msg);
		if (strcmp(msg, DIE) == 0 || strcmp(msg, EAT_ENOUGHT) == 0)
			philo->root->finish = 1;
	}
	pthread_mutex_unlock(&philo->root->print);
}
