/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szerzeri <szerzeri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 17:13:49 by szerzeri          #+#    #+#             */
/*   Updated: 2024/03/13 16:19:07 by szerzeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_simulation		simulation;
	int					ret;

	if (check_error(argc, argv) == 1)
	{
		printf("Error: Wrong arguments !!\n");
		return (0);
	}
	ret = init_struct(&simulation, argc, argv);
	if (ret != SUCCESS)
	{
		display_error(ret);
		return (free_memory(&simulation), 0);
	}
	ret = create_threads(&simulation);
	if (ret != SUCCESS)
		return(0);
	monitor_philosophers(&simulation);
	pthread_mutex_unlock(simulation.print_mutex);
	ret = join_threads(&simulation);
	free_memory(&simulation);
	return (0);
}
