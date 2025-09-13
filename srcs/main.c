/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibarbouc <ibarbouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 18:42:53 by ibarbouc          #+#    #+#             */
/*   Updated: 2025/09/13 19:25:47 by ibarbouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// int	main(int ac, char **av)
// {
// 	t_data	data;

// 	if (ac != 5 && ac != 6)
// 		return (1);
// 	if (init_structs(&data, ac, av) != 0)
// 	{
// 		printf("error : init failed\n");
// 		return (1);
// 	}
// 	return (0);
// }

// int	main(int ac, char **av)
// {
// 	t_data	data;
// 	int		i;

// 	// Vérif parsing
// 	if (is_not_valid(ac, av))
// 	{
// 		printf("Erreur : arguments invalides\n");
// 		return (1);
// 	}

// 	// Init structures
// 	if (init_structs(&data, ac, av) != 0)
// 	{
// 		printf("Erreur : initialisation des structures\n");
// 		return (1);
// 	}

// 	// Affichage de test
// 	printf("=== DATA ===\n");
// 	printf("Nombre de philosophes : %d\n", data.number_of_philo);
// 	printf("time_to_die   : %ld\n", data.time_to_die);
// 	printf("time_to_eat   : %ld\n", data.time_to_eat);
// 	printf("time_to_sleep : %ld\n", data.time_to_sleep);
// 	printf("num_of_meal   : %d\n", data.num_of_meal);
// 	printf("start_time    : %ld\n", data.start_time);
// 	printf("stop_dinner   : %d\n\n", data.stop_dinner);

// 	// Affichage des philosophes
// 	printf("=== PHILOS ===\n");
// 	i = 0;
// 	while (i < data.number_of_philo)
// 	{
// 		printf("Philo %d : id=%d, last_meal_time=%ld, left_fork=%p, right_fork=%p\n",
// 			i, data.philo[i].id, data.philo[i].last_meal_time,
// 			(void *)data.philo[i].left_fork, (void *)&data.philo[i].right_fork);
// 		i++;
// 	}

// 	// Libération mémoire
// 	free(data.philo);

// 	return (0);
// }