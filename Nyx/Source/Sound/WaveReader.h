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
#ifndef NYX_CORE_INCLUDED_WAVE_READER_H_
#define NYX_CORE_INCLUDED_WAVE_READER_H_

namespace Nyx {

	///Formatチャンク構造体
	struct FormatChunk
	{
		uchar formatChunkID[4];  ///FMTチャンクID
		uint chunkSize; ///<チャンクサイズ
		ushort formatTag; ///<フォーマットID
		ushort channelNum;///<チャンネル数
		uint   samplingRate; ///<サンプリングレート
		uint   bytesPerSec;//<データ速度
		ushort blockSize; ///<ブロックサイズ
		ushort bitsRate;///< サンプルあたりのビット数
	};

	///データチャンク構造体
	struct DataChunk
	{
		uchar dataChunkID[4];///< データチャンクID
		uint chunkSize;  ///< チャンクサイズ 
	};

	///Waveファイルヘッダ構造体
	struct WaveFileHeader
	{
		uchar riffID[4];  ///< RIFFフォーマットID
		uint fileSize;///< ファイルサイズ
		uchar waveID[4];  ///< WaveファイルID
		FormatChunk formatChunk; ///<フォーマットチャンク
		DataChunk   dataChunk;   ///<データチャンク
	};

	///wavファイルリーダ
	class WaveReader {
	public:
		/**
		* コンストラクタ
		*/
		explicit WaveReader();


		/**
		* コンストラクタ
		* @param const std::wstring& ファイル名
		*/
		explicit WaveReader(const std::wstring& fileName);

	
		
		/**
		* ファイルからWaveファイルを読み込みます
		* @param std::wstring wavファイル名
		*/
		void ReadFromFile(const std::wstring& fileName);


		/**
		* Waveファイルヘッダの取得します
		* @return const WaveFileHeader& WAVEファイルヘッダ
		*/
		const WaveFileHeader& GetFileHeader() const;
		

		/**
		* Waveデータを取得します
		* @return std::shared_ptr<char> WAVEデータ
		*/
		const std::shared_ptr<char> GetWaveData() const;
	private:
		ulong cursorPos_;
		std::wstring   fileName_;        ///< ファイル名
		WaveFileHeader waveHeader_;      ///<Waveファイルヘッダ
		std::shared_ptr<char> waveData_; ///<Waveデータ
	};
}
#endif
