#include <stdlib.h>
#include <conio.h>
#include <tgi.h>
#include <cc65.h>

#include "sprites.h"

//#define DEBUG 1

#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)  \
  (byte & 0x80 ? '1' : '0'), \
  (byte & 0x40 ? '1' : '0'), \
  (byte & 0x20 ? '1' : '0'), \
  (byte & 0x10 ? '1' : '0'), \
  (byte & 0x08 ? '1' : '0'), \
  (byte & 0x04 ? '1' : '0'), \
  (byte & 0x02 ? '1' : '0'), \
  (byte & 0x01 ? '1' : '0')

/* Graphics definitions */
#define SCREEN_X        (tgi_getxres())
#define SCREEN_Y        (tgi_getyres())
#define MAXCOL          (tgi_getcolorcount())

/* Use static local variables for speed */
#pragma static-locals (1);


void draw_sprite(const unsigned char bitmap[], const unsigned char x_offset, const unsigned char y_offset)
{

    const unsigned char width = bitmap[0];
    const unsigned char height = bitmap[1];
    register unsigned char x, y, thebyte;

    for (y = 0; y < height; ++y) {
        for (x = 0; x < width; ++x) {
            thebyte = bitmap[x + (y * width) + 2];
#ifdef DEBUG            
            cprintf("%d,%d i=%d r=%02X "BYTE_TO_BINARY_PATTERN"\r\n", x, y, x + (y * width) + 2, thebyte, BYTE_TO_BINARY(thebyte));
#else
            /* kth bit of n = (n >> k) & 1 */
            if ((thebyte >> 0) & 1) tgi_setpixel((x * 8) + x_offset, y + y_offset);
            if ((thebyte >> 1) & 1) tgi_setpixel((x * 8) +  1 + x_offset, y + y_offset);
            if ((thebyte >> 2) & 1) tgi_setpixel((x * 8) +  2 + x_offset, y + y_offset);
            if ((thebyte >> 3) & 1) tgi_setpixel((x * 8) +  3 + x_offset, y + y_offset);
            if ((thebyte >> 4) & 1) tgi_setpixel((x * 8) +  4 + x_offset, y + y_offset);
            if ((thebyte >> 5) & 1) tgi_setpixel((x * 8) +  5 + x_offset, y + y_offset);
            if ((thebyte >> 6) & 1) tgi_setpixel((x * 8) +  6 + x_offset, y + y_offset);
            if ((thebyte >> 7) & 1) tgi_setpixel((x * 8) +  7 + x_offset, y + y_offset);
#endif
        }
    }

   /* tgi_outtextxy(10, 10, "Hello World");
    tgi_line(5,5,40,40); */

}

int main (void)
{
    unsigned char err;

    clrscr ();

#ifndef DEBUG
    /* Install the graphics driver */
    tgi_install (tgi_static_stddrv);
    
    err = tgi_geterror ();
    if (err  != TGI_ERR_OK) {
        cprintf ("Error #%d initializing graphics.\r\n%s\r\n",
                 err, tgi_geterrormsg (err));
        if (doesclrscrafterexit ()) {
            cgetc ();
        }
        exit (EXIT_FAILURE);
    };
    cprintf ("ok.\n\r");

    /* Initialize graphics */
    tgi_init ();
    tgi_clear ();
    draw_sprite(enemy1_bitmap, 30, 10);
    draw_sprite(enemy2_bitmap, 10, 30);
    draw_sprite(enemy3_bitmap, 30, 30);
    draw_sprite(enemy4_bitmap, 50, 10);
#endif
    draw_sprite(player_bitmap, 0, 0);

    /* Fetch the character from the keyboard buffer and discard it */
    cgetc ();
#ifndef DEBUG
    /* Shut down gfx mode and return to textmode */
    tgi_done ();
#endif
    if (doesclrscrafterexit ()) {
        /* Wait for a key, then end */
        cputs ("Press any key when done...\n\r");
        cgetc ();
    }

    /* Done */
    return EXIT_SUCCESS;
}
