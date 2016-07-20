#include "graphicalFunctions.h"
#include <iostream>
#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>
#include "kioskKeyInput.h"
#include <algorithm>


int testfoo = 0;
//int weatherfoo = 0;

GtkWidget *infoLabel = gtk_label_new(NULL);  // TODO: put in header
//infoLabel = gtk_label_new(NULL);
char* infoMessage = "";

GtkWidget *weatherLabel = gtk_label_new(NULL);  // TODO: put in header
GtkWidget *weatherForecast = gtk_label_new(NULL);
GtkWidget *weatherTodayHighTempLabel = gtk_label_new(NULL);
GtkWidget *weatherTodayLowTempLabel = gtk_label_new(NULL);
GtkWidget *weatherImage;
GtkWidget *labelInfoPage;
GtkWidget *RentalSuccessLabel;
GtkWidget *RentalImageFrame1;
GtkWidget *RentalImageFrame2;
GtkWidget *RentalImageFrame3;
GtkWidget *RentalImageFrame4;
GtkWidget *RentalImageFrame5;
GtkWidget *RentalImageBike1;
GtkWidget *RentalImageBike2;
GtkWidget *RentalImageBike3;
GtkWidget *RentalImageBike4;
GtkWidget *RentalImageBike5;
GtkWidget *AdminWifiIpAddressLabel;
GtkWidget *Admin3gIpAddressLabel;
GtkWidget *PowerSystemLevelLabel;
GtkWidget *OnlineCodeLabel;
GtkWidget *RentalReturnedLabel;
GtkWidget *bicycleReportProblemSuccessErrorOrLabel;


graphicalFunctions::graphicalFunctions(void)
{
	GtkWidget *window;
	gtk_notebook_new();
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    mainWindow = window;
    gtk_window_set_default_size (GTK_WINDOW (window), 1024, 600);
    gtk_widget_set_size_request(window, 1024, 600);
    gtk_window_set_resizable (GTK_WINDOW(window), FALSE);
	kki = kioskKeyInput();
}

gint graphicalFunctions::connectSignals(){
	g_signal_connect (G_OBJECT (mainWindow), "destroy",G_CALLBACK (destroy_window), NULL);
}

gint graphicalFunctions::buildUI(){

    // create fixed widget to layer 3 notebooks on -- buttons, menu items, buttons
    fixed = gtk_fixed_new();
    gtk_container_add (GTK_CONTAINER (mainWindow), fixed);

    // button col left
    frame = gtk_frame_new (0);
	gtk_widget_set_size_request (frame, 180, 600);

	// button col right
	frame = gtk_frame_new (0);
	gtk_widget_set_size_request (frame, 212, 624);

	// center
	frame = gtk_frame_new (0);
	gtk_widget_set_size_request (frame, 644, 600);

  	centerNotebook = gtk_notebook_new ();
    gtk_notebook_set_tab_pos (GTK_NOTEBOOK (centerNotebook), GTK_POS_TOP);
    gtk_fixed_put (GTK_FIXED(fixed), centerNotebook, 200, 0);
    gtk_widget_show (centerNotebook);


	///////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////// center column notebook
	///////////////////////////////////////////////////////////////////////////////////////////////////////
	centerFixed = gtk_fixed_new();
	// main page

	image = gtk_image_new_from_file("/home/pi/bike_project/Tfronts.png");
	
	label = gtk_label_new ("0");

	label1 = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label1), "<span foreground=\"black\" font=\"55\"><b>York College</b></span>");
	//gtk_fixed_put (GTK_FIXED(centerFixed), label1, 15, 0);
	gtk_fixed_put (GTK_FIXED(centerFixed), label1, 95, 0);
	label1 = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label1), "<span foreground=\"black\" font=\"55\"><b>   Bicycle</b></span>");
	//gtk_fixed_put (GTK_FIXED(centerFixed), label1, 0, 100);
	gtk_fixed_put (GTK_FIXED(centerFixed), label1, 130, 85);
	label1 = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label1), "<span foreground=\"black\" font=\"55\"><b>Rental System</b></span>"); 
	gtk_fixed_put (GTK_FIXED(centerFixed), label1, 60, 170);
	label1 = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label1), "<span foreground=\"black\" font=\"25\"><b>http://york-abrs.herokuapp.com</b></span>");
	gtk_fixed_put (GTK_FIXED(centerFixed), label1, 60, 290);
	gtk_fixed_put (GTK_FIXED(centerFixed), image, 10, 340);
	//gtk_fixed_put (GTK_FIXED(centerFixed), image, 10, 300);
	gtk_notebook_append_page (GTK_NOTEBOOK (centerNotebook), centerFixed, label);

	 ///////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////// left column notebook
    ///////////////////////////////////////////////////////////////////////////////////////////////////////
    leftNotebook = gtk_notebook_new ();
    gtk_notebook_set_tab_pos (GTK_NOTEBOOK (leftNotebook), GTK_POS_TOP);
    gtk_fixed_put (GTK_FIXED(fixed), leftNotebook, 0, 0);
    gtk_widget_show (leftNotebook);
    label = gtk_label_new ("0");
    leftFixed = gtk_fixed_new();



    label1 = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label1), "<span foreground=\"black\" font=\"30\"><b>Rent</b></span>");
	gtk_fixed_put (GTK_FIXED(leftFixed), label1, 40, UI_BUTTON_POSITION_1);
	label1 = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label1), "<span foreground=\"black\" font=\"30\"><b>Info</b></span>");
	gtk_fixed_put (GTK_FIXED(leftFixed), label1, 40, UI_BUTTON_POSITION_2);
	label1 = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label1), "<span foreground=\"black\" font=\"30\"><b>Weather</b></span>");
	gtk_fixed_put (GTK_FIXED(leftFixed), label1, 15, UI_BUTTON_POSITION_3);

	gtk_notebook_append_page (GTK_NOTEBOOK (leftNotebook), leftFixed, label);




	///////////////////////////////////////////////////////////////////////////////////////////////////////
    // right column notebook
    ///////////////////////////////////////////////////////////////////////////////////////////////////////
    rightNotebook = gtk_notebook_new ();
    gtk_notebook_set_tab_pos (GTK_NOTEBOOK (rightNotebook), GTK_POS_TOP);
    gtk_fixed_put (GTK_FIXED(fixed), rightNotebook, 824, 0);
    gtk_widget_show (rightNotebook);
    label = gtk_label_new ("0");
    rightFixed = gtk_fixed_new();
  
    label1 = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label1), "<span foreground=\"black\" font=\"30\"><b>Report</b></span>");
	gtk_fixed_put (GTK_FIXED(rightFixed), label1, 40, UI_BUTTON_POSITION_1);
//	label1 = gtk_label_new(NULL);
//	gtk_label_set_markup(GTK_LABEL(label1), "<span foreground=\"black\" font=\"30\"><b>Rates</b></span>");
//	gtk_fixed_put (GTK_FIXED(rightFixed), label1, 40, UI_BUTTON_POSITION_2);
//	label1 = gtk_label_new(NULL);
//	gtk_label_set_markup(GTK_LABEL(label1), "<span foreground=\"black\" font=\"30\"><b>Map</b></span>");
//	gtk_fixed_put (GTK_FIXED(rightFixed), label1, 45, UI_BUTTON_POSITION_3);
	label1 = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label1), "<span foreground=\"black\" font=\"30\"><b>Map</b></span>");
	gtk_fixed_put (GTK_FIXED(rightFixed), label1, 45, UI_BUTTON_POSITION_2);

  	gtk_notebook_append_page (GTK_NOTEBOOK (rightNotebook), rightFixed, label);

  	////////////////////////////////////////////////////////////////////////////
  	/////////////// rental screen 
  	/////////////////////////////////////////////////////////////////////////////

	////// center rent //////
	centerFixed = gtk_fixed_new();
	label = gtk_label_new ("1");
	label1 = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label1), "<span foreground=\"black\" font=\"55\"><b>Rent a Bicycle</b></span>"); 
	gtk_fixed_put (GTK_FIXED(centerFixed), label1, 50, 200);
	label1 = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label1), "<span foreground=\"black\" font=\"40\"><b>Choose Payment Method</b></span>"); 
	gtk_fixed_put (GTK_FIXED(centerFixed), label1, 0, 300);

	gtk_notebook_append_page (GTK_NOTEBOOK (centerNotebook), centerFixed, label);

	////// left rent ///////
    leftFixed = gtk_fixed_new();
	label = gtk_label_new ("1");

    label1 = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label1), "<span foreground=\"black\" font=\"30\"><b>Credit</b></span>");
	gtk_fixed_put (GTK_FIXED(leftFixed), label1, 30, 100);
	label1 = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label1), "<span foreground=\"black\" font=\"30\"><b>Card</b></span>");
	gtk_fixed_put (GTK_FIXED(leftFixed), label1, 40, 140);

	label1 = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label1), "<span foreground=\"black\" font=\"30\"><b>Back</b></span>");
	gtk_fixed_put (GTK_FIXED(leftFixed), label1, 40, UI_BUTTON_POSITION_4);

    gtk_notebook_append_page (GTK_NOTEBOOK (leftNotebook), leftFixed, label);


	////// right rent //////
	label = gtk_label_new ("1");
    rightFixed = gtk_fixed_new();
  
    label1 = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label1), "<span foreground=\"black\" font=\"30\"><b>Online</b></span>");
	gtk_fixed_put (GTK_FIXED(rightFixed), label1, 40, 100);
	label1 = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label1), "<span foreground=\"black\" font=\"30\"><b>Code</b></span>");
	gtk_fixed_put (GTK_FIXED(rightFixed), label1, 40, 140);
	label1 = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label1), "<span foreground=\"black\" font=\"30\"><b>Cancel</b></span>");
	gtk_fixed_put (GTK_FIXED(rightFixed), label1, 40, UI_BUTTON_POSITION_4);

  	gtk_notebook_append_page (GTK_NOTEBOOK (rightNotebook), rightFixed, label);


   	////////////////////////////////////////////////////////////////////////////
  	/////////////// rental screen - pay with credit card 
  	/////////////////////////////////////////////////////////////////////////////

	////// center rent - pay with credit card //////
	centerFixed = gtk_fixed_new();
	label = gtk_label_new ("2");
	label1 = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label1), "<span foreground=\"black\" font=\"55\"><b>Please Swipe</b></span>"); 
	gtk_fixed_put (GTK_FIXED(centerFixed), label1, 70, 100);
	label1 = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label1), "<span foreground=\"black\" font=\"55\"><b>Your Credit Card</b></span>"); 
	gtk_fixed_put (GTK_FIXED(centerFixed), label1, 20, 225);



	gtk_notebook_append_page (GTK_NOTEBOOK (centerNotebook), centerFixed, label);

	////// left rent - pay with credit card///////
    leftFixed = gtk_fixed_new();
	label = gtk_label_new ("2");
	label1 = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label1), "<span foreground=\"black\" font=\"30\"><b>Back</b></span>");
	gtk_fixed_put (GTK_FIXED(leftFixed), label1, 40, UI_BUTTON_POSITION_4);

    gtk_notebook_append_page (GTK_NOTEBOOK (leftNotebook), leftFixed, label);


	////// right rent - pay with credit card//////
	label = gtk_label_new ("2");
    rightFixed = gtk_fixed_new();  

	label1 = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label1), "<span foreground=\"black\" font=\"30\"><b>Cancel</b></span>");
	gtk_fixed_put (GTK_FIXED(rightFixed), label1, 40, UI_BUTTON_POSITION_4);

  	gtk_notebook_append_page (GTK_NOTEBOOK (rightNotebook), rightFixed, label);



  	////////////////////////////////////////////////////////////////////////////
  	/////////////// rental screen - pay online 
  	/////////////////////////////////////////////////////////////////////////////

	////// center rent - pay online //////
	centerFixed = gtk_fixed_new();
	label = gtk_label_new ("3");
	//label1 = gtk_label_new(NULL);
	//gtk_label_set_markup(GTK_LABEL(label1), "<span foreground=\"black\" font=\"55\"><b>Enter 4-Digit\nOnline Code\n On Keypad</b></span>");
	//gtk_misc_set_alignment (GTK_MISC(label1), 0.5, 0);
	//gtk_fixed_put (GTK_FIXED(centerFixed), label1, 70, 30);

	label1 = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label1), "<span foreground=\"black\" font=\"50\"><b>Please enter 4-digit</b></span>");
	gtk_fixed_put (GTK_FIXED(centerFixed), label1, 10, 0);

	label1 = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label1), "<span foreground=\"black\" font=\"50\"><b>one-time use code</b></span>");
	gtk_fixed_put (GTK_FIXED(centerFixed), label1, 32, 85);
	label1 = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label1), "<span foreground=\"black\" font=\"50\"><b>from START RENTAL</b></span>");
	gtk_fixed_put (GTK_FIXED(centerFixed), label1, 0, 170);

	label1 = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label1), "<span foreground=\"black\" font=\"50\"><b>section of</b></span>");
	gtk_fixed_put (GTK_FIXED(centerFixed), label1, 150, 255);

	label1 = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label1), "<span foreground=\"black\" font=\"30\"><b>http://york-abrs.herokuapp.com</b></span>");
	gtk_fixed_put (GTK_FIXED(centerFixed), label1, 10, 340);

	OnlineCodeLabel = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(OnlineCodeLabel), "<span foreground=\"black\" font=\"55\"><b></b></span>");
	gtk_fixed_put (GTK_FIXED(centerFixed), OnlineCodeLabel, 200, 425);

	gtk_notebook_append_page (GTK_NOTEBOOK (centerNotebook), centerFixed, label);

	////// left rent - pay online///////
    leftFixed = gtk_fixed_new();
	label = gtk_label_new ("3");

	label1 = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label1), "<span foreground=\"black\" font=\"30\"><b>Back</b></span>");
	gtk_fixed_put (GTK_FIXED(leftFixed), label1, 40, UI_BUTTON_POSITION_4);

    gtk_notebook_append_page (GTK_NOTEBOOK (leftNotebook), leftFixed, label);


	////// right rent - pay online//////
	label = gtk_label_new ("3");
    rightFixed = gtk_fixed_new();
  
    label1 = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label1), "<span foreground=\"black\" font=\"30\"><b>Submit</b></span>");
	gtk_fixed_put (GTK_FIXED(rightFixed), label1, 40, UI_BUTTON_POSITION_1);

	label1 = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label1), "<span foreground=\"black\" font=\"30\"><b>Help</b></span>");
	gtk_fixed_put (GTK_FIXED(rightFixed), label1, 60, UI_BUTTON_POSITION_4);

  	gtk_notebook_append_page (GTK_NOTEBOOK (rightNotebook), rightFixed, label);



  	////////////////////////////////////////////////////////////////////////////
  	/////////////// rental screen - thank you
  	/////////////////////////////////////////////////////////////////////////////

	////// center rent - thank you //////
	centerFixed = gtk_fixed_new();
	label = gtk_label_new ("4");
	RentalSuccessLabel = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(RentalSuccessLabel), "<span foreground=\"black\" font=\"55\"><b>Bicycle 4\nIs Unlocked\nSafe Travels</b></span>");
	gtk_fixed_put (GTK_FIXED(centerFixed), RentalSuccessLabel, 200, 100);
