#ifndef NYX_CORE_INCLUDED_DIRECTSOUND_DEFINITION_H_
#define NYX_CORE_INCLUDED_DIRECTSOUND_DEFINITION_H_

//--------------------------------------------------------------
//Direct Sound
#define DIRECTSOUND_VERSION 0x0900
#include <dsound.h> 
#pragma comment( lib, "dsound.lib")


typedef LPDIRECTSOUND8 DirectSound;				//DirectSoudオブジェクト
typedef LPDIRECTSOUNDBUFFER DirectSoundBuffer; //DirectSoundセカンダリーバッファー
typedef LPDIRECTSOUND3DBUFFER DirectSound3DBuffer; //DirectSound3Dセカンダリーバッファー
typedef LPDIRECTSOUND3DLISTENER DirectSound3DListener;//DirectSound3D Listener


#endif