//
// Created by evgenii on 21.04.17.
//

#include "alu.h"


void table_command_init() {
    table_command[10] = READ;
}

int alu(int command, int operand) {
    return 0;
}


int cu() {
    char command, operand;
    int_least16_t memory_cell;
    int flg;
    flg = sc_memoryGet(InctructionCounter, &memory_cell);
    if (flg  !=  OK) {
        return -1;
    }
    flg = sc_commandDecode(memory_cell, &command, &operand);
    if (flg != OK) {
        sc_regSet(FLAG_WRONG_COMMAND, 1);
        sc_regSet(FLAG_IGNORE_IMP, 1);
        alarm(0);
        return -1;
    }
    if (command < 0 && command > 99)
        return -1;
    handler_command handler = table_command[command];
    handler((void *)(intptr_t) operand);
    draw_interface();
    return 0;
}

void *READ(void *p) {
    char *buf;
    buf = read_console();
    add_messange(buf);
    int_least16_t value;
    decod_val(buf, &value);
    sc_memorySet((int)(intptr_t) p, value);
    free(buf);
    InctructionCounter++;
    draw_instructionCounter();
    return 0;
}
