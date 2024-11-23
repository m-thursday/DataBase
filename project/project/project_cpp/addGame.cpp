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
   string query1 = "SELECT * from Game;";
   myDB.query(query1);
   builder.append("<br><br><br> <p style = 'background-color:powderblue'>Game table before:" + myDB.query(query1) +"</p><br>");
 
   // Parse input string to get restaurant Name and Type and  City
   string TeamID1;
   string TeamID2;
   string Score1;
   string Score2;
   string Date;
   if(argc == 6){
      TeamID1= argv[1];
      TeamID2 = argv[2];
      Score1 = argv[3];
      Score2 = argv[4];
      Date = argv[5];
      
   }
   else{
      builder.append("<p style = 'background-color:powderblue'>Fill in all the input</p>");
      return 1;
   }
   // Read command line arguments
   // First arg, arg[0] is the name of the program
   // Next args are the parameters
   

   
   // Get the next id
   string q = "select IFNULL(max(gameID), 0) as gameID from Game";
   sql::ResultSet *result = myDB.rawQuery(q);
   int next_id = 1;
   if (result->next()) // get first row of result set
      next_id += result->getInt("gameID");

   // Insert the new restaurant
   //string input = gameID + "," + TeamID1 + "," + TeamID2 + "," + Score1 + "," + Score2 + ",'"  + Date + "'";
   
   string values = "INSERT INTO Game VALUES (" + to_string(next_id) + "," + TeamID1 + "," + TeamID2 + "," + Score1 + "," + Score2 + ",'"  + Date + "')";
   
   // DEBUG:
   // printf("%s", input.c_str());
   //myDB.insert("Game", input);    // insert new restaurant
   
   myDB.query(values);
   
   //For debugging purposes: Show the database after insert
   
   builder.append("<br><br><br> <p style = 'background-color:powderblue'>Table Game after:" + myDB.query(query1) + "</p>");
   cout << builder; 
       
   myDB.disConnect();//disconect Database

   return 0;
}


