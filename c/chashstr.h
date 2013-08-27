/*
 * chashstr.h
 *
 *  Created on: 2011-6-3
 *      Author: xuzewen
 */

#ifndef CHASHSTR_H_
#define CHASHSTR_H_

#if !defined (__LIBMISC_H__) && !defined (__LIBMISC__)
#error libmisc.h can be included directly.
#endif

#include "macro.h"

typedef struct
{
	char* k;
	void* v;
	unsigned int use;
} chstrkv;

typedef struct
{
	int asize; /**allocated size.*/
	int size;/**elements size.*/
	chstrkv* kv;
	pthread_mutex_t mutex;
} chashstr;

chashstr* chashstr_new();

int chashstr_put(chashstr* map, const char* k, void* v);

int chashstr_get(chashstr* map, const char* k, void** v);

int chashstr_remove(chashstr* map, const char* k);

void chashstr_remove_all(chashstr* map);

int chashstr_size(chashstr* map);

#endif /* CHASHSTR_H_ */
