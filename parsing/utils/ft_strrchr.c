/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalami <aalami@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 14:41:01 by adardour          #+#    #+#             */
/*   Updated: 2023/08/24 13:40:39 by aalami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

char	*ft_strrchr(char *s, int c)
{
	int	length;

	length = ft_strlen(s);
	if (c == 0)
		return ((char *)s + length);
	while (length--)
	{
		if (s[length] == (unsigned char)c)
			return ((char *)s + length);
	}
	return (NULL);
}
