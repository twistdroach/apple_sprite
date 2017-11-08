/*****************************************************************************\
** mandelbrot sample program for cc65.                                       **
**                                                                           **
** (w) 2002 by groepaz/hitmen, TGI support by Stefan Haubenthal              **
\*****************************************************************************/



#include <stdlib.h>
#include <conio.h>
#include <tgi.h>
#include <cc65.h>

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


void draw_sprite(const unsigned char bitmap[])
{

    const unsigned char width = bitmap[0];
    const unsigned char height = bitmap[1];
    register unsigned char x, y, thebyte;

    for (y = 0; y < height; ++y) {
        for (x = 0; x < width; ++x) {
            thebyte = bitmap[x + (y * width) + 2];
            /* kth bit of n = (n >> k) & 1 */
#ifndef DEBUG            
            if ((thebyte >> 0) & 1) tgi_setpixel(x * 8,y);
            if ((thebyte >> 1) & 1) tgi_setpixel((x * 8) +  1,y);
            if ((thebyte >> 2) & 1) tgi_setpixel((x * 8) +  2,y);
            if ((thebyte >> 3) & 1) tgi_setpixel((x * 8) +  3,y);
            if ((thebyte >> 4) & 1) tgi_setpixel((x * 8) +  4,y);
            if ((thebyte >> 5) & 1) tgi_setpixel((x * 8) +  5,y);
            if ((thebyte >> 6) & 1) tgi_setpixel((x * 8) +  6,y);
            if ((thebyte >> 7) & 1) tgi_setpixel((x * 8) +  7,y);
#else
            cprintf("%d,%d i=%d r=%02X "BYTE_TO_BINARY_PATTERN"\r\n", x, y, x + (y * width) + 2, thebyte, BYTE_TO_BINARY(thebyte));
#endif
        }
    }

   /* tgi_outtextxy(10, 10, "Hello World");
    tgi_line(5,5,40,40); */

}

int main (void)
{
    unsigned char err;
    /* {w:16,h:27,bpp:1,xform:"rotate(-90deg)"}  */
#ifdef DEBUG
    static const unsigned char player_bitmap[] = {2,4,0x00,0x00,0x00,0x0c,0x04,0x1e,0x46,0x3f,0xb8,0x7f,0xb0,0x7f,0xba,0x7f,0xfd,0x3f,0xfc,0x07,0xfc,0x07,0xfd,0x3f,0xba,0x7f,0xb0,0x7f,0xb8,0x7f,0x46,0x3f,0x04,0x1e,0x00,0x0c};
#else
    static const unsigned char player_bitmap[] = {2,27,0x0,0x0,0x0,0x0,0x0f,0x00,0x3e,0x00,0xf4,0x07,0xec,0x00,0x76,0x00,0x2b,0x00,0x33,0x00,0x75,0x00,0xf5,0x00,0xeb,0x31,0xbf,0xef,0x3f,0xcf,0xbf,0xef,0xeb,0x31,0xf5,0x00,0x75,0x00,0x33,0x00,0x2b,0x00,0x76,0x00,0xec,0x00,0xf4,0x07,0x3e,0x00,0x0f,0x00,0x00,0x00,0x0,0x0};
    /* static const unsigned char player_bitmap[] = {2,17,0x00,0x00,0x00,0x0c,0x04,0x1e,0x46,0x3f,0xb8,0x7f,0xb0,0x7f,0xba,0x7f,0xfd,0x3f,0xfc,0x07,0xfc,0x07,0xfd,0x3f,0xba,0x7f,0xb0,0x7f,0xb8,0x7f,0x46,0x3f,0x04,0x1e,0x00,0x0c}; */
#endif

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
#endif
    draw_sprite(player_bitmap);

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
