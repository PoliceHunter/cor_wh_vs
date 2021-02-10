/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_flags_with_o.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmyrcell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 12:11:06 by tmyrcell          #+#    #+#             */
/*   Updated: 2020/02/23 19:30:38 by tmyrcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_printf.h"

char	*work_flags_with_o(t_flag *flag, char *tmp)
{
	if (ft_strcmp("0", tmp) == 0 && flag->precision == 0
			&& flag->is_dot == 1 && flag->flag_hash == 0)
	{
		ft_strdel(&tmp);
		if (flag->width < 2)
			return (ft_strdup(""));
		else
			tmp = ft_strdup("");
	}
	tmp = first_step_for_o(flag, tmp);
	tmp = second_step_for_o(flag, tmp);
	return (tmp);
}

char	*first_step_for_o(t_flag *flag, char *tmp)
{
	char *ptr;

	if (flag->flag_hash == 1 && ft_strcmp("0", tmp) == 0)
		return (tmp);
	if (flag->flag_hash == 1)
	{
		ptr = ft_strjoin("0", tmp);
		ft_strdel(&tmp);
		return (ptr);
	}
	return (tmp);
}

char	*second_step_for_o(t_flag *flag, char *tmp)
{
	if (flag->precision == 0 && flag->is_dot == 0)
	{
		if (flag->flag_zero == 1 && flag->flag_minus == 0)
		{
			if (flag->width > ft_strlen(tmp))
				tmp = ad_0_aftersign(tmp, flag->width - ft_strlen(tmp));
		}
		else if (flag->width > ft_strlen(tmp))
		{
			if (flag->flag_minus == 1)
				tmp = ad_fld_end(tmp, flag->width - ft_strlen(tmp));
			else
				tmp = add_fld_strt(tmp, flag->width - ft_strlen(tmp));
		}
	}
	else
		tmp = second_step_for_o2(flag, tmp);
	return (tmp);
}

char	*second_step_for_o2(t_flag *flag, char *tmp)
{
	if (flag->precision > ft_strlen(tmp))
		tmp = ad_0_aftersign(tmp, flag->precision - ft_strlen(tmp));
	if (flag->width > ft_strlen(tmp))
	{
		if (flag->flag_minus == 1)
			tmp = ad_fld_end(tmp, flag->width - ft_strlen(tmp));
		else
			tmp = add_fld_strt(tmp, flag->width - ft_strlen(tmp));
	}
	return (tmp);
}
