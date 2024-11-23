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
   string Date;

   // Read command line arguments
   // First arg, arg[0] is the name of the program
   // Next args are the parameters
   Date = argv[1];

   
   // Get the next id
   // string q = "select IFNULL(max(ID), 0) as max_id from GAME";
   // sql::ResultSet *result = myDB.rawQuery(q);
   // int next_id = 1;
   // if (result->next()) // get first row of result set
   //    next_id += result->getInt("max_id");

   // Insert the new restaurant
   string input = "SELECT T1.Location AS Team1Location, T1.Nickname AS Team1Name, CASE WHEN G.Score1 > G.Score2 THEN 'Won' ELSE 'Lost' END AS Result, T2.Location AS Team2Location, T2.Nickname AS Team2Name, G.Date, CONCAT(G.Score1, '-', G.Score2) AS Score FROM Game G JOIN Team T1 ON G.TeamId1 = T1.TeamId JOIN Team T2 ON G.TeamId2 = T2.TeamId WHERE G.Date = '" + Date + "'";

   // DEBUG:
   // printf("%s", input.c_str());
   myDB.query(input);    // insert new restaurant
   
   //For debugging purposes: Show the database after insert
   builder.append("<br><br><br>  <p style = 'background-color:powderblue'>Table Game after:" + myDB.query(input)+ "</p>");
   cout << builder; 
       
   myDB.disConnect();//disconect Database

   return 0;
}