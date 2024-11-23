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
 
   // For debugging purposes:  Show the database before insert
   string builder = "";
   string query1 = "SELECT * from Player;";
   builder.append("<br><br><br>  <p style = 'background-color:powderblue'>Player table before:" + myDB.query(query1) +"</p><br>");
 
   // Parse input string to get restaurant Name and Type and  City
   string TeamID;
   string Name;
   string Position;

   // Read command line arguments
   // First arg, arg[0] is the name of the program
   // Next args are the parameters
   TeamID= argv[1];
   Name = argv[2];
   Position = argv[3];

   
   // Get the next id
   string q = "select IFNULL(max(PlayerID), 0) as max_id from Player";
   sql::ResultSet *result = myDB.rawQuery(q);
   int next_id = 1;
   if (result->next()) // get first row of result set
      next_id += result->getInt("max_id");

   // Insert the new restaurant
   string input = to_string(next_id) + "," + TeamID + ",'" + Name + "','" + Position + "'";

   // DEBUG:
   // printf("%s", input.c_str());
   myDB.insert("Player", input);    // insert new restaurant
 
   //For debugging purposes: Show the database after insert
   builder.append("<br><br><br>  <p style = 'background-color:powderblue'>Table Player after:" + myDB.query(query1)+ "</p>");
   cout << builder; 
       
   myDB.disConnect();//disconect Database

   return 0;
}


