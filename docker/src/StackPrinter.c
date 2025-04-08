/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StackPrinter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athierry <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:31:11 by athierry          #+#    #+#             */
/*   Updated: 2025/04/08 19:25:59 by athierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define UPPER_BITS(c) (((char) (c) & 0xf0) >> 4)
#define LOWER_BITS(c) ((char) (c) & 0x0f)
#define VGA_WIDTH 80
#define VGA_LENGTH 25
#define VGA_BUFFER_SIZE VGA_WIDTH * VGA_LENGTH;

void charToHex(const char c, char** writeTo){
	const char base[16] = "0123456789ABCDEF";
	*((*writeTo)++) = base[UPPER_BITS(c)];
	*((*writeTo)++) = base[LOWER_BITS(c)];
	//*((*writeTo)++) = '.';
}

void writeStackToVga(const void *stack, int size, char* vgaBuffer){
	const char* stackAsChar = stack;
	if (size > VGA_BUFFER_SIZE / 2)
		size = VGA_BUFFER_SIZE / 2;
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
