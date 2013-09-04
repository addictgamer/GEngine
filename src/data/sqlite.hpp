/* Copyright Ciprian Ilies */

#pragma once

#include "../internal_header.hpp"

#include <string>
#include <stdio.h>
#include <iostream>

#include <sqlite3.h>

/*
 * SQLite 3 functions.
 */

namespace mdata
{

namespace sqlite
{

class Database
{
private:
	sqlite3 *db;
public:
	Database();

	~Database();

	void open(std::string filepath);

	void close();

	static int SQLiteCallback(void *not_used, int argc, char **argv, char **col_name);

	/*
	 * Creates a table, if it doesn't exist.
	 */
	void createTable(std::string table_name, std::string column_args);

	/*
	 * Returns false if table does not exist, true if table exists:
	 */
	/*bool tableExists()
	{
		//TODO: Figure this out. http://stackoverflow.com/questions/3499295/how-do-i-check-if-a-table-exists-in-sqlite3-c-api
		std::string sql = "select count(type) from sqlite_master where type='table' and name='" + TABLE_NAME_TO_CHECK + "';"

		//Execute the query/statement.
		sqlite3_stmt *stmt;
		int rc = sqlite3_prepare_v2(db, create_table_sql, -1, &stmt, NULL);
		rc = sqlite3_step(stmt); //0 if doesn't exist, 1 if exists.
		return rc;
	}*/
};

} //namespace sqlite

} //namespace mdata
