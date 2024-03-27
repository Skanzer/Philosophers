/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 16:37:17 by szerzeri          #+#    #+#             */
/*   Updated: 2024/03/27 16:08:34 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_digits(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (!(argv[i][j] >= '0' && argv[i][j] <= '9'))
				return (1);
			else
				j++;
		}
		i++;
	}
	return (0);
}

int	check_phi_nb(char **argv)
{
	if (ft_atol(argv[1]) == 0)
		return (1);
	return (0);
}

int	check_limit(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (ft_atol(argv[i]) > __INT_MAX__)
			return (1);
		i++;
	}
	return (0);
}

int	check_error(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (1);
	else if (check_digits(argv) == 1)
		return (1);
	else if (check_phi_nb(argv) == 1)
		return (1);
	else if (argv[5] && ft_atol(argv[5]) == 0)
		return (1);
	else if (check_limit(argv) == 1)
		return (1);
	return (0);
}
