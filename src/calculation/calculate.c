/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   calculate.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: qvan-der <qvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/11/12 13:10:48 by qvan-der      #+#    #+#                 */
/*   Updated: 2025/11/12 13:10:58 by qvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <subnetcalc.h>

void	calc_subnet(t_subnet *s)
{
	uint32_t	ip;

	ip = (s->ip.o1 << 24) | (s->ip.o2 << 16) | (s->ip.o3 << 8) | s->ip.o4;
	s->host_bits = 32 - s->prefix;
	if (s->prefix == 0)
		s->mask = 0;
	else
		s->mask = 0xFFFFFFFF << s->host_bits;
	s->network = ip & s->mask;
	s->broadcast = s->network | ~s->mask;
}