//	label1 = gtk_label_new(NULL);
//	gtk_label_set_markup(GTK_LABEL(label1), "<span foreground=\"black\" font=\"55\"><b>Is Unlocked</b></span>");
//	gtk_fixed_put (GTK_FIXED(centerFixed), label1, 100, 225);
//	label1 = gtk_label_new(NULL);
//	gtk_label_set_markup(GTK_LABEL(label1), "<span foreground=\"black\" font=\"55\"><b>Safe Travels</b></span>");
//	gtk_fixed_put (GTK_FIXED(centerFixed), label1, 100, 450);
	RentalImageFrame1 = gtk_image_new_from_file("/home/pi/bike_project/both.png");
	RentalImageFrame2 = gtk_image_new_from_file("/home/pi/bike_project/both.png");
	RentalImageFrame3 = gtk_image_new_from_file("/home/pi/bike_project/both.png");
	RentalImageFrame4 = gtk_image_new_from_file("/home/pi/bike_project/both.png");
	RentalImageFrame5 = gtk_image_new_from_file("/home/pi/bike_project/both.png");
	gtk_fixed_put (GTK_FIXED(centerFixed), RentalImageFrame1, 0, 400);
	gtk_fixed_put (GTK_FIXED(centerFixed), RentalImageFrame2, 150, 400);
	gtk_fixed_put (GTK_FIXED(centerFixed), RentalImageFrame3, 300, 400);
	gtk_fixed_put (GTK_FIXED(centerFixed), RentalImageFrame4, 450, 400);
	gtk_fixed_put (GTK_FIXED(centerFixed), RentalImageFrame5, 600, 400);

	gtk_notebook_append_page (GTK_NOTEBOOK (centerNotebook), centerFixed, label);

	////// left rent - thank you///////
	leftFixed = gtk_fixed_new();
	label = gtk_label_new ("4");
	label1 = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label1), "<span foreground=\"black\" font=\"30\"><b>OK</b></span>");
	gtk_fixed_put (GTK_FIXED(leftFixed), label1, 40, UI_BUTTON_POSITION_4);

	gtk_notebook_append_page (GTK_NOTEBOOK (leftNotebook), leftFixed, label);



	////// right rent - thank you//////
	label = gtk_label_new ("4");
    rightFixed = gtk_fixed_new();

  	gtk_notebook_append_page (GTK_NOTEBOOK (rightNotebook), rightFixed, label);


  	////////////////////////////////////////////////////////////////////////////
  	/////////////// MAP ///////////////////////////////////////////////////////
  	/////////////////////////////////////////////////////////////////////////////

	////// map - center //////
	centerFixed = gtk_fixed_new();
	label = gtk_label_new ("5");
	label1 = gtk_label_new(NULL);
//	gtk_label_set_markup(GTK_LABEL(label1), "<span foreground=\"black\" font=\"50\"><b>Map</b></span>");
//	gtk_fixed_put (GTK_FIXED(centerFixed), label1, 250, 0);

//	label1 = gtk_label_new(NULL);
//	gtk_label_set_markup(GTK_LABEL(label1), "<span foreground=\"black\" font=\"50\"><b>You are Here</b></span>");
//	gtk_fixed_put (GTK_FIXED(centerFixed), label1, 100, 430);



	gtk_notebook_append_page (GTK_NOTEBOOK (centerNotebook), centerFixed, label);

	////// map - left///////
    leftFixed = gtk_fixed_new();
	label = gtk_label_new ("5");

	label1 = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label1), "<span foreground=\"black\" font=\"30\"><b>Back</b></span>");
	gtk_fixed_put (GTK_FIXED(leftFixed), label1, 40, UI_BUTTON_POSITION_4);

	image = gtk_image_new_from_file("/home/pi/bike_project/location.png");
	gtk_fixed_put (GTK_FIXED(leftFixed), image, 0, 0);

    gtk_notebook_append_page (GTK_NOTEBOOK (leftNotebook), leftFixed, label);


	////// map - right //////
	label = gtk_label_new ("5");
    rightFixed = gtk_fixed_new(); 

  	gtk_notebook_append_page (GTK_NOTEBOOK (rightNotebook), rightFixed, label);


  	////////////////////////////////////////////////////////////////////////////
  	/////////////// report problem main
  	/////////////////////////////////////////////////////////////////////////////

	////// report problem main - center //////
	centerFixed = gtk_fixed_new();
	label = gtk_label_new ("6");
	label1 = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label1), "<span foreground=\"black\" font=\"55\"><b>Report a Problem</b></span>");
	gtk_fixed_put (GTK_FIXED(centerFixed), label1, 100, 0);
	label1 = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label1), "<span foreground=\"black\" font=\"35\"><b>Which Bicycle Rack</b></span>");
	gtk_fixed_put (GTK_FIXED(centerFixed), label1, 100, 150);
	label1 = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label1), "<span foreground=\"black\" font=\"35\"><b>has the Problem?</b></span>");
	gtk_fixed_put (GTK_FIXED(centerFixed), label1, 100, 190);

//	label1 = gtk_label_new(NULL);
//	gtk_label_set_markup(GTK_LABEL(label1), "<span foreground=\"black\" font=\"30\"><b>Please indicate the area</b></span>");
//	gtk_fixed_put (GTK_FIXED(centerFixed), label1, 50, 270);
//	label1 = gtk_label_new(NULL);
//	gtk_label_set_markup(GTK_LABEL(label1), "<span foreground=\"black\" font=\"30\"><b>of inconvenience and we will</b></span>");
//	gtk_fixed_put (GTK_FIXED(centerFixed), label1, 0, 310);
//	label1 = gtk_label_new(NULL);
//	gtk_label_set_markup(GTK_LABEL(label1), "<span foreground=\"black\" font=\"30\"><b>attempt to address the problem</b></span>");
//	gtk_fixed_put (GTK_FIXED(centerFixed), label1, 0, 350);
//	label1 = gtk_label_new(NULL);
//	gtk_label_set_markup(GTK_LABEL(label1), "<span foreground=\"black\" font=\"30\"><b>in a timely manner.</b></span>");
//	gtk_fixed_put (GTK_FIXED(centerFixed), label1, 0, 390);


	gtk_notebook_append_page (GTK_NOTEBOOK (centerNotebook), centerFixed, label);

	////// report problem main - left///////
    leftFixed = gtk_fixed_new();
	label = gtk_label_new ("6");

  	label1 = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label1), "<span foreground=\"black\" font=\"30\"><b>Rack 1</b></span>");
	gtk_fixed_put (GTK_FIXED(leftFixed), label1, 40, 100);
	label1 = gtk_label_new(NULL);
