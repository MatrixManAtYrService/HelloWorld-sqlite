#ifndef DBACCESS_H
#define DBACCESS_H

#include <string>
#include <vector>

// A value from a query together with the name of the column it came from
struct queryCell
{
    std::string colName;
    std::string value;
};

struct queryResults
{
    int err;
    std::vector<queryCell> cells;
};

class DBAccess
{
    public:

    // used to fetch SQL results
    void callback(int argc, char **argv, char **azColName);

    // used to store SQL results
    queryResults results;

    // Opens a connection, runs a query, and closes it
    queryResults RunScript(std::string dbName, std::string sql);

};

#endif
