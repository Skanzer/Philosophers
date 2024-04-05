/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szerzeri <szerzeri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 13:55:50 by szerzeri          #+#    #+#             */
/*   Updated: 2024/04/04 15:53:17 by szerzeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_philo(t_philosopher *philo, t_general *input)
{
	int	ret;

	ret = 0;
	philo->eat_count = 0;
	philo->last_meal = 0;
	philo->start_time = 0;
	philo->exit = 0;
	philo->left_fork = NULL;
	philo->right_fork = NULL;
	philo->sim_data.nb_phi = input->nb_phi;
	philo->sim_data.t_d = input->t_d;
	philo->sim_data.t_e = input->t_e;
	philo->sim_data.t_s = input->t_s;
	philo->sim_data.nb_e = input->nb_e;
	ret = init_mutexes(philo);
	return (ret);
}

int	init_mutexes(t_philosopher *philo)
{
	if (pthread_mutex_init(&philo->philo_mutex, NULL) != SUCCESS)
		return (MUTEX_ERROR);
	if (pthread_mutex_init(&philo->meal_mutex, NULL) != SUCCESS)
		return (MUTEX_ERROR);
	if (pthread_mutex_init(&philo->eat_count_mutex, NULL) != SUCCESS)
		return (MUTEX_ERROR);
	philo->left_fork = malloc(sizeof(pthread_mutex_t));
	if (!philo->left_fork)
		return (ALLOC_ERROR);
	if (pthread_mutex_init(philo->left_fork, NULL) != SUCCESS)
		return (MUTEX_ERROR);
	return (SUCCESS);
}

void	add_philo_to_list(t_philosopher *philo, t_simulation *simulation)
{
	t_philosopher	*head;

	head = simulation->philosophers;
	if (head == NULL)
	{
		simulation->philosophers = philo;
		philo->next = NULL;
		philo->previous = NULL;
	}
	else
	{
		while (head->next != NULL)
			head = head->next;
		head->next = philo;
		philo->previous = head;
		if (philo->index == philo->sim_data.nb_phi)
		{
			philo->next = simulation->philosophers;
			philo->next->right_fork = philo->left_fork;
			philo->next->previous = philo;
		}
		else
			philo->next = NULL;
		philo->right_fork = head->left_fork;
	}
}

int	simulation_struct(t_simulation *simulation, int argc, char **argv)
{
	simulation->nb_finished = 0;
	simulation->start_time = 0;
	simulation->philosophers = NULL;
	take_input(&simulation->sim_data, argc, argv);
	simulation->print_mutex = malloc(sizeof(pthread_mutex_t));
	if (!simulation->print_mutex)
		return (ALLOC_ERROR);
	if (pthread_mutex_init(simulation->print_mutex, NULL) != SUCCESS)
		return (MUTEX_ERROR);
	return (SUCCESS);
}

int	init_struct(t_simulation *simulation, int argc, char **argv)
{
	t_philosopher	*philo;
	int				i;
	int				ret;

	i = 1;
	ret = 0;
	ret = simulation_struct(simulation, argc, argv);
	if (ret != SUCCESS)
		return (ret);
	while (i <= simulation->sim_data.nb_phi)
	{
		philo = malloc(sizeof(t_philosopher));
		if (!philo)
			return (ALLOC_ERROR);
		philo->index = i;
		ret = init_philo(philo, &simulation->sim_data);
		if (ret != SUCCESS)
			return (ret);
		philo->print_mutex = simulation->print_mutex;
		add_philo_to_list(philo, simulation);
		if (simulation->sim_data.nb_phi == 1)
			philo->next = philo;
		i++;
	}
	return (ret);
}
