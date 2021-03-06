/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dtoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmyrcell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 11:46:15 by tmyrcell          #+#    #+#             */
/*   Updated: 2020/02/23 19:19:07 by tmyrcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_printf.h"

char	*ft_dtoa(double num, unsigned int precision)
{
	return (ft_ldtoa(num, precision));
}
