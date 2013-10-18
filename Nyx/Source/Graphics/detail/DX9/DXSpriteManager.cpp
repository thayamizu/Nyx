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
#include "PCH/PCH.h"
#include "Debug/Assert.h"
#include "Debug/DebugOutput.h"

#include "Graphics/DX9/DirectGraphicsDevice.h"
#include "Graphics/DX9/DXSprite.h"
#include "Graphics/DX9/DXSpriteManager.h"
#include "IO/PackedFile.h"

namespace Nyx {
	namespace DX9 {

		using std::unique_ptr;
		using Nyx::PackedFile;
		const int DXSpriteManager::defaultCapacity = 255;

		//-----------------------------------------------------------------------------------------
		//
		DXSpriteManager::DXSpriteManager() {
			spriteContainer.reserve(defaultCapacity);
		}

		//-----------------------------------------------------------------------------------------
		//
		DXSpriteManager::DXSpriteManager(int capacity) {
			spriteContainer.reserve(capacity);
		}

		//-----------------------------------------------------------------------------------------
		//
		DXSpriteManager::~DXSpriteManager() 
		{
			Release();
		}

		//-----------------------------------------------------------------------------------------
		//
		bool DXSpriteManager::Load(DirectGraphicsDevice& device, std::wstring fileName, int width, int height, int cw, int ch) {
			//最後に.が見つかった場所を探す(ファイル名に.が含まれている場合の対策)
			int pos = fileName.find_last_of (L".");
			if (pos == std::wstring::npos) {
				return false;
			}
			//拡張子のみを取得する
			std::wstring ext = fileName.substr(pos+1, fileName.size());

			//ロード
			if (ext== L"pack") {
				LoadFromPackedFile(device, fileName, width, height, cw, ch);
			}
			else if (ext == L"bmp" || ext == L"jpg" || ext == L"jpeg"|| ext==L"png") {
				LoadFromFile(device, fileName, width, height, cw, ch);
			}
			else {
				return false;
			}

			return true;
		}
		//-----------------------------------------------------------------------------------------
		//
		void DXSpriteManager::Restore(DirectGraphicsDevice& device) {
			int size = spriteContainer.size();

			for (int i=0; i < size; i++) {
				spriteContainer[i]->CreateSprite(device);
				spriteContainer[i]->Restore();
			}
		}


		//-----------------------------------------------------------------------------------------
		//
		void DXSpriteManager::Release() {
			Clear();
		}
		//-----------------------------------------------------------------------------------------
		//
		int DXSpriteManager::Add(DXSprite* s) {
			if (s ==NULL) return -1;

			spriteContainer.push_back(s);

			return spriteContainer.size();
		}
		//-----------------------------------------------------------------------------------------
		//
		void DXSpriteManager::Clear() {
			int size=spriteContainer.size();
			for (int i=0; i< size; i++) {
				SafeDelete(spriteContainer[i]);
			}

			spriteContainer.clear();
		}

		//-----------------------------------------------------------------------------------------
		//
		DXSprite* DXSpriteManager::GetSprite(size_t index){
			if (index < 0 && index < spriteContainer.size()) {
				return NULL;
			}

			return spriteContainer[index];
		}

		//-----------------------------------------------------------------------------------------
		//
		bool DXSpriteManager::OnResetDevice() {
			int size = spriteContainer.size();
			for (int i=0; i<size; i++) {
				HRESULT hr = spriteContainer[i]->OnResetDevice();
				if (FAILED(hr)) {
					return false;
				}
			}
			return true;
		}
		//----------------------------------------------------------------------------------------------
		//
		bool DXSpriteManager::OnLostDevice() {
			int size = spriteContainer.size();
			for (int i=0; i<size; i++) {
				HRESULT hr = spriteContainer[i]->OnLostDevice();
				if (FAILED(hr)) {
					return false;
				}
			}
			return true;
		}
		//-----------------------------------------------------------------------------------------
		//
		bool DXSpriteManager::LoadFromFile(DirectGraphicsDevice& device, std::wstring fileName, int w, int h, int cw, int ch) {
			spriteContainer.push_back(new DXSprite(device, fileName, w, h, cw, ch ));

			return true;
		}

		//-----------------------------------------------------------------------------------------
		//
		bool DXSpriteManager::LoadFromPackedFile(DirectGraphicsDevice& device, std::wstring fileName, int w, int h, int cw, int ch) {
			unique_ptr<PackedFile> pack = unique_ptr<PackedFile>(new PackedFile(fileName.c_str()));
			int n = pack->GetFileNum();//パッキングされたファイルの数を取得
			for (int i=0; i < n; i++) {//一括で読んでまえ
				spriteContainer.push_back(new DXSprite(device, pack->GetFileData(i), pack->GetFileSize(i) , w, h, cw, ch));
			}
			return true;
		}
	}
}