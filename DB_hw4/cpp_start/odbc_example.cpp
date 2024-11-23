// DO:  more ~username/.my.cnf to see your password
// CHANGE:  MYUSERNAME and MYMYSQLPASSWORD in the main function to your username and mysql password
// COMPILE AND RUN:      ./compileandruncpp.sh
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/metadata.h>
#include <cppconn/resultset_metadata.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

#include <iostream>
#include <ctime>
 
using namespace std;
 
sql::Driver *driver;
sql::Connection *con;
sql::Statement *statement;
sql::ResultSet *resultSet;
sql::ResultSetMetaData *metaData;
sql::Connection* Connect(string, string);
 
void insert(string table, string values );
void initDatabase(const string Username, const string Password, const string SchemaName);
void query (string q);
void print (sql::ResultSet *resultSet);
void disconnect();
void printRecords(sql::ResultSet *resultSet, int numColumns);
void printHeader(sql::ResultSetMetaData *metaData, int numColumns);
 
void menu(int &value);
void findMenus();
void orderItem(int &orderNo);
void listOrders();
void cancelOrder();
void addDish(int &dishNo, int &itemNo);
void typeMenu();

bool isFound = false;


int main() 
{
    string Username = "mathursb";             // Change to your own username
    string mysqlPassword = "eej2Quoo";   // Change to your own mysql password
    // string Username = "kevinz";
    // string mysqlPassword = "Yee8mei8"
    initDatabase(Username, mysqlPassword, Username); //init and testing - use it to enter your queries

    int input;
    int orderNo = 9;
    int dishNo = 80;
    int itemNo = 12;
    do{
    menu(input);

    switch(input){
        case 1:
            findMenus();
            break;
        case 2:
            orderItem(orderNo);
            break;
        case 3:
            listOrders();
            break;
        case 4:
            cancelOrder();
            break;
        case 5:
            addDish(dishNo, itemNo);
            break;
        default:
            cout << "Hurray You're Finished. We'll miss you  </3 \n";
            disconnect();
            break;
    }
    }while(input != 6);
     
}   
//prints the menu for the user to see
void menu(int &value){
	cout << "\n\t----Option Menu----\n";
    cout << "1. Find all available menu items at a given restaurant\n";
    cout << "2. Order an available menu item from a particular restaurant\n";
    cout << "3. List all food orders for a particular restaurant\n";
    cout << "4. Cancel a food order\n";
    cout << "5. Add anew dish for a restaurant\n";
    cout << "6. Quit\n";
    cout << "\n";
    cout << "Enter an Option: ";
    cin >> value;
    while (value < 1 || value > 6){
        cout << "User Input Error: try again\n";
        cout << ">>> ";
        cin >> value;
    }
}
//finds the menu from the seleted restaurant and city and displays the table
void findMenus(){
    string restaurant, city, q;
    cin.ignore();

    query("SELECT restaurantName, city FROM Restaurant");

    cout << "\nEnter a Restaurant Name: ";
    getline(cin, restaurant, '\n');
    while (restaurant.length() > 15 || restaurant.length() == 0){
        cout << "Error Warning: Character String out of limit try again\n";
        cout << ">>> ";
        getline(cin, restaurant, '\n');
    }

    cout << "Enter a City Name: ";
    getline(cin, city, '\n');
    while (city.length() > 15 || city.length() == 0){
        cout << "Error Warning: Character String out of limit try again\n";
        cout << ">>> ";
        getline(cin, city, '\n');
    }


    // find and list out menu items from restaurant
    // output restaurant name once
    // lsit dish name and price for each available menu item

    q = "SELECT dishName, price " 
         "FROM Restaurant a, Dish b, MenuItem c "
         "WHERE a.restaurantID = c.restaurantNo AND b.dishNo = c.dishNo AND a.restaurantName = '" + restaurant + "' AND a.city = '" + city + "';";

    cout << endl << restaurant << " in " << city << " was selected\n";

    query(q);



}
    /*
    Prompt the user for the dishName of the item that they want to order.
    if the dish is fournd, display the itemNo, restaurantName, city and price
    for all matches. Prompt the user for the itemNo for the menuItem that they want
    to order. Add the itemNo, current time, and current date to the FoodOrder table.
    */
