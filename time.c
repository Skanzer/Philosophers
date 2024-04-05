/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szerzeri <szerzeri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 16:23:47 by szerzeri          #+#    #+#             */
/*   Updated: 2024/03/05 15:32:32 by szerzeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long int	get_timestamp(long int start)
{
	long int		timestamp;
	long int		actual;

	actual = time_in_ms();
	timestamp = actual - start;
	return (timestamp);
}

long int	time_in_ms(void)
{
	struct timeval	time;
	long int		time_ms;

	gettimeofday(&time, NULL);
	time_ms = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (time_ms);
}

void	wait_duration(long int duration)
{
	long long	converted;

	converted = duration * 1000;
	usleep(converted);
}
