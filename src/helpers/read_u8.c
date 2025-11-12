/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_u8.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: qvan-der <qvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/11/12 13:09:37 by qvan-der      #+#    #+#                 */
/*   Updated: 2025/11/12 13:14:43 by qvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <ctype.h>
#include <subnetcalc.h>

int	read_u8(const char **p, uint8_t *v)
{
	int	n;
	int	d;

	n = 0;
	d = 0;
	while (isdigit(**p))
	{
		if (++d > 3)
			return (0);
		n = n * 10 + (**p - '0');
		if (n > 255)
			return (0);
		(*p)++;
	}
	*v = (uint8_t)n;
	return (d > 0);
}
