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
#include <boost/container/flat_map.hpp>
typedef boost::intrusive_ptr< IDirectSound8 >           dsound_ptr;               ///< DirectSoud�I�u�W�F�N�g
typedef boost::intrusive_ptr< IDirectSoundBuffer >      dsound_primary_buffer_ptr;  ///< DirectSoud�v���C�}���o�b�t�@
typedef boost::intrusive_ptr< IDirectSoundBuffer8 >     dsound_buffer_ptr;         ///< DirectSound�Z�J���_���[�o�b�t�@�[
typedef boost::intrusive_ptr< IDirectSound3DBuffer8 >   dsound_3d_buffer_ptr;       ///< DirectSound3D�Z�J���_���[�o�b�t�@�[
typedef boost::intrusive_ptr< IDirectSound3DListener8 > dsound_3d_listener_ptr;     ///< DirectSound3D Listener

#endif