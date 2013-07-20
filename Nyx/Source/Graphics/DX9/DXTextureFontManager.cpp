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
#include "Graphics/ITextureFont.h"
#include "Graphics/DX9/DXTextureFont.h"
#include "Graphics/DX9/DXTextureFontManager.h"
#include "Primitive/Matrix44.h"
#include "Primitive/Color4.h"
#include "Thread/Thread.h"
namespace Nyx {
	namespace DX9 {

		//-----------------------------------------------------------------------------------------
		//
		const int DXTextureFontManager::defaultTransparent = 255;

		//-----------------------------------------------------------------------------------------
		//
		DXTextureFontManager::DXTextureFontManager() 
			:fontSize(32), fontName(L"�l�r ����"),fontColor(Color4c::White), textSpeed(10),rowNum(12), columnNum(3),cursorRead(0),
			transparent(defaultTransparent)
		{
			textstring.reserve(255);
			container.reserve(255);
			charInfo.reserve(255);
		}

		//-----------------------------------------------------------------------------------------
		//
		DXTextureFontManager::DXTextureFontManager(int capacity, std::wstring font, int size,Color4c color, int speed)
			:fontName(font),fontSize(size), fontColor(color), textSpeed(speed),rowNum(12), columnNum(3),cursorRead(0),
			transparent(defaultTransparent)
		{
			textstring.reserve(capacity);
			container.reserve(capacity);
			charInfo.reserve(capacity);
		}

		//-----------------------------------------------------------------------------------------
		//
		DXTextureFontManager::~DXTextureFontManager()
		{

			Release();
		}

		//-----------------------------------------------------------------------------------------
		//
		int DXTextureFontManager::Load(DirectGraphicsDevice& device)
		{
			Release();	
			CharInfo info={false, 0};
			//�Z�b�g���Ă��镶���񂩂�t�H���g���쐬
			uint n = textLength;//rowNum*columnNum; //�ǂݍ��ޕ�����
			uint pos;
			for (pos=0; pos < n; pos++) {
				if ((cursorRead + pos) >= textstring.size()) {break;}
				DXTextureFont * font = new DXTextureFont();
				Assert(font != NULL);
				font->Create(device, fontSize, &textstring[cursorRead + pos], fontName);


				charInfo.push_back(info);
				container.push_back(font);

			}
			//�ŏ��̕�����`��ς݂ɐݒ�
			if (pos != 0) {
				charInfo[0].isDrawed = true;
				charInfo[0].transparency = 255;
			}

			//�ǂݍ��񂾈ʒu���L��
			cursorRead += pos;

			//���[�h�����v�f��Ԃ�
			return pos;
		}

		//-----------------------------------------------------------------------------------------
		//
		void DXTextureFontManager::Release() {
			int size= container.size();
			for (int i=0; i < size; ++i) {
				if (container[i] != NULL ) {
					SafeDelete(container[i]);
				}
			}

			container.clear();
			charInfo.clear();
		}

		//-----------------------------------------------------------------------------------------
		//
		bool DXTextureFontManager::OnResetDevice() {
			int size = container.size();
			for (int i=0; i<size; i++) {
				HRESULT hr = container[i]->OnResetDevice();
				if (FAILED(hr)) {
					return false;
				}
			}
			return true;
		}

		//-----------------------------------------------------------------------------------------
		//
		bool DXTextureFontManager::OnLostDevice() {
			int size = container.size();
			for (int i=0; i<size; i++) {
				HRESULT hr = container[i]->OnLostDevice();
				if (FAILED(hr)) {
					return false;
				}
			}
			return true;
		}

		//-----------------------------------------------------------------------------------------
		//
		void DXTextureFontManager::Render(int index, float x, float y, float z,  float sx, float sy, float angle)
		{
			Matrix44 world;
			world.Identity();
			Matrix44::SetTransform(&world, sx,sy, 1, 0, 0,angle, x, y, z);

			fontColor.a = charInfo[index].transparency;
			container[index]->Render(world, fontColor);
		}

