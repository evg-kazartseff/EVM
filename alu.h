//
// Created by evgenii on 21.04.17.
//

#ifndef COMPUTER_ALU_H
#define COMPUTER_ALU_H

#include "MySimpleComputer.h"
#include "draw_interface.h"
#include "handler.h"

typedef void *(* handler_command)(void *p);

handler_command table_command[100];

void table_command_init();

int alu(int command, int operand);
int cu();

void *READ(void *p);
#endif //COMPUTER_ALU_H
