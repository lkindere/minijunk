/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 22:40:44 by mmeising          #+#    #+#             */
/*   Updated: 2022/05/20 03:34:13 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*ft_strndup(char *ptr, int len)
{
	char	*ret;
	int		i;

	ret = ft_calloc(len + 1, sizeof(char));
	if (ret == NULL)
		return (NULL);
	i = 0;
	while (ptr[i] && i < len)
	{
		ret[i] = ptr[i];
		i++;
	}
	return (ret);
}
