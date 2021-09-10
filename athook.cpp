// athook.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "athook.h"
#include <iostream>
#include <fstream>

using namespace std;

// This is an example of an exported variable
const UINT WM_HOOKEX = RegisterWindowMessage("WM_HOOKEX_BS");
const UINT WM_HOOK_CONTROL = RegisterWindowMessage("WM_HOOK_ATCONTROL");
WNDPROC				OldWndProc = NULL;
BOOL bHooked = 0;
#define pCW ((CWPSTRUCT*)lParam)

#define cmd_start 1000
#define cmd_end 1001
#define cmd_push 1002
#define cmd_sendchar 1003

#define FUNC_MOVE_TO 8000
#define FUNC_ENTITY_INTERACT 8001
#define FUNC_DIALOG_INTERACT 8002
#define FUNC_BUYITEM 8003
#define FUNC_USE_HORSE 8004
#define FUNC_MONEY_INTERACT 8005
#define FUNC_COMPOSE_ITEM  8006
#define FUNC_USE_ITEM 8007
#define FUNC_REBIRTH 8008
#define FUNC_PICKPUT 8009
#define FUNC_SELECTMENU 8010
#define FUNC_CHAT 8011
#define FUNC_CHOSAUAN 8012
#define FUNC_BAYBAN 8014
#define FUNC_MOITV 8015
#define FUNC_GROUP 8016
#define FUNC_LEVELUP 8017
#define FUNC_VUTITEM 8018
#define FUNC_BANITEM 8019
#define FUNC_LATBAI 8020
#define FUNC_NHATITEM 8021
#define FUNC_LATBAI1 8022
#define FUNC_CHONSV 8024
#define FUNC_CLEAR 8026
#define FUNC_PHUTHANH 8027
#define FUNC_MORUONG 8028
#define FUNC_ENTITY_INTERACT1 8029
#define FUNC_START_GAME 8030
#define FUNC_CHOOSE_SERVER 8031
#define FUNC_CLICK_NPC 8040
#define FUNC_SHORT_MOVE 8041
int param_length;
int params[10];
int func_call;
char szData[255];
AUTOHOOK_API unsigned int __stdcall GetMsg(void)
{
	return WM_HOOK_CONTROL;
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
			hDll = (HINSTANCE) hModule;
			DisableThreadLibraryCalls(hDll);
		break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

void WriteLog(){
}

void funcMoveTo(int posX, int posY, int mapID){
	_asm{
		//sabay
		push edx;
		push ecx;
		push eax;
		mov edx, 0;
		push edx;
		mov ecx, posY;
		push ecx;
		mov eax, posX;
		push eax;
		mov edx, mapID;
		push edx;
		MOV ECX,0x00948ED0;//B76750
		mov eax,0x004E5370;//505160
		call eax;
		pop eax;
		pop ecx;
		pop edx;

		//push edx;
		//push ecx;
		//push eax;
		//mov edx, 6;
		//push edx;
		//mov ecx, posY;
		//push ecx;
		//mov eax, posX;
		//push eax;
		//mov edx, mapID;
		//push edx;
		//MOV ECX,0x00B76750;//B76750
  	    //mov eax,0x00505160;//505160
		//call eax;
		//pop eax;
		//pop ecx;
		//pop edx;
	}
}

/* binary buff...
* 89 45 E4 6A 00 6A 00 6A 00 6A 00 6A 00 6A 00 8B
45 0C 50 6A 04 8B 4D E4
*/
////move(2, toa x, toa y,0,0,0,0)
////click npc(4,id npc,0,0,00,0,)
////danh wai(3,-1,idnpc,idkill)
////buffkill (3,toax,toay,idkill)
//void SendNpc(int pra1,int pra2,int pra3,int pra4,int pra5,int pra6,int pra7,int pNpc)
void EntityInteractive(int pra1,int pra2,int pra3,int pra4,int pra5,int pra6,int pra7,int pNpc)
{
	__asm {
		push eax;
		push ecx;
		push 0;
		mov eax, pra7;
		push eax;
		mov eax, pra6;
		push eax;
		mov eax, pra5;
		push eax;
		mov eax, pra4;
		push eax;
		mov eax, pra3;
		push eax;
		mov eax, pra2;
		push eax;
		mov eax, pra1;
		push eax;
		mov ecx, pNpc;
		mov eax, 0x004E6C80;
		call eax;
		pop ecx;
		pop eax;
	}
            
}
//click npc jxsabay
void funcClickNPC(int idNPC,int baseAddress)
{
	__asm {
		push eax;
		push ecx;
		push edx;
		mov eax,0;
		push eax;
		mov eax, 0;
		push eax;
		mov eax, 0;
		push eax;
		mov eax, 0;
		push eax;
		mov eax,idNPC;
		push eax;
		mov edx, 4;
		push edx;
		mov edx, baseAddress;
		push edx;
		mov ecx, 0x008A7654;
		mov eax, 0x004E6C80;
		call eax;
		pop edx;
		pop ecx;
		pop eax;
	}
}
void funcShortMove(int idMap,int X, int Y,int Y2,int baseAddress)
{
	__asm {
		push eax;
		push ecx;
		push edx;
		mov eax, 0;
		push eax;
		mov eax, 0;
		push eax;
		mov eax, idMap;
		push eax;
		mov eax, Y;
		push eax;
		mov eax, X;
		push eax;
		mov eax, Y2;
		push eax;
		mov edx, baseAddress;
		push edx;
		mov ecx, 0x008A7654;
		mov eax, 0x004E6C80;
		call eax;
		pop edx;
		pop ecx;
		pop eax;
	}
}
/* mua item
* 
*/
void funcBuyItem(int itemPos, int param2, int quantity, int param4, int param5){
	_asm{
		push eax;
		push ecx;
		mov eax, param5;
		push eax;
		mov eax, param4;
		push eax;
		mov eax, quantity;
		push eax;
		mov eax, param2;
		push eax;
		mov eax, itemPos;
		push eax;
    	MOV ECX,0x00A5B1B4;
		mov eax,0x00509470;
		CALL eax;
		pop ecx;
		pop eax;
	}
}

/// <summary>
/// bán item
/// </summary>
/// <param name="xitem"></param>
void BanItem(int xitem)
{
                __asm {
                                push eax;
                                push ecx;
                                push xitem;
								mov ecx,0x00A34760;
                                mov eax,0x004F47C0;
                                call eax;
                                pop ecx;
                                pop eax;
                }
}


/// <summary>
/// sử dụng ngựa
/// </summary>
/// <param name="playerAddress"></param>
/// <param name="use"></param>
void funcUseHorse(int playerAddress, int use){
	_asm{
		push eax;
		push ecx;
		push 0;
		push 0;
		push 0;
		push 0;
		push 0;
		mov eax, use;
		push eax;
		mov ecx, playerAddress;
		mov eax, 0x0048B090;
		call eax;
		pop ecx;
		pop eax;
	}
}
/// <summary>
/// chế item
/// </summary>
/// <param name="itemId"></param>
void funcComposeItem(int itemId){ 
	_asm{
		push eax;
		push ecx;
		mov eax, 1;
		push eax;
		mov eax, itemId;
		push eax;
		mov ecx,0x00A34760; 
		mov eax,0x004F40C0;
		call eax;
		pop ecx;
		pop eax;
	}
}
/// <summary>
/// sử dụng item
/// </summary>
/// <param name="xitem"></param>
/// <param name="yitem"></param>
void UseItem(int xitem,int yitem)
{
                __asm {
                                push eax;
                                push ecx;
                                mov eax,xitem;
                                push eax;
                                mov eax,yitem;
                                push eax;
                                mov eax,2;
                                push eax;
                                 mov ecx,0x00A34760;
                                mov eax,0x004F6AF0;
                                call eax;
                                pop ecx;
                                pop eax;
                }
}
/// <summary>
/// hồi sinh
/// </summary>
/// <param name="pra"></param>
/// <param name="mang"></param>
void funcRebirth(int pra,int mang){
  __asm {
                                push eax;
                                push ecx;
                                mov eax,0;
                                push eax;
                                mov eax,3;
                                push eax;
                                mov ecx,mang;
                                mov eax,0x00621080;
                                call eax;
                                pop ecx;
                                pop eax;
        }
}

void funcPickNPutItem(int locationPick, int colPick, int rowPick, int locationPut, int colPut, int rowPut, int ItemLocationAddress){
	_asm{
		push eax;
		push ecx;
		mov eax, rowPut;
		push eax;
		mov eax, colPut;
		push eax;
		mov eax, locationPut;
		push eax;
		mov eax, rowPick;
		push eax;
		mov eax, colPick;
		push eax;
		mov eax, locationPick;
		push eax;
		mov ecx, ItemLocationAddress;
		mov eax, 0x00479CF0;
		call eax;
		pop ecx;
		pop eax;
	}

}
void SelectMenu(int idmenu,int idxmenu){
      __asm {
                                push eax;
                                push ecx;
                                mov eax,idxmenu;
                                push eax;
                                mov ecx,idmenu;
                                mov eax,0x00705710;
                                call eax;
                                pop eax;
                                pop ecx;
        }
}


void LevelUp()
{
   __asm{
        push eax;
        push ecx;
		mov ecx,0x00A5B1B4; 
        mov eax,0x00509530;
        call eax;
        pop ecx;
        pop eax;
   }
}



void Chat(char* szcmd)
{
if(!szcmd) return;	
	__asm
{
		push eax;
		push szcmd;
		mov eax,0x0062E280;// 5D 8B 8C 24 20 01 00 00 5B 5F B8 01 00 00 00 5E 
		call eax;
		add esp,4;
		pop eax;
}	
}
void ChoSauAn(int xitem,int yitem)
{
                __asm {
                                push eax;
                                push ecx;
                                mov eax,xitem;
                                push eax;
                                mov eax,yitem;
                                push eax;
                                mov eax,2;
                                push eax;
                                mov ecx,0x00A5B1B4;
                                mov eax,0x005094D0;
                                call eax;
                                pop ecx;
                                pop eax;
                }
}


void VutItem(int xitem)
{
                __asm {
                                push eax;
                                push ecx;
                                push xitem;
                                mov eax,0x004079F0;
                                call eax;
                                pop ecx;
                                pop eax;
                }
}


void funcBayBan(int chedo) //sai dia chi
{
   __asm{
        push eax;
        push ecx;
        push chedo;
        mov ecx,0x0098E600; //9.0.5 baseaddress
        mov eax,0x0077031C;//9.0.5
        call eax;
        pop ecx;
        pop eax;
   }
}


/////////// tổ đội/////////////////////////////////////
void Group(int var1,int var2, int var3, int PlayerAdd){ 
	_asm{ 
		push eax;
		push ecx;
		push var1;
		push var2;
		push var3;
		mov eax, PlayerAdd;
		push eax;
		mov ecx, 0x00A5B1B4;
		mov eax, 0x00509BF0;
		call eax;
		pop ecx;
		pop eax; 
	} 
}

void LatBai(int Bai) //latbaiphoban
{
        __asm {
                                push eax;
                                push ecx;							
                                push Bai;
								push 0x33;
                                mov ecx, 0x00A34760;
                                mov eax,0x004F8010;
                                call eax;
							    pop ecx;
                                pop eax;
                              
        }
}

void EntityInteractive1(int pra1,int pra2,int pra3,int pNpc1,int pra4,int pra5,int pra6,int pra7,int pNpc) //sai dia chi
{
                __asm {
                        push eax;
                        push ecx;
						push 0;
                        mov eax,pra7;
                        push eax;
                        mov eax,pra6;
                        push eax;
                        mov eax,pra5;
                        push eax;
                        mov eax,pra4;
                        push eax;
                        mov ecx,pNpc1;
                        mov eax,0x004A1880;
					    call eax;
                        mov eax,pra3;
                        push eax;
                        mov eax,pra2;
                        push eax;
                        mov eax,pra1;
                        push eax;
                        mov ecx,pNpc;
                        mov eax,0x0048CDD0;
                        call eax;
                        pop ecx;
                        pop eax;
                }
}
void startGame() 
{
	__asm {
		push edi;
		mov edi, 0x00619F30;
		call edi;
		pop edi;
		
	}
}
void chooseServer(int idcum, int idServer, int base)
{
	__asm {
		push eax;
		push base;
		push idServer;
		push idcum;
		mov ecx, base;
		mov eax, 0x006174A0;
		call eax;
		mov eax, 0x00619F30;
		call eax;
		mov ecx, [0x009574B4];
		mov eax, [ecx];
		call dword ptr[eax + 0x2C];
		add esp, 04;
	}
}
void ResetCall(){
	func_call = 0;
	param_length = 0;
	for (int i = 0; i<10; i++)
		params[i] = 0;
}


void ProcessCall(){
	switch (func_call){
		case FUNC_MOVE_TO:{
			if (param_length == 3)
				funcMoveTo(params[0], params[1], params[2]);
			break;
		}
		case FUNC_ENTITY_INTERACT:{
			EntityInteractive(params[0], params[1], params[2], params[3], params[4], params[5], params[6], params[7]);
			break;
		}
		case FUNC_CLICK_NPC: {
			funcClickNPC(params[0], params[1]);
			break;
		}
		case FUNC_SHORT_MOVE: {
			funcShortMove(params[0], params[1], params[2], params[3], params[4]);
			break;
		}
		/*case FUNC_DIALOG_INTERACT:{
			funcDialogInteractive(params[0], params[1], params[2]);
			break;
		}*/
		case FUNC_BUYITEM:{
			funcBuyItem(params[0], params[1], params[2], params[3], params[4]);
			break;
		}
	  
		case FUNC_USE_HORSE:{
			funcUseHorse(params[0], params[1]);
			break;
		}

		/*case FUNC_MONEY_INTERACT:{
			funcMoneyInteract(params[0], params[1], params[2]);
			break;
		}*/
		case FUNC_COMPOSE_ITEM:{
			funcComposeItem(params[0]);
			break;
		}
	    case FUNC_USE_ITEM:{
	        UseItem(params[0], params[1]);
             break;
		}
		case FUNC_REBIRTH:{
			funcRebirth(params[0], params[1]);
			break;
		}

		case FUNC_PICKPUT:{
			funcPickNPutItem(params[0], params[1], params[2], params[3], params[4], params[5], params[6]);
			break;
		}
		
	   case FUNC_SELECTMENU:{
		SelectMenu(params[0], params[1]);
             break;
		}
	    case FUNC_CHAT:{
      	   Chat(szData);
             break;
		}
	   case FUNC_CHOSAUAN:{
	    ChoSauAn(params[0], params[1]);
             break;
		}
	 	case FUNC_BAYBAN:{
			funcBayBan(params[0]);
			break;

		}	  
	   /* case FUNC_MOITV:{
	    MoiTV(params[0]);
             break;
		}*/
		case FUNC_GROUP:{
			Group(params[0], params[1], params[2],params[3]);
			break;
		}
    	case FUNC_LEVELUP:{
	       LevelUp();
              break;
		}
		case FUNC_VUTITEM:{
	       VutItem(params[0]);
              break;
		}
    	case FUNC_BANITEM:{
	       BanItem(params[0]);
              break;
		}
		case FUNC_LATBAI:{
	       LatBai(params[0]);
              break;
		}
		/*case FUNC_NHATITEM:{
	       NhatItem(params[0]);
              break;
		}*/
	
		/*case FUNC_LATBAI1:{
	       LatBai1(params[0]);
              break;
		}*/
			
		/*case FUNC_CHONSV:{
	       Chonsv(params[0]);
              break;
		 
		}*/
	    case FUNC_CLEAR:{
        	strcpy(szData,"");
             break;
		}

        case FUNC_PHUTHANH:{
        EntityInteractive(0x14, params[0],0 , 0,0,0,0, params[1]);
        break;
	   }

		/*case FUNC_MORUONG:{
	       MoRuong(szData);  
              break;
		}*/
		case FUNC_ENTITY_INTERACT1:{
			EntityInteractive1(params[0], params[1], params[2], params[3],params[4], params[5], params[6], params[7], params[8]);
			break;
		}
		
		case FUNC_START_GAME: {
			startGame();
			break;
		}
		case FUNC_CHOOSE_SERVER: {
			chooseServer(params[0], params[1], params[2]);
			break;
		}
	}   
	ResetCall();
}

LRESULT CALLBACK NewWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_HOOK_CONTROL)
	{
		//Setting Parameters
		ofstream myfile ("C:\\Temps\\atlog.txt", ios::app);
		switch (wParam)
		{
			case cmd_start:{
				ResetCall();
				func_call = lParam;
				if (myfile.is_open())
				{
					myfile << "Receive start command "<<lParam<<".\n";
				}

				break;
			}

			case cmd_sendchar:{
               sprintf(szData,"%s%c",szData,lParam);
                break;
				}
			case cmd_end:{
				ProcessCall();
				if (myfile.is_open())
				{
					myfile << "Receive end command.\n";
				}
				break;
			}
			case cmd_push:{
				params[param_length] = lParam;
				param_length++;
				if (myfile.is_open())
				{
					myfile << "Receive push command "<< lParam<<"\n";
				}
				break;
			}
			default:
				break;
		}
		return 123;
		if (myfile.is_open())
			myfile.close();
	}
	return CallWindowProc(OldWndProc, hWnd, uMsg, wParam, lParam);
}

