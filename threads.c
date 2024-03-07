/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szerzeri <szerzeri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 12:07:33 by szerzeri          #+#    #+#             */
/*   Updated: 2024/03/05 19:28:32 by szerzeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	create_threads(t_simulation *simulation)
{
	t_philosopher	*philosopher;
	int				ret;

	philosopher = simulation->philosophers;
	simulation->start_time = time_in_ms();
	ret = 0;
	while (1)
	{
		philosopher->start_time = simulation->start_time;
		ret = pthread_create(&philosopher->philo, NULL, begin_simulation, philosopher);
		if (ret != 0)
			return (ret);
		philosopher = philosopher->next;
		if (philosopher == simulation->philosophers)
			break;
	}
	return (ret);
}

int	join_threads(t_simulation *simulation)
{
	t_philosopher	*philosopher;
	int				ret;

	philosopher = simulation->philosophers;
	ret = 0;
	while (1)
	{
		ret = pthread_join(philosopher->philo, NULL);
		if (ret != 0)
			return (ret);
		philosopher = philosopher->next;
		if (philosopher == simulation->philosophers)
			break;
	}
	return (ret);
}
