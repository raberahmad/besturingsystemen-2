#include <sys/vga.h>
#include <sys/print.h>
#include <sys/ps2.h>



void input(){
    char c = ps2_getch();
    
    if(c == '\e'){
        if (ps2_getch()=='['){
            c = ps2_getch();
            struct vga_cursor vg = vga_curget();
            switch (c)
            {
            case 'A':
                // UP
                
                vg.y = vg.y-1;
                vga_curset(vg, false);
                break;
            case 'B':
                vg.y = vg.y+1;
                vga_curset(vg, false);
                break;
            case 'C':
                // Right
                vg.x = vg.x+1;
                vga_curset(vg, false);
                break;
            case 'D':
                // Left
                vg.x = vg.x-1;
                vga_curset(vg, false);
                break;
            default:
                break;
            }
        }
    
    }
    else if(c == '\b'){
        /*
        struct vga_cursor vg = vga_curget();
        vg.x = vg.x-1;
        vga_curset(vg, false);
        printf("%i%i", vg);
        */
    }
    else{
        printf("%c", c);
    }

}    

int main()
{
    while (true)
    {   
        input();
    }
    return 0;
}
