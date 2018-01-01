/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 13:34:52 by kboucaud          #+#    #+#             */
/*   Updated: 2016/11/13 11:00:00 by kboucaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char				*part;
	unsigned int		i;

	i = 0;
	if (s == NULL)
		return (NULL);
	part = (char*)malloc(sizeof(char) * (len + 1));
	if (part == NULL)
		return (NULL);
	while (i < len)
	{
		part[i] = s[start + i];
		i++;
	}
	part[i] = '\0';
	return (part);
}
