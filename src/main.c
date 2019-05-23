/*
 *
 * BertOS - I/O assignment
 * src/main.c
 *
 * Copyright (C) 2019 Bastiaan Teeuwen <bastiaan@mkcl.nl>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301,
 * USA.
 *
 */

#include <sys/vga.h>
#include <sys/print.h>
#include <sys/ps2.h>



void input(){
    char c = ps2_getch();
    
    if(c == '\e'){
        if (ps2_getch()=='['){
            c = ps2_getch();
            switch (c)
            {
            case 'A':
                // UP
                printf("%s", "jahooooor");
                break;
            case 'B':
                // Down
                printf("%s", "JAAA");
                break;
            case 'C':
                // Right
                printf("%s", "JAAA");
                break;
            case 'D':
                // Left
                printf("%s", "JAAA");
                break;
                     
            default:
                break;
            }
        }
    
    }
    else if(c == '\b'){

        struct vga_cursor vg = vga_curget();
        vg.x = vg.x-1;
        vga_curset(vg, false);
        //printf("%i%i", vg);

    }
    else{
        printf("%c", c);
    }

}    

void main(void)
{
    while (true)
    {   
        input();
    }
    return 0;
}
