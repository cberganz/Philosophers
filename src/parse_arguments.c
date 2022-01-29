/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 05:47:15 by cberganz          #+#    #+#             */
/*   Updated: 2022/01/29 13:51:37 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
**	Check each argument and return 1 if a non numerical character is found.
*/

static uint8_t	args_are_not_numerical(char **args)
{
	int	i;
	int	j;

	i = 1;
	while (args[i])
	{
		j = 0;
		if (args[i][j] == '\0')
			return (1);
		while (args[i][j])
		{
			if (args[i][j] < '0' || args[i][j] > '9')
				return (1);
			j++;
		}
		i++;
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
		printf("Usage : ./philo number_of_philo time_to_die time_to_eat time_to_sleep [number_of_meals]");
		return (-1);
	}
	if (args_are_not_numerical(args))
	{
		printf("Error.\nInvalid arguments.\n");
		return (-2);
	}
	root->start_time = get_time();
	root->number_of_philo = ft_atoi(args[1]);
	root->time_to_die = ft_atoi(args[2]);
	root->time_to_eat = ft_atoi(args[3]);
	root->time_to_sleep = ft_atoi(args[4]);
	if (root->number_of_philo < 1 || root->time_to_die < 1 || root->time_to_eat < 1 || root->time_to_sleep < 1)
	{
		printf("Error.\nEvery argument must be over 1.\n");
		return (-3);
	}
	if (args[5] != NULL)
		root->number_of_meals = ft_atoi(args[5]);
	else
		root->number_of_meals = -1;
	root->finish = 0;
	return (0);
}
