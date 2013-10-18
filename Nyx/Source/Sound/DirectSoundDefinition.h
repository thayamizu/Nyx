#ifndef NYX_CORE_INCLUDED_DIRECTSOUND_DEFINITION_H_
#define NYX_CORE_INCLUDED_DIRECTSOUND_DEFINITION_H_
#include "PCH/PCH.h"

//--------------------------------------------------------------
#include <boost/intrusive_ptr.hpp>
//Direct Sound
#define DIRECTSOUND_VERSION 0x0900
#include <dsound.h> 
#include <d3dx9.h>
#pragma comment( lib, "dsound.lib")

typedef boost::intrusive_ptr< IDirectSound8 >           DirectSoundPtr;               ///< DirectSoudオブジェクト
typedef boost::intrusive_ptr< IDirectSoundBuffer >      DirectSoundPrimaryBufferPtr;  ///< DirectSoudプライマリバッファ
typedef boost::intrusive_ptr< IDirectSoundBuffer8 >     DirectSoundBufferPtr;         ///< DirectSoundセカンダリーバッファー
typedef boost::intrusive_ptr< IDirectSound3DBuffer8 >   DirectSound3DBufferPtr;       ///< DirectSound3Dセカンダリーバッファー
typedef boost::intrusive_ptr< IDirectSound3DListener8 > DirectSound3DListenerPtr;     ///< DirectSound3D Listener

#endif