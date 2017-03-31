//
// Created by evgenii on 08.03.17.
//

#ifndef COMPUTER_DRAW_INTERFACE_H
#define COMPUTER_DRAW_INTERFACE_H

#include "MySimpleComputer.h"
#include "MyBigChars.h"
#include "MyTerm.h"
#include <sys/stat.h>
#include <fcntl.h>

#define Col_BIG_CHAR 19
int32_t BigCharsArray[Col_BIG_CHAR * 2];

int Load_BIG_CHAR(void);
int fromArrayToBigChar(int32_t *big, char *arr);
int write_big_char();
int draw_interface(void);
int draw_memory(void);
int print_memory_cell(char *buf, int_least16_t cell);
int draw_accumulator(void);
int draw_instructionCounter(void);
int draw_operation(int address);
int draw_flag(void);
int draw_bigchar(int address);
int draw_keys(void);
int draw_IO(void);

#endif //COMPUTER_DRAW_INTERFACE_H