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
		 * コンストラクタ
		 */
		sqlite3_database();

		/**
		 * コンストラクタ
		 * @param const std::wstring& dbName
		 */
		sqlite3_database(const std::wstring& dbName);

		/**
		 * デストラクタ
		 */
		~sqlite3_database();

		/**
		 * トランザクションを開始します
		 */
		void begin_transaction();


		/**
		 * トランザクションをロールバックします
		 */
		void rollback_transaction();


		/**
		 * トランザクションをコミットします
		 */

		void commit_transaction();
	
		/**
		 * データベースをオープンする
		 * @param const std::wstring& dbName
		 */
		bool open(const std::wstring& dbName);

		/**
		 * データベースを閉じる
		 */
		void close();

		/**
		*  クエリ式を実行します．
		* const std::wstring& query
		*/
		record_set  execute(const std::wstring& query);

	private:
		sqlite3* db_;
		sqlite3_stmt * statement_;
	};
}

#endif