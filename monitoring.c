/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 11:33:17 by szerzeri          #+#    #+#             */
/*   Updated: 2024/03/27 16:09:58 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	set_exit(t_philosopher *first)
{
	t_philosopher	*philosopher;

	philosopher = first->next;
	while (1)
	{
		pthread_mutex_lock(&philosopher->philo_mutex);
		philosopher->exit = 1;
		pthread_mutex_unlock(&philosopher->philo_mutex);
		philosopher = philosopher->next;
		if (philosopher == first)
			return ;
	}
}

static int	check_die(t_philosopher *philosopher)
{
	pthread_mutex_lock(&philosopher->meal_mutex);
	if (get_timestamp(philosopher->last_meal) > philosopher->sim_data.t_d)
	{
		philosopher->exit = 1;
		pthread_mutex_unlock(&philosopher->meal_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philosopher->meal_mutex);
	return (0);
}

static int	check_eat_count(t_philosopher *philosopher, t_simulation *sim)
{
	pthread_mutex_lock(&philosopher->philo_mutex);
	if (philosopher->eat_count == sim->sim_data.nb_e)
		sim->nb_finished++;
	pthread_mutex_unlock(&philosopher->philo_mutex);
	if (sim->nb_finished == sim->sim_data.nb_e)
	{
		pthread_mutex_lock(sim->print_mutex);
		return (0);
	}
	return (1);
}

void	monitor_philosophers(t_simulation *sim)
{
	t_philosopher	*philosopher;

	philosopher = sim->philosophers;
	wait_duration(1);
	while (1)
	{
		if (check_die(philosopher) == 1)
		{
			print_action(philosopher, DIYING);
			set_exit(philosopher);
			return ;
		}
		if (sim->sim_data.nb_e != -1)
		{
			if (check_eat_count(philosopher, sim) == 0)
				return ;
		}
		philosopher = philosopher->next;
	}
}
