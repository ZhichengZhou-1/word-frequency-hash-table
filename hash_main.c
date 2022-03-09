#include "header.h"
#include "hash_structures.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int hashTableSize = 500;// the initial size of the hash table


int main(int argc, char **argv) {
        FILE *fp;
	hashEntry *hashTable = NULL;
	hashTable = hashInit(hashTableSize);
	hashEntry *hashTable_2 = NULL;// new hash table for growing
        int total_num_nodes = 0; // total number of collisions at all spots
	int d = 0;// length of sorted arr
	int starting_index;
 	int print_num; // user specified number of items to be printed

	if(atoi(argv[1]) >= 0) { // exit if the user didn't have "-" in front of the number
			fprintf(stderr, "format: -num\n");
			exit(6);
	}
	if(atoi(argv[1]) == 0) { // exit if the user enter -0
		fprintf(stderr, "number of items can't be 0.\n");
		exit(7);
	}


	if(argc > 1) {
		print_num = abs(atoi(argv[1]));
	}

	if(argc == 2 && print_num != 0) {
		fprintf(stderr, "No file specified.\n"); // exit if only the executable and the number of items are given
		exit(3);
	}
	if(argc < 2 && print_num == 0 ){
		fprintf(stderr, "No argument specified.\n"); // exit if only the executable is given
		exit(4);
	}

	if( print_num != 0){
		 starting_index = 2;
	}
	else {
		 starting_index = 1;
	}
	
	for( starting_index; starting_index < argc; starting_index++) {
	/*	if(fp == NULL) {
			fprintf(stderr, "CANNOT open the file.\n");
			exit(2);
		}*/
		               

        	fp = fopen(argv[starting_index], "r");
		if(fp == NULL) {
			fprintf(stderr, "CANNOT open the file.\n");
                        exit(2);
                }
		if(argc < 2 && fp == NULL) {
			fprintf(stderr, "No file specified.\n");
			exit(3);
		}

        	char *word1 = NULL;
        	char *word2 = NULL;
		word1 = getNextWord(fp);
		if(word1 == NULL) {
			fprintf(stderr, "Empty file.\n");
			exit (5);
		}

        	while (1) {
                	word2 = word1;
		
                	if(word1 == NULL) {
                        	break;
                	}
                	word1 = getNextWord(fp);
                	if(word1 == NULL) {
				free(word2);
                        	break;

                	}
		
                char str[256] = "";//empty string
                char str1[256] = " ";// space to be concatenated
                strcpy(str,word2);
                strcat(str,str1);
                strcat(str,word1);
		free(word2);

                char *hash_index_pointer = str;
                if(hash_index_pointer == NULL){
                        break;
                }
                int hash_index = crc64(hash_index_pointer) % hashTableSize; // getting a hash key for word pairs
		
		if(hashFind(hashTable, hash_index_pointer, hash_index) != 1){ // if the word pair is already in the table, increment the count, otherwise, add
                        hashAdd(hashTable, hash_index_pointer, hash_index);
		}

			int collision_at_one_location = collisionFind(hashTable[hash_index]); // calculating the number of collisions at the given hash key
			if (collision_at_one_location >= 15){ // the threshold for the hash table to grow is 15
				int hashSize_2 = hashTableSize; // hashSize_2 holds the old hash table size
				hashTableSize = hashTableSize * 3; // when growing each time, the size is increased by a factor of 3
                        	hashTable_2 = hashInit(hashTableSize); // hashTable_2 has 3 times bigger size than the original table

                        	for( int a = 0; a < hashSize_2; a++) {
					//printf("%d",a);
                                	struct node *temp_node = node_return(hashTable[a]); // node _return returns all the nodes at given location
					if(temp_node != NULL){

                                  	while(temp_node != NULL) {
                                        	hash_index = crc64(temp_node->word) % hashTableSize; // rehashing the word pair by the new size
                                        	hashAdd_to_new_table(hashTable_2, temp_node, hash_index); // add it to the new table
						temp_node = temp_node->next;
			
					 	
					}
				
					}
				}

			hashFree(hashTable, hashSize_2);
			hashTable = hashTable_2;
			}
			
			



        }
	free(word1);
	fclose(fp);
	
	}
        	struct node *unsorted_arr;
		for(int i = 0; i<hashTableSize; ++i){ // finding total number of nodes in the table
                	collisionFind(hashTable[i]);
                	total_num_nodes = total_num_nodes + collisionFind(hashTable[i]);
        	}

		// the average number of collisions is 3, the maximum is 15, when the collision at any location is greater than 15, the hash table grows
		/*int ave_collision = total_num_nodes / hashTableSize;
        	printf("Average collision is: %d\n", ave_collision);*/

                unsorted_arr = malloc(total_num_nodes*sizeof(struct node));
                for( int i = 0; i<hashTableSize; ++i) {
                        struct node *new_node = node_return(hashTable[i]);
                        while(new_node) {
                                unsorted_arr[d].word = new_node->word;
                                unsorted_arr[d].count = new_node->count;
                                new_node = new_node->next;
                                d++;


			}
		}
		//qsort sorting the array of all nodes in descending order
		qsort(unsorted_arr, d, sizeof(struct node), comparator);
		if(print_num != 0) {
			for( int i = 0; i<print_num; ++i) {

                		printf(" %d %s\n",unsorted_arr[i].count, unsorted_arr[i].word);
        		}
		}
		else {
			for ( int i =0; i < total_num_nodes; ++i) {
				printf(" %d %s\n", unsorted_arr[i].count, unsorted_arr[i].word);
			}
		}

		
		free(unsorted_arr);

       		hashFree(hashTable, hashTableSize);
	
		//free(hashTable_2);
        	return 0;


	}

