/*
  ABRS Backend Server Communication Plugin
*/
#include "backendFunctionality.h"
#include "PowerSystems.h"
#include "CANWorker.h"

char rental_url[] = "https://york-abrs.herokuapp.com/rent.json";
char return_url[] = "https://york-abrs.herokuapp.com/return.json";
char status_url[] = "http://york-abrs.herokuapp.com/update/k/condition.json";
char bike_status_url[] = "http://york-abrs.herokuapp.com/update/b/condition.json";
char kiosk_id[] = "kiosk_YujVFz35";

char http_response_buffer[10000];
int http_response_buffer_pointer = 0;
int http_response_buffer_size = 10000;
time_t lastPeriodicStatusUpdate = 0;

void substring(char* in, char* out, size_t start, size_t stop) {
  size_t i;
  for(i = 0; i < (stop-start); i++) {
    out[i] = in[start+i];
  }
  out[i] = 0;
  
  return;
}

rental_response attemptRental(int one_time_code, char* bike_ids) {
  // Allocate a buffer for the post variables
  char this_post[1000];
  if(one_time_code < 1000){
	  sprintf(this_post, "kiosk_id=%s&bikeTag=%s&code=0%d", kiosk_id, bike_ids, one_time_code);
  } else{
	  sprintf(this_post, "kiosk_id=%s&bikeTag=%s&code=%d", kiosk_id, bike_ids, one_time_code);
  }
  
  // Clear the current value of the response buffer
  http_response_buffer[0] = 0;
  http_response_buffer_pointer = 0;
  
  // Submit the rental request to the backend server
  curl_wrapper(rental_url, this_post);
  
  if( SHOWDEBUG ) {
    printf("URL: %s\n", return_url);
    printf("Request: %s\n", this_post);
    printf("Response: %s\n", http_response_buffer);
  }
  
  // Parse Response
  jsmn_parser par; // Create a new instance of our parser
  jsmntok_t tokens[10]; // Allocate some tokens for it
  int token_len = 10;
  jsmn_init(&par); // Init the parser
  jsmn_parse(
    &par
    , http_response_buffer
    , (size_t) http_response_buffer_pointer
    , tokens
    , 10
  ); // Parse the response
  
  // Check for the JSON parser response (We are looking for the status code)
  int i;
  if( tokens[0].type == JSMN_OBJECT ) {
    for(i = 1; i < token_len; i++) {
      if( tokens[i].type == JSMN_STRING && tokens[i].size == 1 ) {
	char outBuffer[1000];
	substring(http_response_buffer, outBuffer, tokens[i].start, tokens[i].end);
	if( strcmp(outBuffer, "status") == 0 ) {
	  substring(http_response_buffer, outBuffer, tokens[i+1].start, tokens[i+1].end);
	  
	  bool responseHandled = false;
	  if( strcmp(outBuffer, "100") == 0 ) {
	      return BAD_CODE;
	  }
	  
	  if( strcmp(outBuffer, "200") == 0 ) {
	      return SUCCESS;
	      responseHandled = true;
	  }
	  
	  if( !responseHandled ) {
	      return UNKNOWN_ERROR;
	  }
	}
      }
    }
  }
  
  return UNKNOWN_ERROR;
}

void periodic_status_update() {
	if((lastPeriodicStatusUpdate + 60) < time(NULL)) {
		sendStatusUpdate();
		lastPeriodicStatusUpdate = time(NULL);
	}
}

rental_response attemptReturn(char* bike_ids) {
  // Allocate a buffer for the post variables
  char this_post[1000];
  sprintf(this_post, "kiosk_id=%s&bikeTag=%s", kiosk_id, bike_ids);
  
  // Clear the current value of the response buffer
  http_response_buffer[0] = 0;
  http_response_buffer_pointer = 0;
  
  // Submit the rental request to the backend server
  curl_wrapper(return_url, this_post);
  
  if( SHOWDEBUG ) {
    printf("URL: %s\n", return_url);
    printf("Request: %s\n", this_post);
    printf("Response: %s\n", http_response_buffer);
  }
  
  // Parse Response
  jsmn_parser par; // Create a new instance of our parser
  jsmntok_t tokens[10]; // Allocate some tokens for it
  int token_len = 10;
  jsmn_init(&par); // Init the parser
  jsmn_parse(
    &par
    , http_response_buffer
    , (size_t) http_response_buffer_pointer
    , tokens
    , 10
  ); // Parse the response
  
  // Check for the JSON parser response (We are looking for the status code)
  int i;
  if( tokens[0].type == JSMN_OBJECT ) {
    for(i = 1; i < token_len; i++) {
      if( tokens[i].type == JSMN_STRING && tokens[i].size == 1 ) {
	char outBuffer[1000];
	substring(http_response_buffer, outBuffer, tokens[i].start, tokens[i].end);
	if( strcmp(outBuffer, "status") == 0 ) {
	  substring(http_response_buffer, outBuffer, tokens[i+1].start, tokens[i+1].end);
	  
	  bool responseHandled = false;
	  
	  if( strcmp(outBuffer, "200") == 0 ) {
	      return SUCCESS;
	      responseHandled = true;
	  }
	  
	  if( !responseHandled ) {
	      return UNKNOWN_ERROR;
	  }
	}
      }
    }
  }
  
  return UNKNOWN_ERROR;
}

