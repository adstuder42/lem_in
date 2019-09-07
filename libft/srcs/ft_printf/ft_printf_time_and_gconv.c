/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_time_and_gconv.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thzimmer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 13:42:37 by thzimmer          #+#    #+#             */
/*   Updated: 2019/02/20 11:43:19 by thzimmer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

/*
** Selects output for the g flags, whether it is in dtoa form or exponent.
*/

static char	ft_gconv_selector(t_var *var)
{
	long double nb;
	int			i;

	nb = var->d ? var->ld : var->f;
	nb = nb < 0 ? -nb : nb;
	i = 0;
	if (nb < 1.0L)
	{
		while (nb < 1.0L && (nb = nb * 10.0L))
			i++;
		if (i > 4)
			return (1);
		return (0);
	}
	while (nb >= 1.0L && (nb = nb / 10.0L))
		i++;
	if (i > var->prec)
		return (1);
	return (0);
}

/*
** Selects the good output form and starts the calculation. The result is
** sent to ft_gconv_output.
*/

void		ft_gconv_start(t_var *v, int i, int j)
{
	long double	dec;

	if (ft_gconv_selector(v))
	{
		ft_add_exp(v);
		ft_exp_rerounding(v);
		i = ft_strlen(v->s);
		while (v->s[i] != 'e')
			i--;
		i--;
		while (((j = i) && v->s[i] == '0') || (!v->hash && v->s[i] == '.'))
			while (v->s[j++])
				v->s[j - 1] = v->s[j];
	}
	else
	{
		dec = (v->d ? v->ld : v->f);
		while (dec < 1 && (dec *= 10.0L))
			v->prec++;
		ft_dtoa_start(v);
		v->s[v->prec + 1] = '\0';
		while (v->s[v->prec] != '.' || v->s[v->prec] == '0')
			v->s[v->prec--] = '\0';
		v->s[v->prec--] = '\0';
	}
}

/*
** Creates a string with the name of the month including the whitespaces.
*/

static void	ft_get_month(char *monthnb, char **month)
{
	if (monthnb[0] == '0' && monthnb[1] == '1')
		*month = ft_strdup(" Janvier ");
	if (monthnb[0] == '0' && monthnb[1] == '2')
		*month = ft_strdup(" Fevrier ");
	if (monthnb[0] == '0' && monthnb[1] == '3')
		*month = ft_strdup(" Mars ");
	if (monthnb[0] == '0' && monthnb[1] == '4')
		*month = ft_strdup(" Avril ");
	if (monthnb[0] == '0' && monthnb[1] == '5')
		*month = ft_strdup(" Mai ");
	if (monthnb[0] == '0' && monthnb[1] == '6')
		*month = ft_strdup(" Juin ");
	if (monthnb[0] == '0' && monthnb[1] == '7')
		*month = ft_strdup(" Juillet ");
	if (monthnb[0] == '0' && monthnb[1] == '8')
		*month = ft_strdup(" Aout ");
	if (monthnb[0] == '0' && monthnb[1] == '9')
		*month = ft_strdup(" Septembre ");
	if (monthnb[0] == '1' && monthnb[1] == '0')
		*month = ft_strdup(" Octobre ");
	if (monthnb[0] == '1' && monthnb[1] == '1')
		*month = ft_strdup(" Novembre ");
	if (monthnb[0] == '1' && monthnb[1] == '2')
		*month = ft_strdup(" Decembre ");
}

/*
** Returns a string with <day month year>.
*/

static char	*ft_datetoa(unsigned long long nb)
{
	char	monthnb[3];
	char	year[5];
	char	*day;
	char	*s1;
	char	*s2;

	if (!(day = ft_date_init(nb)))
		return (NULL);
	monthnb[0] = day[2];
	monthnb[1] = day[3];
	monthnb[2] = '\0';
	year[0] = day[4];
	year[1] = day[5];
	year[2] = day[6];
	year[3] = day[7];
	year[4] = '\0';
	day[2] = '\0';
	s2 = NULL;
	ft_get_month(monthnb, &s2);
	s1 = ft_strjoin(day, s2);
	free(day);
	free(s2);
	s2 = ft_strjoin(s1, year);
	free(s1);
	return (s2);
}

/*
** Calculates the flagged output of a time variable.
*/

void		ft_time_output(t_var *var, char **output)
{
	int		len;

	ft_get_attributes(var);
	ft_get_format(var);
	ft_apply_format(var);
	var->s = ft_datetoa(var->ull);
	if (!var->s)
	{
		free(var->s);
		*output = ft_strdup("(date error)");
		var->width = 12;
		var->varlen += 12;
		return ;
	}
	len = ft_strlen(var->s);
	var->prec = len;
	var->width = len;
	if (!(*output = (char *)malloc(sizeof(char) * (var->width + 1))))
		return (ft_putstr("error from malloc in ft_time_output.\n"));
	ft_apply_flags(output, len, var);
	var->varlen += var->width;
	free(var->s);
}
