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

   // Read command line arguments
   // First arg, arg[0] is the name of the program
   // Next args are the parameters

   
   // Get the next id
   // string q = "select IFNULL(max(ID), 0) as max_id from GAME";
   // sql::ResultSet *result = myDB.rawQuery(q);
   // int next_id = 1;
   // if (result->next()) // get first row of result set
   //    next_id += result->getInt("max_id");
    cout << "hello" << endl;
   // Insert the new restaurant
   
   string input = "SELECT T.Conference, T.Nickname, T.Location, "
                  "COUNT(CASE WHEN (G.TeamId1 = T.TeamId AND G.Score1 > G.Score2) OR "
                  "(G.TeamId2 = T.TeamId AND G.Score2 > G.Score1) THEN 1 ELSE NULL END) AS TotalWins, "
                  "COUNT(CASE WHEN ((G.TeamId1 = T.TeamId AND G.Score1 > G.Score2) OR "
                  "(G.TeamId2 = T.TeamId AND G.Score2 > G.Score1)) AND "
                  "T1.Conference = T2.Conference THEN 1 ELSE NULL END) AS ConferenceWin "
                  "FROM Team T "
                  "LEFT JOIN Game G ON T.TeamId = G.TeamId1 OR T.TeamId = G.TeamId2 "
                  "LEFT JOIN Team T1 ON G.TeamId1 = T1.TeamId "
                  "LEFT JOIN Team T2 ON G.TeamId2 = T2.TeamId "
                  "GROUP BY T.TeamId, T.Conference, T.Nickname, T.Location "
                  "ORDER BY T.Conference ASC, TotalWins DESC, ConferenceWin DESC;";

   // DEBUG:
   // printf("%s", input.c_str());
   
   myDB.query(input);    // insert new restaurant
   
   //For debugging purposes: Show the database after insert
   
   builder.append("<br><br><br>  <p style = 'background-color:powderblue'> Table after:" + myDB.query(input) + "</p>");
   cout << builder; 
       
   myDB.disConnect();//disconect Database

   return 0;
}