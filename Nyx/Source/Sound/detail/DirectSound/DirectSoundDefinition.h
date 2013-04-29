#ifndef NYX_CORE_INCLUDED_DIRECTSOUND_DEFINITION_H_
#define NYX_CORE_INCLUDED_DIRECTSOUND_DEFINITION_H_
#include "PCH/PCH.h"

//--------------------------------------------------------------
//Direct Sound
#define DIRECTSOUND_VERSION 0x0900
#include <dsound.h> 
#pragma comment( lib, "dsound.lib")

typedef boost::intrusive_ptr< IDirectSound >           DirectSoundPtr;          ///< DirectSoudオブジェクト
typedef boost::intrusive_ptr< IDirectSoundBuffer >     DirectSoundBufferPtr;    ///< DirectSoundセカンダリーバッファー
typedef boost::intrusive_ptr< IDirectSound3DBuffer >   DirectSound3DBufferPtr;  ///< DirectSound3Dセカンダリーバッファー
typedef boost::intrusive_ptr< IDirectSound3DListener > DirectSound3DListenerPtr;///< DirectSound3D Listener

#endif