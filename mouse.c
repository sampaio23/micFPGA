#include<conio.h>
#define WIN32_LEAN_AND_MEAN // Exclude Extra Windows Crap
#define WIN32_EXTRA_LEAN // Exclude More Windows Crap
#include <windows.h>
#include <stdio.h>
#include<winuser.h>

int main(void)
{
    POINT p;
    GetCursorPos(&p);
    char c;
    // Use whatever method you need to get the keys
    // getch is just a function that gets the arrow keys so i use it here
    while (1){
    c = getch();
    fflush(stdin);
    if(c == 'M') // Right Arrow Key
        p.x += 10;  // Move Cursor Right
    if(c == 'K'){ // Left Arrow Key
        mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
        mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);}  // Move Cursor Left
    if(c == 'H') // Up Arrow Key
        p.y += 10;  // Move Cursor Up
    if(c == 'P') // Down Arrow KEy
        p.y -= 10;  // Move Cursor Down

    SetCursorPos(p.x,p.y);
    }
}

