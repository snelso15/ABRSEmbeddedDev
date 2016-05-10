#ifndef kioskKeyInput_H
#define kioskKeyInput_H

#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>


#define KEY_UP 65362
#define KEY_DOWN 65364
#define KEY_LEFT 65361
#define KEY_RIGHT 65363
#define KEY_a 97
#define KEY_b 98
#define KEY_c 99
#define KEY_d 100
#define KEY_e 101
#define KEY_f 102
#define KEY_g 103
#define KEY_h 104
#define KEY_space 32
#define KEY_0 48
#define KEY_1 49
#define KEY_2 50
#define KEY_3 51
#define KEY_4 52
#define KEY_5 53
#define KEY_6 54
#define KEY_7 55
#define KEY_8 56
#define KEY_9 57
#define KEY_star 6550542
#define KEY_hash 6550535


class kioskKeyInput
{

	public:
		kioskKeyInput(void);
		gchar readKey(guint& kioskKeyVal);

};

#endif
