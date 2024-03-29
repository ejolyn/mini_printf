/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processor_numbers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejolyn <ejolyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 10:48:12 by ejolyn            #+#    #+#             */
/*   Updated: 2020/11/28 12:03:16 by ejolyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	counter_nul_spaces(int *count_spaces, int len, t_parsered *inf)
{
	if (inf->precision != 0 && (inf->width > len || inf->precision > len))
	{
		if (inf->width > inf->precision)
		{
			if (inf->precision > len)
			{
				inf->count_nul = inf->precision - len;
				*count_spaces = inf->width - inf->precision;
			}
			else
				*count_spaces = inf->width - len;
		}
		else if (inf->precision > len)
			inf->count_nul = inf->precision - len;
	}
	else
	{
		if (inf->flag_nul != 0 && inf->width > len)
			inf->count_nul = inf->width - len;
		else if (inf->width > len)
			*count_spaces = inf->width - len;
	}
}

void	counter_helper(int *count_spaces, int numb, t_parsered *inf, int len)
{
	if (numb < 0 && (inf->type == 'd' || inf->type == 'i'))
	{
		if (inf->precision > len - 1 && inf->precision_flag == 1)
		{
			inf->count_nul = inf->count_nul + 1;
			if (*count_spaces > 0 && *count_spaces > 0 &&
				inf->precision_flag == 1)
				*count_spaces = *count_spaces - 1;
		}
	}
	if (numb == 0 && inf->precision_flag == 1 && inf->precision == 0)
	{
		*count_spaces = inf->width;
		inf->ret_value -= 1;
	}
	inf->ret_value += inf->count_nul + *count_spaces + len;
}

void	process_number(va_list *argptr, t_parsered *inf)
{
	int		numb;
	int		len;
	int		count_spaces;

	numb = va_arg(*argptr, int);
	len = counter(numb);
	len = (numb < 0) ? len + 1 : len;
	count_spaces = 0;
	counter_nul_spaces(&count_spaces, len, inf);
	counter_helper(&count_spaces, numb, inf, len);
	if (inf->flag_minus == 0)
		while (count_spaces--)
			write(1, " ", 1);
	if (numb < 0)
		write(1, "-", 1);
	if (!(numb == 0 && inf->precision_flag == 1 && inf->precision == 0))
	{
		while (inf->count_nul--)
			write(1, "0", 1);
		ft_putnbr_fd(numb);
	}
	if (inf->flag_minus == 1)
		while (count_spaces--)
			write(1, " ", 1);
}

void	process_unsigned_number(va_list *argptr, t_parsered *inf)
{
	unsigned int	numb;
	int				len;
	int				count_spaces;

	numb = va_arg(*argptr, int);
	len = u_counter(numb);
	count_spaces = 0;
	counter_nul_spaces(&count_spaces, len, inf);
	counter_helper(&count_spaces, numb, inf, len);
	if (inf->flag_minus == 0)
		while (count_spaces--)
			write(1, " ", 1);
	if (!(numb == 0 && inf->precision_flag == 1 && inf->precision == 0))
	{
		while (inf->count_nul--)
			write(1, "0", 1);
		ft_put_u_nbr_fd(numb);
	}
	if (inf->flag_minus == 1)
		while (count_spaces--)
			write(1, " ", 1);
}
