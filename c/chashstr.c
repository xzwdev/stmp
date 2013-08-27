/*
 * chashstr.c
 *
 *  Created on: 2011-6-3
 *      Author: xzw
 */

#include "chashstr.h"

#define CHASHSTR_INIT_SIZE					0x400
#define CHASHSTR_FULL						-1

static int chashstr_hash(chashstr* map, const char* k);
static unsigned int chashstr_hash_str(chashstr* map, const char* k);
static int chashstr_rhash(chashstr* map);

chashstr* chashstr_new()
{
	chashstr* chs = (chashstr*) malloc(sizeof(chashstr));
	chs->kv = (chstrkv*) malloc(sizeof(chstrkv) * CHASHSTR_INIT_SIZE);
	memset(chs->kv, 0, sizeof(chstrkv) * CHASHSTR_INIT_SIZE);
	chs->asize = CHASHSTR_INIT_SIZE;
	chs->size = 0;
	return chs;
}

int chashstr_put(chashstr* map, const char* k, void* v)
{
	void* x = NULL;
	if (chashstr_get(map, k, &x) == 0)
		return 1;
	int index = chashstr_hash(map, k);
	while (index == CHASHSTR_FULL)
	{
		chashstr_rhash(map);
		index = chashstr_hash(map, k);
	}
	map->kv[index].k = malloc(strlen(k) + 1);
	memset(map->kv[index].k, 0, strlen(k) + 1);
	memcpy(map->kv[index].k, k, strlen(k));
	map->kv[index].v = v;
	map->kv[index].use = 1;
	map->size += 1;
	return 0;
}

/**found return 0, otherwise return 1.*/
int chashstr_get(chashstr* map, const char* k, void** v)
{
	int index = chashstr_hash_str(map, k);
	int i = 0;
	for (; i < map->asize; ++i)
	{
		if (map->kv[index].k != 0 && strcmp(map->kv[index].k, k) == 0 && map->kv[index].use == 1)
		{
			if (v != NULL)
				*v = map->kv[index].v;
			return 0;
		}
		index = (index + 1) % map->asize;
	}
	return 1;
}

int chashstr_remove(chashstr* map, const char* k)
{
	int index = chashstr_hash_str(map, k);
	int i = 0;
	for (; i < map->asize; ++i)
	{
		if (map->kv[index].k != 0 && strcmp(map->kv[index].k, k) == 0 && map->kv[index].use == 1)
		{
			map->kv[index].use = 0;
			free(map->kv[index].k);
			if (map->kv[index].v != NULL)
				free(map->kv[index].v);
			map->kv[index].k = 0;
			map->kv[index].v = 0;
			map->size -= 1;
			return 0;
		}
		index = (index + 1) % map->asize;
	}
	return 1;
}

void chashstr_remove_all(chashstr* map)
{
	int i = 0;
	for (; i < map->asize; ++i)
	{
		if (map->kv[i].use == 1)
		{
			map->kv[i].use = 0;
			free(map->kv[i].k);
			if (map->kv[i].v != NULL)
				free(map->kv[i].v);
			map->kv[i].k = 0;
			map->kv[i].v = 0;
		}
	}
}

int chashstr_size(chashstr* map)
{
	return map->size;
}

/*-----------------------------------------------------------------------------------------------------------*/
/*                                                                                                           */
/*                                      private function call                                                */
/*                                                                                                           */
/*-----------------------------------------------------------------------------------------------------------*/
unsigned int chashstr_hash_str(chashstr* map, const char* k)
{
	unsigned int hash = 0;
	do
	{
		hash ^= (unsigned int) *k;
		hash += (hash << 1) + (hash << 4) + (hash << 7) + (hash << 8) + (hash << 24);
	} while (*++k);
	return hash % map->asize;
}

int chashstr_hash(chashstr* map, const char* k)
{
	if (map->size == map->asize)
		return CHASHSTR_FULL;
	int index = chashstr_hash_str(map, k);
	int i = 0;
	for (; i < map->asize; i++)
	{
		if (map->kv[index].use == 0)
			return index;
		if (map->kv[index].k == k && map->kv[index].use == 1)
			return index;
		index = (index + 1) % map->asize;
	}
	return CHASHSTR_FULL;
}

int chashstr_rhash(chashstr* map)
{
	chstrkv* kv = (chstrkv*) malloc(2 * map->asize * sizeof(chstrkv));
	memset(kv, 0, 2 * map->asize * sizeof(chstrkv));
	//
	chstrkv* oldkv = map->kv;
	map->kv = kv; //new kv.
	//
	int oldsize = map->asize;
	map->asize = map->asize * 2; //new allocated size.
	//
	map->size = 0; //by zero.
	//
	int i = 0;
	for (; i < oldsize; ++i)
	{
		if (oldkv[i].use == 1)
		{
			chashstr_put(map, oldkv[i].k, oldkv[i].v);
			free(oldkv[i].k);
		}
	}
	free(oldkv);
	return 0;
}
