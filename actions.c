/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 13:06:51 by szerzeri          #+#    #+#             */
/*   Updated: 2024/03/27 16:07:31 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	fork_lock(t_philosopher *philosopher)
{
	pthread_mutex_lock(&philosopher->philo_mutex);
	if (philosopher->exit == 1)
	{
		pthread_mutex_unlock(&philosopher->philo_mutex);
		return ;
	}
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
	pthread_mutex_unlock(&philosopher->philo_mutex);
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
	print_eat(philosopher);
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
