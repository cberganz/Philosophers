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

static int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	get_time(void)
{
	static struct timeval	time;
	int						ret;

	gettimeofday(&time, 0);
	ret = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (ret);
}

void	my_usleep(long int timetosleep)
{
	long int start;
	long int actual_time;
	long int end;

	start = get_time();
	end = start + timetosleep;
	while (1)
	{
		actual_time = get_time();
		if (actual_time >= end)
			break ;
		usleep(10);
	}
}

void	print_message(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->root->print);
	if (philo->root->finish == 0)
	{
		if (ft_strcmp(msg, EAT_ENOUGHT) == 0)
			printf("%s\n", msg);
		else
			printf("%d %d %s\n", get_time() - philo->root->start_time, philo->id, msg);
		if (ft_strcmp(msg, DIE) == 0 || ft_strcmp(msg, EAT_ENOUGHT) == 0)
			philo->root->finish = 1;
	}
	pthread_mutex_unlock(&philo->root->print);
}
