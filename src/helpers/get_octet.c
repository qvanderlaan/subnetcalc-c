/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_octet.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: qvan-der <qvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/11/12 13:09:28 by qvan-der      #+#    #+#                 */
/*   Updated: 2025/11/12 13:14:46 by qvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <subnetcalc.h>

uint8_t	get_octet(uint32_t value, int index)
{
	return ((value >> (8 * (3 - index))) & 0xFF);
}
