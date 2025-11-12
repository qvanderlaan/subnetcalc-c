/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   calc_error.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: qvan-der <qvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/11/12 13:11:17 by qvan-der      #+#    #+#                 */
/*   Updated: 2025/11/12 13:15:04 by qvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <subnetcalc.h>

int	calc_error(void)
{
	printf("Error: Invalid IP address format.\n");
	printf("Expected format: xxx.xxx.xxx.xxx/yy\n");
	return (1);
}