//	gtk_label_set_markup(GTK_LABEL(label1), "<span foreground=\"black\" font=\"30\"><b>Problem</b></span>");
//	gtk_fixed_put (GTK_FIXED(leftFixed), label1, 15, 140);
//	label1 = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label1), "<span foreground=\"black\" font=\"30\"><b>Back</b></span>");
	gtk_fixed_put (GTK_FIXED(leftFixed), label1, 40, UI_BUTTON_POSITION_4);

    gtk_notebook_append_page (GTK_NOTEBOOK (leftNotebook), leftFixed, label);


	////// report problem main - right//////
	label = gtk_label_new ("6");
    rightFixed = gtk_fixed_new();
  
    label1 = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label1), "<span foreground=\"black\" font=\"30\"><b>Rack 2</b></span>");
	gtk_fixed_put (GTK_FIXED(rightFixed), label1, 40, UI_BUTTON_POSITION_1);
	label1 = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label1), "<span foreground=\"black\" font=\"30\"><b>Rack 3</b></span>");
	gtk_fixed_put (GTK_FIXED(rightFixed), label1, 40, UI_BUTTON_POSITION_2);
	label1 = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label1), "<span foreground=\"black\" font=\"30\"><b>Rack 4</b></span>");
	gtk_fixed_put (GTK_FIXED(rightFixed), label1, 40, UI_BUTTON_POSITION_3);
	label1 = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label1), "<span foreground=\"black\" font=\"30\"><b>Rack 5</b></span>");
	gtk_fixed_put (GTK_FIXED(rightFixed), label1, 40, UI_BUTTON_POSITION_4);

  	gtk_notebook_append_page (GTK_NOTEBOOK (rightNotebook), rightFixed, label);



  	////////////////////////////////////////////////////////////////////////////
  	/////////////// processing transaction
  	/////////////////////////////////////////////////////////////////////////////

	////// processing transaction - center//////
	centerFixed = gtk_fixed_new();
	label = gtk_label_new ("7");
	label1 = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label1), "<span foreground=\"black\" font=\"70\"><b>Processing</b></span>"); 
	gtk_fixed_put (GTK_FIXED(centerFixed), label1, 65, 100);
	label1 = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label1), "<span foreground=\"black\" font=\"70\"><b>Transaction</b></span>"); 
	gtk_fixed_put (GTK_FIXED(centerFixed), label1, 50, 220);
	image = gtk_image_new_from_file("/home/pi/bike_project/processing2.gif");
	gtk_fixed_put (GTK_FIXED(centerFixed), image, 160, 300);



	gtk_notebook_append_page (GTK_NOTEBOOK (centerNotebook), centerFixed, label);

	////// processing transaction - right///////
    leftFixed = gtk_fixed_new();
	label = gtk_label_new ("7");

    gtk_notebook_append_page (GTK_NOTEBOOK (leftNotebook), leftFixed, label);


	////// processing transaction - left//////
	label = gtk_label_new ("7");
    rightFixed = gtk_fixed_new();  

  	gtk_notebook_append_page (GTK_NOTEBOOK (rightNotebook), rightFixed, label);


  	////////////////////////////////////////////////////////////////////////////
  	/////////////// Transaction Failed
  	/////////////////////////////////////////////////////////////////////////////

	////// processing transaction - center//////
	centerFixed = gtk_fixed_new();
	label = gtk_label_new ("8");
	label1 = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label1), "<span foreground=\"black\" font=\"70\"><b>We're Sorry</b></span>"); 
	gtk_fixed_put (GTK_FIXED(centerFixed), label1, 65, 0);
	label1 = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label1), "<span foreground=\"black\" font=\"70\"><b>Your</b></span>"); 
	gtk_fixed_put (GTK_FIXED(centerFixed), label1, 200, 100);
	label1 = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label1), "<span foreground=\"black\" font=\"70\"><b>Transaction</b></span>"); 
	gtk_fixed_put (GTK_FIXED(centerFixed), label1, 50, 200);
	label1 = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label1), "<span foreground=\"black\" font=\"70\"><b>Cannot Be</b></span>"); 
	gtk_fixed_put (GTK_FIXED(centerFixed), label1, 70, 300);
	label1 = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label1), "<span foreground=\"black\" font=\"70\"><b>Completed</b></span>"); 
	gtk_fixed_put (GTK_FIXED(centerFixed), label1, 70, 400);
	label1 = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label1), "<span foreground=\"black\" font=\"70\"><b>At This Time</b></span>"); 
	gtk_fixed_put (GTK_FIXED(centerFixed), label1, 50, 500);

	gtk_notebook_append_page (GTK_NOTEBOOK (centerNotebook), centerFixed, label);

	////// processing transaction - right///////
    leftFixed = gtk_fixed_new();
	label = gtk_label_new ("8");	label1 = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label1), "<span foreground=\"black\" font=\"30\"><b>Back</b></span>");
	gtk_fixed_put (GTK_FIXED(leftFixed), label1, 40, UI_BUTTON_POSITION_4);

    gtk_notebook_append_page (GTK_NOTEBOOK (leftNotebook), leftFixed, label);


	////// processing transaction - left//////
	label = gtk_label_new ("8");
    rightFixed = gtk_fixed_new();
  	gtk_notebook_append_page (GTK_NOTEBOOK (rightNotebook), rightFixed, label);





  	////////////////////////////////////////////////////////////////////////////
  	/////////////// Advertisments
  	/////////////////////////////////////////////////////////////////////////////

	////// Advertisments - center//////
	centerFixed = gtk_fixed_new();
	label = gtk_label_new ("9");
	//label1 = gtk_label_new(NULL);
	//gtk_label_set_markup(GTK_LABEL(label1), "<span foreground=\"black\" font=\"60\"><b>Press Any\nButton To Rent\nA Bicycle</b></span>");
	//gtk_misc_set_alignment (GTK_MISC(label1), 0.5, 0);
	//gtk_fixed_put (GTK_FIXED(centerFixed), label1, 100, 0);



//	label1 = gtk_label_new(NULL);
//	gtk_label_set_markup(GTK_LABEL(label1), "<span foreground=\"black\" font=\"70\"><b>a Bicycle</b></span>");
//	gtk_fixed_put (GTK_FIXED(centerFixed), label1, 150, 220);
	image = gtk_image_new_from_file("/home/pi/bike_project/bicycle_racer_md_wm.gif");
	//gtk_fixed_put (GTK_FIXED(centerFixed), image, 200, 350);
	gtk_fixed_put (GTK_FIXED(centerFixed), image, 200, 255);



	gtk_notebook_append_page (GTK_NOTEBOOK (centerNotebook), centerFixed, label);

	////// Advertisments - right///////
    leftFixed = gtk_fixed_new();
	label = gtk_label_new ("9");

	label1 = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label1), "<span foreground=\"black\" font=\"60\"><b>Free Bicycle Rentals For</b></span>");
	gtk_fixed_put (GTK_FIXED(leftFixed), label1, 80, 30);

	label1 = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label1), "<span foreground=\"black\" font=\"60\"><b>YCP Students And Faculty</b></span>");
	gtk_fixed_put (GTK_FIXED(leftFixed), label1, 40, 125);



	//label1 = gtk_label_new(NULL);
	//gtk_label_set_markup(GTK_LABEL(label1), "<span foreground=\"black\" font=\"60\"><b>YCP Students And Faculty</b></span>");
	//gtk_fixed_put (GTK_FIXED(leftFixed), label1, 40, 30);

	//label1 = gtk_label_new(NULL);
	//gtk_label_set_markup(GTK_LABEL(label1), "<span foreground=\"black\" font=\"60\"><b>Free Bicycle Rentals</b></span>");
	//gtk_fixed_put (GTK_FIXED(leftFixed), label1, 140, 125);

	label1 = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label1), "<span foreground=\"black\" font=\"60\"><b>Please Press Any Button</b></span>");
	gtk_fixed_put (GTK_FIXED(leftFixed), label1, 75, 450);

    gtk_notebook_append_page (GTK_NOTEBOOK (leftNotebook), leftFixed, label);


	////// Advertisments - left//////
	label = gtk_label_new ("9");
    rightFixed = gtk_fixed_new();

  	gtk_notebook_append_page (GTK_NOTEBOOK (rightNotebook), rightFixed, label);




  	////////////////////////////////////////////////////////////////////////////
	/////////////// Info Screen //////////////////////////////////

	////// center Info //////
	centerFixed = gtk_fixed_new();
	labelInfoPage = gtk_label_new ("10");

	label1 = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label1), "<span foreground=\"black\" font=\"60\"><b>2016 ABRS Team</b></span>");
	gtk_fixed_put (GTK_FIXED(centerFixed), label1, 0, 0);

	image = gtk_image_new_from_file("/home/pi/bike_project/Team.png");
	gtk_fixed_put (GTK_FIXED(centerFixed), image, 0, 100);

	//gtk_fixed_put (GTK_FIXED(centerFixed), infoLabel, 0, 50);
	gtk_notebook_append_page (GTK_NOTEBOOK (centerNotebook), centerFixed, labelInfoPage);

	////// left Info///////
	leftFixed = gtk_fixed_new();
	//label = gtk_label_new ("10");

	label1 = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label1), "<span foreground=\"black\" font=\"30\"><b>Back</b></span>");
	gtk_fixed_put (GTK_FIXED(leftFixed), label1, 40, UI_BUTTON_POSITION_4);

//	image = gtk_image_new_from_file("/home/pi/bike_project/ycpLogo.png");
//	gtk_fixed_put (GTK_FIXED(leftFixed), image, 110, 275);


	gtk_notebook_append_page (GTK_NOTEBOOK (leftNotebook), leftFixed, labelInfoPage);


	////// right Info//////
	//label = gtk_label_new ("10");
	rightFixed = gtk_fixed_new();


//	label1 = gtk_label_new(NULL);
//	gtk_label_set_markup(GTK_LABEL(label1), "<span foreground=\"black\" font=\"30\"><b>Cancel</b></span>");
//	gtk_fixed_put (GTK_FIXED(rightFixed), label1, 40, UI_BUTTON_POSITION_4);

	gtk_notebook_append_page (GTK_NOTEBOOK (rightNotebook), rightFixed, labelInfoPage);


  	////////////////////////////////////////////////////////////////////////////
	////////////////////////// Weather Screen //////////////////////////////////

	////// center Weather //////  // TODO
	centerFixed = gtk_fixed_new();
	label = gtk_label_new ("11");
	GtkWidget * degreesF;
	degreesF = gtk_label_new ("°F");
	gtk_label_set_markup(GTK_LABEL(degreesF), "<span foreground=\"black\" font=\"50\"><b>°F</b></span>");
	gtk_fixed_put (GTK_FIXED(centerFixed), degreesF, 80, 35);
	gtk_notebook_append_page (GTK_NOTEBOOK (centerNotebook), centerFixed, label);
	weatherImage = gtk_image_new_from_file("/home/pi/bike_project/snowy.png");

	gtk_label_set_line_wrap (GTK_LABEL(weatherForecast),true);
	gtk_widget_set_size_request (weatherForecast, 640, 200);
	gtk_label_set_markup(GTK_LABEL(weatherForecast), "<span foreground=\"black\" font=\"40\"><b>°F</b></span>");
	gtk_fixed_put (GTK_FIXED(centerFixed), weatherForecast, 10, 300);


	gtk_label_set_markup(GTK_LABEL(weatherTodayHighTempLabel), "<span foreground=\"black\" font=\"60\"><b>°F</b></span>");
	gtk_fixed_put (GTK_FIXED(centerFixed), weatherTodayHighTempLabel, 620, 10);

	gtk_label_set_markup(GTK_LABEL(weatherTodayLowTempLabel), "<span foreground=\"black\" font=\"60\"><b>°F</b></span>");
	gtk_fixed_put (GTK_FIXED(centerFixed), weatherTodayLowTempLabel, 620, 100);

//	gtk_fixed_put (GTK_FIXED(centerFixed), weatherLabel, 110, 350);
//	gtk_fixed_put (GTK_FIXED(centerFixed), weatherLabel, 10, 10);
	gtk_fixed_put (GTK_FIXED(centerFixed), weatherImage, 220, 10);

	////// left Weather///////
	leftFixed = gtk_fixed_new();
	label = gtk_label_new ("11");

	label1 = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label1), "<span foreground=\"black\" font=\"30\"><b>Back</b></span>");
	gtk_fixed_put (GTK_FIXED(leftFixed), label1, 40, UI_BUTTON_POSITION_4);
	gtk_fixed_put (GTK_FIXED(leftFixed), weatherLabel, 10, 10);

	gtk_notebook_append_page (GTK_NOTEBOOK (leftNotebook), leftFixed, label);

	////// right Weather //////
	label = gtk_label_new ("11");
	rightFixed = gtk_fixed_new();