rental_response sendStatusUpdate() {
  // Allocate a buffer for the post variables
  char this_post[2000];

  int i;
  char bikes[1000];
  bikes[0] = 0;
  for(i = 0; i < NUM_RACKS; i++) {
	  int bike_id = globalCANStat->getRack(i)->heldBikeId;

	  if( bike_id != 0 ) {
		  if( bikes[0] == 0 ) {
			  sprintf(bikes, "%d", bike_id);
		  } else {
			  sprintf(bikes, "%s,%d", bikes, bike_id);
		  }
	  }
  }

  sprintf(this_post, "kiosk_id=%s&condition=100&power=%d&bikeTags=%s", kiosk_id, getBatteryPercentage(), bikes);

  // Clear the current value of the response buffer
  http_response_buffer[0] = 0;
  http_response_buffer_pointer = 0;

  // Submit the rental request to the backend server
  curl_wrapper(status_url, this_post);

  if( SHOWDEBUG ) {
    printf("URL: %s\n", status_url);
    printf("Request: %s\n", this_post);
    printf("Response: %s\n", http_response_buffer);
  }

  // Parse Response
  jsmn_parser par; // Create a new instance of our parser
  jsmntok_t tokens[10]; // Allocate some tokens for it
  int token_len = 10;
  jsmn_init(&par); // Init the parser
  jsmn_parse(
    &par
    , http_response_buffer
    , (size_t) http_response_buffer_pointer
    , tokens
    , 10
  ); // Parse the response

  // Check for the JSON parser response (We are looking for the status code)
  if( tokens[0].type == JSMN_OBJECT ) {
    for(i = 1; i < token_len; i++) {
      if( tokens[i].type == JSMN_STRING && tokens[i].size == 1 ) {
		char outBuffer[1000];
		substring(http_response_buffer, outBuffer, tokens[i].start, tokens[i].end);
		if( strcmp(outBuffer, "status") == 0 ) {
		  substring(http_response_buffer, outBuffer, tokens[i+1].start, tokens[i+1].end);

		  bool responseHandled = false;

		  if( strcmp(outBuffer, "200") == 0 ) {
			  return SUCCESS;
			  responseHandled = true;
		  }

		  if( !responseHandled ) {
			  return UNKNOWN_ERROR;
		  }
		}
      }
    }
  }

  return UNKNOWN_ERROR;
}

rental_response reportBicycleProblem(int bike_id, BIKE_CONDITION_CODE condition) {
  // Allocate a buffer for the post variables
  char this_post[1000];
  int i;
  sprintf(this_post, "bikeTag=%d&condition=%d", bike_id, condition);

  // Clear the current value of the response buffer
  http_response_buffer[0] = 0;
  http_response_buffer_pointer = 0;

  // Submit the rental request to the backend server
  curl_wrapper(bike_status_url, this_post);

  if( SHOWDEBUG ) {
    printf("URL: %s\n", bike_status_url);
    printf("Request: %s\n", this_post);
    printf("Response: %s\n", http_response_buffer);
  }

  // Parse Response
  jsmn_parser par; // Create a new instance of our parser
  jsmntok_t tokens[10]; // Allocate some tokens for it
  int token_len = 10;
  jsmn_init(&par); // Init the parser
  jsmn_parse(
    &par
    , http_response_buffer
    , (size_t) http_response_buffer_pointer
    , tokens
    , 10
  ); // Parse the response

  // Check for the JSON parser response (We are looking for the status code)
  if( tokens[0].type == JSMN_OBJECT ) {
    for(i = 1; i < token_len; i++) {
      if( tokens[i].type == JSMN_STRING && tokens[i].size == 1 ) {
	char outBuffer[1000];
	substring(http_response_buffer, outBuffer, tokens[i].start, tokens[i].end);
	if( strcmp(outBuffer, "status") == 0 ) {
	  substring(http_response_buffer, outBuffer, tokens[i+1].start, tokens[i+1].end);

	  bool responseHandled = false;

	  if( strcmp(outBuffer, "200") == 0 ) {
	      return SUCCESS;
	      responseHandled = true;
	  }

	  if( !responseHandled ) {
	      return UNKNOWN_ERROR;
	  }
	}
      }
    }
  }

  return UNKNOWN_ERROR;
}

bool curl_wrapper(char* url, char* post) {
  CURL *curl;
  CURLcode res;
 
  /* In windows, this will init the winsock stuff */ 
  curl_global_init(CURL_GLOBAL_ALL);
 
  /* get a curl handle */ 
  curl = curl_easy_init();
  if(curl) {
    /* First set the URL that is about to receive our POST. This URL can
       just as well be a https:// URL if that is what should receive the
       data. */ 
	curl_easy_setopt(curl, CURLOPT_URL, url);
    /* Now specify the POST data */ 
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post);
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-agent/1.0");
    
    /* Specify the write callback */
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &curl_write_callback_custom);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&http_response_buffer);
 
    /* Perform the request, res will get the return code */ 
    res = curl_easy_perform(curl);
    /* Check for errors */ 
    if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));
 
    /* always cleanup */ 
    curl_easy_cleanup(curl);
  }
  
  curl_global_cleanup();
  
  return true;
}

size_t curl_write_callback_custom(char *read_pointer, size_t size, size_t nmemb, void *response_buffer) {
  size_t i;
  size_t realsize = size * nmemb;
  for(i = 0; i < realsize && http_response_buffer_pointer < http_response_buffer_size; i++) {
    http_response_buffer[http_response_buffer_pointer] = read_pointer[i];
    http_response_buffer_pointer++;
  }
  return realsize;
}
