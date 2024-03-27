/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 11:03:24 by szerzeri          #+#    #+#             */
/*   Updated: 2024/03/27 16:10:56 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_exit(t_philosopher *philosopher)
{
	pthread_mutex_lock(&philosopher->philo_mutex);
	if (philosopher->exit == 1)
	{
		pthread_mutex_unlock(&philosopher->philo_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philosopher->philo_mutex);
	return (0);
}

static void	sim_one_philo(t_philosopher *philosopher)
{
	pthread_mutex_lock(philosopher->left_fork);
	print_action(philosopher, TAKING_FORK);
	wait_duration(philosopher->sim_data.t_d);
	print_action(philosopher, DIYING);
	pthread_mutex_unlock(philosopher->left_fork);
}

static void	sim_philo(t_philosopher *philosopher)
{
	a_think(philosopher);
	if (philosopher->index == 3)
		wait_duration(1);
	if (philosopher->index % 2 == 1)
	{
		a_eat(philosopher);
		a_sleep(philosopher);
		a_think(philosopher);
	}
	else
	{
		a_sleep(philosopher);
		a_think(philosopher);
	}
	while (1)
	{
		if (check_exit(philosopher) == 1)
			return ;
		a_eat(philosopher);
		a_sleep(philosopher);
		a_think(philosopher);
	}
}

void	*begin_simulation(void *arg)
{
	t_philosopher	*philosopher;

	philosopher = (t_philosopher *)arg;
	pthread_mutex_lock(&philosopher->philo_mutex);
	philosopher->last_meal = time_in_ms();
	pthread_mutex_unlock(&philosopher->philo_mutex);
	if (philosopher->sim_data.nb_phi == 1)
		sim_one_philo(philosopher);
	else
		sim_philo(philosopher);
	return (NULL);
}