//	label1 = gtk_label_new(NULL);
//	gtk_label_set_markup(GTK_LABEL(label1), "<span foreground=\"black\" font=\"30\"><b>Cancel</b></span>");
//	gtk_fixed_put (GTK_FIXED(rightFixed), label1, 40, UI_BUTTON_POSITION_4);

	gtk_notebook_append_page (GTK_NOTEBOOK (rightNotebook), rightFixed, label);



	////////////////////////////////////////////////////////////////////////////
	/////////////// admin screen
	/////////////////////////////////////////////////////////////////////////////

	////// center admin //////
	centerFixed = gtk_fixed_new();
	label = gtk_label_new ("12");
	label1 = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label1), "<span foreground=\"black\" font=\"55\"><b>ADMIN</b></span>");
	gtk_fixed_put (GTK_FIXED(centerFixed), label1, 200, 50);

	PowerSystemLevelLabel = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(PowerSystemLevelLabel), "<span foreground=\"black\" font=\"40\"><b>??</b></span>");
	gtk_fixed_put (GTK_FIXED(centerFixed), PowerSystemLevelLabel, 200, 125);

	Admin3gIpAddressLabel = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(Admin3gIpAddressLabel), "<span foreground=\"black\" font=\"40\"><b>000.000.000.000</b></span>");
	gtk_fixed_put (GTK_FIXED(centerFixed), Admin3gIpAddressLabel, 200, 200);

	AdminWifiIpAddressLabel = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(AdminWifiIpAddressLabel), "<span foreground=\"black\" font=\"40\"><b>000.000.000.000</b></span>");
	gtk_fixed_put (GTK_FIXED(centerFixed), AdminWifiIpAddressLabel, 200, 300);

	gtk_notebook_append_page (GTK_NOTEBOOK (centerNotebook), centerFixed, label);

	////// left admin ///////
	leftFixed = gtk_fixed_new();
	label = gtk_label_new ("12");

	label1 = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label1), "<span foreground=\"black\" font=\"30\"><b>Driver ON</b></span>");
	gtk_fixed_put (GTK_FIXED(leftFixed), label1, 30, UI_BUTTON_POSITION_1);
	label1 = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label1), "<span foreground=\"black\" font=\"30\"><b>Light ON</b></span>");
	gtk_fixed_put (GTK_FIXED(leftFixed), label1, 40, UI_BUTTON_POSITION_2);

	label1 = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label1), "<span foreground=\"black\" font=\"30\"><b>Back</b></span>");
	gtk_fixed_put (GTK_FIXED(leftFixed), label1, 40, UI_BUTTON_POSITION_4);

	gtk_notebook_append_page (GTK_NOTEBOOK (leftNotebook), leftFixed, label);


	////// right admin //////
	label = gtk_label_new ("12");
	rightFixed = gtk_fixed_new();

	label1 = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label1), "<span foreground=\"black\" font=\"30\"><b>Driver OFF</b></span>");
	gtk_fixed_put (GTK_FIXED(rightFixed), label1, 0, UI_BUTTON_POSITION_1);
	label1 = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label1), "<span foreground=\"black\" font=\"30\"><b>Light OFF</b></span>");
	gtk_fixed_put (GTK_FIXED(rightFixed), label1, 0, UI_BUTTON_POSITION_2);
	label1 = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label1), "<span foreground=\"black\" font=\"30\"><b>Cancel</b></span>");
	gtk_fixed_put (GTK_FIXED(rightFixed), label1, 40, UI_BUTTON_POSITION_4);

	gtk_notebook_append_page (GTK_NOTEBOOK (rightNotebook), rightFixed, label);




	////////////////////////////////////////////////////////////////////////////
	/////////////// Return Screen //////////////////////////////////  //screen 13

		////// Center Return //////
		centerFixed = gtk_fixed_new();
		label  = gtk_label_new (NULL);
		gtk_fixed_put (GTK_FIXED(centerFixed), label , 0, 50);

		RentalReturnedLabel = gtk_label_new(NULL);
		gtk_label_set_markup(GTK_LABEL(RentalReturnedLabel), "<span foreground=\"black\" font=\"70\"><b>Bicycle\nReturned\nThank You</b></span>");
		gtk_fixed_put (GTK_FIXED(centerFixed), RentalReturnedLabel, 165, 100);
		gtk_notebook_append_page (GTK_NOTEBOOK (centerNotebook), centerFixed, RentalReturnedLabel);

		////// Left Return //////
		leftFixed = gtk_fixed_new();

		label1 = gtk_label_new(NULL);
		gtk_label_set_markup(GTK_LABEL(label1), "<span foreground=\"black\" font=\"30\"><b>OK</b></span>");
		gtk_fixed_put (GTK_FIXED(leftFixed), label1, 40, UI_BUTTON_POSITION_4);

//		image = gtk_image_new_from_file("/home/pi/bike_project/ycpLogo.png");
//		gtk_fixed_put (GTK_FIXED(leftFixed), image, 110, 275);

		gtk_notebook_append_page (GTK_NOTEBOOK (leftNotebook), leftFixed, label);

		////// Right Return//////
		rightFixed = gtk_fixed_new();

		label1 = gtk_label_new(NULL);
		gtk_label_set_markup(GTK_LABEL(label1), "<span foreground=\"black\" font=\"30\"><b>Cancel</b></span>");
		gtk_fixed_put (GTK_FIXED(rightFixed), label1, 40, UI_BUTTON_POSITION_4);

		gtk_notebook_append_page (GTK_NOTEBOOK (rightNotebook), rightFixed, label);


		////////////////////////////////////////////////////////////////////////////
		/////////////// Bicycle Report Problem screen
		/////////////////////////////////////////////////////////////////////////////

		////// center Bicycle Report Problem //////
		centerFixed = gtk_fixed_new();
		label = gtk_label_new ("14");
		label1 = gtk_label_new(NULL);
		gtk_label_set_markup(GTK_LABEL(label1), "<span foreground=\"black\" font=\"55\"><b>Bicycle Problem</b></span>");
		gtk_fixed_put (GTK_FIXED(centerFixed), label1, 200, 50);



		gtk_notebook_append_page (GTK_NOTEBOOK (centerNotebook), centerFixed, label);

		////// left Bicycle Report Problem ///////
		leftFixed = gtk_fixed_new();
		label = gtk_label_new ("14");

		label1 = gtk_label_new(NULL);
		gtk_label_set_markup(GTK_LABEL(label1), "<span foreground=\"black\" font=\"30\"><b>Tire</b></span>");
		gtk_fixed_put (GTK_FIXED(leftFixed), label1, 30, UI_BUTTON_POSITION_1);
		label1 = gtk_label_new(NULL);
		gtk_label_set_markup(GTK_LABEL(label1), "<span foreground=\"black\" font=\"30\"><b>Seat</b></span>");
		gtk_fixed_put (GTK_FIXED(leftFixed), label1, 40, UI_BUTTON_POSITION_2);
		label1 = gtk_label_new(NULL);
		gtk_label_set_markup(GTK_LABEL(label1), "<span foreground=\"black\" font=\"30\"><b>Wheel</b></span>");
		gtk_fixed_put (GTK_FIXED(leftFixed), label1, 40, UI_BUTTON_POSITION_3);
		label1 = gtk_label_new(NULL);
		gtk_label_set_markup(GTK_LABEL(label1), "<span foreground=\"black\" font=\"30\"><b>Pedal</b></span>");
		gtk_fixed_put (GTK_FIXED(leftFixed), label1, 40, UI_BUTTON_POSITION_4);

		gtk_notebook_append_page (GTK_NOTEBOOK (leftNotebook), leftFixed, label);


		////// right Bicycle Report Problem //////
		label = gtk_label_new ("14");
		rightFixed = gtk_fixed_new();

		label1 = gtk_label_new(NULL);
		gtk_label_set_markup(GTK_LABEL(label1), "<span foreground=\"black\" font=\"30\"><b>Brake</b></span>");
		gtk_fixed_put (GTK_FIXED(rightFixed), label1, 0, UI_BUTTON_POSITION_1);
		label1 = gtk_label_new(NULL);
		gtk_label_set_markup(GTK_LABEL(label1), "<span foreground=\"black\" font=\"30\"><b>Other</b></span>");
		gtk_fixed_put (GTK_FIXED(rightFixed), label1, 0, UI_BUTTON_POSITION_2);
		label1 = gtk_label_new(NULL);
		gtk_label_set_markup(GTK_LABEL(label1), "<span foreground=\"black\" font=\"30\"><b>Cancel</b></span>");
		gtk_fixed_put (GTK_FIXED(rightFixed), label1, 40, UI_BUTTON_POSITION_4);

		gtk_notebook_append_page (GTK_NOTEBOOK (rightNotebook), rightFixed, label);



		////////////////////////////////////////////////////////////////////////////
		/////////////// Bicycle Report Problem Processing Screen //////////////////////////////////  //screen 15

		////// center Bicycle Report Problem Processing //////
		centerFixed = gtk_fixed_new();
		label = gtk_label_new ("15");
		label1 = gtk_label_new(NULL);
		gtk_label_set_markup(GTK_LABEL(label1), "<span foreground=\"black\" font=\"55\"><b>Reporting Bicycle \nProblem \n Please Wait</b></span>");
		gtk_fixed_put (GTK_FIXED(centerFixed), label1, 200, 50);

		gtk_notebook_append_page (GTK_NOTEBOOK (centerNotebook), centerFixed, label);

		////// left Bicycle Report Problem Processing ///////
		leftFixed = gtk_fixed_new();
		label = gtk_label_new ("15");

//		label1 = gtk_label_new(NULL);
//		gtk_label_set_markup(GTK_LABEL(label1), "<span foreground=\"black\" font=\"30\"><b>Tire</b></span>");
//		gtk_fixed_put (GTK_FIXED(leftFixed), label1, 30, UI_BUTTON_POSITION_1);
//		label1 = gtk_label_new(NULL);
//		gtk_label_set_markup(GTK_LABEL(label1), "<span foreground=\"black\" font=\"30\"><b>Seat</b></span>");
//		gtk_fixed_put (GTK_FIXED(leftFixed), label1, 40, UI_BUTTON_POSITION_2);
//		label1 = gtk_label_new(NULL);
//		gtk_label_set_markup(GTK_LABEL(label1), "<span foreground=\"black\" font=\"30\"><b>Wheel</b></span>");
//		gtk_fixed_put (GTK_FIXED(leftFixed), label1, 40, UI_BUTTON_POSITION_3);
//		label1 = gtk_label_new(NULL);
//		gtk_label_set_markup(GTK_LABEL(label1), "<span foreground=\"black\" font=\"30\"><b>Pedal</b></span>");
//		gtk_fixed_put (GTK_FIXED(leftFixed), label1, 40, UI_BUTTON_POSITION_4);

		gtk_notebook_append_page (GTK_NOTEBOOK (leftNotebook), leftFixed, label);


		////// rightBicycle Report Problem Processing //////
		label = gtk_label_new ("15");
		rightFixed = gtk_fixed_new();

