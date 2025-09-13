/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibarbouc <ibarbouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 16:19:00 by ibarbouc          #+#    #+#             */
/*   Updated: 2025/09/13 23:03:40 by ibarbouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	init_data(t_data *data, int ac, char **av)
{
	if (ac != 5 && ac != 6)
		return (1);
	data->number_of_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atol(av[2]);
	data->time_to_eat = ft_atol(av[3]);
	data->time_to_sleep = ft_atol(av[4]);
	if (ac == 6)
		data->num_of_meal = ft_atoi(av[5]);
	else
		data->num_of_meal = -1;
	if (data->number_of_philo <= 0 || data->time_to_die < 60
		|| data->time_to_eat < 60 || data->time_to_sleep < 60 || (ac == 6
			&& data->num_of_meal <= 0))
		return (1);
	data->philo = malloc(sizeof(t_philo) * data->number_of_philo);
	if (!data->philo)
		return (1);
	if (pthread_mutex_init(&data->print_lock, NULL) != 0
		|| pthread_mutex_init(&data->stop_mutex, NULL) != 0)
		return (1);
	data->stop_dinner = 0;
	data->start_time = get_time_in_ms();
	return (0);
}

static int	init_philo(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philo)
	{
		if (pthread_mutex_init(&data->philo[i].right_fork, NULL) != 0)
			return (1);
		i++;
	}
	i = 0;
	while (i < data->number_of_philo)
	{
		data->philo[i].id = i + 1;
		data->philo[i].last_meal_time = data->start_time;
		data->philo[i].data = data;
		data->philo[i].thread = 0;
		data->philo[i].meals_eaten = 0;
		if (data->philo[i].id == data->number_of_philo)
			data->philo[i].left_fork = &data->philo[0].right_fork;
		else
			data->philo[i].left_fork = &data->philo[i + 1].right_fork;
		i++;
	}
	return (0);
}

int	init_structs(t_data *data, int ac, char **av)
{
	if (init_data(data, ac, av) != 0 || init_philo(data) != 0)
		return (1);
	return (0);
}

static int	create_philo_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philo)
	{
		if (pthread_create(&data->philo[i].thread, NULL, routine,
				(void *)&data->philo[i]) != 0)
		{
			while (i > 0)
			{
				pthread_join(data->philo[i - 1].thread, NULL);
				i--;
			}
			return (1);
		}
		i++;
	}
	return (0);
}

int	init_threads(t_data *data)
{
	data->start_time = get_time_in_ms();
	init_philo(data);
	if (pthread_create(&data->monitor, NULL, monitor_routine, data) != 0)
	{
		write(2, "Failed to create monitor thread\n", 31);
		return (1);
	}
	data->monitor_created = 1;
	if (create_philo_threads(data) != 0)
	{
		pthread_join(data->monitor, NULL);
		return (1);
	}
	return (0);
}
