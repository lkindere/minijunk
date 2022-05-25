/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expands_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 18:15:47 by mmeising          #+#    #+#             */
/*   Updated: 2022/05/25 19:14:04 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
 *	Appends char c to the end of string passed by address of itself.
 *	Reallocates and frees the old string.
 *	If str is NULL (no string yet), it creates the str with size 2,
 *	one for char c and one for '\0'.
 */
int	add_char(char **str, char c)
{
	char	*ret;

	if (*str == NULL)
	{
		*str = ft_calloc(2, sizeof(char));
		if (*str == NULL)
			return (internal_error_return(ERROR_MALLOC));
		(*str)[0] = c;
	}
	else
	{
		ret = ft_calloc(ft_strlen(*str) + 2, sizeof(char));
		if (ret == NULL)
			return (internal_error_return(ERROR_MALLOC));
		ft_strlcpy(ret, *str, ft_strlen(*str) + 1);
		ret[ft_strlen(*str)] = c;
		free(*str);
		*str = ret;
	}
	return (0);
}

/*
 *	Appends string add to the end of string passed by address of itself.
 *	Reallocates and frees the old string.
 *	If str is NULL (no string yet), it creates the str with size of add + 1.
 */
int	ft_add_str(char **str, char *add)
{
	int		i;

	i = -1;
	if (*str == NULL)
	{
		*str = ft_calloc(ft_strlen(add) + 1, sizeof(char));
		if (*str == NULL)
			return (internal_error_return(ERROR_MALLOC));
		while (add[++i])
			(*str)[i] = add[i];
	}
	else
	{
		while (add[++i])
			add_char(str, add[i]);
	}
	return (0);
}
