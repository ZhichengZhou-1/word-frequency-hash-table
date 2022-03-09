#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#define HASH_SIZE 500

struct node {
        char *word;
        int count;
        struct node *next;
};
typedef struct node *hashEntry;

//int hashTableSize = 500;

//unsigned long long crc64(char *string);
char *copyString(char *text);
hashEntry *hashInit(int hashsize);
struct node *listInit();
void hashAdd(hashEntry *hashTable, char *word, int h);
void hashAdd_to_new_table(hashEntry *hashTable, struct node *node, int h);
void hashFree(hashEntry *hashTable, int size);
int hashFind(hashEntry *hashTable, char *word, int hash_index);
void listAdd(struct node *sentinel, char *word);
void listAdd_to_new_table(struct node *sentinel, struct node *node);
void listPrint(struct node* sentinel);
void listFree(struct node *sentinel);
int listFind(struct node *sentinel, char *word);
int collisionFind(struct node *sentinel);
int comparator(const void  *p1, const void *p2);
struct node *node_return(struct node *sentinel);

int comparator(const void *p1, const void *p2) {
	return (((struct node*)p2)->count - ((struct node*)p1)->count);
}


/*unsigned long long crc64(char* string) {
    static int initFlag = 0;
    static unsigned long long table[CRC64_TABLE_SIZE];

    if (!initFlag) { initFlag++;
        for (int i = 0; i < CRC64_TABLE_SIZE; i++) {
            unsigned long long part = i;
            for (int j = 0; j < 8; j++) {
                if (part & 1)
                    part = (part >> 1) ^ CRC64_REV_POLY;
                else part >>= 1;
            }
            table[i] = part;
        }
    }

    unsigned long long crc = CRC64_INITIALIZER;
    while (*string)
        crc = table[(crc ^ *string++) & 0xff] ^ (crc >> 8);
    return crc;
}*/

// allocating memory for the word pairs
char *copyString(char *text) {
        char *copy = (char*)malloc((strlen(text)+1) * sizeof(char));
        strcpy(copy, text);
        return copy;
}


// creating empty hash table with specified size
hashEntry *hashInit(int hashsize) {
        hashEntry *hashTable = (hashEntry*)malloc(hashsize * sizeof(hashEntry));
        for (int i = 0; i < hashsize; i++) {
                hashTable[i] = listInit();
        }
        return hashTable;
}

// initializing en empty list
struct node *listInit() {
        struct node *sentinel = (struct node*)malloc(sizeof(struct node));
        sentinel->word = NULL;
        sentinel->count = 0;
        sentinel->next = NULL;
        return sentinel;
}

// adding the word to the table according to the hash index
void hashAdd(hashEntry *hashTable, char *word, int h) {
        //unsigned long long h = crc64(word);
        hashEntry sentinel = hashTable[h];
        listAdd(sentinel, word);
        return;
}

// adding nodes to the new table at given location
void hashAdd_to_new_table(hashEntry *hashTable, struct node *node, int h) {
	hashEntry sentinel = hashTable[h];
	listAdd_to_new_table(sentinel, node);
}


// freeing the entire hash table
void hashFree(hashEntry *hashTable, int size) {
        for(int i = 0; i< size; i++) {
                listFree(hashTable[i]);
        }
        free(hashTable);
        return;
}

// looking for duplicates in the table at the hash index
int hashFind(hashEntry *hashTable, char *word, int hash_index) {
	
	return (listFind(hashTable[hash_index], word));

}


// adding a new node that contains the word pair and count after the sentinel
void listAdd(struct node *sentinel, char *word) {
        struct node *new_node = listInit();
        new_node->next = sentinel->next;
        sentinel->next = new_node;

        new_node->word = copyString(word);
        new_node->count = 1;
        return;
}

// adding the existing nodes from the old table into the new table
void listAdd_to_new_table(struct node *sentinel, struct node *node) {
	if(sentinel->next != NULL) {
		struct node *temp = sentinel->next;
		struct node *new_node = listInit();
	
		new_node->word = copyString(node->word);
		sentinel->next = new_node;
		new_node->next = temp;
		new_node->count = node->count;
		return;
	}
	struct node *new_node = listInit();
	new_node->word = copyString(node->word);
	new_node->count = node->count;
	new_node->next = NULL;
	sentinel->next = new_node;
	return;
}



// printing the contents of all nodes at the location
void listPrint(struct node *sentinel) {
        struct node *next_node = sentinel->next;
        while(next_node != NULL) {
	
                printf("%d %s\n", next_node->count, next_node->word);
                next_node = next_node->next;
        }
        return;
}

// freeing all nodes at the location
void listFree(struct node *sentinel) {
        struct node *next_node = sentinel->next;
        while(sentinel) {
                if(sentinel->word) {
                        free(sentinel->word);
                }
               // if(sentinel->count) {
                //        free(sentinel->count);
                //}
                free(sentinel);

                sentinel = next_node;
                if(next_node) {
                        next_node = next_node->next;
                }
        }
        return;
}

// finding duplicates at the location for the word count
int listFind(struct node *sentinel, char *word) {
	struct node *next_node = sentinel->next;
	while(next_node != NULL) {
		if(strcmp(next_node->word,word) ==0) {
			next_node->count++;
			return 1;
		}
		else {
			next_node = next_node->next;
		}
	}
	return 0;
}

// finding the number of collisions at the location
int collisionFind(struct node *sentinel) {
	int collisionCount = 0;
	struct node *next_node = sentinel->next;
	while(next_node != NULL) {
		collisionCount++;
		next_node = next_node->next;
	}
	return collisionCount;
}

// returing a pointer to the first node after the sentinel node at the location 
// for quick sort
struct node *node_return(struct node *sentinel) {
	struct node *next_node = sentinel->next;
	while(next_node != NULL) {
		return next_node;
		next_node = next_node->next;
	}
	return NULL;
}
