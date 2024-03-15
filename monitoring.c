/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szerzeri <szerzeri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 11:33:17 by szerzeri          #+#    #+#             */
/*   Updated: 2024/03/13 16:49:45 by szerzeri         ###   ########.fr       */
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
	pthread_mutex_lock(&philosopher->philo_mutex);
	if (get_timestamp(philosopher->last_meal) > philosopher->sim_data.t_d)
	{
		philosopher->exit = 1;
		pthread_mutex_unlock(&philosopher->philo_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philosopher->philo_mutex);
	return (0);
}

/*static int	check_eat_count(t_philosopher *philosopher)
{

}
*/
void	monitor_philosophers(t_simulation *sim)
{
	t_philosopher	*philosopher;

	philosopher = sim->philosophers;
	wait_duration(10);
	while (1)
	{
		if (check_die(philosopher) == 1)
		{
			print_action(philosopher, DIYING);
			pthread_mutex_lock(&philosopher->philo_mutex);
			philosopher->exit = 1;
			pthread_mutex_unlock(&philosopher->philo_mutex);
			set_exit(philosopher);
			return ;
		}
		if (sim->sim_data.nb_e != -1)
		{
			if (philosopher->eat_count == sim->sim_data.nb_e)
				philosopher->exit = 1;
		}
		philosopher = philosopher->next;
		wait_duration(1);
	}
}
