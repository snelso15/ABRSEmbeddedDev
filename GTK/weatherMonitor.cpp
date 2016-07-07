/*
 * weatherMonitor.cpp
 *
 *  Created on: Mar 6, 2016
 *      Author: snelso
 */
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>


//#include <curl.h>
#include "weatherMonitor.h"

// gcc -g test2.cpp -I./curl/include/curl -lcurl



struct String {
  char *ptr;
  size_t len;
};

void init_String(struct String *s) {
  s->len = 0;
  s->ptr = static_cast<char*>(malloc(s->len+1));
  if (s->ptr == NULL) {
    fprintf(stderr, "malloc() failed\n");
    exit(EXIT_FAILURE);
  }
  s->ptr[0] = '\0';
}

size_t writefunc(void *ptr, size_t size, size_t nmemb, struct String *s)
{
  size_t new_len = s->len + size*nmemb;
  s->ptr = static_cast<char*>(realloc(s->ptr, new_len+1));
  if (s->ptr == NULL) {
    fprintf(stderr, "realloc() failed\n");
    exit(EXIT_FAILURE);
  }
  memcpy(s->ptr+s->len, ptr, size*nmemb);
  s->ptr[new_len] = '\0';
  s->len = new_len;

  return size*nmemb;
}

struct String getHTML(void)
{
//  char *html;
  CURL *curl;
  CURLcode res;
  struct String s;

  curl = curl_easy_init();
  if(curl) {
    init_String(&s);

    curl_easy_setopt(curl, CURLOPT_URL, "http://weather.yahooapis.com/forecastrss?p=17402");
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);
    res = curl_easy_perform(curl);

   // html = s.ptr;
 //   free(s.ptr);

    /* always cleanup */
    curl_easy_cleanup(curl);
  }
  return s;
}

char * extract_between(char *s, char *p0, char *p3)
{

    char *p1 = strstr(s, p0)+sizeof(p0);
    char *p2 = strstr(p1, p3);
    size_t len = p2-p1;
    char *res = (char*)malloc(sizeof(char)*(len+1));
    strncpy(res, p1, len);
    res[len] = '\0';
    printf("%s\n", res);
}

std::string weather()
{
  String returnString=getHTML();
  char htmlText[returnString.len+1];

  for (int i = 0; i < returnString.len; i++){
	  htmlText[i] = returnString.ptr[i];
  }

  htmlText[returnString.len] = '\0';
  free(returnString.ptr);

  printf("returned char array from getHTML: \n");

  std::string text  = htmlText;
  text = text.substr(text.find("<b>Current Conditions:</b><br />"), -1 );
  text = text.substr(text.find("\n") + 1, -1 );
  text = text.substr(0, text.find("<BR"));


  printf("%s<---\n", text.data());

  return text;
//  printf("size: %i<---\n", text.size());

}
//popen
