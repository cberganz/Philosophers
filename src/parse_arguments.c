/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 05:47:15 by cberganz          #+#    #+#             */
/*   Updated: 2022/02/05 15:50:05 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
**	Check that every argument is an int.
**	return 0 if all arguments are valid.
*/

static int8_t	args_not_int(char **s, int i)
{
	long long	result;
	int			sign;

	while (s[++i])
	{
		result = 0;
		sign = 1;
		if (*s[i] == '\0')
			return (1);
		if (*s[i] == '+' || *s[i] == '-')
		{
			if (*s[i] == '-')
				sign = -1;
			s[i]++;
		}
		while (*s[i] >= '0' && *s[i] <= '9')
		{
			result = (result * 10) + (*s[i] - '0');
			s[i]++;
		}
		if ((result * sign) < INT_MIN || (result * sign) > INT_MAX
				|| *s[i] != '\0')
			return (1);
	}
	return (0);
}

/*
**	Initialize the t_philo structure with the values given by user.
**	Print error message and return -1 in case of an invalid number of arguments.
**	Print error message and return -2 if any argument is not valid.
**	Print error message and return -3 if any argument is above 1.
**	If no number of meals is set by user, its value is set to -1.
*/

int8_t	parse_args(int argc, char **args, t_root *root)
{
	if (argc < 5 || argc > 6)
	{
		printf(USAGE);
		return (-1);
	}
	root->start_time = get_time();
	root->number_of_philo = ft_atoi(args[1]);
	root->time_to_die = ft_atoi(args[2]);
	root->time_to_eat = ft_atoi(args[3]);
	root->time_to_sleep = ft_atoi(args[4]);
	if (args[5] != NULL)
		root->number_of_meals = ft_atoi(args[5]);
	else
		root->number_of_meals = 0;
	if (root->number_of_philo < 1 || root->time_to_die < 1
		|| root->time_to_eat < 1 || root->time_to_sleep < 1
		|| (args[5] && root->number_of_meals < 1) || args_not_int(args, 0))
	{
		printf("Error : Invalid arguments.\n");
		return (-3);
	}
	root->finish = 0;
	return (0);
}