//		label1 = gtk_label_new(NULL);
//		gtk_label_set_markup(GTK_LABEL(label1), "<span foreground=\"black\" font=\"30\"><b>Brake</b></span>");
//		gtk_fixed_put (GTK_FIXED(rightFixed), label1, 0, UI_BUTTON_POSITION_1);
//		label1 = gtk_label_new(NULL);
//		gtk_label_set_markup(GTK_LABEL(label1), "<span foreground=\"black\" font=\"30\"><b>Other</b></span>");
//		gtk_fixed_put (GTK_FIXED(rightFixed), label1, 0, UI_BUTTON_POSITION_2);
//		label1 = gtk_label_new(NULL);
//		gtk_label_set_markup(GTK_LABEL(label1), "<span foreground=\"black\" font=\"30\"><b>Cancel</b></span>");
//		gtk_fixed_put (GTK_FIXED(rightFixed), label1, 40, UI_BUTTON_POSITION_4);

		gtk_notebook_append_page (GTK_NOTEBOOK (rightNotebook), rightFixed, label);


		////////////////////////////////////////////////////////////////////////////
		/////////////// Bicycle Report Problem Success/Error Screen //////////////////////////////////  //screen 16

		////// center Bicycle Report Problem Success/Error //////
		centerFixed = gtk_fixed_new();
		label = gtk_label_new ("16");
		bicycleReportProblemSuccessErrorOrLabel = gtk_label_new(NULL);
		gtk_label_set_markup(GTK_LABEL(bicycleReportProblemSuccessErrorOrLabel), "<span foreground=\"black\" font=\"55\"><b>Reporting Bicycle \nProblem \n Please Wait</b></span>");
		gtk_fixed_put (GTK_FIXED(centerFixed), bicycleReportProblemSuccessErrorOrLabel, 200, 50);

		gtk_notebook_append_page (GTK_NOTEBOOK (centerNotebook), centerFixed, label);

		////// left Bicycle Report Problem Success/Error ///////
		leftFixed = gtk_fixed_new();
		label = gtk_label_new ("16");

		label1 = gtk_label_new(NULL);
		gtk_label_set_markup(GTK_LABEL(label1), "<span foreground=\"black\" font=\"30\"><b>Okay</b></span>");
		gtk_fixed_put (GTK_FIXED(leftFixed), label1, 40, UI_BUTTON_POSITION_4);

		gtk_notebook_append_page (GTK_NOTEBOOK (leftNotebook), leftFixed, label);

		////// rightBicycle Report Problem Success/Error //////
		label = gtk_label_new ("16");
		rightFixed = gtk_fixed_new();

		gtk_notebook_append_page (GTK_NOTEBOOK (rightNotebook), rightFixed, label);


		////////////////////////////////////////////////////////////////////////////
		/////////////// Online Rent Help: Step One Screen
		/////////////////////////////////////////////////////////////////////////////

		////// center Online Rent Help: Step One //////
		centerFixed = gtk_fixed_new();
		label = gtk_label_new ("17");
		label1 = gtk_label_new(NULL);
		gtk_label_set_markup(GTK_LABEL(label1), "<span foreground=\"black\" font=\"40\"><b>Rental Help: Step One</b></span>");
		gtk_fixed_put (GTK_FIXED(centerFixed), label1, 64, 0);



		label1 = gtk_label_new(NULL);
		gtk_label_set_markup(GTK_LABEL(label1), "<span foreground=\"black\" font=\"28\"><b>at http://york-abrs.herokuapp.com</b></span>");
		gtk_fixed_put (GTK_FIXED(centerFixed), label1, 10, 530);


		gtk_notebook_append_page (GTK_NOTEBOOK (centerNotebook), centerFixed, label);

		////// left Online Rent Help: Step One  ///////
		leftFixed = gtk_fixed_new();
		label = gtk_label_new ("17");

		//label1 = gtk_label_new(NULL);
		//gtk_label_set_markup(GTK_LABEL(label1), "<span foreground=\"black\" font=\"30\"><b>Driver ON</b></span>");
		//gtk_fixed_put (GTK_FIXED(leftFixed), label1, 30, UI_BUTTON_POSITION_1);
		//label1 = gtk_label_new(NULL);
		//gtk_label_set_markup(GTK_LABEL(label1), "<span foreground=\"black\" font=\"30\"><b>Light ON</b></span>");
		//gtk_fixed_put (GTK_FIXED(leftFixed), label1, 40, UI_BUTTON_POSITION_2);

		label1 = gtk_label_new(NULL);
		gtk_label_set_markup(GTK_LABEL(label1), "<span foreground=\"black\" font=\"30\"><b>Back</b></span>");
		gtk_fixed_put (GTK_FIXED(leftFixed), label1, 40, UI_BUTTON_POSITION_4);

		image = gtk_image_new_from_file("/home/pi/bike_project/web_login.png");
		gtk_fixed_put (GTK_FIXED(leftFixed), image, 170, 80);

		label1 = gtk_label_new(NULL);
		gtk_label_set_markup(GTK_LABEL(label1), "<span foreground=\"black\" font=\"28\"><b>Sign up and log in with your YCP Credentials</b></span>");
		gtk_fixed_put (GTK_FIXED(leftFixed), label1, 130, 490);


		gtk_notebook_append_page (GTK_NOTEBOOK (leftNotebook), leftFixed, label);


		////// right Online Rent Help: Step One  //////
		label = gtk_label_new ("17");
		rightFixed = gtk_fixed_new();

		label1 = gtk_label_new(NULL);
		gtk_label_set_markup(GTK_LABEL(label1), "<span foreground=\"black\" font=\"30\"><b>Next</b></span>");
		gtk_fixed_put (GTK_FIXED(rightFixed), label1, 65, UI_BUTTON_POSITION_1);
		//label1 = gtk_label_new(NULL);
		//gtk_label_set_markup(GTK_LABEL(label1), "<span foreground=\"black\" font=\"30\"><b>Light OFF</b></span>");
		//gtk_fixed_put (GTK_FIXED(rightFixed), label1, 0, UI_BUTTON_POSITION_2);
		label1 = gtk_label_new(NULL);
		gtk_label_set_markup(GTK_LABEL(label1), "<span foreground=\"black\" font=\"30\"><b>Cancel</b></span>");
		gtk_fixed_put (GTK_FIXED(rightFixed), label1, 40, UI_BUTTON_POSITION_4);

		gtk_notebook_append_page (GTK_NOTEBOOK (rightNotebook), rightFixed, label);


		////////////////////////////////////////////////////////////////////////////
		/////////////// Online Rent Help: Step Two Screen
		/////////////////////////////////////////////////////////////////////////////

		////// center Online Rent: Step Two Help //////
		centerFixed = gtk_fixed_new();
		label = gtk_label_new ("18");
		label1 = gtk_label_new(NULL);
		gtk_label_set_markup(GTK_LABEL(label1), "<span foreground=\"black\" font=\"40\"><b>Rental Help: Step Two</b></span>");
		gtk_fixed_put (GTK_FIXED(centerFixed), label1, 64, 0);

		label1 = gtk_label_new(NULL);
		gtk_label_set_markup(GTK_LABEL(label1), "<span foreground=\"black\" font=\"28\"><b>Click \"Start Rental\" </b></span>");
		gtk_fixed_put (GTK_FIXED(centerFixed), label1, 160, 490);

		label1 = gtk_label_new(NULL);
		gtk_label_set_markup(GTK_LABEL(label1), "<span foreground=\"black\" font=\"28\"><b>Use 4-digit code at Kiosk \"Rent\" Screen</b></span>");
		gtk_fixed_put (GTK_FIXED(centerFixed), label1, 0, 530);


		gtk_notebook_append_page (GTK_NOTEBOOK (centerNotebook), centerFixed, label);

		////// left Online Rent Help: Step Two  ///////
		leftFixed = gtk_fixed_new();
		label = gtk_label_new ("18");

		//label1 = gtk_label_new(NULL);
		//gtk_label_set_markup(GTK_LABEL(label1), "<span foreground=\"black\" font=\"30\"><b>Driver ON</b></span>");
		//gtk_fixed_put (GTK_FIXED(leftFixed), label1, 30, UI_BUTTON_POSITION_1);
		//label1 = gtk_label_new(NULL);
		//gtk_label_set_markup(GTK_LABEL(label1), "<span foreground=\"black\" font=\"30\"><b>Light ON</b></span>");
		//gtk_fixed_put (GTK_FIXED(leftFixed), label1, 40, UI_BUTTON_POSITION_2);

		label1 = gtk_label_new(NULL);
		gtk_label_set_markup(GTK_LABEL(label1), "<span foreground=\"black\" font=\"30\"><b>Back</b></span>");
		gtk_fixed_put (GTK_FIXED(leftFixed), label1, 40, UI_BUTTON_POSITION_4);

		image = gtk_image_new_from_file("/home/pi/bike_project/web_rent.png");
		gtk_fixed_put (GTK_FIXED(leftFixed), image, 170, 80);



		gtk_notebook_append_page (GTK_NOTEBOOK (leftNotebook), leftFixed, label);


		////// right Online Rent Help: Step Two  //////
		label = gtk_label_new ("18");
		rightFixed = gtk_fixed_new();

		label1 = gtk_label_new(NULL);
		gtk_label_set_markup(GTK_LABEL(label1), "<span foreground=\"black\" font=\"30\"><b>Rent</b></span>");
		gtk_fixed_put (GTK_FIXED(rightFixed), label1, 65, UI_BUTTON_POSITION_1);
		//label1 = gtk_label_new(NULL);
		//gtk_label_set_markup(GTK_LABEL(label1), "<span foreground=\"black\" font=\"30\"><b>Light OFF</b></span>");
		//gtk_fixed_put (GTK_FIXED(rightFixed), label1, 0, UI_BUTTON_POSITION_2);
		label1 = gtk_label_new(NULL);
		gtk_label_set_markup(GTK_LABEL(label1), "<span foreground=\"black\" font=\"30\"><b>Cancel</b></span>");
		gtk_fixed_put (GTK_FIXED(rightFixed), label1, 40, UI_BUTTON_POSITION_4);

		gtk_notebook_append_page (GTK_NOTEBOOK (rightNotebook), rightFixed, label);


    ///////////////////////////////////////////////////////////////////////////////////////
    ///////////// disable notebook tab headers
    ///////////////////////////////////////////////////////////////////////////////////////
    gtk_notebook_set_show_tabs (GTK_NOTEBOOK(centerNotebook), FALSE);
    gtk_notebook_set_show_tabs (GTK_NOTEBOOK(leftNotebook), FALSE);
    gtk_notebook_set_show_tabs (GTK_NOTEBOOK(rightNotebook), FALSE);

    gtk_notebook_set_show_border (GTK_NOTEBOOK(centerNotebook), FALSE);
    gtk_notebook_set_show_border (GTK_NOTEBOOK(leftNotebook), FALSE);
    gtk_notebook_set_show_border (GTK_NOTEBOOK(rightNotebook), FALSE);



    ///// draw all items on screen /////
    gtk_widget_show (fixed);
    gtk_widget_show (mainWindow);
    gtk_widget_show_all (mainWindow);


    // uncomment to disable window widget borders
    gtk_window_set_decorated (GTK_WINDOW (mainWindow), FALSE);

    //kioskKeyInput kki();
    //g_signal_connect(G_OBJECT(mainWindow), "key_press_event", G_CALLBACK(key_press_cb), (gpointer) &kki);

    guint32 thisTime = gtk_get_current_event_time();

    g_print("\nTime is %d\n", thisTime);

    //return 0;

}

gint graphicalFunctions::drawWelcomePage(void)
{
	//printf("Down\n");   // key down
	gtk_notebook_set_current_page (GTK_NOTEBOOK (centerNotebook), 0);
	gtk_notebook_set_current_page (GTK_NOTEBOOK (leftNotebook), 0);
	gtk_notebook_set_current_page (GTK_NOTEBOOK (rightNotebook), 0);
	gint uiPageNum = gtk_notebook_get_current_page(GTK_NOTEBOOK(centerNotebook));

	return uiPageNum;
}

