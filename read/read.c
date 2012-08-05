/*
 * read.c
 *
 * Created: 27.2.2012 21:01:41
 *  Author: savpek
 */

#include "framework.h"
#include "./read/public/read.h"
#include "./read/config/read_config.h"
#include "./print/public/print.h"

static statusc_t is_printable(char c) {
	switch(c) {
		case ' '...('~'+1): /* SPACE - DEL */
		case '\n':
	    case '\r': 
		case '\b':	/* Backspace. */
			return SC_TRUE;
		default:
			return SC_FALSE;
	}
}

char read_char( void ) {
	char c;

	/* Check that received character is PRINTABLE character */
	while(1) {
		c = read_try_get_char();
		if( c != 0) return c;		/* <- If not 0, is printable! */
	}
}

char read_try_get_char( void) {
	char c;

	/* If buffer is empty. */
	if(READ_TRY_GET_CHAR(&c) != SC_SUCCESS) return '\0';

	/* If not printable. */
	if( is_printable(c) != SC_TRUE ) return '\0';

	return c;
}

uint8_t read_data( void ) {
	char c;
	while(READ_TRY_GET_CHAR(&c) != SC_SUCCESS );
	return c;
}

statusc_t is_endline_char(char a)
{
    if( a == '\n' || a == '\r')
        return SC_TRUE;
    return SC_FALSE;
}

statusc_t is_backspace_char(char a)
{
    if( a == '\b' || a == 0x7F)
        return SC_TRUE;
    return SC_FALSE;
}

void read_line( char* return_string, uint8_t return_buffer_size ) {
	char c;
	uint8_t idx = 0;
    return_string[0] = '\0';

	while(1) 
    {
        c = read_char();
        if ( is_endline_char(c) == SC_TRUE) 
            break;
        
        if( is_backspace_char(c) == SC_TRUE) 
        {
			if( idx > 0)  {
				idx--;
				print_char(c);
			}
			return_string[idx] = '\0';
		}
        // Is buffer full.
		else if (idx < return_buffer_size) 
        {
			return_string[idx] = c;
			return_string[idx+1] = '\0';
			idx++;
			print_char(c);
		}
	}
	
    print_char('\r');
	print_char('\n');
}

