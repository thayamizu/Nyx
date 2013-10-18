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

typedef boost::intrusive_ptr< IDirectSound8 >           DirectSoundPtr;               ///< DirectSoud�I�u�W�F�N�g
typedef boost::intrusive_ptr< IDirectSoundBuffer >      DirectSoundPrimaryBufferPtr;  ///< DirectSoud�v���C�}���o�b�t�@
typedef boost::intrusive_ptr< IDirectSoundBuffer8 >     DirectSoundBufferPtr;         ///< DirectSound�Z�J���_���[�o�b�t�@�[
typedef boost::intrusive_ptr< IDirectSound3DBuffer8 >   DirectSound3DBufferPtr;       ///< DirectSound3D�Z�J���_���[�o�b�t�@�[
typedef boost::intrusive_ptr< IDirectSound3DListener8 > DirectSound3DListenerPtr;     ///< DirectSound3D Listener

#endif