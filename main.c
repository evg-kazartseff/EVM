//
// Created by jonn on 17.02.17.
//

#include "draw_interface.h"
#include "handler.h"

int main() {
    sc_memoryInit();
    sc_regInit();
    sc_AccumIniit();
    /*int_least16_t cell;
    sc_valueEncode(-123, &cell);
    sc_regSet(FLAG_DIVISION_BY_ZERO, 1);
    sc_regSet(FLAG_IGNORE_IMP, 1);
    sc_memorySet(10, cell);
    sc_valueEncode(16, &cell);
    sc_memorySet(0, cell);
    sc_memorySave("Memory");*/
    draw_interface();
    main_term();
    return 0;
}
