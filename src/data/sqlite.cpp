/* Please refer to license.txt */

#include "sqlite.hpp"

/*namespace mdata
{

namespace sqlite
{

Database::Database()
{
	db = nullptr;
}

Database::~Database()
{
	this->close();
}

void Database::open(std::string filepath)
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

void Database::close()
{
	if (db)
	{
		sqlite3_close(db);
		delete db;
		db = nullptr;
	}
}

static int Database::SQLiteCallback(void *not_used, int argc, char **argv, char **col_name)
{
	int i;
	for (i=0; i<argc; i++)
	{
		printf("%s = %s\n", col_name[i], argv[i] ? argv[i] : "NULL");
	}
	std::cout << "\n";
	return 0;
}

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

} //namespace sqlite

} //namespace mdata
*/
