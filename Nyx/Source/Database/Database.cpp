#include "PCH/PCH.h"
#include "Debug/Assert.h"
#include "Database/Database.h"
#include "Database/Sqlite3Database.h"

namespace nyx
{ 
	//----------------------------------------------------------------------------------
	//  [9/2/2014 hayamizu]
	database::database()
		:db_(new sqlite3_database())
	{

	}

	//----------------------------------------------------------------------------------
	//  [9/2/2014 hayamizu]
	database::database(const std::wstring& dbName)
		: db_(new sqlite3_database(dbName))
	{

	}

	//----------------------------------------------------------------------------------
	//  [9/2/2014 hayamizu]
	database::~database() 
	{
		db_->close();
	}
	
	//----------------------------------------------------------------------------------
	//  [9/2/2014 hayamizu]
	bool database::open(const std::wstring& dbName)
	{
		NYX_ASSERT(db_ != nullptr);
		db_->open(dbName);
	}

	//----------------------------------------------------------------------------------
	//  [9/2/2014 hayamizu]
	void database::close()
	{
		NYX_ASSERT(db_ != nullptr);
		db_->close();
	}

	void database::begin_transaction()
	{
		db_->begin_transaction();
	}
	void database::commit_transaction()
	{
		db_->commit_transaction();
	}

	void database::rollback_transaction()
	{
		db_->rollback_transaction();
	}
	//----------------------------------------------------------------------------------
	//  [9/2/2014 hayamizu]
	record_set  database::execute(const std::wstring& query) {
		NYX_ASSERT(db_ != nullptr);
		return db_->execute(query);
	}
}