gint graphicalFunctions::drawNextPage(void)
{
    //printf("Right\n");  // key right
    gtk_notebook_next_page (GTK_NOTEBOOK(centerNotebook));
    gtk_notebook_next_page (GTK_NOTEBOOK(leftNotebook));
    gtk_notebook_next_page (GTK_NOTEBOOK(rightNotebook)); 
    gint uiPageNum = gtk_notebook_get_current_page(GTK_NOTEBOOK(centerNotebook));

    return uiPageNum;
}

gint graphicalFunctions::drawPrevPage(void)
{
    //printf("Left\n");  // key left/
    gtk_notebook_prev_page (GTK_NOTEBOOK(centerNotebook));
    gtk_notebook_prev_page (GTK_NOTEBOOK(leftNotebook));
    gtk_notebook_prev_page (GTK_NOTEBOOK(rightNotebook));
    gint uiPageNum = gtk_notebook_get_current_page(GTK_NOTEBOOK(centerNotebook));

    return uiPageNum;
}

gint graphicalFunctions::drawRentPage(void)
{
	gtk_notebook_set_current_page (GTK_NOTEBOOK (centerNotebook), 1);
    gtk_notebook_set_current_page (GTK_NOTEBOOK (leftNotebook), 1);
    gtk_notebook_set_current_page (GTK_NOTEBOOK (rightNotebook), 1);
    gint uiPageNum = gtk_notebook_get_current_page(GTK_NOTEBOOK(centerNotebook));
    //onlineCodeCounter = 0;

	return uiPageNum;
}

gint graphicalFunctions::drawReportProblemPage(void)
{
	gtk_notebook_set_current_page (GTK_NOTEBOOK (centerNotebook), 6);
    gtk_notebook_set_current_page (GTK_NOTEBOOK (leftNotebook), 6);
    gtk_notebook_set_current_page (GTK_NOTEBOOK (rightNotebook), 6);
    gint uiPageNum = gtk_notebook_get_current_page(GTK_NOTEBOOK(centerNotebook));

    return uiPageNum;
}

gint graphicalFunctions::drawMapPage(void)
{
	gtk_notebook_set_current_page (GTK_NOTEBOOK (centerNotebook), 5);
    gtk_notebook_set_current_page (GTK_NOTEBOOK (leftNotebook), 5);
    gtk_notebook_set_current_page (GTK_NOTEBOOK (rightNotebook), 5);
    gint uiPageNum = gtk_notebook_get_current_page(GTK_NOTEBOOK(centerNotebook));

    return uiPageNum;
}

gint graphicalFunctions::drawCreditCardPage(void)
{
	gtk_notebook_set_current_page (GTK_NOTEBOOK (centerNotebook), 2);
    gtk_notebook_set_current_page (GTK_NOTEBOOK (leftNotebook), 2);
    gtk_notebook_set_current_page (GTK_NOTEBOOK (rightNotebook), 2);
    gint uiPageNum = gtk_notebook_get_current_page(GTK_NOTEBOOK(centerNotebook));

    return uiPageNum;
}

gint graphicalFunctions::drawOnlineCodePage(void)
{
	std::string code = "";
	gtk_label_set_text(GTK_LABEL(OnlineCodeLabel), code.data());
	const char *format = "<span foreground=\"black\" font=\"55\"><b>%s</b></span>";
	char* markup = g_markup_printf_escaped(format, code.data());
	gtk_label_set_markup(GTK_LABEL(OnlineCodeLabel), markup);
	g_free (markup);

	gtk_notebook_set_current_page (GTK_NOTEBOOK (centerNotebook), 3);
    gtk_notebook_set_current_page (GTK_NOTEBOOK (leftNotebook), 3);
    gtk_notebook_set_current_page (GTK_NOTEBOOK (rightNotebook), 3);
    gint uiPageNum = gtk_notebook_get_current_page(GTK_NOTEBOOK(centerNotebook));

    return uiPageNum;
}

gint graphicalFunctions::drawOnlineCodePage(std::string code)
{
	gtk_label_set_text(GTK_LABEL(OnlineCodeLabel), code.data()); //g_print("g\n");
	const char *format = "<span foreground=\"black\" font=\"55\"><b>%s</b></span>"; //g_print("h\n");
	char* markup = g_markup_printf_escaped(format, code.data());// g_print("i\n");
	gtk_label_set_markup(GTK_LABEL(OnlineCodeLabel), markup);
	g_free (markup);

	gtk_notebook_set_current_page (GTK_NOTEBOOK (centerNotebook), 3);
    gtk_notebook_set_current_page (GTK_NOTEBOOK (leftNotebook), 3);
    gtk_notebook_set_current_page (GTK_NOTEBOOK (rightNotebook), 3);
    gint uiPageNum = gtk_notebook_get_current_page(GTK_NOTEBOOK(centerNotebook));

    return uiPageNum;
}

gint graphicalFunctions::drawSubmitPage(void)
{
	gtk_notebook_set_current_page (GTK_NOTEBOOK (centerNotebook), 7);
	gtk_notebook_set_current_page (GTK_NOTEBOOK (leftNotebook), 7);
	gtk_notebook_set_current_page (GTK_NOTEBOOK (rightNotebook), 7);
	gint uiPageNum = gtk_notebook_get_current_page(GTK_NOTEBOOK(centerNotebook));

	return uiPageNum;
}

gint graphicalFunctions::drawSuccessPage(unsigned int bikeID, int racknum)
{
	char bikeIDString[10];
	sprintf(bikeIDString, "%x", bikeID);

	char rackIDString[10];
	sprintf(rackIDString, "%i", racknum);


	std::string wholeMessage;

	wholeMessage.append("Bike ");
	wholeMessage.append(bikeIDString);
	wholeMessage.append(" is\n");
	wholeMessage.append("unlocked in rack ");
	wholeMessage.append(rackIDString);
	wholeMessage.append("\nSafe Travels!");

	gtk_label_set_text(GTK_LABEL(RentalSuccessLabel), wholeMessage.data()); //g_print("g\n");
	const char *format = "<span foreground=\"black\" font=\"45\"><b>%s</b></span>"; //g_print("h\n");
	char* markup = g_markup_printf_escaped(format, wholeMessage.data());// g_print("i\n");
	gtk_label_set_markup(GTK_LABEL(RentalSuccessLabel), markup);
	g_free (markup);


	gtk_notebook_set_current_page (GTK_NOTEBOOK (centerNotebook), 4);
    gtk_notebook_set_current_page (GTK_NOTEBOOK (leftNotebook), 4);
    gtk_notebook_set_current_page (GTK_NOTEBOOK (rightNotebook), 4);
    gint uiPageNum = gtk_notebook_get_current_page(GTK_NOTEBOOK(centerNotebook));

    return uiPageNum;
}

gint graphicalFunctions::drawFailurePage(void)
{
	gtk_notebook_set_current_page (GTK_NOTEBOOK (centerNotebook), 8);
    gtk_notebook_set_current_page (GTK_NOTEBOOK (leftNotebook), 8);
    gtk_notebook_set_current_page (GTK_NOTEBOOK (rightNotebook), 8);
    gint uiPageNum = gtk_notebook_get_current_page(GTK_NOTEBOOK(centerNotebook));

    return uiPageNum;
}

gint graphicalFunctions::drawInfoPage(void)
{
	//gtk_widget_destroy (infoLabel);
	//infoLabel = gtk_label_new(NULL);
	testfoo++; //g_print("a\n");
	g_print("testfoo = %d\n", testfoo); //g_print("b\n");
	if (testfoo < 2)
	{
		infoMessage = "Proudly designed and\nbuilt by engineering\nstudents of"; //g_print("c\n");
	}
	else
	{
		//infoMessage = "blah blah blah blah \nblah blah blah blah \nstudents of";// g_print("d\n");
		infoMessage = "Proudly designed and\nbuilt by engineering\nstudents of"; //g_print("c\n");
	}
	//g_print("e\n");
	const char *mmessage = infoMessage; //g_print("f\n");
	//gtk_label_set_text (GTK_LABEL(infoLabel), mmessage);
	gtk_label_set_text(GTK_LABEL(infoLabel), mmessage); //g_print("g\n");
	const char *format = "<span foreground=\"black\" font=\"45\"><b>%s</b></span>"; //g_print("h\n");
	char* markup = g_markup_printf_escaped(format, mmessage);// g_print("i\n");
	gtk_label_set_markup(GTK_LABEL(infoLabel), markup); //g_print("j\n");
	//gtk_fixed_put (GTK_FIXED(centerFixed), infoLabel, 0, 50); g_print("k\n");
	//gtk_notebook_append_page (GTK_NOTEBOOK (centerNotebook), centerFixed, labelInfoPage);
	g_free (markup); //g_print("l\n");

	gtk_notebook_set_current_page (GTK_NOTEBOOK (centerNotebook), 10);
    gtk_notebook_set_current_page (GTK_NOTEBOOK (leftNotebook), 10);
    gtk_notebook_set_current_page (GTK_NOTEBOOK (rightNotebook), 10);
    gint uiPageNum = gtk_notebook_get_current_page(GTK_NOTEBOOK(centerNotebook));

    return uiPageNum;
}

