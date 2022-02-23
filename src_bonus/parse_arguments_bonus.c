/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arguments_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 05:47:15 by cberganz          #+#    #+#             */
/*   Updated: 2022/02/23 15:16:27 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
**	Open the different semaphores needed by the program.
**	Semaphores are previously unlinked to prevent from previous use.
**	forks_sem works as token for avaliable forks.
**	print_sem locks the print_message() function.
**	Both are created in shared memory.
*/

static void	initialize_semaphores(t_root *root)
{
	sem_unlink("/forks_sem");
	sem_unlink("/print_sem");
	sem_unlink("/taking_fork_sem");
	sem_unlink("/eating_sem");
	sem_unlink("/finish_sem");
	root->forks_sem = sem_open("/forks_sem", O_CREAT | O_EXCL,
			0660, root->number_of_philo);
	if (root->forks_sem == SEM_FAILED)
		ft_exit(FORKSSEM_OPEN_ERR, root);
	root->print_sem = sem_open("/print_sem", O_CREAT | O_EXCL, 0660, 1);
	if (root->print_sem == SEM_FAILED)
		ft_exit(PRINTSEM_OPEN_ERR, root);
	root->taking_fork_sem = sem_open("/taking_fork_sem",
			O_CREAT | O_EXCL, 0600, 1);
	if (root->taking_fork_sem == SEM_FAILED)
		ft_exit(TAKINGFORKSEM_OPEN_ERR, root);
	root->eating_sem = sem_open("/eating_sem", O_CREAT | O_EXCL, 0600, 1);
	if (root->eating_sem == SEM_FAILED)
		ft_exit(EATINGSEM_OPEN_ERR, root);
	root->finish_sem = sem_open("/finish_sem", O_CREAT | O_EXCL, 0600, 1);
	if (root->finish_sem == SEM_FAILED)
		ft_exit(FINISHSEM_OPEN_ERR, root);
}

/*
**	Allocate heap memory for root members.
**	Error message printed and program properly exited in case of invalid args.
*/

static void	allocate_memory(t_root *root)
{
	root->philo = malloc(root->number_of_philo * sizeof(t_philo));
	if (!root->philo)
		ft_exit(MALLOC_PHILO_ERR, root);
	root->threads = malloc(root->number_of_philo * sizeof(pthread_t));
	if (!root->threads)
		ft_exit(MALLOC_THREADS_ERR, root);
	root->forks_pid = malloc(root->number_of_philo * sizeof(pid_t));
	if (!root->forks_pid)
		ft_exit(MALLOC_FORKSPID_ERR, root);
	initialize_semaphores(root);
}

/*
**	Initialize the t_root structure with the values given by user.
**	Error message printed and program properly exited in case of invalid args.
*/

void	parse_arguments(int argc, char **args, t_root *root)
{
	if (argc < 5 || argc > 6)
		ft_exit(USAGE_ERR, root);
	root->start_time = get_time();
	root->last_eat = root->start_time;
	root->number_of_philo = ft_atoi(args[1]);
	root->time_to_die = ft_atoi(args[2]);
	root->time_to_eat = ft_atoi(args[3]);
	root->time_to_sleep = ft_atoi(args[4]);
	if (args[5] != NULL)
		root->number_of_meals = ft_atoi(args[5]);
	if (root->number_of_philo < 1 || root->time_to_die < 1
		|| root->time_to_eat < 1 || root->time_to_sleep < 1
		|| (args[5] && root->number_of_meals < 1)
		|| args_not_int(args, 0))
		ft_exit(ARGS_ERR, root);
	allocate_memory(root);
}
