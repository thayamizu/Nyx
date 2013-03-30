/********************************************************************************
*
*  The MIT License
*
* Copyright (c)2010 -  t.hayamizu
*
*�ȉ��ɒ�߂�����ɏ]���A�{�\�t�g�E�F�A����ъ֘A�����̃t�@�C���i�ȉ��u�\�t�g�E�F�A�v�j�̕������擾���邷�ׂĂ̐l�ɑ΂��A�\�t�g�E�F
*�A�𖳐����Ɉ������Ƃ𖳏��ŋ����܂��B����ɂ́A�\�t�g�E�F�A�̕������g�p�A���ʁA�ύX�A�����A�f�ځA�Еz�A�T�u���C�Z���X�A�����/��
*���͔̔����錠���A����у\�t�g�E�F�A��񋟂��鑊��ɓ������Ƃ������錠�����������Ɋ܂܂�܂��B
*
*��L�̒��쌠�\������і{�����\�����A�\�t�g�E�F�A�̂��ׂĂ̕����܂��͏d�v�ȕ����ɋL�ڂ�����̂Ƃ��܂��B
*
*�\�t�g�E�F�A�́u����̂܂܁v�ŁA�����ł��邩�Öقł��邩���킸�A����̕ۏ؂��Ȃ��񋟂���܂��B�����ł����ۏ؂Ƃ́A���i���A����̖�*�I�ւ̓K�����A����ь�����N�Q�ɂ��Ă̕ۏ؂��܂݂܂����A����Ɍ��肳�����̂ł͂���܂���B ��҂܂��͒��쌠�҂́A�_��s�ׁA�s�@
*�s�ׁA�܂��͂���ȊO�ł��낤�ƁA�\�t�g�E�F�A�ɋN���܂��͊֘A���A���邢�̓\�t�g�E�F�A�̎g�p�܂��͂��̑��̈����ɂ���Đ������؂̐�
*���A���Q�A���̑��̋`���ɂ��ĉ���̐ӔC������Ȃ����̂Ƃ��܂��B 
********************************************************************************/
#ifndef NYX_CORE_INCLUDED_NYX_CORE_ALL_H_
#define NYX_CORE_INCLUDED_NYX_CORE_ALL_H_

#include "PCH/PCH.h"

// �f�o�b�O
#include "Debug/Assert.h"
#include "Debug/DebugOutput.h"
#include "Debug/MemoryChecker.h"

///GUI
//GUI�̓C���^�t�F�[�X�����Ă�������
#include "GUI/IControl.h"
#include "GUI/ICheckBox.h"
#include "GUI/IDispatcher.h"
#include "GUI/IPushButton.h"
#include "GUI/IRadioButton.h"
#include "GUI/IListBox.h"
#include "GUI/IWindow.h"
#include "GUI/PushButton.h"
#include "GUI/CheckBox.h"
#include "GUI/ListBox.h"
#include "GUI/RadioButton.h"
#include "GUI/Window.h"
#include "GUI/Dispatcher.h"

// �t�@�C�����o��
#include "IO/IFile.h"
#include "IO/File.h"
#include "IO/Logger.h"
#include "IO/PackedFile.h"

// �X���b�h
#include "Thread/CriticalSection.h"
#include "Thread/LockObject.h"
#include "Thread/Thread.h"

// �v���~�e�B�u�I�u�W�F�N�g
#include "Primitive/Color3c.h"
#include "Primitive/Color4c.h"
#include "Primitive/Color3f.h"
#include "Primitive/Color4f.h"
#include "Primitive/Matrix33.h"
#include "Primitive/Matrix44.h"
#include "Primitive/Plane.h"
#include "Primitive/Point2f.h"
#include "Primitive/Point2i.h"
#include "Primitive/Point3f.h"
#include "Primitive/Point3i.h"
#include "Primitive/Quaternion.h"
#include "Primitive/Rect2f.h"
#include "Primitive/Rect2i.h"
#include "Primitive/Vector2.h"
#include "Primitive/Vector3.h"
#include "Primitive/Vector4.h"

///�O���t�B�b�N�X
//���āA�O���t�B�b�N�X�V�X�e�����������Ă�������
/*
DirectX or OpenGL+SDL���󋵂ɉ����đI�ׂ�悤�ɐ݌v�������B
class Sprite;
class Billboard;
class Plane;
class ISceneNode;
class Frustom;
class SceneNodeProperty;
class RenderPass;
class SceneNode;
struct AlphaSceneNode;
class SceneGraphManager;
class CameraNode;
class SkyNode;
class MeshNode;
class RootNode;
class Mesh;
class SkinMesh;
*/
#include "Graphics/Camera.h"
#include "Graphics/IAnimationController.h"
#include "Graphics/IGraphicsDevice.h"
#include "Graphics/IMesh.h"
#include "Graphics/ISprite.h"
#include "Graphics/ITexture.h"
#include "Graphics/ITextureFont.h"
#include "Graphics/GDI/Pen.h"
#include "Graphics/GDI/Font.h"
#include "Graphics/GDI/DIBitmap.h"
#include "Graphics/DX9/DirectGraphicsDevice.h"
#include "Graphics/DX9/DXSprite.h"
#include "Graphics/DX9/DXSpriteManager.h"
#include "Graphics/DX9/DXTextureFont.h"
#include "Graphics/DX9/DXTextureFontManager.h"
#include "Graphics/DX9/XAnimationController.h"
#include "Graphics/DX9/XAnimationMesh.h"
#include "Graphics/DX9/XMesh.h"
#include "Graphics/DX9/XStaticMesh.h"

///�T�E���h
#include "Sound/IAudioBuffer.h"
#include "Sound/IAudioManager.h"
#include "Sound/AudioManager.h"
#include "Sound/WaveReader.h"

///���͋@�� 
#include "Input/IKeyBase.h"
#include "Input/Keyboard.h"
#include "Input/Mouse.h"
#include "Input/Joystick.h"

//����Đ�
#include "Movie/IMoviePlayer.h"
#include "Movie/DSMoviePlayer.h"
#include "Movie/MoviePlayer.h"

// �^�C�}�[
#include "Timer/ITimer.h"
#include "Timer/Timer.h"
#include "Timer/FixedTimer.h"
#include "Timer/FPSTimer.h"
#include "Timer/PerformanceTimer.h"


//���[�e�B���e�B
#include "Utility/Common.h"

//�I�u�W�F�N�g
#include "Object/Delegate.h"
#include "Object/NonCopyable.h"
#include "Object/IResource.h"
#include "Object/IResourceManager.h"


#endif
