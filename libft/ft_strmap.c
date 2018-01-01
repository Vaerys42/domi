/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 12:48:13 by kboucaud          #+#    #+#             */
/*   Updated: 2016/11/13 10:56:16 by kboucaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*new;
	int		i;

	i = 0;
	if (s == NULL || f == NULL)
		return (NULL);
	while (s[i] != '\0')
		i++;
	new = (char*)malloc(sizeof(char) * (i + 1));
	if (new == NULL)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		new[i] = f(s[i]);
		i++;
	}
	new[i] = '\0';
	return (new);
}
