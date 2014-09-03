#ifndef NYX_CORE_INCLUDED_SQLITE3_DATABASE_H_
#define NYX_CORE_INCLUDED_SQLITE3_DATABASE_H_
#include "Sqlite3Fwd.h"
#include "Database/RecordSet.h"

namespace nyx
{
	class sqlite3_database
	{
	public:

		/**
		 * �R���X�g���N�^
		 */
		sqlite3_database();

		/**
		 * �R���X�g���N�^
		 * @param const std::wstring& dbName
		 */
		sqlite3_database(const std::wstring& dbName);

		/**
		 * �f�X�g���N�^
		 */
		~sqlite3_database();

		/**
		 * �g�����U�N�V�������J�n���܂�
		 */
		void begin_transaction();


		/**
		 * �g�����U�N�V���������[���o�b�N���܂�
		 */
		void rollback_transaction();


		/**
		 * �g�����U�N�V�������R�~�b�g���܂�
		 */

		void commit_transaction();
	
		/**
		 * �f�[�^�x�[�X���I�[�v������
		 * @param const std::wstring& dbName
		 */
		bool open(const std::wstring& dbName);

		/**
		 * �f�[�^�x�[�X�����
		 */
		void close();

		/**
		*  �N�G���������s���܂��D
		* const std::wstring& query
		*/
		record_set  execute(const std::wstring& query);

	private:
		sqlite3* db_;
		sqlite3_stmt * statement_;
	};
}

#endif