LRESULT HookProc (int nCode, WPARAM wParam, LPARAM lParam)
{
	HWND hVLWnd = pCW->hwnd;
	HHOOK hHook = (HHOOK)pCW->wParam;
	ofstream myfile ("C:\\Temps\\atlog.txt", ios::app);
	myfile << "Receive hookproc command.\n";
	myfile.close();

	if((pCW->message == WM_HOOKEX) && pCW->lParam)
	{
		UnhookWindowsHookEx(hHook);
		if (bHooked)
			goto END;

		char lib_name[MAX_PATH];
		GetModuleFileName(hDll, lib_name, MAX_PATH);

		if(!LoadLibrary(lib_name))
			goto END;		

		OldWndProc = (WNDPROC)SetWindowLong(hVLWnd, GWL_WNDPROC, (LONG)NewWndProc);
		if(OldWndProc==NULL) {
			FreeLibrary(hDll);
		}
		else
		{
			bHooked = TRUE;
		}
	}
	else if(pCW->message == WM_HOOKEX) 
	{
		UnhookWindowsHookEx(hHook);
		if (!bHooked)
			goto END;
		if(!SetWindowLong(hVLWnd, GWL_WNDPROC, (LONG)OldWndProc))
			goto END;
		FreeLibrary(hDll);
		bHooked = FALSE;
	}
END:
	return CallNextHookEx(hHook, nCode, wParam, lParam);
}


AUTOHOOK_API int __stdcall InjectDll(HWND hWnd)
{	
	if (!IsWindow(hWnd))
		return 0;
	HHOOK hHook = SetWindowsHookEx(WH_CALLWNDPROC,(HOOKPROC)HookProc, hDll, GetWindowThreadProcessId(hWnd,NULL));
	if(hHook==NULL)
		return 0;
	SendMessage(hWnd, WM_HOOKEX, WPARAM(hHook), 1);
	return 1;
}

AUTOHOOK_API int __stdcall UnmapDll(HWND hWnd)
{	
	if (!IsWindow(hWnd))
		return 0;
	HHOOK hHook = SetWindowsHookEx(WH_CALLWNDPROC,(HOOKPROC)HookProc, hDll, GetWindowThreadProcessId(hWnd,NULL));
	if(hHook==NULL)
		return 2;
	SendMessage(hWnd, WM_HOOKEX, (WPARAM)hHook, 0);
	return 1;
}