		//-----------------------------------------------------------------------------------------
		//
		void DXTextureFontManager::RenderAll(float x, float y, float z,  float sx, float sy, float angle)
		{	
			float startX =x;

			for (int i=0; i < columnNum; i++) {
				for (int j=0; j< rowNum; j++) {
					size_t n = i*rowNum+j;
					if (n > textLength) {return;}
					if (n >= charInfo.size()) {
						return;
					}
					if (n > 0) {
						//��O�̕������`��ς݂ł���Ȃ�A���ɕ`�悷�镶���̓����x��������������
						if (charInfo[n-1].isDrawed) {
							//�����x�������Ă���
							charInfo[n].transparency += transparent/textSpeed;
							if (charInfo[n].transparency >= transparent/*Nyx::Limits::UCharMax/2*/) {
								charInfo[n].transparency=transparent;/*Nyx::Limits::UCharMax/2;*/
								charInfo[n].isDrawed=true;
							}
						}
					}

					Render(n, x, y, z, sx, sy, angle);
					x += fontSize;
				}
				y += fontSize;; 
				x = startX;
			}

			/*Matrix44 world = Matrix44::Unit;
			int startX = x;
			int startY = y;
			for (int i=0, cnt=0; i < container.size(); ++i) {
			world=Matrix44::Unit;
			DXTextureFont* font = container[i];

			if (textstring[i] == '\n') {
			x = startX- font->GetWidth();
			y = startY+font->GetHeight();
			cnt = 0;
			continue;
			}else {
			x=startX + cnt*font->GetWidth();
			++cnt;
			}
			Matrix44::Transform(&world, sx, sy, 1, 0, 0, angle,  x, y, z);
			font->Render(world, Color4c::White);
			}*/
		}

		//-----------------------------------------------------------------------------------------
		//
		void DXTextureFontManager::SetText(std::wstring text) {
			//textstring���N���A
			textstring = L"";
			textstring.clear();


			textstring = text;
			cursorRead = 0;
		}

		void DXTextureFontManager::SetTextLength(int len) {
			textLength = len;
		}

		int DXTextureFontManager::GetTextLength() const{
			return textLength;
		}
		//-----------------------------------------------------------------------------------------
		//
		std::wstring DXTextureFontManager::GetText() const {
			return textstring;
		}

		//-----------------------------------------------------------------------------------------
		//
		void DXTextureFontManager::SetFontSize(int size) {
			cursorRead = 0;
			fontSize = size;
		}

		//-----------------------------------------------------------------------------------------
		//
		int DXTextureFontManager::GetFontSize() const
		{
			return fontSize;
		}

		//-----------------------------------------------------------------------------------------
		//
		void DXTextureFontManager::SetFontColor(Color4c color) {
			fontColor = color;
		}

		//-----------------------------------------------------------------------------------------
		//
		Color4c DXTextureFontManager::GetFontColor() 
			const 
		{
			return fontColor;
		}

		//-----------------------------------------------------------------------------------------
		//
		void DXTextureFontManager::AdjustRowAndColumn(int width, int height) {

			//�}�[�W���͖������邱�Ƃɂ���
			//width -= margin * 2;//�E�[�ƍ��[�����Ȃ̂�

			columnNum = height/fontSize;
			rowNum = width/fontSize;

			SetTextLength(columnNum * rowNum);
		}

		//-----------------------------------------------------------------------------------------
		//
		void DXTextureFontManager::SetRow(int n) {
			rowNum = n;
		}

		//-----------------------------------------------------------------------------------------
		//
		int DXTextureFontManager::GetRow() 
			const {
				return rowNum;
		}

		//-----------------------------------------------------------------------------------------
		//
		void DXTextureFontManager::SetColumn(int n) {
			columnNum = n;
		}

		//-----------------------------------------------------------------------------------------
		//
		int DXTextureFontManager::GetColumn() 
			const
		{
			return columnNum;
		}

		//-----------------------------------------------------------------------------------------
		//
		void DXTextureFontManager::SetSpeed(int s) {
			if (s <= 0 ) {s = 1;}
			textSpeed = s;
		}

		//-----------------------------------------------------------------------------------------
		//
		int DXTextureFontManager::GetSpeed() 
			const 
		{
			return textSpeed;
		}

		//-----------------------------------------------------------------------------------------
		//
		void DXTextureFontManager::SetTransparent(int t) {
			if (t <= 0 ) {t = 1;}
			transparent = t;
		}

		//-----------------------------------------------------------------------------------------
		//
		int DXTextureFontManager::GetTransparent() 
			const 
		{
			return transparent;
		}
	}
}