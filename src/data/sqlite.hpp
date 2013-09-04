/* Copyright Ciprian Ilies */

#pragma once

#include "../internal_header.hpp"

#include <string>

/*
 * SQLite 3 functions.
 */

namespace mdata
{

namespace sqlite
{

sqlite3* openDatabase(std::string database)
{
	std::string error_message = "";
	int rc;

	sqlite3 *db = nullptr;

	rc = sqlite3_open(database, &db);

	if (rc)
	{
		fprintf(stderr, "\n[mdata::sqlite] ERROR: Can't open database: %s.\n", sqlite3_errmsg(db));
		exit(0);
	}
	else
	{
		cout << "\n[mdata::sqlite] Opened database successfully.\n";
	}
}

} //namespace sqlite

} //namespace mdata
