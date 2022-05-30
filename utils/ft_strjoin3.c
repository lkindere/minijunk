/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 10:04:05 by lkindere          #+#    #+#             */
/*   Updated: 2022/05/30 21:13:47 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

//Null protected
static size_t	ft_strlenn(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

//Null protected
char	*ft_strjoin3(char const *s1, char const *s2, char const *s3)
{
	char	*join;
	int		i;
	int		j;
	int		k;

	i = -1;
	j = -1;
	k = -1;
	join = malloc(ft_strlenn(s1) + ft_strlenn(s2) + ft_strlenn(s3) + 1);
	if (!join)
		return (NULL);
	while (s1[++i])
		join[i] = s1[i];
	while (s2[++j])
		join[i + j] = s2[j];
	while (s3[++k])
		join[i + j + k] = s3[k];
	join[i + j + k] = '\0';
	return (join);
}
