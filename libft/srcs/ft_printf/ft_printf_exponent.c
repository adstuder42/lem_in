/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_exponent.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thzimmer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 13:41:49 by thzimmer          #+#    #+#             */
/*   Updated: 2019/02/20 11:42:10 by thzimmer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

/*
** Sends the good variable to the function checking if long double or double.
*/

static int	ft_dtoexp_start(t_var *var)
{
	long double nb;
	int			pow;

	if (var->d)
	{
		var->neg = var->ld < 0.0L ? -1 : 1;
		var->ld = var->ld < 0.0L ? -var->ld : var->ld;
	}
	if (!var->d)
	{
		var->neg = var->f < 0.0 ? -1 : 1;
		var->f = var->f < 0.0 ? -var->f : var->f;
	}
	pow = ft_exp_sorting(var, var->d ? var->ld : var->f, &nb);
	ft_decimal_rounding(var, ft_strlen(var->s) - 1, nb);
	return (pow);
}

/*
** Converts to formatted outout. Can receive both double and long double format.
*/

char		*ft_dtoexp(t_var *var, long double nb, int i, long double *dec)
{
	char		*str;
	int			j;

	if (!(str = (char *)malloc(sizeof(char) * (var->prec + i + 3))))
		return (NULL);
	if (var->name == 'g')
		--var->prec;
	j = 0;
	while (j < var->prec + 2)
	{
		nb = nb * 10.0L;
		str[j++] = (int)nb + '0';
		(j == 1) ? (str[j++] = '.') : 0;
		(j == var->prec + 2) ? *dec = ((nb - (int)nb) * 10.0L) : 0;
		nb = nb - (int)nb;
	}
	str[j] = '\0';
	return (str);
}

/*
** Creates the string used in the exp notation.
*/

void		ft_add_exp(t_var *var)
{
	char		*s1;
	char		*s2;
	char		*s3;
	char		*s4;
	int			pow;

	pow = ft_dtoexp_start(var);
	s1 = (pow < 0 ? ft_strdup("e-") : ft_strdup("e+"));
	if (var->s[ft_strlen(var->s) - 1] == '.' && !(var->hash))
		var->s[ft_strlen(var->s) - 1] = '\0';
	s2 = ft_itoa(pow < 0 ? -pow : pow);
	if (pow < 10)
	{
		s4 = s2;
		s2 = ft_strjoin("0", s4);
		free(s4);
	}
	s3 = ft_strjoin(s1, s2);
	free(s1);
	s1 = ft_strjoin(var->s, s3);
	free(s2);
	free(s3);
	free(var->s);
	var->s = s1;
}

/*
** Rerounds after the last attempt in case the rounding is not correct.
*/

void		ft_exp_rerounding(t_var *var)
{
	char	*str;
	int		i;

	if (ft_atoi(var->s) > 9)
	{
		i = ft_strlen(var->s) - 1;
		var->s[1] = '.';
		var->s[2] = '0';
		var->s[i]++;
		while (var->s[i] == ':' && (var->s[i] = '0'))
		{
			--i;
			++var->s[i];
		}
		if (var->s[i] == ',' || var->s[i] == '.')
		{
			--var->s[i];
			++var->s[i + 1];
			str = ft_strjoin(var->s, "0");
			free(var->s);
			var->s = str;
		}
	}
}

/*
** Calculates the n.umber*10e+/-pow notation.
** Uses auxilliary functions to calculate decimal part.
*/

void		ft_exponent_output(t_var *var, char **output)
{
	int		len;

	ft_get_attributes(var);
	ft_get_format(var);
	ft_apply_format(var);
	if (var->prec < 0)
		var->prec = 6;
	ft_add_exp(var);
	ft_exp_rerounding(var);
	len = ft_strlen(var->s);
	if (len > var->prec)
		var->prec = len;
	if ((var->space || var->showsign || var->neg == -1))
		var->prec = var->prec + 1;
	if (var->width < var->prec)
		var->width = var->prec;
	if (!(*output = (char *)malloc(sizeof(char) * (var->width + 1))))
		return (ft_putstr("error from malloc in ft_exponent_output.\n"));
	ft_apply_flags(output, len, var);
	var->varlen += var->width;
	free(var->s);
}
