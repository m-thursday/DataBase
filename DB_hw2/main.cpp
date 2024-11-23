
#include <iostream>
#include "database.h"
#include <string>
#include <algorithm>
using namespace std;

void printData(string id, string first_name, string last_name, string age, 
			   string ticket_num, string fare, string purchase_date)
{
    replace(first_name.begin(), first_name.end(), '_', ' ');
    replace(last_name.begin(), last_name.end(), '_', ' ');
    replace(ticket_num.begin(), ticket_num.end(), '_', ' ');
	cout << "ID: " << id << " first Name: " << first_name << " Last Name: " << last_name
		 << " Age: " << age << " Ticket Num: " << ticket_num << " Fare: " << fare 
		 << " Purchase Date: " << purchase_date << endl;
}

void menu()
{
  
   cout << endl << endl
        << "1) Create new database\n"
        << "2) Open database\n"
        << "3) Close database\n"
        << "4) Read record\n"
        << "5) Display record\n"
        << "6) Update record\n"
        << "7) Create report\n"
        << "8) Add record\n"
        << "9) Delete record\n"
        << "10) Quit\n";
}

void update(){
    
}

int main(int argc, char **argv){

	string id, first_name, last_name, age, ticket_num, fare, purchase_date;
	int selection = -1;
    Database db;
    string filename;
    int recordNum;
    string primaryKey;
    int createReportCount;
    int updateKey;
    string updateInfo;
    string idInput;
    string idHold;
    int emptyRec;
    int rec;

  
	
	cout << endl << "Welcome to your very own Bizzare Adventure, so Go Ahead Mr.Joestar" << endl;
		 
    bool Done = false;
	while (!Done) {
        menu();
		cout  << "Please make your selection: ";
        cin >> selection;
        switch (selection) {
            case 1: // Create new database
                cout << "Enter database name: ";
                cin >> filename;
                if(db.createDb(filename)){
                	cout << "Database created." << endl;
                }
                break;
            case 2: // Open database
                cout << "Enter database name to open: ";
                cin >> filename;
                if(db.openDb(filename)) {
                    cout << "Database opened successfully." << endl;
                } else {
                    cout << "Failed to open database." << endl;
                }
                break;
            case 3: // Close database
                db.closeDb();
     
                break;
            case 4: // Read record
                cout << "Enter record number to display: ";
                cin >> recordNum;
                if(db.readRecord(recordNum, id, first_name, last_name, age, ticket_num, fare, purchase_date) == 1) {
                    printData(id, first_name, last_name, age, ticket_num, fare, purchase_date);
                } else {
                    cout << "Failed to read record or record does not exist." << endl;
                }
                break;
            case 5: // Display record
                // Implementation depends on how the Dtabase class handles displaying a record given the primary key
                cout << "Enter in the primary key to display: ";
                cin >> primaryKey;
                if(db.binarySearch(primaryKey, recordNum, first_name, last_name, age, ticket_num, fare, purchase_date) == 1){
                    printData(primaryKey, first_name, last_name, age, ticket_num, fare, purchase_date);
                }
                else{
                    cout << "Failed to read record or record does not exist." << endl;
                }
                break;
            case 6: // Update record
                // Implementation depends on how the Database class handles updates
                cout << "Enter in the primary key to update: ";
                cin >> primaryKey;
                if(db.binarySearch(primaryKey, recordNum, first_name, last_name, age, ticket_num, fare, purchase_date) == 1){
                    printData(primaryKey, first_name, last_name, age, ticket_num, fare, purchase_date);
                    cout << endl;
                    cout << "What field do you want to change? Type the number." << endl;
                    cout << "1) Update first name" << endl;
                    cout << "2) Update last name" << endl;
                    cout << "3) Update age" << endl;
                    cout << "4) Update ticket number" << endl;
                    cout << "5) Update fare" << endl;
                    cout << "6) Update purchase date" << endl;
                    cout << ">>> ";
                    cin >> updateKey;
                    while (updateKey < 1 || updateKey > 6){
                        cout << "Input failed try again" << endl;
                        cout << ">>> ";
                        cin >> updateKey;
                    }
                    if (updateKey == 1 ){
                        cout << "Enter in the new updated first name: ";
                        cin >> updateInfo;
                        if(db.seqWriteRecord(recordNum, primaryKey, updateInfo, last_name, age, ticket_num, fare, purchase_date) == 1){
                            printData(primaryKey, updateInfo, last_name, age, ticket_num, fare, purchase_date);
                        }
                        else{
                            cout << "Failed to read record or record does not exist." << endl;
                        }
                    }
                    if (updateKey == 2){
                        cout << "Enter in the new updated last name: ";
                        cin >> updateInfo;
                        if(db.seqWriteRecord(recordNum, primaryKey, first_name , updateInfo, age, ticket_num, fare, purchase_date) == 1){
                            printData(primaryKey, first_name, updateInfo, age, ticket_num, fare, purchase_date);
                        }
                        else{
                            cout << "Failed to read record or record does not exist." << endl;
                        }
                    }
                    if (updateKey == 3){
                        cout << "Enter in the new updated age: ";
                        cin >> updateInfo;
                        if(db.seqWriteRecord(recordNum, primaryKey, first_name, last_name, updateInfo, ticket_num, fare, purchase_date) == 1){
                            printData(primaryKey, first_name, last_name, updateInfo, ticket_num, fare, purchase_date);
                        }
                        else{
                            cout << "Failed to read record or record does not exist." << endl;
                        }
                    }
                    if (updateKey == 4){
                        cout << "Enter in the new updated ticket number: ";
                        cin >> updateInfo;
                        if(db.seqWriteRecord(recordNum, primaryKey, first_name, last_name, age, updateInfo, fare, purchase_date) == 1){
                            printData(primaryKey, first_name, last_name, age, updateInfo, fare, purchase_date);
                        }
                        else{
                            cout << "Failed to read record or record does not exist." << endl;
                        }
                    }
                    if (updateKey == 5){
                        cout << "Enter in the new updated fare: ";
                        cin >> updateInfo;
                        if(db.seqWriteRecord(recordNum, primaryKey, first_name, last_name, age, ticket_num, updateInfo, purchase_date) == 1){
                            printData(primaryKey, first_name, last_name, age, ticket_num, updateInfo, purchase_date);
                        }
                        else{
                            cout << "Failed to read record or record does not exist." << endl;
                        }
                    }
                    if (updateKey == 6){
                        cout << "Enter in the new updated date of purchase: ";
                        cin >> updateInfo;
                        if(db.seqWriteRecord(recordNum, primaryKey, first_name, last_name, age, ticket_num, fare, updateInfo) == 1){
                            printData(primaryKey, first_name, last_name, age, ticket_num, fare, updateInfo);
                        }
                        else{
                            cout << "Failed to read record or record does not exist." << endl;
                        }
                    }
                }
                else{
                    cout << "Failed to read record or record does not exist." << endl;
                }
                break;
            case 7: // Create report
                // Could iterate over all records and display them or write to a file
                recordNum = 0;
                createReportCount = 0;
                while(createReportCount < 10){
                    if(db.readRecord(recordNum, id, first_name, last_name, age, ticket_num, fare, purchase_date) == 1){
                        if(id == "_empty_"){
                            recordNum++;
                        }
                        else{
                            printData(id, first_name, last_name, age, ticket_num, fare, purchase_date);
                            recordNum++;
                            createReportCount++;
                        }    
                    }
                    if(db.checkMax(recordNum) ==  1){
                        break;
                    }
                }
                break;
            case 8: // Add record
                // Gather input from the user and use writeRecord or another method to add
                cout << "Enter the ID you wish to add: ";
                cin >> idInput;
                recordNum = 0;
                idHold = "0";
                emptyRec = 0;
                while(stoi(idInput) > stoi(idHold)){
                    if(db.readRecord(recordNum, id, first_name, last_name, age, ticket_num, fare, purchase_date) == 1){
                        
                            if(id == "_empty_"){
                                emptyRec = recordNum;

                                recordNum ++;
                            }
                            else{
                                rec = recordNum;
                                recordNum ++;
                                idHold = id;
                            }
                        
                    }
                    if(db.checkMax(recordNum) == 1){
                    break;
                    }
                }
                if (idInput == idHold){
                    cout << "No space available for record" << endl;
                }else{
                    if (abs(rec - emptyRec) != 1){
                        cout << rec << "    " << emptyRec << endl;
                        cout << "No space available for record" << endl;
                    }else{
                        cout << "Enter First Name: ";
                        cin >> first_name;
                        cout << "Enter Last Name: ";
                        cin >> last_name;
                        cout << "Enter Age: ";
                        cin >> age;
                        cout << "Enter Ticket Number: ";
                        cin >> ticket_num;
                        cout << "Enter Fare: ";
                        cin >> fare;
                        cout << "Enter Date of Purchase: ";
                        cin >> purchase_date;
                        if (db.seqWriteRecord(emptyRec, idInput, first_name, last_name, age, ticket_num, fare, purchase_date) == 1){
                            cout << "Record Added" << endl;
                        };

                    }
                }
                break;
            case 9: // Delete record
                // Implementation depends on how the Database class handles deletion
                cout << "Enter in the primary key to update: ";
                cin >> primaryKey;
                if(db.binarySearch(primaryKey, recordNum, first_name, last_name, age, ticket_num, fare, purchase_date) == 1){
                    if(db.seqWriteRecord(recordNum, "_empty_", "None", "None", "None", "None", "None","None") == 1) {
                        cout << "Record deleted" << endl;
                    }
                    else {
                        cout << "Failed to read record or record does not exist." << endl;
                    }
                }
                break;
            case 10: // Quit
                if (!db.isOpen())
                {
                   cout << "Exiting program." << endl;
                   Done = true;
                }
                else
                   cout << "Please close the database before exiting." << endl;
                break;
            default:
                cout << "Invalid selection, please try again." << endl;
                break;
        }
    }

    return 0;
	
}
