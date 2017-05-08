//
// Created by evgenii on 21.04.17.
//

#include "cpu.h"

void table_command_init() {
    for (int i = 0; i < 100; ++i) {
        table_command[i] = NULL;
        for_alu[i] = false;
    }
    table_command[10] = READ;
    for_alu[10] = false;
    table_command[11] = WRITE;
    for_alu[11] = false;
    table_command[20] = LOAD;
    for_alu[20] = false;
    table_command[21] = STORE;
    for_alu[21] = false;
    table_command[30] = ADD;
    for_alu[30] = true;
    table_command[43] = HALT;
    for_alu[43] = false;
}

int alu(int command, int operand) {
    handler_command handler = table_command[command];
    int flg = 0;
    flg = (int)(intptr_t) handler((void *) (intptr_t) operand);
    return flg;
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
    if(for_alu[command]) {
        flg = alu(command, operand);
    }
    else {
        handler_command handler = table_command[command];
        flg = (int)(intptr_t) handler((void *)(intptr_t) operand);
    }
    return 0;
}

void *READ(void *p) {
    int flg = 0;
    char *buf;
    buf = read_console();
    add_messange(buf);
    int_least16_t value;
    flg = decod_val(buf, &value);
    free(buf);
    if (flg != OK) {
        return (void *)(intptr_t) -1;
    }
    flg = sc_memorySet((int)(intptr_t) p, value);
    if (flg != OK) {
        return (void *)(intptr_t) -1;
    }
    InctructionCounter++;
    return (void *)(intptr_t) 0;
}

void *WRITE(void *p) {
    int flg = 0;
    int_least16_t value;
    flg = sc_memoryGet((int)(intptr_t) p, &value);
    if (flg != OK) {
        return (void *)(intptr_t) -1;
    }
    char buf[6];
    print_memory_cell(buf, value);
    add_messange(buf);
    InctructionCounter++;
    return (void *)(intptr_t) 0;
}

void *HALT(void *p) {
    InctructionCounter = 0;
    sc_regSet(FLAG_IGNORE_IMP, 1);
    return (void *)(intptr_t) 0;
}

void *LOAD(void *p) {
    int flg = 0;
    int_least16_t value;
    flg = sc_memoryGet((int)(intptr_t) p, &value);
    if (flg != OK) {
        return (void *)(intptr_t) -1;
    }
    Accumulator = value;
    InctructionCounter++;
    return (void *)(intptr_t) 0;
}

void *STORE(void *p) {
    int flg = 0;
    flg = sc_memorySet((int)(intptr_t) p, Accumulator);
    if (flg != OK) {
        return (void *)(intptr_t) -1;
    }
    InctructionCounter++;
    return (void *)(intptr_t) 0;
}

void *ADD(void *p) {
    int flg = 0;
    int_least16_t value;
    flg = sc_memoryGet((int)(intptr_t) p, &value);
    if (flg != OK) {
        return (void *)(intptr_t) -1;
    }
    Accumulator += value;
    sc_valueEncode(Accumulator, &Accumulator);
    InctructionCounter++;
    return (void *)(intptr_t) 0;
}
