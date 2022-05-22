/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 20:19:09 by mmeising          #+#    #+#             */
/*   Updated: 2022/05/23 00:19:47 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

#include "exec.h"


int	free_data(t_data *data)
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
	if (data->expands)
		free_2d_char(&data->expands);
	return (0);
}

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
	data->cmds = ft_calloc(1, sizeof(t_cmd));
	if (data->cmds == NULL)
		return (ft_err(MALLOC_FAIL));
	data->cmds->in = -2;
	data->cmds->out = -2;
	if (data->tokens)
		free_tokens(&data->tokens);
	data->flags.single_quote = 0;
	data->flags.double_quote = 0;
	data->cmd_count = 0;
	data->dollar_count = 0;
	if (data->expands)
		free_2d_char(&data->expands);
	if (add_char_ptr(&data->expands) != 0)
		return (MALLOC_FAIL);
	dup2(data->std_in, STDIN_FILENO);
	dup2(data->std_out, STDOUT_FILENO);
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
	t_token	*temp;
	t_data	*data;
	t_data	*old_data;

	if (init_data(&data, envp, argc, argv) != 0)
		return (MALLOC_FAIL);
	// signal_handler(data);
	old_data = data;
	while (true)//can use continue keyword in here in case something fails. print error in the failing function and continue the loop with new input
	{
		printf("NO reset\n");
		if (reset_data(old_data) != 0)
			continue ;
		printf("Reset data\n");
		data->input = readline("TheShell -> ");
		if (!data->input)
			builtin_exit(NULL, NULL);
		if (data->input && data->input[0])
			add_history(data->input);
		if (input_is_empty(data->input))
			continue ;
		// data->input = expander(data->input, data);
				printf("AFter subshell\n");
		subshells(data);
		printf("AFter subshell\n");
		while (data)
		{
			printf("Seg lexer\n");
			if (lexer(data) != 0)
				continue ;
			temp = data->tokens;
			printf("seg parser\n");
			if (parser(data) != 0)
				continue ;
			printf("SEg heredoc\n");
			if (do_heredoc(data) != 0)
				continue ;
			printf("seg in out\n");
			in_out_std(data);
			printf("seg exec\n");
			executer(data, data->cmds);
			printf("seg data next\n");
			printf("datanext: %p\n", data->next);
			data = data->next;
			printf("After next\n");
		}
		t_data *stuff;
		t_data *stuff2;

		stuff = old_data->next;
		while (stuff)
		{
			stuff2 = stuff;
			stuff = stuff->next;
			free_data(stuff2);
			free(stuff2);
		}
		printf("All freed\n");
	}
}
