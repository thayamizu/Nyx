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
			//�Ō��.�����������ꏊ��T��(�t�@�C������.���܂܂�Ă���ꍇ�̑΍�)
			int pos = fileName.find_last_of (L".");
			if (pos == std::wstring::npos) {
				return false;
			}
			//�g���q�݂̂��擾����
			std::wstring ext = fileName.substr(pos+1, fileName.size());

			//���[�h
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
			int n = pack->GetFileNum();//�p�b�L���O���ꂽ�t�@�C���̐����擾
			for (int i=0; i < n; i++) {//�ꊇ�œǂ�ł܂�
				spriteContainer.push_back(new DXSprite(device, pack->GetFileData(i), pack->GetFileSize(i) , w, h, cw, ch));
			}
			return true;
		}
	}
}