/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szerzeri <szerzeri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 17:13:49 by szerzeri          #+#    #+#             */
/*   Updated: 2024/04/04 17:03:07 by szerzeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	exit_sim(t_simulation *sim)
{
	free_memory(sim);
	pthread_mutex_destroy(sim->print_mutex);
	free(sim->print_mutex);
}

static int	init_sim(t_simulation *sim, int argc, char **argv)
{
	int	ret;

	ret = init_struct(sim, argc, argv);
	if (ret != SUCCESS)
	{
		display_error(ret);
		exit_sim(sim);
		return (1);
	}
	ret = create_threads(sim);
	if (ret != SUCCESS)
	{
		display_error(ret);
		exit_sim(sim);
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_simulation		simulation;

	if (check_error(argc, argv) == 1)
	{
		printf("Error: Wrong arguments !!\n");
		return (0);
	}
	if (init_sim(&simulation, argc, argv) != 0)
		return (0);
	if (simulation.sim_data.nb_phi != 1)
	{
		monitor_philosophers(&simulation);
		pthread_mutex_unlock(simulation.print_mutex);
	}
	join_threads(&simulation);
	exit_sim(&simulation);
	return (0);
}