void orderItem(int &orderNo){
    string values;
    cin.ignore();

    string dishName, itemNo, e, strYear, strMonth, strDay, strHour, strMinute;
    int year, month, day, hour, minute;
    query("SELECT dishName, type FROM Dish;");

    cout << "Enter a dish name: ";
    getline(cin, dishName);
    while(dishName.length() > 25 || dishName.length() == 0){
        cout << "Error Warning: Character String out of limit try again\n";
        cout << ">>> ";
        getline(cin, dishName);
    }
    e = "SELECT itemNo, restaurantName, city, price FROM Restaurant a, Dish b, MenuItem c WHERE b.dishName = '" + dishName + "' AND b.dishNo = c.dishNo AND c.restaurantNo = a.restaurantID ;";
    query(e);
    if(isFound){
    //query("SELECT* FROM MenuItem;");
    cout << "Enter a item number you want to order: ";
    getline(cin, itemNo);
    cout << "Enter a current year: ";
    cin >> year;
    cout << "Enter a current month: ";
    cin >> month;
    while(month > 12 || month < 0){
        cout << "Error. Enter a current month: ";
        cin >> month;
    }
    cout << "Enter a current day: ";
    cin >> day;
    while(day > 31 || day < 0){
        cout << "Error. Enter a current day: ";
        cin >> day;
    }
    cout << "Enter a current hour (using 24 hour format): ";
    cin >> hour;
    while(hour > 24 || hour < 0){
        cout << "Error. Enter a current hour (using 24 hour format): ";
        cin >> hour;
    }
    cout << "Enter a current minute: ";
    cin >> minute;
    while(minute > 60 || minute < 0){
        cout << "Error. Enter a current minute: ";
        cin >> minute;
    }
    strYear = to_string(year);
    strMonth = to_string(month);
    strDay = to_string(day);
    strHour = to_string(hour);
    strMinute = to_string(minute);
    values = orderNo + ", " + itemNo + ",'"+ strYear +"-" + strMonth +"-"+ strDay + "', '" + strHour + ":" + strMinute + "'";
    insert ("FoodOrder", values); 
    orderNo ++;
    }
}
//Lists the order from the given restaurant name and city
void listOrders(){
    string restaurant, city, q;
    cin.ignore();

    query("SELECT restaurantName, city FROM Restaurant");

    cout << "\nEnter a Restaurant Name: ";
    getline(cin, restaurant, '\n');
    while (restaurant.length() > 15 || restaurant.length() == 0){
        cout << "Error Warning: Character String out of limit try again\n";
        cout << ">>> ";
        getline(cin, restaurant, '\n');
    }

    cout << "Enter a City Name: ";
    getline(cin, city, '\n');
    while (city.length() > 15 || city.length() == 0){
        cout << "Error Warning: Character String out of limit try again\n";
        cout << ">>> ";
        getline(cin, city, '\n');
    }

    cout << restaurant << " was selected\n";
    cout << city << " was selected\n";
    q = "SELECT dishName, price, date, time FROM Dish a, MenuItem b, FoodOrder c, Restaurant d WHERE d.restaurantName = '" + restaurant + "' AND d.city = '" + city + "' AND b.itemNo = c.itemNo AND b.dishNo = a.dishNo AND d.restaurantID = b.restaurantNo;";
    query(q);

}
//delete order from the given order number
void cancelOrder(){
    cin.ignore();
    string orderNum, q;
    query("SELECT* FROM FoodOrder");
    cout << "Select and order from the table above to cancel: ";
    getline(cin, orderNum);

    q = "DELETE FROM FoodOrder a WHERE '" + orderNum + "' = a.orderNo;";
    query(q);

}
void addDish(int &dishNo, int &itemNo){
    cin.ignore();
    string restaurant, city, name, type, price, q, dishValue, menuValue, restaurantNo, dishNum, itemNum;
    int option;

    query("SELECT restaurantName, city FROM Restaurant");
    cout << "\nEnter a Restaurant Name: ";
    getline(cin, restaurant, '\n');
    while (restaurant.length() > 15 || restaurant.length() == 0){
        cout << "Error Warning: Character String out of limit try again\n";
        cout << ">>> ";
        getline(cin, restaurant, '\n');
    }

    cout << "Enter a City Name: ";
    getline(cin, city, '\n');
    while (city.length() > 15 || city.length() == 0){
        cout << "Error Warning: Character String out of limit try again\n";
        cout << ">>> ";
        getline(cin, city, '\n');
    }

    if (restaurant == "Tasty Thai"){
        if (city == "Dallas"){
            restaurantNo = "0";
        }
        else {
            restaurantNo = "5";
        }
    }
    else{
        restaurantNo = "3";
    }

    q = "SELECT restaurantName, city FROM Restaurant a WHERE a.restaurantName = '" + restaurant + "' AND a.city = '" + city + "';";
    query(q);
    if (isFound){
        query("SELECT* FROM Dish;");
        cout << "\nEnter a new Dish Name: ";
        getline(cin, name);
        while (name.length() > 25 || name.length() == 0){
            cout << "Error Warning: Character String out of limit try again\n";
            cout << ">>> ";
            getline(cin, name, '\n');
        }

        do{
        typeMenu();
        cout << "\nSelect a Dish Type: ";
        cin >> option;
        switch(option){
            case 1:
                type = "ap";
                break;
            case 2:
                type = "en";
                break;
            case 3:
                type = "ds";
                break;
            default:
                break;
        }
        }while (option < 1 && option > 3);
        cout << "Enter the price of your Dish: ";
        cin >> price;
        // add error checking to the price

        dishNum = to_string(dishNo);

        itemNum = to_string(itemNo);

        dishValue = dishNum + ", " + name + ", " + type;

        menuValue = itemNum + ", " + restaurantNo + ", " + dishNum + ", " + price;

        query("INSERT into Dish values(" + dishValue + ");");
    
        query("INSERT into MenuItem values(" + menuValue + ");");

        dishNo ++;
        itemNo ++;
        
    }
    
}
//displays the menu of the types for the dish table
void typeMenu(){
    cout << "\n\t----Types of Dishes----\n";
    cout << "1. appetizer (ap)\n";
    cout << "2. entree    (en)\n";
    cout << "3. dessert   (ds)\n";
}

