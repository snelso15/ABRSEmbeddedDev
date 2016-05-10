#include <iostream>
#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>
#include "workerCallbacks.h"

#define KEY_UP 65362
#define KEY_LEFT 65361
#define KEY_RIGHT 65363


int main(int argc, char *argv[]){
    gtk_init (&argc, &argv);

    waitForWifi();

    registerWorkers();

    gtk_main ();

    cleanUp();
}
