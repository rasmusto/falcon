/*
 * hashMap.c - CS261 Assignment 6
 * written by Torben Rasmusssen
 * fall 2009
 */

#include "hashMap.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char * newStr (char * charBuffer);
int stringHash (char * str);

char * newStr (char * charBuffer)
{
	char * p = (char *)malloc(1 + strlen(charBuffer));
	strcpy(p, charBuffer);
	return p;
}

void initMap (struct hashMap * ht, int tableSize) 
{
	int i;

	ht->count = 0;
	ht->table = (struct hashLink **)malloc(tableSize * sizeof(struct hashLink *));
	ht->tableSize = tableSize;
	for(i = 0; i < tableSize; i++)
	{
		ht->table[i] = NULL;
	}
}

void insertMap (struct hashMap * ht, KeyType k, ValueType v) 
{
	struct hashLink * current;
	struct hashLink * newLink;
	struct hashLink ** newTable;
	struct hashLink ** tempTable;
	int i;
	int size;
	KeyType * str;
	int index = stringHash(k) % ht->tableSize; 

	if(containsKey(ht, k))
	{
		current = ht->table[index];
		while(current != NULL)
		{
			if(!strcmp(current->key, k))
			{
				current->value += v;
				break;
			}
			current = current->next;
		}
	}
	else
	{
		if((ht->count / ht->tableSize) >= 3)
		{
			newTable = (struct hashLink **)malloc(ht->tableSize * 2 * sizeof(struct hashLink *));
			tempTable = ht->table;
			ht->table = newTable;
			ht->count = 0;
			size = ht->tableSize;
			ht->tableSize *= 2;
			for(i = 0; i < size; i++)
			{
				current = tempTable[i];
				while(current != NULL)
				{
					insertMap(ht, newStr(current->key), current->value);
					current = current->next;
				}
			}
			free(tempTable);
		}
		newLink = (struct hashLink *)malloc(sizeof(struct hashLink));
		current = ht->table[index];
		ht->table[index] = newLink;
		newLink->next = current;
		newLink->value = v;
		newLink->key = (KeyType)malloc(strlen(k) * sizeof(KeyType));
		str = (KeyType *)malloc(strlen(k) * sizeof(KeyType));
		newLink->key = newStr(k);
		ht->count++;
	}
}

ValueType atMap (struct hashMap * ht, KeyType k) 
{
	struct hashLink * current;
	if(containsKey(ht, k))
	{
		current = ht->table[stringHash(k) % ht->tableSize];
		while(strcmp(current->key, k))
		{
			current = current->next;
		}
		return current->value;
	}
	return -1;
}

int containsKey(struct hashMap * ht, KeyType k) 
{
	struct hashLink * current;
	int index = stringHash(k) % ht->tableSize;

	if(ht->table[index] != NULL)
	{
		current = ht->table[index];
		while(current != NULL)
		{
			if(!strcmp(current->key, k))
			{
				return 1;
			}
			current = current->next;
		}
	}
	return 0;
}

void removeKey (struct hashMap * ht, KeyType k)
{
	struct hashLink * current;
	struct hashLink * previous;
	int index = stringHash(k) % ht->tableSize;
	if(containsKey(ht, k))
	{
		current = ht->table[index];
		if(!strcmp(current->key, k))
		{
			ht->table[index] = current->next;
			ht->count--;
			free(current);
			return;
		}
		while(strcmp(current->key, k))
		{
			previous = current;
			current = current->next;
		}
		previous->next = current->next;
	}
	ht->count--;
	return;
}

int stringHash (char * str) 
{
	int i, r;
	r = 0;
	for(i = 0; str[i] != 0; i++)
		r += str[i];
	return r;
}

/*
int main(int argc, const char * argv[]) 
{
	int i;
	struct hashMap * test = (struct hashMap *)malloc(sizeof(struct hashMap));
	struct hashLink * current = (struct hashLink *)malloc(sizeof(struct hashLink));
	initMap(test, 1024);
	insertMap(test, "a", 1);
	insertMap(test, "b", 2);
	insertMap(test, "c", 3);
	insertMap(test, "abc", 1);
	insertMap(test, "It", 1);
	insertMap(test, "was", 1);
	insertMap(test, "the", 1);
	insertMap(test, "best", 1);
	insertMap(test, "of", 1);
	insertMap(test, "times", 1);
	insertMap(test, "It", 1);
	insertMap(test, "was", 1);
	insertMap(test, "the", 1);
	insertMap(test, "worst", 1);
	insertMap(test, "of", 1);
	insertMap(test, "times", 1);
	insertMap(test, "d", 1);
	insertMap(test, "e", 1);
	insertMap(test, "f", 2);
	insertMap(test, "g", 3);
	insertMap(test, "h", 2);
	insertMap(test, "i", 3);
	for(i = 0; i < test->tableSize; i++)
	{
		current = test->table[i];
		while(current != 0)
		{
			printf("%s : ",current->key);
			printf("%d\n",current->value);
			current = current->next;
		}
	}
	return 0;
}
*/
