/* Copyright Ciprian Ilies */

#pragma once

#include <string>
#include <stdio.h>
#include <iostream>

#include "../internal_header.hpp"

/*extern "C" {
#include "sqlite/sqlite3.h"
}*/

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
		//This function really shouldn't be called if db already exists.
		if (db)
		{
			sqlite3_close(db);
			delete db;
		}

		std::string error_message = "";
		int rc;

		rc = sqlite3_open(filepath.c_str(), &db);

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
		std::string sql = "CREATE TABLE IF NOT EXISTS " + table_name + "(" + column_args + ");";

		char* error_message = nullptr;

		int rc = sqlite3_exec(db, sql.c_str(), SQLiteCallback, 0, &error_message);
		if (rc != SQLITE_OK)
		{
			fprintf(stderr, "\n[mdata::sqlite::Database] createTable() ERROR: SQL error: %s\n", error_message);
			sqlite3_free(error_message);
		}
		else
		{
			std::cout << "\n[mdata::sqlite::Database] Table created successfully\n";
		}
	}

	/*
	 * Inserts a value into a table.
	 */
	void insert(std::string table_name, std::string value_format, std::string values)
	{
		std::string sql = "INSERT INTO " + table_name + " " + value_format + " " + values;

		char* error_message = nullptr;

		int rc = sqlite3_exec(db, sql.c_str(), SQLiteCallback, 0, &error_message);
		if (rc != SQLITE_OK)
		{
			fprintf(stderr, "\n[mdata::sqlite::Database] insert() ERROR: SQL error: %s\n", error_message);
			sqlite3_free(error_message);
		}
		else
		{
			std::cout << "\n[mdata::sqlite::Database] Records created successfully\n";
		}
	}
};

} //namespace sqlite

} //namespace mdata
