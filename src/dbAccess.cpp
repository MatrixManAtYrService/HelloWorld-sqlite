#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include "sqlite3/sqlite3.h"
#include "dbAccess.h"

using namespace std;


// thanks to stackoverflow user: mah for this method.  Explanation:
// http://stackoverflow.com/questions/14437433/proper-use-of-callback-function-of-sqlite3-in-c
int c_callback(void *param, int argc, char **argv, char **azColName)
{
    DBAccess* caller = reinterpret_cast<DBAccess*>(param);
    caller->callback(argc, argv, azColName);
    return 0;
}

void DBAccess::callback(int argc, char **argv, char **azColName)
{
    results.cells.clear();
    results.cells.reserve(argc);

    int i;
    for(i=0; i<argc; i++)
    {
        queryCell cell;
        cell.colName = string(azColName[i]);
        cell.value = string(argv[i] ? argv[i] : "NULL");
        results.cells.push_back(cell);
    }

}

// This method based on: http://www.sqlite.org/quickstart.html
queryResults DBAccess::RunScript(string dbName, string sql)
{
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;

    rc = sqlite3_open(dbName.c_str(), &db);
    if( rc )
    {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        results.err = 1;
        return(results);
    }
    rc = sqlite3_exec(db, sql.c_str(), c_callback, this, &zErrMsg);
    if( rc!=SQLITE_OK )
    {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        results.err = 2;
    }
    else
    {
        results.err = 0;     // success
    }
    sqlite3_close(db);

    return results;
}
