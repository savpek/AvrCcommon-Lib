#include "framework.h"
#include "statusc/public/statusc.h"
#include "str/public/str.h"

static void print_line(char* string) {
	for(uint8_t i = 0; string[i] != '\0'; i++)
		STATUSC_ASSERT_OUTPUT_CHAR(string[i]);
}


void statusc_assert_body(uint8_t assert_value, char* file_name, uint32_t assert_line ) 
{
	if( assert_value == 0)
	{
		print_line("\033[93m \n\rASSERT evaluated FALSE at line ");
		
		char* print_temp[STR_DEC_UINT32_SIZE];
		str_from_uint32(assert_line, print_temp);
		print_line(print_temp);
		
		print_line(" in file ");
		print_line(file_name);
		print_line("\033[0m \n\r");
	}	
}
