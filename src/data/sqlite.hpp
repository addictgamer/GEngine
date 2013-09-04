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
	sqlite3* db;
public:
	Database()
	{
		db = nullptr;
	}

	~Database()
	{
		this->close();
	}

	void open(std::string filepath)
	{
		//This really shouldn't be called if db already exists.
		if (db)
		{
			sqlite3_close(db);
			delete db;
		}

		std::string error_message = "";
		int rc;

		rc = sqlite3_open(database.c_str(), &db);

		if (rc)
		{
			fprintf(stderr, "\n[mdata::sqlite::Database] ERROR: Can't open database: %s.\n", sqlite3_errmsg(db));
			exit(0);
		}
		else
		{
			std::cout << "\n[mdata::sqlite::Database] Opened database successfully.\n";
		}
	}

	void close()
	{
		if (db)
		{
			sqlite3_close(db);
			delete db;
			db = nullptr;
		}
	}

	static int SQLiteCallback(void *not_used, int argc, char **argv, char **col_name)
	{
		int i;
		for (i=0; i<argc; i++)
		{
			printf("%s = %s\n", col_name[i], argv[i] ? argv[i] : "NULL");
		}
		std::cout << "\n";
		return 0;
	}

	/*
	 * Creates a table, if it doesn't exist.
	 */
	void createTable(std::string table_name, std::string column_args)
	{
		std::string sql = "CREATE TABLE IF NOTE EXISTS " + table_name + "(" + column_args + ");";

		char* error_message = nullptr;

		int rc = sqlite3_exec(db, sql, SQLiteCallback, 0, &error_message);
		if (rc != SQLITE_OK)
		{
			fprintf(stderr, "\n[mdata::sqlite::Database] ERROR: SQL error: %s\n", error_message);
			sqlite3_free(error_message);
		}
		else
		{
			std::cout << "\n[mdata::sqlite::Database] Table created successfully\n";
		}
	}

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
