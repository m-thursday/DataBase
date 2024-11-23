/* Compile using:
g++ -Wall -I/usr/include/cppconn -o odbc odbc_insert_restaurant.cpp -L/usr/lib -lmysqlcppconn 
run: 
./odbc */
#include "odbc_db.h"
#include <iostream>
#include <string>
using namespace std;


int main(int argc, char *argv[])
{
string Username = "mathursb";   // Change to your own username
string mysqlPassword = "eej2Quoo";  // Change to your mysql password
string SchemaName = "mathursb"; // Change to your username

   odbc_db myDB;
   myDB.Connect(Username, mysqlPassword, SchemaName);
   myDB.initDatabase();
 
   // Parse input string to get restaurant Name and Type and  City
   string builder;
   string teamName;

   // Read command line arguments
   // First arg, arg[0] is the name of the program
   // Next args are the parameters
   teamName = argv[1];

   
   // Get the next id
   // string q = "select IFNULL(max(ID), 0) as max_id from GAME";
   // sql::ResultSet *result = myDB.rawQuery(q);
   // int next_id = 1;
   // if (result->next()) // get first row of result set
   //    next_id += result->getInt("max_id");

   // Insert the new restaurant
   string input = "SELECT Name, Position FROM Player p, Team t WHERE t.Nickname = '" + teamName + "' AND p.TeamId = t.TeamId";

   // DEBUG:
   // printf("%s", input.c_str());
   myDB.query(input);    // insert new restaurant
 
   //For debugging purposes: Show the database after insert
   builder.append("<br><br><br> <p style = 'background-color:powderblue'> Table Player after:" + myDB.query(input) + "</p>");
   cout << builder; 
       
   myDB.disConnect();//disconect Database

   return 0;
}


