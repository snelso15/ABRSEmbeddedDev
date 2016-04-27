#include "kioskKeyInput.h"
#include <iostream>



kioskKeyInput::kioskKeyInput(void)
{

}

gchar kioskKeyInput::readKey(guint &kioskKeyVal)
{
	printf("Seen Key Value = %d\n", kioskKeyVal);
	gchar key = 'z';
	// handle menu navigation
	switch( kioskKeyVal ) 
	{
		case KEY_a:
			key = 'a';
			printf("%c\n", key);
			break;
		case KEY_b:
			key = 'b';
			printf("%c\n", key);
			break;
		case KEY_c:
			key = 'c';
			printf("%c\n", key);
			break;
		case KEY_d:
			key = 'd';
			printf("%c\n", key);
			break;
		case KEY_e:
			key = 'e';
			printf("%c\n", key);
			break;
		case KEY_f:
			key = 'f';
			printf("%c\n", key);
			break;
		case KEY_g:
			key = 'g';
			printf("%c\n", key);
			break;
		case KEY_h:
			key = 'h';
			printf("%c\n", key);
			break;
		case KEY_space:
			key = ' ';
			break; 
		case KEY_0:
			key = '0';
			printf("%c\n", key);
			break;
		case KEY_1:
			key = '1';
			printf("%c\n", key);
			break;
		case KEY_2:
			key = '2';
			printf("%c\n", key);
			break;
		case KEY_3:
			key = '3';
			printf("%c\n", key);
			break;
		case KEY_4:
			key = '4';
			printf("%c\n", key);
			break;
		case KEY_5:
			key = '5';
			printf("%c\n", key);
			break;
		case KEY_6:
			key = '6';
			printf("%c\n", key);
			break;
		case KEY_7:
			key = '7';
			printf("%c\n", key);
			break;
		case KEY_8:
			key = '8';
			printf("%c\n", key);
			break;
		case KEY_9:
			key = '9';
			printf("%c\n", key);
			break;
		case KEY_star:
			key = '*';
			printf("%c\n", key);
			break;
		case KEY_hash:
			key = '#';
			printf("%c\n", key);
			break;
		default:				
		//				
			break;   
	}
	return key;

}

