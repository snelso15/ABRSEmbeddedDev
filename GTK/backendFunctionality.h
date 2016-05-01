//backend-functionality.h
/*
  Function definitions for ABRS Backend Server Communications
*/

#ifndef BACKENDFUNCTIONALITY_H
#define BACKENDFUNCTIONALITY_H

//#ifdef __cplusplus
//extern "C" {
//#endif

#include <stdbool.h>
#include "jsmn/jsmn.h"
//#include "jsmn/jsmn.c"
#include </home/snelso/rpi/rootfs/usr/include/curl/curl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
  SUCCESS
  , BAD_CODE
  , UNKNOWN_ERROR
} rental_response;

// ******************** SETTINGS **********************
extern char rental_url[];
extern char return_url[];
extern char kiosk_id[];
#define SHOWDEBUG false

extern char http_response_buffer[10000];
extern int http_response_buffer_pointer;
extern int http_response_buffer_size;

bool curl_wrapper(char* url, char* post);

size_t curl_write_callback_custom(char *read_pointer, size_t size, size_t nmemb, void *response_buffer);

void substring(char* in, char* out, size_t start, size_t stop);

rental_response attemptRental(int one_time_code, char* bike_ids);
rental_response attemptReturn(char* bike_ids);

bool kioskBeginRental(int one_time_code);

//#ifdef __cplusplus
//}
//#endif

#endif
