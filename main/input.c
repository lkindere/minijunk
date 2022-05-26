/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 18:23:43 by lkindere          #+#    #+#             */
/*   Updated: 2022/05/26 22:34:43 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	get_input(char **full_input, t_data *data)
{
	if (data->is_fork)
		return ;
	if (!*full_input)
		*full_input = readline("MiniJunk XD: ");
		// printf("Data->exit_code: %d\n", data->exit_code);
	if (!*full_input)
		exit (data->exit_code);
	if (*full_input && (*full_input)[0])
		add_history(*full_input);
	if (input_is_empty(*full_input))
	{
		free(*full_input);
		*full_input = NULL;
		reset_data(data);
	}
}

int	input_is_empty(char	*input)
{
	int	i;

	i = 0;
	if (!input)
		return (1);
	while (input[i] == ' ')
		i++;
	if (input[i] == '\0')
		return (1);
	else
		return (0);
}

int	is_input(char *full_input, char *segment)
{
	if (!segment || input_is_empty(segment))
	{
		if (!full_input || input_is_empty(full_input))
			return (0);
	}
	return (1);
}
