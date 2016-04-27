#include <iostream>
#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>
#include "graphicalFunctions.h"
#include "KeyPressInterpreter.h"

#define KEY_UP 65362
#define KEY_LEFT 65361
#define KEY_RIGHT 65363

int count = 0;

int unlock_msg_cb(gpointer data){
	KeyPressInterpreter *p_kpi = static_cast<KeyPressInterpreter *>(data);
	printf("timer went off! Checking to see if unlock msg should be sent....\n");
	p_kpi->tryDataPull();
	if(p_kpi->testCode()){
		printf("code matched! should send message!\n");
		p_kpi->printQueue();
		p_kpi->resetCodeBuffer();
	} else {
		printf("Key not matched....\n");
		p_kpi->printQueue();
	}
	return 1;
}



int main(int argc, char *argv[]){

	printf("starting!!!..........!!!!.........\n");
    gtk_init (&argc, &argv);
	graphicalFunctions gF = graphicalFunctions();
	gF.buildUI();
	gF.connectSignals();
	printf("CONNECTING BITCHOFASIGNAL\n");

	GAsyncQueue *q = g_async_queue_new();

	KeyPressInterpreter *kpi = new KeyPressInterpreter(q);

	g_signal_connect(G_OBJECT(gF.getMainWindow()), "key_press_event", G_CALLBACK(&key_press_cb), &gF);
	gdk_threads_add_timeout(1000, unlock_msg_cb, kpi);
	gdk_threads_add_timeout(3000, cbfn2, kpi);
    gtk_main ();
}

