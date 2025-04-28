/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stackPrinter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athierry <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:31:11 by athierry          #+#    #+#             */
/*   Updated: 2025/04/28 20:38:52 by athierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/stackPrinter.h"

void charToHex(const uint8_t c, uint16_t** writeTo){
	const char base[16] = "0123456789ABCDEF";
	const uint8_t* vgaAsChar = (uint8_t*) *writeTo;
	*((*writeTo)++) = base[UPPER_BITS(c)] | VGAWHITE << 8;
	*((*writeTo)++) = base[LOWER_BITS(c)] | VGAWHITE << 8;
	*((*writeTo)++) = '.' | VGAWHITE << 8;
}

void printAddress( const void *stack, uint16_t** writeTo ){
	const char base[] = "@address ";
	const uint8_t* vgaAsChar = (uint8_t*) *writeTo;
	uint64_t stackAs16Int = (uint64_t) stack;
	int i = 0;
	while (*(base + i))
		*((*writeTo)++) = *(base + i++) | VGAWHITE << 8;
	*writeTo += INT16REPLENGTH - 1;
	i = 1;
	while (i < INT16REPLENGTH){
		*(*writeTo - i++) = stackAs16Int % 10 + '0' | VGAWHITE << 8;
		stackAs16Int /= 10;
	}
	*((*writeTo)++) = ':' | VGAWHITE << 8;
	*((*writeTo)++) = ' ' | VGAWHITE << 8;

}

void printStackLine( const void *stack, uint16_t** writeTo ){
	const uint8_t* stackAsChar = (uint8_t*) stack;
	const uint8_t* vgaAsChar = (uint8_t*) *writeTo;
	printAddress(stack, writeTo);
	**writeTo = ' ' | VGAWHITE << 8;
	for (int i = 0; i < LINESIZE; i++)
		charToHex(*(stackAsChar - i), writeTo);
	*((*writeTo) - 1) = ' ' | VGAWHITE << 8;
	*((*writeTo)++) = ' ' | VGAWHITE << 8;
	for (int i = 0; i < LINESIZE - 1; i++)
		*((*writeTo)++) = *(stackAsChar + i) | VGAWHITE << 8;
}

void writeStackToVga(const void *stack, int size, uint16_t* vgaBuffer){
	const uint8_t* stackAsChar = (uint8_t*) stack;
	const uint8_t* vgaAsChar = (uint8_t*) vgaBuffer;
	if (size > VGA_BUFFER_SIZE / 2)
		size = VGA_BUFFER_SIZE / 2;
	//for (int i = 0; i < 4; i++)
		//charToHex((((unsigned long) stack) >> i * 8) & 0xff, &vgaBuffer);
	for (int i = 0; i < 25; i++){
		printStackLine(stackAsChar, &vgaBuffer);
		//vgaBuffer += 1;
		stackAsChar -= LINESIZE;
	}
}

void initialAddress(const void *stack, uint16_t* vgaBuffer){
	printAddress(stack, &vgaBuffer);
}

/*
#include "stdio.h"
int main( void ){
	char vgaBuffer[20000];
	char stack[] = "hello world how are you doing";
	initialAddress((const void *) 10, (uint16_t *) &vgaBuffer);
	writeStackToVga((void*) stack, 12, (uint16_t*) vgaBuffer);
	printf("%s\n", vgaBuffer);
	return 0;
}
*/
