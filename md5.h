/*
 * crypt.h
 *
 *  Created on: 10 abr 2022
 *      Author: algtc
 */

#ifndef MD5_H_
#define MD5_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>


void md5(uint8_t *initial_msg, size_t initial_len);
char* encrypt(char *argv);

#endif /* MD5_H_ */
