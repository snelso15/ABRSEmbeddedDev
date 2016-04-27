/*
 * weatherMonitor.h
 *
 *  Created on: Mar 6, 2016
 *      Author: snelso
 */

#ifndef GTK_WEATHERMONITOR_H_
#define GTK_WEATHERMONITOR_H_

#include </home/snelso/rpi/rootfs/usr/include/curl/curl.h>
#include <string>
//void weather(char *buff);
std::string weather();

 void init_String(struct String *s);
 size_t writefunc(void *ptr, size_t size, size_t nmemb, struct String *s);
 //char * getHTML(void);
 struct String  getHTML(void);
 char * extract_between(char *s, char *p0, char *p3);

#endif /* GTK_WEATHERMONITOR_H_ */
