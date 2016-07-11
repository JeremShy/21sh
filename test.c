/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <jcamhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/07 18:07:04 by jcamhi            #+#    #+#             */
/*   Updated: 2016/07/11 18:03:39 by vsteffen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

int main()
{
	char truc[1001];
	printf("on entre dans le programme\n");
	while  (read(0, truc, 1000));
	printf("on sort du programme\n");
// 		exit(0);
	return (0);
}
