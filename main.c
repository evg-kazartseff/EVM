//
// Created by jonn on 17.02.17.
//

#include "draw_interface.h"
#include "handler.h"
#include "signal.h"

int main() {
    sc_memoryInit();
    sc_regInit();
    sc_AccumIniit();
    sc_InstractionCounterInit();
    set_signals();
    draw_interface();
    main_term();
    return 0;
}
