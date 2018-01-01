/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/21 17:41:42 by kboucaud          #+#    #+#             */
/*   Updated: 2016/11/26 16:35:51 by kboucaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include "includes/libft.h"

static int	ft_words(const char *s, char c)
{
	int		cnt;
	int		i;

	cnt = 0;
	i = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		if (s[i] != c && s[i] != '\0')
		{
			while (s[i] != c && s[i] != '\0')
				i++;
			cnt++;
		}
	}
	return (cnt);
}

static int	ft_size(const char *s, char c, int i)
{
	int		size;

	size = 0;
	while (s[i] != c)
	{
		size++;
		i++;
	}
	return (size);
}

char		**ft_strsplit(const char *s, char c)
{
	char	**new;
	int		nb_words;
	int		j;
	int		i;

	j = 0;
	i = 0;
	if (s == NULL)
		return (NULL);
	nb_words = ft_words(s, c);
	new = (char**)malloc(sizeof(char*) * (nb_words + 1));
	if (new == NULL)
		return (NULL);
	while (nb_words)
	{
		while (s[i] == c)
			i++;
		new[j] = ft_strsub(s, i, ft_size(s, c, i));
		while (s[i] != c)
			i++;
		j++;
		nb_words--;
	}
	new[j] = NULL;
	return (new);
}
