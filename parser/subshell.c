/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 22:00:50 by lkindere          #+#    #+#             */
/*   Updated: 2022/05/23 05:45:53 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "exec.h"

// code/minishell$ (export abc=potatoes && echo $abc) && echo $abc
// potatoes


// ➜  minishell git:(master) ✗ (rm test && cat test)
// cat: test: No such file or directory

// code/minishell$ (rm junk && cat jun*)
// cat: 'jun*': No such file or directory

//Run each segment up until &&/|| individually then expand and do wildcards again
//data->input = 1 segment

int     is_split(int c, int d)
{
    if (c == '&' && d == '&')
        return (1);
    if (c == '|' && d == '|')
        return (2);
    if (c == '&' && d != '&')
        return (-1);
    return (0);
}

int clone_data(t_data *data, char *new_input, int and_or)
{
    int i;

    i = -1;
    init_data(data->next, data->envp);
    // data->next = malloc(sizeof(t_data));
    // if (!data)
    //     return (1);
    // data->next->envp = clone_envp(data->envp);
    // data->next->pwd = getcwd(data->next->pwd, 0);
    // data->next->exit_code = 0;
    // data->next->std_in = 0;
    // data->next->std_out = 1;
    // data->next->next = NULL;
    data->next->input = malloc(ft_strlen(new_input) + 1);
    // data->next->and_or = and_or;
    // if (!(data->next->envp || data->next->pwd
    //     || data->next->tokens || data->next->input))
    //     return (2);
    while (new_input[++i])
    {
        data->next->input[i] = new_input[i];
        new_input[i] = 0;
    }
}
 
void    split_data(t_data *data, char *input)
{
    int i;
    int split;

    i = -1;
    split = 0;
    while (data && data->input[++i] && !split)
    {
        split = is_split(data->input[i], data->input[i + 1]);
        if (split == -1)
            printf("Syntax error near unexpected token `&'\n");
        if (split > 0)
        {   
            printf("Data input: %s\n", data->input);
            if (clone_data(data, &data->input[i + 2], split) != 0)
                return (1);
                        printf("Data input: %s\n", data->input);
            data->input[i] = 0;
            data->input[i - 1] = 0;
            data = data->next;
            printf("Cloning data: %s\n", data->input);
            i = -1;
            split = 0;
        }
    }
}

void    print_data(t_data *data)
{
    int i;

    i = 0;
    while (data)
    {
        printf("Data: %p\n", data);
        i++;
        printf("Data %d: and_or: %d %s\n", i, data->and_or, data->input);
        data = data->next;
    }
}

void    subshells(t_data *data)
{
    data->next = NULL;
    split_data(data, data->input); // split until || or &&
    print_data(data);
}