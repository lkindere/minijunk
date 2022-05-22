/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expands_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeising <mmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 18:15:47 by mmeising          #+#    #+#             */
/*   Updated: 2022/05/19 03:08:31 by mmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
 *	Reallocates array of strings passed by address to be of size of
 *	count of strings inside + 2.
 *	+ 2 for one new string and the NULL terminator.
 */
int	add_char_ptr(char ***arr)
{
	char	**ret;
	int	i;

	if (*arr == NULL)//no expands array is there, which means we need to create the first string + NULL terminator
	{
		*arr = ft_calloc(2, sizeof(char *));
		if (*arr == NULL)
			return (ft_err(MALLOC_FAIL));
	}
	else
	{
		i = 0;
		while ((*arr)[i])
			i++;
		// printf("add_char_ptr's i + 2 is %i\n", i + 2);
		ret = ft_calloc(i + 2, sizeof(char *));//+ 2 for terminating NULL and new string
		if (ret == NULL)
			return (ft_err(MALLOC_FAIL));
		i = -1;
		while ((*arr)[++i])
			ret[i] = (*arr)[i];
		free(*arr);
		*arr = ret;
	}
	return (0);
}

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
			return (ft_err(MALLOC_FAIL));
		(*str)[0] = c;
	}
	else
	{
		ret = ft_calloc(ft_strlen(*str) + 2, sizeof(char));
		if (ret == NULL)
			return (ft_err(MALLOC_FAIL));
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
			return (ft_err(MALLOC_FAIL));
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