gint graphicalFunctions::drawWeatherPage(void) // TODO
{
	bool weatherError = false;

	std::string theweather;

	if (weatherError)
	{
		theweather = "Temporarily\nOut of Order";

		gtk_label_set_text(GTK_LABEL(weatherLabel), theweather.data()); //g_print("g\n");
		const char *format = "<span foreground=\"black\" font=\"45\"><b>%s</b></span>"; //g_print("h\n");
		char* markup = g_markup_printf_escaped(format, theweather.data());// g_print("i\n");
		gtk_label_set_markup(GTK_LABEL(weatherLabel), markup);
		g_free (markup);
	}
	else
	{

	//	std::string theweather = weather();
		//std::string theweather = getTemperature();

		std::string lowT;
		std::string highT;
	//	lowT.append("L ");
		lowT.append(lowTemp);
		lowT.erase(std::remove(lowT.begin(), lowT.end(), '\n'), lowT.end());
		lowT.append("°");
		lowT.append("F");

	//	highT.append("H ");
		highT.append(highTemp);
		highT.erase(std::remove(highT.begin(), highT.end(), '\n'), highT.end());
		highT.append("°");
		highT.append("F");


		std::string theweather = currentTemp;
		std::string iconName;
		iconName.append(weatherIconName);
		iconName.erase(std::remove(iconName.begin(), iconName.end(), '\n'), iconName.end());


	//	printf("\n\nfrom graphical functions, weathertext: %s\n\n", theweather.data());
		printf("\n\nfrom graphical functions, weathertext: %s\n\n", theweather.data());

		printf("\n\nfrom graphical functions, Forecast: %s\n\n", currentWeatherForecast.data());

		int numCurrentWeatherForecastCharacters = 0;
		numCurrentWeatherForecastCharacters = getStringSize(currentWeatherForecast);
		printf("From GraphicalFuncktions:--: Forecast size = %d\n\n", numCurrentWeatherForecastCharacters);

		gtk_label_set_text(GTK_LABEL(weatherLabel), theweather.data()); //g_print("g\n");
		const char *format = "<span foreground=\"black\" font=\"100\"><b>%s</b></span>"; //g_print("h\n");
		char* markup = g_markup_printf_escaped(format, theweather.data());// g_print("i\n");
		gtk_label_set_markup(GTK_LABEL(weatherLabel), markup);
		g_free (markup);

		if (numCurrentWeatherForecastCharacters < 130){
			gtk_label_set_text(GTK_LABEL(weatherForecast), currentWeatherForecast.data()); //g_print("g\n");
			const char *format2 = "<span foreground=\"black\" font=\"35\"><b>%s</b></span>"; //g_print("h\n");
			char* markup2 = g_markup_printf_escaped(format2, currentWeatherForecast.data());// g_print("i\n");
			gtk_label_set_markup(GTK_LABEL(weatherForecast), markup2);
			g_free (markup2);
		} else {
			gtk_label_set_text(GTK_LABEL(weatherForecast), currentWeatherForecast.data()); //g_print("g\n");
			const char *format2 = "<span foreground=\"black\" font=\"25\"><b>%s</b></span>"; //g_print("h\n");
			char* markup2 = g_markup_printf_escaped(format2, currentWeatherForecast.data());// g_print("i\n");
			gtk_label_set_markup(GTK_LABEL(weatherForecast), markup2);
			g_free (markup2);
		}

		gtk_label_set_text(GTK_LABEL(weatherTodayHighTempLabel), highT.data()); //g_print("g\n");
		const char *format3 = "<span foreground=\"black\" font=\"60\"><b>%s</b></span>"; //g_print("h\n");
		char* markup3 = g_markup_printf_escaped(format3, highT.data());// g_print("i\n");
		gtk_label_set_markup(GTK_LABEL(weatherTodayHighTempLabel), markup3);
		g_free (markup3);

		gtk_label_set_text(GTK_LABEL(weatherTodayLowTempLabel), lowT.data()); //g_print("g\n");
		const char *format4 = "<span foreground=\"black\" font=\"60\"><b>%s</b></span>"; //g_print("h\n");
		char* markup4 = g_markup_printf_escaped(format4, lowT.data());// g_print("i\n");
		gtk_label_set_markup(GTK_LABEL(weatherTodayLowTempLabel), markup4);
		g_free (markup4);





//		switch(str2int(iconName))
//		{
//		case str2int("clear"):
//		{
//			gtk_image_set_from_file(GTK_IMAGE(weatherImage), "/home/pi/bike_project/weatherIcons/sunny.png");
//		}
//		break;
//		default:
//			break;
//		}

		//gtk_image_set_from_file(GTK_IMAGE(weatherImage), "/home/pi/bike_project/weatherIcons/sunny.png");
		gtk_image_set_from_file(GTK_IMAGE(weatherImage), weatherIconName.data());
		printf("%s\n", weatherIconName.data());


	}
//	int weatherfoo = 3;
//
//	switch (weatherfoo)
//	{
//		case 0:
//			gtk_image_set_from_file(GTK_IMAGE(weatherImage), "/home/pi/bike_project/cloudy.png");
//			break;
//		case 1:
//			gtk_image_set_from_file(GTK_IMAGE(weatherImage), "/home/pi/bike_project/partly_cloudy.png");
//			break;
//		case 2:
//			gtk_image_set_from_file(GTK_IMAGE(weatherImage), "/home/pi/bike_project/storm_lightning.png");
//			break;
//		case 3:
//			gtk_image_set_from_file(GTK_IMAGE(weatherImage), "/home/pi/bike_project/storm_rain.png");
//			break;
//		case 4:
//			gtk_image_set_from_file(GTK_IMAGE(weatherImage), "/home/pi/bike_project/storm_snow.png");
//			break;
//		case 5:
//			gtk_image_set_from_file(GTK_IMAGE(weatherImage), "/home/pi/bike_project/sunny.png");
//			break;
//		default:
//			break;
//	}
//	printf("line 863\n");
	gtk_notebook_set_current_page (GTK_NOTEBOOK (centerNotebook), 11);
    gtk_notebook_set_current_page (GTK_NOTEBOOK (leftNotebook), 11);
    gtk_notebook_set_current_page (GTK_NOTEBOOK (rightNotebook), 11);
    gint uiPageNum = gtk_notebook_get_current_page(GTK_NOTEBOOK(centerNotebook));
    //weatherfoo++;
   // printf("line 868\n");
    //return uiPageNum;
    return 11;
}

gint graphicalFunctions::drawAdminPage(void)
{
	// start power code
	int battPercentInt = getBatteryPercentage();
	char battPercentString[100];

	//char* buffer = ... allocate a buffer ...

	printf("From getBatterPercentage() -- battPercentInt = %d\n", battPercentInt);

	sprintf(battPercentString, "%d", battPercentInt);
	printf("From sprintf -- battPercentString = %s\n", battPercentString);

	gtk_label_set_text(GTK_LABEL(PowerSystemLevelLabel),  battPercentString); //g_print("g\n");
	const char *format1 = "<span foreground=\"black\" font=\"40\"><b>%s</b></span>"; //g_print("h\n");
	char* markup1 = g_markup_printf_escaped(format1, battPercentString);// g_print("i\n");
	gtk_label_set_markup(GTK_LABEL(PowerSystemLevelLabel), markup1);
	g_free (markup1);

	// end power code


	//std::string threegIP =  get3gIP();
	std::string threegIP =  "3G Offline";
	printf("from graphicalfunctions, drawing admin page, ip: %s\n", threegIP.data());

	gtk_label_set_text(GTK_LABEL(Admin3gIpAddressLabel),  threegIP.data()); //g_print("g\n");
	const char *format2 = "<span foreground=\"black\" font=\"40\"><b>%s</b></span>"; //g_print("h\n");
	char* markup2 = g_markup_printf_escaped(format2, threegIP.data());// g_print("i\n");
	gtk_label_set_markup(GTK_LABEL(Admin3gIpAddressLabel), markup2);
	g_free (markup2);


	std::string wifiIP =  getWifiIP();
	printf("from graphicalfunctions, drawing admin page, ip: %s\n", wifiIP.data());

	gtk_label_set_text(GTK_LABEL(AdminWifiIpAddressLabel),  wifiIP.data()); //g_print("g\n");
	const char *format3 = "<span foreground=\"black\" font=\"40\"><b>%s</b></span>"; //g_print("h\n");
	char* markup3 = g_markup_printf_escaped(format3, wifiIP.data());// g_print("i\n");
	gtk_label_set_markup(GTK_LABEL(AdminWifiIpAddressLabel), markup3);
	g_free (markup3);
	//AdminIpAddressLabel

	gtk_notebook_set_current_page (GTK_NOTEBOOK (centerNotebook), 12);
    gtk_notebook_set_current_page (GTK_NOTEBOOK (leftNotebook), 12);
    gtk_notebook_set_current_page (GTK_NOTEBOOK (rightNotebook), 12);
    gint uiPageNum = gtk_notebook_get_current_page(GTK_NOTEBOOK(centerNotebook));

    return uiPageNum;
}

gint graphicalFunctions::drawReturnPage(unsigned int bikeID)
{
	char bikeIDString[10];
	sprintf(bikeIDString, "%x", bikeID);
	std::string wholeMessage;

	wholeMessage.append("Bike ");
	wholeMessage.append(bikeIDString);
	wholeMessage.append("\nwas returned,\nThank you!");

	gtk_label_set_text(GTK_LABEL(RentalReturnedLabel), wholeMessage.data()); //g_print("g\n");
	const char *format = "<span foreground=\"black\" font=\"45\"><b>%s</b></span>"; //g_print("h\n");
	char* markup = g_markup_printf_escaped(format, wholeMessage.data());// g_print("i\n");
	gtk_label_set_markup(GTK_LABEL(RentalReturnedLabel), markup);
	g_free (markup);

	gtk_notebook_set_current_page (GTK_NOTEBOOK (centerNotebook), 13);
    gtk_notebook_set_current_page (GTK_NOTEBOOK (leftNotebook), 13);
    gtk_notebook_set_current_page (GTK_NOTEBOOK (rightNotebook), 13);
    gint uiPageNum = gtk_notebook_get_current_page(GTK_NOTEBOOK(centerNotebook));

    return uiPageNum;
}

gint graphicalFunctions::drawAdvertisementsPage(void)
{
	gtk_notebook_set_current_page (GTK_NOTEBOOK (centerNotebook), 9);
    gtk_notebook_set_current_page (GTK_NOTEBOOK (leftNotebook), 9);
    gtk_notebook_set_current_page (GTK_NOTEBOOK (rightNotebook), 9);
    gint uiPageNum = gtk_notebook_get_current_page(GTK_NOTEBOOK(centerNotebook));

    return uiPageNum;
}

gint graphicalFunctions::drawBikeProblemsPage(int rackNumber)
{
	gtk_notebook_set_current_page (GTK_NOTEBOOK (centerNotebook), 14);
    gtk_notebook_set_current_page (GTK_NOTEBOOK (leftNotebook), 14);
    gtk_notebook_set_current_page (GTK_NOTEBOOK (rightNotebook), 14);
    gint uiPageNum = gtk_notebook_get_current_page(GTK_NOTEBOOK(centerNotebook));

    return uiPageNum;
}

gint graphicalFunctions::drawBikeReportProblemProcessingPage(BIKE_CONDITION_CODE code)
{
	setBikeProblemCode(code);

	gtk_notebook_set_current_page (GTK_NOTEBOOK (centerNotebook), 15);
    gtk_notebook_set_current_page (GTK_NOTEBOOK (leftNotebook), 15);
    gtk_notebook_set_current_page (GTK_NOTEBOOK (rightNotebook), 15);
    gint uiPageNum = gtk_notebook_get_current_page(GTK_NOTEBOOK(centerNotebook));

    return uiPageNum;
}


gint graphicalFunctions::drawBikeReportProblemProcessingSuccessOrErrorPage(std::string successOrError)
{
	//  bicycleReportProblemSuccessErrorOrLabel

	gtk_label_set_text(GTK_LABEL(bicycleReportProblemSuccessErrorOrLabel), successOrError.data()); //g_print("g\n");
	const char *format = "<span foreground=\"black\" font=\"45\"><b>%s</b></span>"; //g_print("h\n");
	char* markup = g_markup_printf_escaped(format, successOrError.data());// g_print("i\n");
	gtk_label_set_markup(GTK_LABEL(bicycleReportProblemSuccessErrorOrLabel), markup);
	g_free (markup);

	gtk_notebook_set_current_page (GTK_NOTEBOOK (centerNotebook), 16);
    gtk_notebook_set_current_page (GTK_NOTEBOOK (leftNotebook), 16);
    gtk_notebook_set_current_page (GTK_NOTEBOOK (rightNotebook), 16);
    gint uiPageNum = gtk_notebook_get_current_page(GTK_NOTEBOOK(centerNotebook));

    return uiPageNum;
}

gint graphicalFunctions::drawOnlineRentHelpPageStepOne(void)
{
	gtk_notebook_set_current_page (GTK_NOTEBOOK (centerNotebook), 17);
    gtk_notebook_set_current_page (GTK_NOTEBOOK (leftNotebook), 17);
    gtk_notebook_set_current_page (GTK_NOTEBOOK (rightNotebook), 17);
    gint uiPageNum = gtk_notebook_get_current_page(GTK_NOTEBOOK(centerNotebook));

    return uiPageNum;
}

gint graphicalFunctions::drawOnlineRentHelpPageStepTwo(void)
{
	gtk_notebook_set_current_page (GTK_NOTEBOOK (centerNotebook), 18);
    gtk_notebook_set_current_page (GTK_NOTEBOOK (leftNotebook), 18);
    gtk_notebook_set_current_page (GTK_NOTEBOOK (rightNotebook), 18);
    gint uiPageNum = gtk_notebook_get_current_page(GTK_NOTEBOOK(centerNotebook));

    return uiPageNum;
}


