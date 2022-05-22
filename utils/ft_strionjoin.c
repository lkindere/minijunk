/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strionjoin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 20:30:49 by lkindere          #+#    #+#             */
/*   Updated: 2022/05/22 19:56:05 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include <stdlib.h>

static size_t	ft_strilen(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

//String index overwrite n join
//Joins s1 with s2 starting at s1[index] overwriting n characters
//s1 chars after [index] get moved to the end of s2
//Changes index pointer to the first element after s2
//IF INDEX + N > STRLEN(S1) BEHAVIOUR IS UNDEFINED
//Doesn't free s1 or s2
char	*ft_strionjoin(char *s1, char *s2, int n, int *index)
{
	char	*join;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	join = malloc(ft_strilen(s1) + ft_strilen(s2) + 1 - n);
	if (!join)
		return (NULL);
	while (s1 && s1[j] && i < (*index))
		join[i++] = s1[j++];
	j+= n;
	while (s2 && s2[k])
		join[i++] = s2[k++];
	*index = i;
	while (s1 && s1[j])
		join[i++] = s1[j++];
	join[i] = 0;
	return (join);
}

// #include <string.h>
// #include <stdio.h>

// int	main(void)
// {
// 	char	**join;
// 	char	**a1;
// 	char 	**a2;

// 	a1 = malloc(sizeof(char *) * 10);
// 	a2 = malloc(sizeof(char *) * 10);
// 	a1[0] = strdup("1 This");
// 	a1[1] = strdup("1 Is");
// 	a1[2] = strdup("1 A");
// 	a1[3] = strdup("1 String");
// 	a1[4] = strdup("1 Array");
// 	a1[5] = NULL;
// 	a2[0] = strdup("2 This");
// 	a2[1] = strdup("2 Is");
// 	a2[2] = strdup("2 A");
// 	a2[3] = strdup("2 String");
// 	a2[4] = strdup("2 Array");
// 	a2[5] = NULL;

// 	join = ft_straiojoin(a1, a2, 3);
// 	for (int i = 0; join[i]; i++)
// 		printf("%s\n", join[i]);
// 	return (0);
// }
