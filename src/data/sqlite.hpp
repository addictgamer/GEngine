/* Copyright Ciprian Ilies */

#pragma once

#include <string>
#include <stdio.h>
#include <iostream>

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
	Database();
	~Database();
    void open(std::string);
    void close();
    static int SQLiteCallback(void *not_used, int argc, char **argv, char **col_name);
    void createTable(std::string table_name, std::string column_args);
};

} //namespace sqlite

} //namespace mdata
