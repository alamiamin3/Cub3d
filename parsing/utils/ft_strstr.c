/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalami <aalami@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 13:30:36 by adardour          #+#    #+#             */
/*   Updated: 2023/08/24 13:40:39 by aalami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

const char	*ft_strstr(const char *haystack, const char *needle)
{
	int	haystack_index;
	int	needle_index;
	int	match_index;

	if (!(*needle))
		return (NULL);
	haystack_index = 0;
	while (haystack[haystack_index] != '\0')
	{
		needle_index = 0;
		match_index = haystack_index;
		while (needle[needle_index] != '\0' && \
			haystack[match_index] == needle[needle_index])
		{
			match_index++;
			needle_index++;
		}
		if (needle[needle_index] == '\0')
			return (haystack + haystack_index);
		haystack_index++;
	}
	return (NULL);
}
