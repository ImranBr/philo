/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibarbouc <ibarbouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 23:34:18 by ibarbouc          #+#    #+#             */
/*   Updated: 2025/09/11 00:03:00 by ibarbouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_number(const char *str)
{
	int		i;
	long	result;

	i = 0;
	result = 0;
	if (str[i] == '-' || str[i] == '\0')
		return (1);
	if (str[i] == '+')
	{
		i++;
		if (str[i] == '\0')
			return (1);
	}
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);
		result = result * 10 + (str[i] - '0');
		if (result > INT_MAX)
			return (1);
		i++;
	}
	if (result == 0)
		return (1);
	return (0);
}

int	is_not_valid(int ac, char **av)
{
	int	i;

	if (ac < 5 || ac > 6)
		return (1);
	i = 1;
	while (i < ac)
	{
		if (check_number(av[i]))
			return (1);
		i++;
	}
	return (0);
}
