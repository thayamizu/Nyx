#include "PCH/PCH.h"
#include "sqlite3.h"
#include "Sqlite3Database.h"


namespace nyx
{
	std::string get_column_type(int type_code) {
		std::string column_type = "";

		switch (type_code)
		{
		case  SQLITE_INTEGER:
			column_type = "INTEGER"; break;
		case  SQLITE_FLOAT:
			column_type = "FLOAT"; break;
		case  SQLITE_TEXT:
			column_type = "TEXT"; break;
		case  SQLITE_BLOB:
			column_type = "BLOB"; break;
		case  SQLITE_NULL:
			column_type = "NULL"; break;
		default:
			throw std::runtime_error("sqlite3 have no such field type.");

		}
		return column_type;
	}
	//----------------------------------------------------------------------------------
	//  [9/2/2014 hayamizu]
	sqlite3_database::sqlite3_database()
		:db_(NULL), statement_(NULL)
	{

	}
	sqlite3_database::sqlite3_database(const std::wstring& dbName)
		:db_(NULL), statement_(NULL)
	{
		open(dbName);
	}

	//----------------------------------------------------------------------------------
	//  [9/2/2014 hayamizu]
	sqlite3_database::~sqlite3_database()
	{
		
	}


	//----------------------------------------------------------------------------------
	//  [9/2/2014 hayamizu]
	bool sqlite3_database::open(const std::wstring& dbName) 
	{
		int result = sqlite3_open16(dbName.c_str(), &db_);
		if (result != SQLITE_OK) {
			throw std::runtime_error(::sqlite3_errmsg(db_));
		}

		return (result == SQLITE_OK);
	}


	//----------------------------------------------------------------------------------
	//  [9/2/2014 hayamizu]
	void sqlite3_database::begin_transaction() {
		int ret = sqlite3_exec(db_, "BEGIN;", NULL, NULL, NULL);
		if (ret != SQLITE_OK) {
			throw std::runtime_error(sqlite3_errmsg(db_));
		}
	}


	//----------------------------------------------------------------------------------
	//  [9/2/2014 hayamizu]
	void sqlite3_database::commit_transaction() 
	{
		int ret = sqlite3_exec(db_, "COMMIT;", NULL, NULL, NULL);
		if (ret != SQLITE_OK) {
			throw std::runtime_error(sqlite3_errmsg(db_));
		}
	}


	//----------------------------------------------------------------------------------
	//  [9/2/2014 hayamizu]
	void sqlite3_database::rollback_transaction()
	{
		int ret = sqlite3_exec(db_, "ROLLBACK;", NULL, NULL, NULL);
		if (ret != SQLITE_OK) {
			throw std::runtime_error(sqlite3_errmsg(db_));
		}
	}

	//----------------------------------------------------------------------------------
	//  [9/2/2014 hayamizu]
	void sqlite3_database::close() 
	{
		if (statement_ != NULL) {
			sqlite3_finalize(statement_);
		}
		if (db_ != NULL) {
			sqlite3_close(db_);
		}
	}


	//----------------------------------------------------------------------------------
	//  [9/2/2014 hayamizu]
	record_set sqlite3_database::execute(const std::wstring& query)
	{
		auto rs = record_set();
		auto ret = sqlite3_prepare16_v2(db_, query.c_str(), -1, &statement_, NULL);
		if (ret != SQLITE_OK) {
			throw std::runtime_error(sqlite3_errmsg(db_));
		}

		if (statement_ == NULL) {
			return rs; //if invalid query, return empty record set
		}

		// get column number
		auto columns = sqlite3_column_count(statement_);
		
		while (true) {
			detail::record rc;

			ret = sqlite3_step(statement_);
			if (ret == SQLITE_ERROR) { // raise any error
				throw std::runtime_error(sqlite3_errmsg(db_));
			}
			else if (ret == SQLITE_BUSY) { // can't lock database
				throw std::runtime_error(sqlite3_errmsg(db_));
			}
			else if (ret == SQLITE_DONE) {
				break;
			}
			else if (ret == SQLITE_ROW) {
				for (int i = 0; i < columns; ++i) {
					std::string name = (char*)sqlite3_column_name(statement_, i);
					std::string type = get_column_type(sqlite3_column_type(statement_, i));
					std::string value =(char*)sqlite3_column_text(statement_, i);
					rc.push_back(detail::field(name, type, value));
				}
			
				rs.push_back(rc);
			}
		}

		return rs;
	}
}