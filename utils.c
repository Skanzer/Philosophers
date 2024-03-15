/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szerzeri <szerzeri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 17:51:21 by szerzeri          #+#    #+#             */
/*   Updated: 2024/03/13 13:28:17 by szerzeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long int	ft_atol(const char *str)
{
	long int	result;
	int			i;

	result = 0;
	i = 0;
	while (str[i] <= 57 && str[i] >= 48)
	{
		result = (result * 10) + (str[i] - 48);
		i++;
	}
	return (result);
}

void	*ft_calloc(size_t n_membr, size_t size)
{
	void	*ret;
	size_t	total;
	size_t	i;

	i = 0;
	total = n_membr * size;
	ret = (void *)malloc(total);
	if (!ret)
		return (NULL);
	while (i < total)
	{
		*(unsigned char *)ret = '\0';
		i++;
		ret++;
	}
	return (ret);
}

void	display_error(int ret)
{
	if (ret == ALLOC_ERROR)
		printf("Error: Failed to allocate memory\n");
	else if (ret == THREAD_ERROR)
		printf("Error: Failed to create/join threads\n");
	else if (ret == MUTEX_ERROR)
		printf("Error: Failed to create mutex\n");
}

void	free_memory(t_simulation *sim)
{
	t_philosopher	*node;
	t_philosopher	*tmp;

	node = sim->philosophers;
	while (1)
	{
		pthread_mutex_destroy(node->left_fork);
		pthread_mutex_destroy(&node->philo_mutex);
		free(node->left_fork);
		tmp = node;
		node = node->next;
		free(tmp);
		if (node == sim->philosophers)
			break ;
	}
}

void	print_action(t_philosopher *philosopher, t_philo_state state)
{
	long int	timestamp;

	pthread_mutex_lock(&philosopher->philo_mutex);
	timestamp = get_timestamp(philosopher->start_time);
	pthread_mutex_unlock(&philosopher->philo_mutex);
	pthread_mutex_lock(philosopher->print_mutex);
	printf("%ld %i ", timestamp, philosopher->index);
	if (state == TAKING_FORK)
		printf("%s\n", FORK);
	else if (state == SLEEPING)
		printf("%s\n", SLEEP);
	else if (state == EATING)
		printf("%s\n", EAT);
	else if (state == THINKING)
		printf("%s\n", THINK);
	else if (state == DIYING)
	{
		printf("%s\n", DIE);
		return ;
	}
	pthread_mutex_unlock(philosopher->print_mutex);
}
