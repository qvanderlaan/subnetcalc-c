/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: qvan-der <qvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/11/12 13:09:05 by qvan-der      #+#    #+#                 */
/*   Updated: 2025/11/12 13:10:40 by qvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <subnetcalc.h>

int	parse_ipv4(const char *s, t_subnet *out)
{
	const char	*p = s;

	if (!read_u8(&p, &out->ip.o1) || *p++ != '.')
		return (0);
	if (!read_u8(&p, &out->ip.o2) || *p++ != '.')
		return (0);
	if (!read_u8(&p, &out->ip.o3) || *p++ != '.')
		return (0);
	if (!read_u8(&p, &out->ip.o4) || *p++ != '/')
		return (0);
	if (!read_u8(&p, &out->prefix) || out->prefix > 32)
		return (0);
	return (*p == '\0');
}
