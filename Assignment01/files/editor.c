#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "editor.h"

/**
*editor.c
*
*Definition of the functions in editor.h are in this file.
*
*Student ID: 300492211
*Name: Matt Lawrence Aguila Romanes
*/

/* Core */

/**
 * Task 4.
 * Insert a charater in the editing buffer.
 * @param editing_buffer Editing buffer
 * @param editing_buflen Length of editing buffer in bytes
 * @param to_insert Character to insert
 * @param pos Index where insertion should occur
 * @return 1 if the insertion occurred, otherwise 0
 */
int editor_insert_char(char editing_buffer[], int editing_buflen, char to_insert, int pos){
	char toBeMoved[editing_buflen];

	/* Checks if the given index is outside the boundaries of the given array */
	if(pos < 0 || pos >= editing_buflen){ 
		return 0;
	}

	for(int i = pos; i < editing_buflen; i++){
		toBeMoved[i + 1] = editing_buffer[i];
	}

	editing_buffer[pos] = to_insert; 

	/* Shifts each character from given position onwards to the right by 1 index */
	for(int i = pos + 1; i < editing_buflen; i++){
		editing_buffer[i] = toBeMoved[i];
	}

	return 1;

}

/**
 * Task 5.
 * Delete the first occurrence of the character in the editing buffer.
 * @param editing_buffer Editing buffer
 * @param editing_buflen Length of editing buffer in bytes
 * @param to_delete Character to delete
 * @param offset Index to start searching for the character to delete
 * @return 1 if the deletion occurred, otherwise 0
 */
int editor_delete_char(char editing_buffer[], int editing_buflen, char to_delete, int offset){

	for(int i = offset; i < editing_buflen; i++){
		if(editing_buffer[i] == to_delete){
			for(int j = i; j < editing_buflen; j++){
				editing_buffer[j] = editing_buffer[j + 1];
				return 1;
			}
		}
	}


	return 0; 
}

