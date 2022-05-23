/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 20:19:09 by mmeising          #+#    #+#             */
/*   Updated: 2022/05/23 06:01:31 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

#include "exec.h"

/*
 *	Resets the data that needs to be cleaned for every time we get new input.
 *	Includes resetting stdin and stdout from the backup saved in data.
 */
int	reset_data(t_data *data)
{
	if (data->input)
	{
		free(data->input);
		data->input = NULL;
	}
	if (data->cmds)
		free_cmds(&data->cmds);
	if (data->tokens)
		free_tokens(&data->tokens);
	return (0);
}

int	input_is_empty(char	*input)
{
	int	i;

	i = 0;
	while (input[i] == ' ')
		i++;
	if (input[i] == '\0')
		return (1);
	else
		return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_token *temp;
	t_data	data;
	t_data 	*dtemp;

	signal_handler(&data);
	while (true)//can use continue keyword in here in case something fails. print error in the failing function and continue the loop with new input
	{
		if (init_data(&data, envp) != 0)
			continue ;
		data.input = readline("TheShell -> ");
		if (!data.input)
			builtin_exit(NULL, NULL);
		if (data.input && data.input[0])
			add_history(data.input);
		// subshells(data);
		if (input_is_empty(data.input))
			continue ;
		dtemp = &data;
		while (dtemp)
		{
			// data->input = expander(data->input, data);
			if (lexer(dtemp) != 0)
				continue ;
			temp = dtemp->tokens;
			if (parser(dtemp) != 0)
				continue ;

			if (do_heredoc(&data) != 0)
				continue ;

			in_out_std(dtemp);

			executer(dtemp, dtemp->cmds);

			dtemp = dtemp->next;
		}
		reset_data(&data);
	}
}
