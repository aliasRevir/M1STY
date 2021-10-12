/*
M1STY ver 0.8

README

按 Alt + 0 ~ 9 对当前窗口进行不同程度的透明化
按 Alt + '+' 或 '-' 微调
按 Alt + '~' 禁止调整某个窗口，并把它变回不透明

单击这个窗口之后，按 Alt + '\' 将其隐藏。
** 注意！！！只能隐藏，不能显示，而且不保证对其他窗口无效！！！

按 Alt + 退格(backspace)结束程序
** 这在任何情况下有效。

*/


#include <stdio.h>
#include <conio.h>

// #define _WIN32_WINNT 0x0601
// Windows 7
#include <windows.h>

using namespace std;


int main() {
    RECT rect;
    HWND hwnd=NULL,oldhwnd=NULL;
    int a=0,b=0,proc=0,hide=0;
    int spamA=0,spamB=0;

    int num[10]= {0};
    int numAlpha[10]= {1+254*0/9,1+254*1/9,1+254*2/9,1+254*3/9,1+254*4/9,1+254*5/9,1+254*6/9,1+254*7/9,1+254*8/9,1+254*9/9};
    int Alpha=255;

    puts("Press Alt + {Num 0~9} to Set Opacity.\n");
    puts("Press Alt + {+} / {-} to Increase / Decrease Opacity.\n");
    puts("Press Alt + {~} to Protect a Window From Control.");
    puts(" >> If You Want to Control It Again, Press Alt and Switch Back From Another Window.\n");

    // finish this ...
    // finished [08/05 20:34]
    puts("Press Alt + {\\} to Hide this Window.");
    puts(" >> Once Hidden, It Can't Shown Again.\n");
    puts("Press Alt + Backspace to Exit.");
    //

    while(1) {
        /*
        hwnd=GetForegroundWindow();
        if(hwnd!=oldhwnd) {
            DWORD dwExStyle=GetWindowLong(hwnd,GWL_EXSTYLE);
            if(!(dwExStyle&0x80000))
                SetWindowLong(hwnd,GWL_EXSTYLE,dwExStyle^0x80000);
            GetWindowRect(hwnd, &rect);

            x=rect.left;
            y=rect.top;
            width=rect.right-x;
            height=rect.bottom-y;
            oldhwnd=hwnd;
        }
        */
        Sleep(1);

        if(GetKeyState(18)<0) { // Alt
            hwnd=GetForegroundWindow();
            if(hwnd!=oldhwnd) {
                DWORD dwExStyle=GetWindowLong(hwnd,GWL_EXSTYLE);
                if(!(dwExStyle&0x80000))
                    SetWindowLong(hwnd,GWL_EXSTYLE,dwExStyle^0x80000);
                GetWindowRect(hwnd, &rect);
                oldhwnd=hwnd;
            }

            a=GetKeyState(187);
            if(a<0) {
                if(spamA==0) {
                    if(Alpha<=239)Alpha+=16;
                    else Alpha=255;
                    SetLayeredWindowAttributes(hwnd, 0, Alpha, LWA_ALPHA);

                    spamA=1;
                    do {
                        a=GetKeyState(187);
                        spamA++;
                        if(spamA>=500000) {
                            spamA-=10000;
                            if(Alpha<=254)Alpha+=1;
                            else Alpha=255;
                            SetLayeredWindowAttributes(hwnd, 0, Alpha, LWA_ALPHA);
                        }
                    } while(a<0);
                }
            } else {
                spamA=0;
            }
            b=GetKeyState(189);
            if(b<0) {
                if(spamB==0) {
                    if(Alpha>=17)Alpha-=16;
                    else Alpha=1;
                    SetLayeredWindowAttributes(hwnd, 0, Alpha, LWA_ALPHA);

                    spamB=1;
                    do {
                        b=GetKeyState(189);
                        spamB++;
                        if(spamB>=500000) {
                            spamB-=10000;
                            if(Alpha>=2)Alpha-=1;
                            else Alpha=1;
                            SetLayeredWindowAttributes(hwnd, 0, Alpha, LWA_ALPHA);
                        }
                    } while(b<0);
                }
            } else {
                spamB=0;
            }

            for(int i=0; i<=9; i++) {
                num[i]=GetKeyState(48+i);
                if(num[i]<0) {
                    Alpha=numAlpha[i];
                    SetLayeredWindowAttributes(hwnd, 0, Alpha, LWA_ALPHA);
                    do {
                        num[i]=GetKeyState(48+i);
                    } while(num[i]<0);

                }
            }

            proc=GetKeyState(192);
            if(proc<0) {

                DWORD dwExStyle=GetWindowLong(hwnd,GWL_EXSTYLE);
                if((dwExStyle&0x80000))
                    SetWindowLong(hwnd,GWL_EXSTYLE,dwExStyle^0x80000);
                do {
                    proc=GetKeyState(192);

                } while(proc<0);
            }

            hide=GetKeyState(220);
            if(hide<0) {

                ShowWindow(hwnd,false);
                DWORD dwExStyle=GetWindowLong(hwnd,GWL_EXSTYLE);

                SetWindowLong(hwnd, GWL_EXSTYLE, ( dwExStyle | WS_EX_TOOLWINDOW ) & WS_EX_APPWINDOW);

                do {
                    hide=GetKeyState(220);

                } while(hide<0);
            }

            if(GetKeyState(8)<0) { // Backspace
                goto EXIT;
            }
        }
    }
    EXIT:;
    puts("Process Exited.\n");
    return 0;
}