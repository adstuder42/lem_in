/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_numerical_to_ascii.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thzimmer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 13:42:26 by thzimmer          #+#    #+#             */
/*   Updated: 2019/02/20 11:42:57 by thzimmer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

/*
** Reduce the number to 0.XX after successive divisions by 10 and then extracts
** the digits with successive multiplications by 10 and cutting the decimal.
*/

static char	*ft_dtoa(t_var *var, long double nb, long double *dec)
{
	long double	buff;
	char		*str;
	int			i;
	int			j;

	i = 0;
	buff = nb;
	while (buff >= 1.0L && (buff = buff / 10.0L))
		i++;
	i = (i == 0 ? 1 : i);
	if (!(str = (char *)malloc(sizeof(char) * (i + var->prec + 3))))
		return (NULL);
	nb = nb / ft_dpow(10.0L, i - 1);
	j = 0;
	while (j < i + var->prec + 2)
	{
		str[j++] = (unsigned long long)nb + '0';
		(j == i) ? (str[j++] = '.') : 0;
		var->name == 'f' && j == i + var->prec + 2 ? *dec = nb : 0;
		var->name == 'g' && j == var->prec + 2 ? *dec = nb : 0;
		nb = nb - (unsigned long long)nb;
		nb = nb * 10;
	}
	str[j] = '\0';
	return (str);
}

/*
** Checks the double or long double format, starts dtoa and rounds the number.
*/

void		ft_dtoa_start(t_var *var)
{
	long double	decimal;
	int			i;

	if ((i = 1) && var->d)
	{
		var->neg = (var->ld < 0.0L ? -1 : 1);
		var->ld = (var->ld < 0.0L ? -var->ld : var->ld);
		var->s = ft_dtoa(var, var->ld, &decimal);
	}
	if (!var->d)
	{
		var->neg = (var->f < 0.0L ? -1 : 1);
		var->f = (var->f < 0.0L ? -var->f : var->f);
		var->s = ft_dtoa(var, var->f, &decimal);
	}
	while (ft_dpow(10.0L, i) - 1 < (var->d ? var->ld : var->f))
		i++;
	ft_decimal_rounding(var, ((var->name == 'f')
	? i + var->prec : var->prec), decimal);
	var->s[i + var->prec + 1] = '\0';
	if (var->s[ft_strlen(var->s) - 1] == '.' && !var->hash)
		var->s[ft_strlen(var->s) - 1] = '\0';
}

/*
** Converts to formatted output.
*/

static void	ft_add_prefix(char *res, int zero, char prefix, t_var *var)
{
	while (--zero >= 0)
		res[prefix + zero] = '0';
	if (prefix)
		res[0] = '0';
	if (prefix == 2)
		res[1] = var->name == 'X' ? 'X' : 'x';
	if (var->name == 'p' && var->prec == 0 && var->ull == 0)
		res[2] = '\0';
}

char		*ft_ultoa(char prefix, int b, t_var *var, unsigned long long nb)
{
	int		i;
	int		zero;
	char	*res;
	char	low;

	i = 0;
	low = (var->name == 'x' || var->name == 'p') ? 32 : 0;
	while (ft_dpow(b, i) - 1 < (long double)nb)
		i++;
	i = i == 0 ? 1 : i;
	zero = var->prec > i ? var->prec - i : 0;
	if (!(res = (char *)malloc(sizeof(char) * (prefix + zero + i + 1))))
		return (NULL);
	res[prefix + zero + i] = '\0';
	while (i-- > 0)
	{
		res[prefix + zero + i] = nb % b + (nb % b > 9
													? 'A' + low - 10 : '0');
		nb = nb / b;
	}
	ft_add_prefix(res, zero, prefix, var);
	return (res);
}

/*
** Converts the number into a string. Number adopts the long long format.
*/

char		*ft_ltoa(long long nb)
{
	unsigned long long	nb2;
	char				*res;
	int					i;

	i = 0;
	nb2 = (nb < 0 ? -nb : nb);
	while (ft_upow(10, i) - 1 < nb2)
		i++;
	i = (i == 0) ? 1 : i;
	if (!(res = (char *)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	res[i] = '\0';
	while (i-- > 0)
	{
		res[i] = nb2 % 10 + '0';
		nb2 = nb2 / 10;
	}
	return (res);
}
