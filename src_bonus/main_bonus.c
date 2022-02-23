/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 04:32:23 by cberganz          #+#    #+#             */
/*   Updated: 2022/02/23 15:16:16 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int argc, char *argv[])
{
	t_root			root;

	memset(&root, 0, sizeof(t_root));
	parse_arguments(argc, argv, &root);
	create_forks(&root, root.number_of_philo);
	create_threads(&root, root.number_of_philo);
	join_threads(&root, root.number_of_philo);
	if (root.eat_enough)
		printf(EAT_ENOUGH);
	free_parent(&root);
	return (EXIT_SUCCESS);
}
