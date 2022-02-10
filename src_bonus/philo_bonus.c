/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 04:32:23 by cberganz          #+#    #+#             */
/*   Updated: 2022/02/07 17:34:20 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	free_all(t_root *root)
{
	sem_unlink("/forks_sem");
	sem_unlink("/print_sem");
	sem_unlink("/taking_fork_sem");
	sem_unlink("/end_sem");
	sem_close(root->forks_sem);	
	sem_close(root->print_sem);
	sem_close(root->taking_fork_sem);
	sem_close(root->end_sem);
	if (root->philo)
		free(root->philo);
	if (root->threads)
		free(root->threads);
	if (root->forks_pid)
		free(root->forks_pid);
}

t_root	*root_ptr(void)
{
	static t_root	root;

	return (&root);
}

void	ft_exit(int exit_code)
{
	t_root	*root;

	root = root_ptr();
	printf("%s\n", error_messages[exit_code - 2]);
	free_all(root);
	exit(exit_code);
}

int	main(int argc, char *argv[])
{
	t_root			*root;

	root = root_ptr();
	memset(root, 0, sizeof(t_root));
	parse_args(argc, argv, root);
	initialize_structures(root);
	create_forks(root, root->number_of_philo);
	create_threads(root, root->number_of_philo);
	sem_wait(root->end_sem);
	my_usleep(100);
	if (root->eat_enought)
		printf(EAT_ENOUGHT);
	free_all(root);
	return (EXIT_SUCCESS);
}
