#include "framework.h"

#include "str/public/str.h"

static void get_hex_string(uint32_t int_value, uint8_t *ret_char)
	{
	/* First we mask off rest than last 4 bits (which counts as one
	 * hex character */
	int_value = int_value &	0x0000000F;

	/* If value is number */
	if(int_value >= 0 && int_value <= 9)
		{
		*ret_char = int_value+'0';
		}
	/* If value is HEX */
	else
		{
		*ret_char = int_value+'A'-10;
		}
	}

static void return_string_from_uint(uint32_t input_value, char *output_str, uint32_t divider, uint8_t str_begin_idx) {
	uint8_t number_idx = 0;

	do
		{
		if(( input_value / divider ) != 0 ||
			number_idx > 0)
			{
			output_str[str_begin_idx] = ( input_value / divider )+'0';
			str_begin_idx++;
			number_idx++;
			}

		input_value = input_value%divider;
		divider = divider/10;

		} while ( divider != 0 );

	/* This is for special case: value was 0. */
	if(number_idx == 0) {
		output_str[str_begin_idx] = '0';
		str_begin_idx++;
	}

	output_str[str_begin_idx] = '\0';
}

void str_merge(char *source, char *target, uint8_t begin_idx ) {
	uint8_t i = 0;
	while (source[i] != '\0')
		{
		target[i+begin_idx] = source[i];
		i++;
		}

}

void str_from_uint8_hex(uint8_t input_value, char *output_str)
	{
	str_merge("0x", output_str, 0);
	get_hex_string(input_value>>4, output_str+2);
	get_hex_string(input_value, output_str+3);
	output_str[4] = '\0';
	}


void str_from_uint32_hex(uint32_t input_value, char *output_str)
	{
	str_merge("0x", output_str, 0);
	get_hex_string(input_value>>28, output_str+2);
	get_hex_string(input_value>>24, output_str+3);
	get_hex_string(input_value>>20, output_str+4);
	get_hex_string(input_value>>16, output_str+5);
	get_hex_string(input_value>>12, output_str+6);
	get_hex_string(input_value>>8, output_str+7);
	get_hex_string(input_value>>4, output_str+8);
	get_hex_string(input_value, output_str+9);
	output_str[10] = '\0';
	}


void str_from_uint8(uint8_t input_value, char *output_str)
	{
	/* Divider 100! 255 value which is max value of
	 * uint8. */
	return_string_from_uint((uint32_t)input_value, output_str, 100, 0);
	}

void str_from_uint32(uint32_t input_value, char *output_str)
	{
	/* Divider 1000000000! 4,294,967,295 value which is max value of
	 * uint32. */
	return_string_from_uint(input_value, output_str, 1000000000, 0);
	}

void str_from_int32(int32_t input_value, char *output_str)
	{
	uint8_t str_idx = 0;

	/* If value is negative */
	if (input_value < 0)
		{
		output_str[str_idx] = '-';
		input_value = input_value * -1;
		str_idx++;
		}

	/* Now value is "positive", so we can use same algorythm as to uint type. */
	return_string_from_uint((uint32_t)input_value, output_str, 1000000000, str_idx);
	}

extern statusc_t str_compare( char *string_one, char *string_two, uint8_t compare_begin_from_idx, uint8_t max_idx_to_compare)
	{
	int32_t string_idx = compare_begin_from_idx-1;

	do {
		string_idx++;
		if(	string_one[string_idx] != string_two[string_idx] )
			{
			return SC_FALSE;
			}
	} while ( string_one[string_idx] != '\0' && string_idx < max_idx_to_compare);

	return SC_TRUE;
	}

static uint8_t get_first_token_idx( char *in_source_str, char delimiter, uint8_t token_number) {
	uint8_t begin_idx = 0;

	for(uint8_t i = 0, token_count = 0;
		token_count < token_number && in_source_str[i] != '\0';
		i++)
		{
			if(in_source_str[i] == delimiter)
				token_count++;
			begin_idx = i;
		}

	if(begin_idx > 0 ) begin_idx++;
	return begin_idx;
}

static uint8_t get_second_token_idx( char *in_source_str, char delimiter, uint8_t search_begin_idx) {

	for(uint8_t i = search_begin_idx;
		in_source_str[i] != delimiter && in_source_str[i] != '\0';
		i++)
		{
			search_begin_idx = i;
		}

	return search_begin_idx;
}

statusc_t str_get_token_indexes( char *in_source_str, char delimiter, uint8_t token_number, uint8_t *out_begin_idx, uint8_t *out_end_idx ) {

	if( in_source_str == NULL ||
		out_begin_idx == NULL ||
		out_begin_idx == NULL )
		{
			return SC_NULL_ARGUMENT;
		}

	*out_begin_idx = 0;
	*out_end_idx = 0;

	*out_begin_idx = get_first_token_idx(in_source_str, delimiter, token_number);

	*out_end_idx = get_second_token_idx( in_source_str, delimiter, *out_begin_idx);

	if( *out_begin_idx == *out_end_idx)
		return SC_OUT_OF_RANGE;
	else
		return SC_SUCCESS;
	}

statusc_t is_substring_in_string( char* substring, char* master_string, uint8_t substring_offset, uint8_t *query_last_idx) 
{
    
	for(uint8_t i = 0; substring[i] != 0; i++)
    {
        *query_last_idx = i + substring_offset;
        
        if(master_string[i+substring_offset] == NULL)
            return SC_FALSE;
        
        if(substring[i] != master_string[i+substring_offset])
            return SC_FALSE;
    }
    
    return SC_TRUE;
}

statusc_t str_is_substring_of(char* master_string, char* substring, uint8_t substring_offset) 
{   
    uint8_t not_used;
    return is_substring_in_string(substring, master_string, substring_offset, &not_used);
}

statusc_t is_character_in_list_or_is_null( char * character_list, char end_character ) 
{
    if(end_character == NULL)
        return SC_TRUE;
    
    for(uint8_t i = 0; character_list[i] != 0; i++)
        if(end_character == character_list[i])
            return SC_TRUE;
            
    return SC_FALSE;
}

statusc_t str_is_word_in_string(  char* string, 
                                  char* word,
                                  uint8_t word_offset,
                                  char *accepted_ends) 
{   
    uint8_t query_last_idx;
    if(is_substring_in_string(word, string, word_offset, &query_last_idx) == SC_FALSE)
        return SC_FALSE;
    
    char end_character = string[query_last_idx+1];
    
    return is_character_in_list_or_is_null(accepted_ends, end_character);
}