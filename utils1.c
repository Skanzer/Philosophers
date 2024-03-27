/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 11:22:36 by szerzeri          #+#    #+#             */
/*   Updated: 2024/03/27 16:06:37 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_eat(t_philosopher *philosopher)
{
	long int	timestamp;

	pthread_mutex_lock(&philosopher->philo_mutex);
	if (philosopher->exit == 1)
	{
		pthread_mutex_unlock(&philosopher->philo_mutex);
		return ;
	}
	pthread_mutex_lock(&philosopher->meal_mutex);
	pthread_mutex_lock(philosopher->print_mutex);
	timestamp = get_timestamp(philosopher->start_time);
	printf("%ld %i %s\n", timestamp, philosopher->index, FORK);
	printf("%ld %i %s\n", timestamp, philosopher->index, FORK);
	printf("%ld %i %s\n", timestamp, philosopher->index, EAT);
	pthread_mutex_unlock(philosopher->print_mutex);
	philosopher->last_meal = time_in_ms();
	pthread_mutex_unlock(&philosopher->meal_mutex);
	if (philosopher->sim_data.nb_e != -1)
	{
		philosopher->eat_count++;
		if (philosopher->eat_count == philosopher->sim_data.nb_e)
			philosopher->exit = 1;
	}
	pthread_mutex_unlock(&philosopher->philo_mutex);
}

void	take_input(t_general *input, int argc, char **argv)
{
	input->nb_phi = ft_atol(argv[1]);
	input->t_d = ft_atol(argv[2]);
	input->t_e = ft_atol(argv[3]);
	input->t_s = ft_atol(argv[4]);
	if (argc == 6)
		input->nb_e = ft_atol(argv[5]);
	else
		input->nb_e = -1;
}