gint graphicalFunctions::printSomething(void)
{
	//printf("TJTJTJTJTJTJTJTJTJTJTJTJTJTJTJ\n");
	//printf("TJTJTJTJTJTJTJTJTJTJTJTJTJTJTJ\n");
	//printf("TJTJTJTJTJTJTJTJTJTJTJTJTJTJTJ\n");
	//printf("TJTJTJTJTJTJTJTJTJTJTJTJTJTJTJ\n");
	//printf("TJTJTJTJTJTJTJTJTJTJTJTJTJTJTJ\n");
	//printf("TJTJTJTJTJTJTJTJTJTJTJTJTJTJTJ\n");
	//printf("TJTJTJTJTJTJTJTJTJTJTJTJTJTJTJ\n");
	//printf("TJTJTJTJTJTJTJTJTJTJTJTJTJTJTJ\n");
	//printf("TJTJTJTJTJTJTJTJTJTJTJTJTJTJTJ\n");
	//printf("TJTJTJTJTJTJTJTJTJTJTJTJTJTJTJ\n");
	//printf("TJTJTJTJTJTJTJTJTJTJTJTJTJTJTJ\n");
	//printf("TJTJTJTJTJTJTJTJTJTJTJTJTJTJTJ\n");
	//printf("TJTJTJTJTJTJTJTJTJTJTJTJTJTJTJ\n");
	//printf("TJTJTJTJTJTJTJTJTJTJTJTJTJTJTJ\n");
	//printf("TJTJTJTJTJTJTJTJTJTJTJTJTJTJTJ\n");
	//printf("TJTJTJTJTJTJTJTJTJTJTJTJTJTJTJ\n");
	//printf("TJTJTJTJTJTJTJTJTJTJTJTJTJTJTJ\n");
	//printf("TJTJTJTJTJTJTJTJTJTJTJTJTJTJTJ\n");
	//printf("TJTJTJTJTJTJTJTJTJTJTJTJTJTJTJ\n");
	//printf("TJTJTJTJTJTJTJTJTJTJTJTJTJTJTJ\n");
	//printf("TJTJTJTJTJTJTJTJTJTJTJTJTJTJTJ\n");
	return 1;
}

void graphicalFunctions::destroy_window( GtkWidget *widget,
                      gpointer  pointer )
 {
     gtk_main_quit ();
 }

//static void key_press_cb(GtkWidget *widget, GdkEventKey *kevent, gpointer data);
void graphicalFunctions::updateUI(char key){
	key = tolower(key);
	switch (getuiPageNum())
	{
		case (0):  // welcome screen
		{
			drawWelcomePage();
			switch (key)
			{
				case 'a':  // Rent Screen
					//setuiPageNum(drawRentPage());
					setuiPageNum(drawOnlineCodePage());
            		key = 'z';
					break;
				case 'b':
					setuiPageNum(drawInfoPage());
					key = 'z';
					break;
				case 'c':
					setuiPageNum(drawWeatherPage());
					key = 'z';
					break;
				case 'd':
					break;
				case 'e':  // Report Problem
					setuiPageNum(drawReportProblemPage());
            		key = 'z';
					break;
				case 'f':  // Map
					setuiPageNum(drawMapPage());
            		key = 'z';
					break;
				case 'g':
					break;
//				case 'h':  // Admin
//					setuiPageNum(drawAdminPage());
//					key = 'z';
//					break;
				default:
					break;
			}
			break;
		}
		case (1):  // Rent screen
		{
			switch (key)
			{
				case 'a':  // Credit Card
					setuiPageNum(drawCreditCardPage());
            		key = 'z';
					break;
				case 'd': // Back
					setuiPageNum(drawWelcomePage());
            		key = 'z';
					break;
				case 'e':  // Online Code
					setuiPageNum(drawOnlineCodePage());
            		key = 'z';
					break;
				case 'h':  // Cancel
					setuiPageNum(drawWelcomePage());
            		key = 'z';
					break;
//				case 'r': // Draw Return
//					setuiPageNum(drawReturnPage());
//					key = 'z';
//					break;
				default:
					break;
			}
			break;
		}
		case (2):  // Swipe Credit Card
		{
			switch (key)
			{
				case 'd':  // Back
					setuiPageNum(drawRentPage());
            		key = 'z';
					break;
				case 'h': // Cancel
					setuiPageNum(drawWelcomePage());
            		key = 'z';
					break;
				default:
					break;
			}
			break;
		}
		case (3):  // Online Payment
		{
			switch (key)
			{
				case 'd':  // Back
					setuiPageNum(drawWelcomePage());
            		key = 'z';
					break;
//				case 'e':  // submit
//					setuiPageNum(drawSubmitPage());
//            		key = 'z';
//					break;
				case 'h': // Help
					setuiPageNum(drawOnlineRentHelpPageStepOne());
            		key = 'z';
					break;
				default:  // was the keypad used?
					break;
			}
			break;
		}
		case (4): // successful rent //TODO
		{
			switch (key)
			{
			case 'd':
				setuiPageNum(drawWelcomePage());
				key = 'z';
				break;
			default:
				break;
			}
		}
		case (5):  // Map Screen
		{
			switch (key)
			{
				case 'd':  // Back
					setuiPageNum(drawWelcomePage());
            		key = 'z';
					break;
				default:
					break;
			}
			break;
		}
		case (6):  // Report Problem
		{
			switch (key)
			{
				case 'a':  // Bike 1
				{
					setuiPageNum(drawBikeProblemsPage(0));
					key = 'z';
					break;
				}
				case 'd':  // Back
				{
					setuiPageNum(drawWelcomePage());
            		key = 'z';
					break;
				}
				case 'e':  // Bike 2
				{
					setuiPageNum(drawBikeProblemsPage(1));
					key = 'z';
					break;
				}
				case 'f':  // Bike 3
				{
					setuiPageNum(drawBikeProblemsPage(2));
					key = 'z';
					break;
				}

				case 'g':  // Bike 4
				{
					setuiPageNum(drawBikeProblemsPage(3));
					key = 'z';
					break;
				}
				case 'h':  // Bike 5
				{
					setuiPageNum(drawBikeProblemsPage(4));
            		key = 'z';
					break;
				}
				default:
					break;
			}
			break;
		}
		case (7):  // Processing Transaction
			{
			switch (key)
			{
//				case 'a':
//					setuiPageNum(drawSuccessPage());
//					key = 'z';
//					break;

//			case ' ':
//			{
//				if(0)//good code
//				{
//					setuiPageNum(drawSuccessPage());
//					key = 'z';
//				}
//				else //bad code
//				{
//					setuiPageNum(drawFailurePage());
//					key = 'z';
//				}
//				break;
//			}
			default:
				break;
			}
			break;
			}
		case (8): // Transaction Failure
		{
			switch (key)
			{
				case 'd':
				{
					setuiPageNum(drawWelcomePage());
            		key = 'z';
					break;
				}
				default:
					break;
		}
		break;
		case (9): // Advertisements Page
		{
			switch (key)
			{
				case 'a':
				{
					setuiPageNum(drawWelcomePage());
					key = 'z';
					break;
				}
				case 'b':
				{
					setuiPageNum(drawWelcomePage());
					key = 'z';
					break;
				}
				case 'c':
				{
					setuiPageNum(drawWelcomePage());
					key = 'z';
					break;
				}
				case 'd':
				{
					setuiPageNum(drawWelcomePage());
					key = 'z';
					break;
				}
				case 'e':
				{
					setuiPageNum(drawWelcomePage());
					key = 'z';
					break;
				}
				case 'f':
				{
					setuiPageNum(drawWelcomePage());
					key = 'z';
					break;
				}
				case 'g':
				{
					setuiPageNum(drawWelcomePage());
					key = 'z';
					break;
				}
				case 'h':
				{
					setuiPageNum(drawWelcomePage());
					key = 'z';
					break;
				}
				default:
					break;

			}
		}
		case (10): // Info Page
		{
			switch (key)
			{
				case 'd':
				{
					setuiPageNum(drawWelcomePage());
					key = 'z';
					break;
				}
//				case 'h':
//				{
//					setuiPageNum(drawWelcomePage());
//					key = 'z';
//					break;
//				}
				default:
					break;
			}
			break;
		}
		case (11): // Info Page
		{
			switch (key)
			{
				case 'd':
				{
					setuiPageNum(drawWelcomePage());
					key = 'z';
					break;
				}
//				case 'h':
//				{
//					setuiPageNum(drawWelcomePage());
//					key = 'z';
//					break;
//				}
				default:
					break;
			}
			break;
		}
		case (12): // Info Page
		{
			switch (key)
			{
				case 'd':
				{
					setuiPageNum(drawWelcomePage());
					key = 'z';
					break;
				}
				case 'h':
				{
					setuiPageNum(drawWelcomePage());
					key = 'z';
					break;
				}
				default:
					break;
			}
			break;
		}
		case (13): // Info Page
		{
			switch (key)
			{
				case 'd':
				{
					setuiPageNum(drawWelcomePage());
					key = 'z';
					break;
				}
				case 'h':
				{
					setuiPageNum(drawWelcomePage());
					key = 'z';
					break;
				}
				default:
					break;
			}
			break;
		}
		case (14): // Problems List Screen
		{
			switch (key)
			{
				case 'a':
				{
					setuiPageNum(drawBikeReportProblemProcessingPage(TIRE));
					key = 'z';
					break;
				}
				case 'b':
				{
					setuiPageNum(drawBikeReportProblemProcessingPage(SEAT));
					key = 'z';
					break;
				}
				case 'c':
				{
					setuiPageNum(drawBikeReportProblemProcessingPage(WHEEL));
					key = 'z';
					break;
				}
				case 'd':
				{
					setuiPageNum(drawBikeReportProblemProcessingPage(PEDAL));
					key = 'z';
					break;
				}
				case 'e':
				{
					setuiPageNum(drawBikeReportProblemProcessingPage(BRAKE));
					key = 'z';
					break;
				}
				case 'f':
				{
					setuiPageNum(drawBikeReportProblemProcessingPage(OTHER));
					key = 'z';
					break;
				}
				case 'h':
				{
					setuiPageNum(drawWelcomePage());
					key = 'z';
					break;
				}
				default:
					break;
				}
		}
		case (16): // report bike problem success or error screen
		{
			switch (key)
			{
				case 'd':
				{
					setuiPageNum(drawWelcomePage());
					key = 'z';
					break;
				}
				default:
					break;
			}
			break;
		}
		case (17): // Bike Rent Help Step One
		{
			switch (key)
			{
				case 'd':
				{
					setuiPageNum(drawOnlineCodePage());
					key = 'z';
					break;
				}
				case 'e':
				{
					setuiPageNum(drawOnlineRentHelpPageStepTwo());
					key = 'z';
					break;
				}
				case 'h':
				{
					setuiPageNum(drawWelcomePage());
					key = 'z';
					break;
				}
				default:
					break;
				}
		}
		case (18): // Bike Rent Help Step Two
		{
			switch (key)
			{
				case 'd':
				{
					setuiPageNum(drawOnlineRentHelpPageStepOne());
					key = 'z';
					break;
				}
				case 'e':
				{
					setuiPageNum(drawOnlineCodePage());
					key = 'z';
					break;
				}
				case 'h':
				{
					setuiPageNum(drawWelcomePage());
					key = 'z';
					break;
				}
				default:
					break;
				}
		}
		default:
			break;
		}
	}
}

