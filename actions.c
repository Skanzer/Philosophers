/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szerzeri <szerzeri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 13:06:51 by szerzeri          #+#    #+#             */
/*   Updated: 2024/03/13 18:14:46 by szerzeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	fork_lock(t_philosopher *philosopher)
{
	if (philosopher->index % 2 == 0)
	{
		pthread_mutex_lock(philosopher->left_fork);
		pthread_mutex_lock(philosopher->right_fork);	
	}
	else
	{
		pthread_mutex_lock(philosopher->right_fork);
		pthread_mutex_lock(philosopher->left_fork);
	}
	
}

void	fork_unlock(t_philosopher *philosopher)
{
	pthread_mutex_unlock(philosopher->left_fork);
	pthread_mutex_unlock(philosopher->right_fork);	
}

void	a_eat(t_philosopher *philosopher)
{
	if (check_exit(philosopher) == 1)
		return ;
	fork_lock(philosopher);
	print_action(philosopher, TAKING_FORK);
	print_action(philosopher, TAKING_FORK);
	print_action(philosopher, EATING);
	pthread_mutex_lock(&philosopher->philo_mutex);
	philosopher->last_meal = time_in_ms();
	if (philosopher->sim_data.nb_e != -1)
		philosopher->eat_count++;
	pthread_mutex_unlock(&philosopher->philo_mutex);
	wait_duration(philosopher->sim_data.t_e);
	fork_unlock(philosopher);
}

void	a_sleep(t_philosopher *philosopher)
{
	if (check_exit(philosopher) == 1)
		return ;
	print_action(philosopher, SLEEPING);
	wait_duration(philosopher->sim_data.t_s);
}

void	a_think(t_philosopher *philosopher)
{
	if (check_exit(philosopher) == 1)
		return ;
	print_action(philosopher, THINKING);
}
