/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 10:37:50 by lkindere          #+#    #+#             */
/*   Updated: 2022/05/26 19:10:12 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "main.h"

typedef struct s_expander
{
	int		i;
	int		dollar_len;
	int		single_quote;
	int		double_quote;
	char	*expansion;
}	t_expander;

//Utils
void	init_expander(t_expander *xp);
char	*retrieve_var(char **envp, int index);
char	**sort_wildcards(char **wildcards);

//Meta
char	*quote_meta(char *expansion);

#endif