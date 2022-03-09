#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "hash_table.h"
#define CRC64_REV_POLY      0x95AC9329AC4BC9B5ULL
#define CRC64_INITIALIZER   0xFFFFFFFFFFFFFFFFULL
#define CRC64_TABLE_SIZE    256
#define HASH_SIZE 500


struct node {
        char *word;
        int count;
        struct node *next;
};
typedef struct node *hashEntry;

//int hashTableSize = 256;

unsigned long long crc64(char *string);
char *copyString(char *text);
hashEntry *hashInit(int hashsize);
struct node *listInit();
void hashAdd(hashEntry *hashTable, char *word, int h);
void hashAdd_to_new_table(hashEntry *hashTable, struct node *node, int h);
void hashPrintAll(hashEntry *hashTable, int cellNum);
void hashFree(hashEntry *hashTable, int size);
int hashFind(hashEntry *hashTable, char *word, int hash_index);
void listAdd(struct node *sentinel, char *word);
void listAdd_to_new_table(struct node *sentinel, struct node *node);
int listLength(struct node *sentinel);
void listPrint(struct node* sentinel);
void listFree(struct node *sentinel);
int listFind(struct node *sentinel, char *word);
int collisionFind(struct node *sentinel);
int comparator(const void  *p1, const void *p2);
struct node *node_return(struct node *sentinel);
