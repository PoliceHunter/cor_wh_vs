/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_flags_with_d.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmyrcell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 12:08:18 by tmyrcell          #+#    #+#             */
/*   Updated: 2020/02/22 17:42:43 by jczech           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_printf.h"

char	*work_flags_with_d(t_flag *flag, char *tmp)
{
	if (ft_strcmp("0", tmp) == 0 && flag->precision == 0
			&& flag->is_dot == 1)
		return (check_zero_for_d(flag, tmp));
	tmp = set_sign_for_d(flag, tmp);
	tmp = second_step_for_d(flag, tmp);
	return (tmp);
}

char	*check_zero_for_d(t_flag *flag, char *str)
{
	ft_strdel(&str);
	if (flag->width == 1)
	{
		str = ft_strnew(flag->flag_plus ? 1 : 0);
		if (flag->flag_plus)
			str[0] = '+';
	}
	else
	{
		str = ft_memset(ft_memalloc(flag->width + 1), ' ', flag->width + 1);
		if (flag->flag_plus == 1 && flag->flag_minus == 0)
			str[flag->width - 1] = '+';
		else if (flag->flag_plus == 1 && flag->flag_minus == 1)
			str[0] = '+';
	}
	str[flag->width] = '\0';
	return (str);
}

char	*set_sign_for_d(t_flag *flag, char *tmp)
{
	char *ptr;

	if (flag->flag_plus == 1)
	{
		if (tmp[0] != '-')
		{
			ptr = ft_strjoin("+", tmp);
			ft_strdel(&tmp);
			return (ptr);
		}
	}
	else if (flag->flag_space == 1)
	{
		if (tmp[0] != '-')
		{
			ptr = ft_strjoin(" ", tmp);
			ft_strdel(&tmp);
			return (ptr);
		}
	}
	return (tmp);
}

char	*second_step_for_d(t_flag *flag, char *tmp)
{
	unsigned int len_wihtout_sign;
	unsigned int len;

	if (flag->precision == 0 && flag->is_dot == 0)
	{
		len_wihtout_sign = ft_strlen(tmp);
		if (flag->flag_zero == 1 && flag->flag_minus == 0)
		{
			if (flag->width > len_wihtout_sign)
				tmp = fill_0_after_space(tmp, flag->width - len_wihtout_sign);
		}
		else if (flag->width > len_wihtout_sign)
		{
			len = ft_strlen(tmp);
			if (flag->flag_minus == 1)
				tmp = ad_fld_end(tmp, flag->width - len);
			else
				tmp = add_fld_strt(tmp, flag->width - len);
		}
	}
	else
		tmp = second_step_for_d2(flag, tmp);
	return (tmp);
}

char	*second_step_for_d2(t_flag *flag, char *tmp)
{
	unsigned int len;

	len = len_without_spec(tmp);
	if (flag->precision > len && flag->flag_minus == 1 && flag->flag_zero == 1)
		tmp = fill_0_after_space(tmp, flag->width - len);
	else if (flag->precision > len)
		tmp = fill_0_after_space(tmp, flag->precision - len);
	if (flag->width > ft_strlen(tmp))
	{
		if (flag->flag_minus == 1)
			tmp = ad_fld_end(tmp, flag->width - ft_strlen(tmp));
		else
			tmp = add_fld_strt(tmp, flag->width - ft_strlen(tmp));
	}
	return (tmp);
}
