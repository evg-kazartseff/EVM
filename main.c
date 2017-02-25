//
// Created by jonn on 17.02.17.
//

#include "MySimpleComputer.h"
#include "MyTerm.h"

int main() {
   /* sc_memoryInit();
    int flg = 0;
    flg = sc_memorySet(0, 0);
    printf("memory set: address: 0, value 0; flag: %d\n", flg);
    flg = sc_memorySet(99, 99);
    printf("memory set: address: 99, value 99; flag: %d\n", flg);
    int val1, val2;
    flg = sc_memoryGet(0, &val1);
    printf("memory get: address: 0, value %d; flag: %d\n", val1, flg);
    flg = sc_memoryGet(99, &val2);
    printf("memory get: address: 99, value %d; flag: %d\n", val2, flg);

    flg = sc_memorySave("memory");
    printf("memory save: flag %d\n", flg);
    flg = sc_memoryLoad("memory");
    printf("memory load: flag %d\n", flg);

    for (char i = 0; i < 127; i++){
        int_least16_t encode;
        sc_commandEncode(i, i, &encode);
        printf("encode %x sizeof %u\n", encode, (uint) sizeof(encode));
        char comand, operand;
        int res = sc_commandDecode(encode, &comand, &operand);
        printf("comand: %d operand: %d flag: %d\n", comand, operand, res);
    }

    sc_regInit();

    int over, division, seg, ign, wrong;
    flg = sc_regSet(FLAG_OVERFLOW, 1);
    printf("register set overflow: %d\n", flg);
    flg = sc_regSet(FLAG_DIVISION_BY_ZERO, 1);
    printf("register set division by zero: %d\n", flg);
    flg = sc_regSet(FLAG_SEGMENTATION_FAULT, 1);
    printf("register set segfault: %d\n", flg);
    flg = sc_regSet(FLAG_IGNORE_IMP, 1);
    printf("register set ignore imp: %d\n", flg);
    flg = sc_regSet(FLAG_WRONG_COMMAND, 1);
    printf("register set wrong comand: %d\n", flg);

    sc_regGet(FLAG_OVERFLOW, &over);
    sc_regGet(FLAG_DIVISION_BY_ZERO, &division);
    sc_regGet(FLAG_SEGMENTATION_FAULT, &seg);
    sc_regGet(FLAG_IGNORE_IMP, &ign);
    sc_regGet(FLAG_WRONG_COMMAND, &wrong);
    printf("registor flags: %d %d %d %d %d\n", over, division, seg, ign, wrong);*/
    mt_clrscr();
    mt_setbgcolor(clr_green);
    printf("test\n");
    mt_setbgcolor(clr_default);
    mt_setfgcolor(clr_red);
    printf("test2\n");
    mt_setfgcolor(clr_default);
    uint16_t rows;
    uint16_t cols;
    int flg = mt_getscreensize(&rows, &cols);
    printf("Screan size flg %d: %d %d\n", flg, rows, cols);
    flg = mt_gotoXY(2, 2);
    printf("Goto flg %d x: %d y: %d", flg, 20, 20);
    return 0;
}