/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szerzeri <szerzeri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 17:13:49 by szerzeri          #+#    #+#             */
/*   Updated: 2024/03/06 13:44:22 by szerzeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	set_exit(t_philosopher *first)
{
	t_philosopher	*philosopher;

	philosopher	= first;
	while (1)
	{
		pthread_mutex_lock(&philosopher->philo_mutex);
		philosopher->exit = 1;
		pthread_mutex_unlock(&philosopher->philo_mutex);
		philosopher = philosopher->next;
		if (philosopher == first)
			break;
	}
}

void	monitor_philosophers(t_simulation *sim)
{
	t_philosopher	*philosopher;

	philosopher = sim->philosophers;
	while (1)
	{
		pthread_mutex_lock(&philosopher->philo_mutex);
		if (get_timestamp(philosopher->last_meal) >= sim->sim_data.t_d)
		{
			print_action(philosopher, DIYING);
			set_exit(philosopher);
			break;
		}
		if (sim->sim_data.nb_e != -1)
		{
			if (philosopher->eat_count == sim->sim_data.nb_e)
				philosopher->exit = 1;
		}
		pthread_mutex_unlock(&philosopher->philo_mutex);
		philosopher = philosopher->next;
	}
}

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
	ret = join_threads(&simulation);
	monitor_philosophers(&simulation);
	free_memory(&simulation);
	return (0);
}
/*
		threads = malloc(sizeof(pthread_t) * input.nb_phi);
		if (!threads)
			return (0);
		memset(threads, 0, sizeof(pthread_t *)); 
		while (i < input.nb_phi)
		{
			threads[i] = i + 1;
			ret = pthread_create(&threads[i], NULL, *test, &input);
			if(ret == -1)
				return (0);
			i++;
		}
		i = 0;
		while (i < input.nb_phi)
		{
			pthread_join(threads[i], NULL);
			i++;
		}
		printf("after the thread\n");
*/