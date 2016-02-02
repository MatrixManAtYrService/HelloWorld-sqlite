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

    string create = "create table [fish] ( [seuss1] text, [seuss2] text );";

    string insert = "insert into [fish] ( [seuss1], [seuss2] ) values "
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
    auto results = db.RunScript(dbName, retrieve);
    BOOST_CHECK_EQUAL(results.err, 0);

    BOOST_CHECK_EQUAL(results.cells[0].colName, "seuss1");
    BOOST_CHECK_EQUAL(results.cells[0].value, "one fish");

    BOOST_CHECK_EQUAL(results.cells[1].colName, "seuss2");
    BOOST_CHECK_EQUAL(results.cells[1].value, "two fish");

    BOOST_CHECK_EQUAL(results.cells[2].colName, "seuss1");
    BOOST_CHECK_EQUAL(results.cells[2].value, "red fish");

    BOOST_CHECK_EQUAL(results.cells[3].colName, "seuss2");
    BOOST_CHECK_EQUAL(results.cells[3].value, "blue fish");

 
}

