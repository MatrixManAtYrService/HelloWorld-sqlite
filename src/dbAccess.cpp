#include <stdio.h>
#include <string>
#include "sqlite3/sqlite3.h"
#include "dbAccess.h"

using namespace std;

int callback(void *NotUsed, int argc, char **argv, char **azColName)
{
  int i;
  for(i=0; i<argc; i++)
  {
    printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
  }
  printf("\n");
  return 0;
}

int DBAccess::RunScript(string dbName, string sql)
{
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;

    int returnVal = 0;

    rc = sqlite3_open(dbName.c_str(), &db);
    if( rc )
    {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return(1);
    }
    rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);
    if( rc!=SQLITE_OK )
    {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        returnVal = 1;
    }
    sqlite3_close(db);
    return returnVal;
}
