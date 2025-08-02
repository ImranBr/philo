/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibarbouc <ibarbouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 16:19:00 by ibarbouc          #+#    #+#             */
/*   Updated: 2025/08/02 21:16:22 by ibarbouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_data(t_data *data, int ac, char **av)
{
	if (ac != 5 && ac != 6)
		return (1);
	data->num_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atol(av[2]);
	data->time_to_eat = ft_atol(av[3]);
	data->time_to_sleep = ft_atol(av[4]);
	if (ac == 6)
		data->num_of_meal = ft_atoi(av[5]);
	data->philo = malloc(sizeof(t_philo) * data->num_philo);
	if (!data->philo)
		return (1);
	if (pthread_mutex_init(&data->print_lock, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&data->stop_mutex, NULL) != 0)
		return (1);
	data->stop_dinner = 0;
	return (0);
}

int	init_philo(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philo)
	{
		if (pthread_mutex_init(&data->philo->right_fork, NULL) != 0)
			return (1);
		i++;
	}
	i = 0;
	while (i < data->num_philo)
	{
		data->philo[i].id = i + 1;
		data->philo[i].last_meal_time = 0;
		data->philo[i].data = data;
		if(data->philo[i].id == data->num_philo)
			data->philo[i].left_fork = &data->philo[0].right_fork;
		else
		{
			data->philo[i].left_fork = &data->philo[i + 1].right_fork;
		}
		i++;
	}
	return (0);
}
