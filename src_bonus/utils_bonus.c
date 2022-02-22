/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 06:46:14 by cberganz          #+#    #+#             */
/*   Updated: 2022/02/17 11:05:48 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
	long int	start;
	long int	actual_time;
	long int	end;

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

void	print_message(t_root *root, char *msg)
{
	sem_wait(root->finish_sem);
	if (root->finish == 1)
	{
		sem_post(root->finish_sem);
		return ;
	}
	if (root->finish == 0)
	{
		sem_wait(root->print_sem);
		printf("%d %d %s\n", get_time() - root->start_time, root->id, msg);
		if (ft_strcmp(msg, DIE) == 0)
		{
			root->finish = 1;
			sem_post(root->finish_sem);
			return ;
		}
		sem_post(root->print_sem);
	}
	sem_post(root->finish_sem);
}
