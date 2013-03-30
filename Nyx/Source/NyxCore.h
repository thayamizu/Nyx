/********************************************************************************
*
*  The MIT License
*
* Copyright (c)2010 -  t.hayamizu
*
*以下に定める条件に従い、本ソフトウェアおよび関連文書のファイル（以下「ソフトウェア」）の複製を取得するすべての人に対し、ソフトウェ
*アを無制限に扱うことを無償で許可します。これには、ソフトウェアの複製を使用、複写、変更、結合、掲載、頒布、サブライセンス、および/ま
*たは販売する権利、およびソフトウェアを提供する相手に同じことを許可する権利も無制限に含まれます。
*
*上記の著作権表示および本許諾表示を、ソフトウェアのすべての複製または重要な部分に記載するものとします。
*
*ソフトウェアは「現状のまま」で、明示であるか暗黙であるかを問わず、何らの保証もなく提供されます。ここでいう保証とは、商品性、特定の目*的への適合性、および権利非侵害についての保証も含みますが、それに限定されるものではありません。 作者または著作権者は、契約行為、不法
*行為、またはそれ以外であろうと、ソフトウェアに起因または関連し、あるいはソフトウェアの使用またはその他の扱いによって生じる一切の請
*求、損害、その他の義務について何らの責任も負わないものとします。 
********************************************************************************/
#ifndef NYX_CORE_INCLUDED_NYX_CORE_ALL_H_
#define NYX_CORE_INCLUDED_NYX_CORE_ALL_H_

#include "PCH/PCH.h"

// デバッグ
#include "Debug/Assert.h"
#include "Debug/DebugOutput.h"
#include "Debug/MemoryChecker.h"

///GUI
//GUIはインタフェース化しておくこと
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

// ファイル入出力
#include "IO/IFile.h"
#include "IO/File.h"
#include "IO/Logger.h"
#include "IO/PackedFile.h"

// スレッド
#include "Thread/CriticalSection.h"
#include "Thread/LockObject.h"
#include "Thread/Thread.h"

// プリミティブオブジェクト
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

///グラフィックス
//さて、グラフィックスシステムを実装していこうか
/*
DirectX or OpenGL+SDLを状況に応じて選べるように設計したい。
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

///サウンド
#include "Sound/IAudioBuffer.h"
#include "Sound/IAudioManager.h"
#include "Sound/AudioManager.h"
#include "Sound/WaveReader.h"

///入力機器 
#include "Input/IKeyBase.h"
#include "Input/Keyboard.h"
#include "Input/Mouse.h"
#include "Input/Joystick.h"

//動画再生
#include "Movie/IMoviePlayer.h"
#include "Movie/DSMoviePlayer.h"
#include "Movie/MoviePlayer.h"

// タイマー
#include "Timer/ITimer.h"
#include "Timer/Timer.h"
#include "Timer/FixedTimer.h"
#include "Timer/FPSTimer.h"
#include "Timer/PerformanceTimer.h"


//ユーティリティ
#include "Utility/Common.h"

//オブジェクト
#include "Object/Delegate.h"
#include "Object/NonCopyable.h"
#include "Object/IResource.h"
#include "Object/IResourceManager.h"


#endif
