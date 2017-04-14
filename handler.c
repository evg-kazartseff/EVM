//
// Created by evgenii on 12.04.17.
//

#include "handler.h"

void handler_key(keys key, uint *place_x, uint *place_y)
{
    switch (key) {
        case KEY_l:
            handler_loud();
            break;
        case KEY_s:
            handler_save();
            break;
        case KEY_r:
            break;
        case KEY_t:
            break;
        case KEY_i:
            break;
        case KEY_q:
            break;
        case KEY_up:
            *place_x -= 1;
            if (*place_x == -1) {
                *place_x = 9;
            }
            draw_memory(*place_x, *place_y);
            draw_bigchar(*place_x * 10 + *place_y);
            break;
        case KEY_down:
            *place_x += 1;
            if (*place_x == 10) {
                *place_x = 0;
            }
            draw_memory(*place_x, *place_y);
            draw_bigchar(*place_x * 10 + *place_y);
            break;
        case KEY_left:
            *place_y -= 1;
            if (*place_y == -1) {
                *place_y = 9;
            }
            draw_memory(*place_x, *place_y);
            draw_bigchar(*place_x * 10 + *place_y);
            break;
        case KEY_right:
            *place_y += 1;
            if (*place_y == 10) {
                *place_y = 0;
            }
            draw_memory(*place_x, *place_y);
            draw_bigchar(*place_x * 10 + *place_y);
            break;
        case KEY_f5:
            handler_loud_accumulation();
            break;
        case KEY_f6:
            handler_loud_instr_coutner();
            break;
        case KEY_x:break;
        case KEY_d:break;
        case KEY_enter:
            handler_loud_cell_memory(*place_x, *place_y);
            break;
        case KEY_other:break;
    }

}

int main_term()
{
    keys key;
    uint place_x = 0;
    uint place_y = 0;
    rk_mytermsave();
    do {
        rk_readkey(&key);
        handler_key(key, &place_x, &place_y);
    } while (key != KEY_q);
    rk_mytermrestore();
    uint16_t max_x, max_y;
    mt_getscreensize(&max_x, &max_y);
    mt_gotoXY(1, (uint16_t) (max_x - 1));
    return 0;
}

void handler_loud() {
    draw_load_save_memory();
    char *buf;
    buf = read_console();
    if (buf != NULL) {
        if (strcmp(buf, "\033") == 0) {
            free(buf);
            draw_interface();
            return;
        }
        int flag = sc_memoryLoad(buf);
        if (flag != OK) {
            add_messange("Error read memory file!");
        }
        free(buf);
    }
    draw_interface();
    return;
}

void handler_save() {
    draw_load_save_memory();
    char *buf;
    buf = read_console();
    if (buf != NULL) {
        if (strcmp(buf, "\033") == 0) {
            free(buf);
            draw_interface();
            return;
        }
        int flag = sc_memorySave(buf);
        if (flag != OK) {
            add_messange("Error save memory file!");
        }
        free(buf);
    }
    draw_interface();
    return;
}

void handler_loud_cell_memory(uint place_x, uint place_y) {
    draw_load_cell();
    char *buf;
    buf = read_console();
    if (buf != NULL) {
        if (strcmp(buf, "\033") == 0) {
            free(buf);
            draw_interface();
            return;
        }
        int_least16_t val;
        int flg = decod_val_com(buf, &val);
        if (flg == OK) {
            flg = sc_memorySet(place_x * 10 + place_y, val);
            if (flg != OK) {
                add_messange("Could not set cell value");
            }
        }
        else {
            add_messange("Could not set cell value");
        }
        free(buf);
    }
    draw_interface();
    return;
}

int decod_val_com(char *buf, int_least16_t *cell) {
    if (buf[0] == '+') {
        if (strlen(buf) > 5) {
            return -1;
        }
        int val = atoi(&buf[1]);
        if ((val > 127) || (val < -127)) {
            return -1;
        }

        int flg = sc_valueEncode((char) val, cell);
        if (flg != OK) {
            return -1;
        }
    }
    else {
        if (strlen(buf) > 7) {
            return -1;
        }
        char *command_str = strtok(buf, ":");
        if (command_str == NULL) {
            return -1;
        }
        char *operand_str = strtok(NULL, ":");
        if (operand_str == NULL) {
            return -1;
        }
        int command = atoi(command_str);
        int operand = atoi(operand_str);
        if ((command < -127) || (command > 127) || (operand < -127) || (operand > 127)) {
            return -1;
        }
        int flg = sc_commandEncode((char) command, (char) operand, cell);
        if (flg != OK) {
            return -1;
        }
    }
    return 0;
}

void handler_loud_accumulation() {
    draw_load_cell();
    char *buf;
    buf = read_console();
    if (buf != NULL) {
        if (strcmp(buf, "\033") == 0) {
            free(buf);
            draw_interface();
            return;
        }
        int_least16_t val;
        int flg = decod_val(buf, &val);
        if (flg == OK) {
            Accumulator = val;
        }
        else {
            add_messange("Could not set cell value");
        }
        free(buf);
    }
    draw_interface();
    return;
}

int decod_val(char *buf, int_least16_t *cell) {
    if (buf[0] == '+') {
        if (strlen(buf) > 5) {
            return -1;
        }
        int val = atoi(&buf[1]);
        if ((val > 127) || (val < -127)) {
            return -1;
        }
        int flg = sc_valueEncode((char) val, cell);
        if (flg != OK) {
            return -1;
        }
    } else {
        return -1;
    }
    return 0;
}

void handler_loud_instr_coutner() {
    draw_load_cell();
    char *buf;
    buf = read_console();
    if (buf != NULL) {
        if (strcmp(buf, "\033") == 0) {
            free(buf);
            draw_interface();
            return;
        }
        int_least16_t val;
        int flg = decod_val(buf, &val);
        if (flg == OK) {
            InctructionCounter = (int_least8_t) val;
        }
        else {
            add_messange("Could not set cell value");
        }
        free(buf);
    }
    draw_interface();
    return;
}
