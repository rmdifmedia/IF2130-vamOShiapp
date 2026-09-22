#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "header/text/framebuffer.h"
#include "header/stdlib/string.h"
#include "header/cpu/portio.h"

void framebuffer_set_cursor(uint8_t r, uint8_t c) {
    // Hitung posisi linear kursor (tanpa dikali 2)
    uint16_t pos = r * 80 + c;

    // Kirim High Byte kursor ke port VGA
    out(CURSOR_PORT_CMD, 0x0E); // 0x0E adalah register untuk kursor high byte
    out(CURSOR_PORT_DATA, (uint8_t) ((pos >> 8) & 0xFF));

    // Kirim Low Byte kursor ke port VGA
    out(CURSOR_PORT_CMD, 0x0F); // 0x0F adalah register untuk kursor low byte
    out(CURSOR_PORT_DATA, (uint8_t) (pos & 0xFF));
}

void framebuffer_write(uint8_t row, uint8_t col, char c, uint8_t fg, uint8_t bg) {
    // Cast alamat memori ke pointer array agar bisa diisi
    uint8_t *fb = (uint8_t*) FRAMEBUFFER_MEMORY_OFFSET;
    
    // Hitung posisi index array
    uint32_t index = (row * 80 + col) * 2;
    
    // Masukkan karakter ASCII ke byte pertama
    fb[index] = (uint8_t) c;
    
    // Masukkan atribut warna ke byte kedua
    fb[index + 1] = (bg << 4) | (fg & 0x0F);
}

void framebuffer_clear(void) {
    for (uint8_t r = 0; r < 25; r++) {
        for (uint8_t c = 0; c < 80; c++) {
            // Tulis spasi kosong dengan warna default
            framebuffer_write(r, c, ' ', 0x07, 0x00);
        }
    }
}
