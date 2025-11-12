/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   show_usage.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: qvan-der <qvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/11/12 13:05:50 by qvan-der      #+#    #+#                 */
/*   Updated: 2025/11/12 13:14:58 by qvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <subnetcalc.h>

int	show_usage(void)
{
	printf("Usage: subnetcalc <IPv4_ADDRESS/PREFIX>\n");
	printf("Example: ./subnetcalc 192.168.10.55/20\n");
	return (1);
}
