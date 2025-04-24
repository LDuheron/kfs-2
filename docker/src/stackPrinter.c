/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stackPrinter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athierry <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:31:11 by athierry          #+#    #+#             */
/*   Updated: 2025/04/24 20:13:19 by athierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stackPrinter.h"

void charToHex(const uint8_t c, uint16_t** writeTo){
	const char base[16] = "0123456789ABCDEF";
	*((*writeTo)++) = base[UPPER_BITS(c)] | VGAWHITE << 8;
	*((*writeTo)++) = base[LOWER_BITS(c)] | VGAWHITE << 8;
	//*((*writeTo)++) = '.';
}

void writeStackToVga(const void *stack, int size, uint16_t* vgaBuffer){
	const uint8_t* stackAsChar = stack;
	if (size > VGA_BUFFER_SIZE / 2)
		size = VGA_BUFFER_SIZE / 2;
	//for (int i = 0; i < 4; i++)
		//charToHex((((unsigned long) stack) >> i * 8) & 0xff, &vgaBuffer);
	for (int i = 0; i < size; i++)
		charToHex(*(stackAsChar++), &vgaBuffer);
}

/*
#include <stdio.h>

int main( void ){
	char str[25];
	char stack[] = "HELLO WORLD";
	writeStackToVga((void*) stack, 12, str);
	printf("in str: %s\n", str);
	return 0;
}
*/
