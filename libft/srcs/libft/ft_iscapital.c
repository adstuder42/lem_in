/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iscapital.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thzimmer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 18:01:31 by thzimmer          #+#    #+#             */
/*   Updated: 2018/11/14 13:16:37 by thzimmer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	ft_iscapital(char c)
{
	if (c >= 'A' && c <= 'Z')
		return (1);
	return (0);
}