// Connect to the database
sql::Connection* Connect(const string Username, const string Password)
 {
	 try{
	
		driver = get_driver_instance();
		con = driver->connect("tcp://127.0.0.1:3306", Username, Password);
		}
		 
	catch (sql::SQLException &e) {
        cout << "ERROR: SQLException in " << __FILE__;
        cout << " (" << __func__<< ") on line " << __LINE__ << endl;
        cout << "ERROR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << ")" << endl;
        }
   return con;
}

// Disconnect from the database
void disconnect()
{
		delete resultSet;
		delete statement;
		con -> close();
		delete con;
} 

// Execute an SQL query passed in as a string parameter
// and print the resulting relation

void query (string q)
{
    try {
        resultSet = statement->executeQuery(q);
        cout<<("---------------------------------\n");
        cout<<("Query: \n" + q + "\n\nResult: \n");
        if (resultSet -> rowsCount() == 0){
            isFound = false;
            cout << "No Results Found\n";
        }
        else{
            isFound = true;
            print(resultSet);
        }
        
    }
    catch (sql::SQLException e) {
        
    cout << "ERROR: SQLException in " << __FILE__;
    cout << " (" << __func__<< ") on line " << __LINE__ << endl;
    cout << "ERROR: " << e.what();
    cout << " (MySQL error code: " << e.getErrorCode();
    cout << ", SQLState: " << e.getSQLState() << ")" << endl;
    }
}
 
// Print the results of a query with attribute names on the first line
// Followed by the tuples, one per line
void print (sql::ResultSet *resultSet) 
{
    try{
		if (resultSet -> rowsCount() != 0)
		{
   		   sql::ResultSetMetaData *metaData = resultSet->getMetaData();
           int numColumns = metaData->getColumnCount();
		   printHeader( metaData, numColumns);
           printRecords( resultSet, numColumns);
		}
        else
			throw runtime_error("ResultSetMetaData FAILURE - no records in the result set");
    }
	catch (std::runtime_error &e) {
    }
    
}	

// Print the attribute names
void printHeader(sql::ResultSetMetaData *metaData, int numColumns)
{    
	/*Printing Column names*/  
    for (int i = 1; i <= numColumns; i++) {
            if (i > 1)
                cout<<",  ";
            cout<< metaData->getColumnLabel(i); //ColumnName
        }
    cout<<endl;
}		

// Print the attribute values for all tuples in the result
void printRecords(sql::ResultSet *resultSet, int numColumns)   
{ 
    while (resultSet->next()) {
        for (int i = 1; i <= numColumns; i++) {
            if (i > 1)
                cout<<",  ";
            cout<< resultSet->getString(i);
            ;
        }
    cout<<endl;
    }
}
 
// Insert into any table, any values from data passed in as String parameters
void insert(const string table, const string values) 
{
    string query = "INSERT into " + table + " values (" + values + ")";
    statement->executeUpdate(query);
}
 

// init and  testing
// Assumes that the tables are already created
void initDatabase(const string Username, const string Password, const string SchemaName) 
{
        // Create a connection 
        con = Connect (Username, Password);
        driver = get_driver_instance();
        con = driver->connect("tcp://127.0.0.1:3306", Username, Password);

        // Connect to the MySQL test database 
        con->setSchema(SchemaName);
 
        // Create a MYSQL statement to hold queries
        statement = con->createStatement();
}
