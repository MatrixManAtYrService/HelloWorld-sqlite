#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE "Database Access Tests"

#include <string>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include "dbAccess.h"

#include <boost/test/unit_test.hpp> //include this last

using namespace std;

// Deletes a database with the given name
// used to clear those that may have been created in a previous test
void DeleteTempDB(string name)
{
    if( remove(name.c_str()) != 0 )
        cout << "prior db: " << name << " not found" << endl;
    else
        cout << "prior db: " << name << " deleted" << endl;
}

BOOST_AUTO_TEST_CASE(DBReadWriteIntegity_Basic)
{
    string dbName = "test.db";

    string create = "create table [fish] ( [one] text, [two] text );";

    string insert = "insert into [fish] ( [one], [two] ) values "
    "('one fish', 'two fish')"
    ",('red fish', 'blue fish');";

    string retrieve = "select * from [fish];";


    // clear the way for a new db
    DeleteTempDB(dbName);
    DBAccess db;

    cout << "Creating Table:       " << create << endl;
    BOOST_CHECK_EQUAL(db.RunScript(dbName, create).err, 0);

    cout << "Populating Values:    " << insert << endl;
    BOOST_CHECK_EQUAL(db.RunScript(dbName, insert).err, 0);

    cout << "Fetching Value:       " << retrieve << endl;
    auto results1 = db.RunScript(dbName, retrieve);
    auto results2 = db.RunScript(dbName, retrieve);
    BOOST_CHECK_EQUAL(results2.err, 0);

    for (auto &cell : results2.cells)
    {
        cout << "XXX" << cell.value << "XXX\n";
    }

 
}

