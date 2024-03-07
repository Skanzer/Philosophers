/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szerzeri <szerzeri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 11:03:24 by szerzeri          #+#    #+#             */
/*   Updated: 2024/03/06 13:58:00 by szerzeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	sim_one_philo(t_philosopher *philosopher)
{
	pthread_mutex_lock(philosopher->left_fork);
	print_action(philosopher, TAKING_FORK);
	wait_duration(philosopher->sim_data.t_d);
	pthread_mutex_unlock(philosopher->left_fork);
	pthread_mutex_lock(&philosopher->philo_mutex);
	philosopher->exit = 1;
	pthread_mutex_unlock(&philosopher->philo_mutex);
}

void	a_eat(t_philosopher *philosopher)
{
	pthread_mutex_lock(&philosopher->philo_mutex);
	pthread_mutex_lock(philosopher->left_fork);
	print_action(philosopher, TAKING_FORK);
	pthread_mutex_lock(philosopher->right_fork);
	print_action(philosopher, TAKING_FORK);
	philosopher->last_meal = time_in_ms();
	print_action(philosopher, EATING);
	pthread_mutex_unlock(&philosopher->philo_mutex);
	wait_duration(philosopher->sim_data.t_e);
	pthread_mutex_unlock(philosopher->left_fork);
	pthread_mutex_unlock(philosopher->right_fork);
	if (philosopher->sim_data.nb_e != -1)
	{
		pthread_mutex_lock(&philosopher->philo_mutex);
		philosopher->eat_count++;
		pthread_mutex_unlock(&philosopher->philo_mutex);
	}
}

void	a_sleep(t_philosopher *philosopher)
{
	pthread_mutex_lock(&philosopher->philo_mutex);
	print_action(philosopher, SLEEPING);
	pthread_mutex_unlock(&philosopher->philo_mutex);
	wait_duration(philosopher->sim_data.t_s);
}

void	a_think(t_philosopher *philosopher)
{
	pthread_mutex_lock(&philosopher->philo_mutex);
	print_action(philosopher, THINKING);
	pthread_mutex_unlock(&philosopher->philo_mutex);
}

void	sim_three_philo(t_philosopher *philosopher)
{
	while (philosopher->exit != 1)
	{
		if (philosopher->index == 2)
		{
			a_eat(philosopher);
			a_sleep(philosopher);
			a_think(philosopher);
		}
		else if (philosopher->index == 3)
		{
			a_sleep(philosopher);
			a_think(philosopher);
			a_eat(philosopher);
		}
		else
		{
			a_sleep(philosopher);
			a_think(philosopher);
			a_eat(philosopher);
		}
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
	else if (philosopher->sim_data.nb_phi == 3)
		sim_three_philo(philosopher);
	/*else
		sim_philo(philosopher);*/
	return (NULL);
}
