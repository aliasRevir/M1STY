/*
M1STY ver 0.9

By XiEn1847
Finished at [2021/10/11 22:01]
*/

#include <stdio.h>
#include <conio.h>
#include <windows.h>


using namespace std;


int main(){
	RECT rect;
	HWND hwnd=NULL,oldhwnd=NULL;

	int numkey[4]={48,49,56,57}; // '0','1','8','9'
	int numAlpha[10]={1+254*0/9,1+254*1/9,1+254*8/9,1+254*9/9};
	int Alpha=255;
	puts("Press Alt + Num { 0,1,8,9 } to Set Opacity.\n");
	puts("Press Alt + { + } / { - } to Increase / Decrease Opacity.\n");
	puts("Press Alt + { ~ } to Protect a Window From Control.");
	puts(" >> If You Want to Control It Again, Press Alt and Switch Back From Another Window.\n");
	puts("Press Alt + { [ } to Enable/Disable Clicking Through the Window.");
	puts("Press Alt + { ] } to Enable/Disable Always-on-Top.");
	// finish this ...
	// finished [08/05 20:34]
	// added '[' and ']' at [10/11 22:01]
	puts("Press Alt + { \\ } to Hide this Window.");
	puts(" >> Once Hidden, It Can't be Shown Again.\n");
	puts("Press Alt + Backspace to Exit.");
	while(1){
		Sleep(1);
		// Key 'Alt'
		if(GetKeyState(18)<0){ 
			hwnd=GetForegroundWindow();
			if(hwnd!=oldhwnd){
				Alpha=255;
				DWORD dwExStyle=GetWindowLong(hwnd,GWL_EXSTYLE);
				if(!(dwExStyle&0x80000))
					SetWindowLong(hwnd,GWL_EXSTYLE,dwExStyle|0x80000);
				GetWindowRect(hwnd,&rect);
				oldhwnd=hwnd;
			}
			// Key '+' Increases Alpha
			if(GetKeyState(187)<0){
				int spamA=0;
				if(Alpha<=252)Alpha+=3;
				else Alpha=255;
				SetLayeredWindowAttributes(hwnd,0,Alpha,LWA_ALPHA);
				do{
					spamA++;
					if(spamA>=500000){
						spamA-=17000;
						if(Alpha<=254)Alpha+=1;
						else Alpha=255;
						SetLayeredWindowAttributes(hwnd,0,Alpha,LWA_ALPHA);
					}
				}while(GetKeyState(187)<0);
			}
			//
			// Key '-' Decreases Alpha
			if(GetKeyState(189)<0){
				int spamB=0;
				if(Alpha>=4)Alpha-=3;
				else Alpha=1;
				SetLayeredWindowAttributes(hwnd,0,Alpha,LWA_ALPHA);
				do{
					spamB++;
					if(spamB>=500000){
						spamB-=17000;
						if(Alpha>=2)Alpha-=1;
						else Alpha=1;
						SetLayeredWindowAttributes(hwnd,0,Alpha,LWA_ALPHA);
					}
				}while(GetKeyState(189)<0);
			}
			//
			// Key '0','1','8','9' Sets Alpha
			for(int i=0;i<=3;i++) {
				if(GetKeyState(numkey[i])<0){
					Alpha=numAlpha[i];
					SetLayeredWindowAttributes(hwnd,0,Alpha,LWA_ALPHA);
					do{}while(GetKeyState(numkey[i])<0);
				}
			}
			//
			// Key '~' Disables Changing
			if(GetKeyState(192)<0){
				DWORD dwExStyle=GetWindowLong(hwnd,GWL_EXSTYLE);
				if(dwExStyle&0x80000)
					SetWindowLong(hwnd,GWL_EXSTYLE,dwExStyle^0x80000);
				do{}while(GetKeyState(192)<0);
			}
			//
			// Key '\' Hides The Window
			if(GetKeyState(220)<0){
				ShowWindow(hwnd,false);
				DWORD dwExStyle=GetWindowLong(hwnd,GWL_EXSTYLE);
				SetWindowLong(hwnd,GWL_EXSTYLE,(dwExStyle|WS_EX_TOOLWINDOW)&WS_EX_APPWINDOW);
				do{}while(GetKeyState(220)<0);
			}
			//
			// Key '[' Enables/Disables Clicking Through the Window
			if(GetKeyState(219)<0){
				DWORD dwExStyle=GetWindowLong(hwnd,GWL_EXSTYLE);
				SetWindowLong(hwnd,GWL_EXSTYLE,dwExStyle^0x20L);
				do{}while(GetKeyState(219)<0);
			}
			//
			// Key ']' Enables/Disables Always-on-Top
			if(GetKeyState(221)<0){
				if(GetWindowLong(hwnd,GWL_EXSTYLE)&WS_EX_TOPMOST){
					// The window is topmost.
					SetWindowPos(hwnd,HWND_NOTOPMOST,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
				}else{
					// The window is not topmost.
					SetWindowPos(hwnd,HWND_TOPMOST,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
				}
				do{}while(GetKeyState(221)<0);
			}
			//
			// Key 'Backspace' Exits The Program
			if(GetKeyState(8)<0){goto EXIT;}
		}
	}
	EXIT:;
	puts("Process Exited.\n");
	return 0;
}