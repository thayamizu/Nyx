#ifndef NYX_CORE_INCLUDED_SQLite_H_
#define NYX_CORE_INCLUDED_SQLite_H_

#include <sqlite3.h>
#include <sqlite3ext.h>

#if defined(_UNICODE) || defined(UNICODE) 
#define SQLiteOpen       sqlite3_open16
#define SQLitePrepare    sqlite3_prepare16
#define SQLitePreParev2  sqlite3_prepare16_v2
#else
#define SQLiteOpen       sqlite3_open
#define SQLitePrepare    sqlite3_prepare
#define SQLitePreParev2  sqlite3_preparev2
#endif
#define SQLiteStep       sqlite3_step
#define SQLiteClose      sqlite3_close
#define SQLiteFinalize   sqlite3_finalize

namespace Nyx {

	typedef sqlite3_stmt            SQLiteStatement;
	typedef sqlite3                 SQLite;
	typedef sqlite3_backup          SQLiteBackup;
	typedef sqlite3_blob            SQLiteBlob;
	typedef sqlite3_context         SQLiteContext;
	typedef sqlite3_file            SQLiteFile;
	typedef sqlite3_index_info      SQLiteIndexInfo;
	typedef sqlite3_int64           SQLiteInt64;
	typedef sqlite3_uint64          SQLiteUInt64;
	typedef sqlite3_io_methods      SQLiteIOMethods;
	typedef sqlite3_mem_methods     SQLiteMemMethods;
	typedef sqlite3_module          SQLiteModule;
	typedef sqlite3_mutex           SQLiteMutex;
	typedef sqlite3_mutex_methods   SQLiteMutexMethods;
	typedef sqlite3_pcache          SQLitePCache;
	typedef sqlite3_pcache_methods2 SQLitePCacheMethods2;
	typedef sqlite3_pcache_page     SQLitePCachePage;
	typedef sqlite3_value           SQLiteValue;
	typedef sqlite3_vfs             SQLiteVfs;
	typedef sqlite3_vtab            SQLiteVtab;
	typedef sqlite3_vtab_cursor     SQLiteVtabCursor;
}
#endif