#include <iomanip>
#include <iostream>
#include <algorithm>
#include "database.h"
#include <string>

using namespace std;

Database::Database()
{
	num_records = -1;
    record_size = -1;
}

Database::~Database()
{
}

bool Database::createDb(const string filename)
{
	/////////////////////////////////////possible strings might need to be set to an initial value
	string id, first_name, last_name, age, ticket_num, fare, purchase_date;

    // open csv file for reading
    f_csv.open(filename+".csv");
	if (!f_csv){
		cerr << "Failed to open csv file" << endl;
		return false;
    }

    // open data file for writing
	f_db.open(filename+".data", f_db.out);
    if (!f_db)
    {
		cerr << "Failed to open data file" << endl;
		return false;
    }

    // files are open
    num_records = 0;
	while(readCsv(id, first_name, last_name, age, ticket_num, fare, purchase_date))
	{
		writeRecord(id, first_name, last_name, age, ticket_num, fare, purchase_date);
        num_records++;
		writeRecord("_empty_", "None", "None", "None", "None", "None", "None");
        num_records++;
	}
	
	f_csv.close();
	f_db.close();
	
	//config file section
	ofstream f_cfg;
	f_cfg.open(filename+".config");
	if (!f_cfg)
		cerr << "Failed to create configuration file." << endl;
	else
	{
		f_cfg << num_records << " " << RECORD_SIZE << endl;
	}
	f_cfg.close();
	return true;
}

bool Database::openDb(const string filename)
{
bool Success = false;

    if (isOpen())
       cout << "There is a database open already.   Please close that first." << endl;
    else
    {
	   //read config file and set values
	   ifstream f_cfg;
   	
	   f_db.open(filename+".data");
	   f_cfg.open(filename+".config");
   	
	   if (!f_cfg || !f_db)
		   cerr << "Failed to open configuration file, openDb." << endl;
	   else
	   {
		  f_cfg >> num_records >> record_size;
	      f_cfg.close();
	      Success = true;
	   }
    }
    return Success;
}

void Database::closeDb()
{
	//does not say to update the config file here, might be a good idea to add it in
	if (isOpen()){
		f_db.close();
		num_records = -1;
		cout << "Database closed." << endl;
	}
	else{
		cout << "No database is open." << endl;
	}
}

bool Database::readCsv(string &id, string &firstName, string &lastName, string &age, string &ticketNum, string &fare, string &purchaseDate)
{
	if(getline(f_csv, id, ','))
	{
		getline(f_csv, firstName, ',');
		getline(f_csv, lastName, ',');
		getline(f_csv, age, ',');
		getline(f_csv, ticketNum, ',');
		getline(f_csv, fare, ',');
		getline(f_csv, purchaseDate);
		return true;
	}
	else
		return false;
}

void Database::writeRecord(string id, string first_name, string last_name, string age, 
						   string ticket_num, string fare, string purchase_date)
{

    // replace spaces with _
    replace(first_name.begin(), first_name.end(), ' ', '_');
    replace(last_name.begin(), last_name.end(), ' ', '_');
    replace(ticket_num.begin(), ticket_num.end(), ' ', '_');

	//do formatted writes
	f_db << setw(ID_SIZE) << left << id.substr(0, ID_SIZE) << " " 
         << setw(FIRST_SIZE) << left << first_name.substr(0, FIRST_SIZE) << " " 
         << setw(LAST_SIZE) << left << last_name.substr(0, LAST_SIZE) << " " 
         << setw(AGE_SIZE) << left << age.substr(0, AGE_SIZE) << " " 
         << setw(TICKET_NUM_SIZE) << left << ticket_num.substr(0, TICKET_NUM_SIZE) << " " 
         << setw(FARE_SIZE) << left << fare.substr(0, FARE_SIZE) << " " 
         << setw(DATE_SIZE) << left << purchase_date.substr(0, DATE_SIZE) << endl;
}
bool Database::seqWriteRecord(const int record_num, string id, string first_name, string last_name, 
						 string age, string ticket_num, string fare, string purchase_date)
{
    bool Success = false;
        if(!isOpen()){
            cout <<"No Database open" << endl;
        }
        else if ((record_num < 0)||(record_num >= num_records)){
            cout << "value is out range" << endl;
        }
        else{
            f_db.seekg(((record_num) * record_size), ios::beg);
            // replace spaces with _
            replace(first_name.begin(), first_name.end(), ' ', '_');
            replace(last_name.begin(), last_name.end(), ' ', '_');
            replace(ticket_num.begin(), ticket_num.end(), ' ', '_');

	        //do formatted writes
	        f_db << setw(ID_SIZE) << left << id.substr(0, ID_SIZE) << " " 
                 << setw(FIRST_SIZE) << left << first_name.substr(0, FIRST_SIZE) << " " 
                 << setw(LAST_SIZE) << left << last_name.substr(0, LAST_SIZE) << " " 
                 << setw(AGE_SIZE) << left << age.substr(0, AGE_SIZE) << " " 
                 << setw(TICKET_NUM_SIZE) << left << ticket_num.substr(0, TICKET_NUM_SIZE) << " " 
                 << setw(FARE_SIZE) << left << fare.substr(0, FARE_SIZE) << " " 
                 << setw(DATE_SIZE) << left << purchase_date.substr(0, DATE_SIZE) << endl;
            Success = true;
        }
        return Success;
}

bool Database::readRecord(const int record_num, string &id, string &first_name, string &last_name, 
						 string &age, string &ticket_num, string &fare, string &purchase_date)
{
bool Success = false;

	if (!isOpen())
		cout <<"No Database open" << endl;
	else if ((record_num < 0) || (record_num >= num_records))
		cout << "value is out of range" << endl << endl;
    else
    {
	   f_db.seekg(((record_num) * record_size), ios::beg);
       f_db >> id >> first_name >> last_name >> age >> ticket_num >> fare >> purchase_date;
       Success = true;
    }
		
	return Success;
}
bool Database::checkMax(const int record_num){
    bool Found = false;
    if(!isOpen()){
        cout << "No Database open" << endl;
    }
    else if((record_num < 0) || (record_num >= num_records)){
        Found = true;
    }
    return Found;
}
bool Database::isOpen()
{
   return f_db.is_open();
} 
bool Database::binarySearch(const string Id, int &recordNum,
                      string &FirstName, string &LastName, string &Age,string &TicketNum, string &Fare, string &DateOfPurchase)
{
    // Initialize low and high indices for binary search
    int Low = 0;
    int High = num_records - 1;
    bool Found = false;

    while (!Found && High >= Low)
    {
        // Calculate middle index for current search range
        int Middle = (Low + High) / 2;
        string MiddleId;

        // Update recordNum to current middle index
        recordNum = Middle;

        // Read record at middle index
        if (!readRecord(Middle, MiddleId, FirstName, LastName, Age, TicketNum, Fare, DateOfPurchase)) {
            //cout << "recordNum" << recordNum << endl;
            return false; // Return false if reading record fails
        }

        // Check if the current record is empty
        if (MiddleId == "_empty_") {
            // Find the nearest non-empty record from current middle
            int nonEmptyRecord = findNearestNonEmpty(Middle, Low , High);
            if (nonEmptyRecord == -1) {
                // Return false if no non-empty record is found
                return false; 
            }

            // Update Middle to index of nearest non-empty record
            Middle = nonEmptyRecord;
            //cout << "recordNum" << recordNum << endl;
            if (!readRecord(Middle, MiddleId, FirstName, LastName, Age, TicketNum, Fare, DateOfPurchase)) {
                return false; // Return false if reading record fails
            }
            //correct  the record num for nearest space to insert
            if (stoi(MiddleId)>stoi(Id)){
                recordNum=Middle-1;
            }
            else{
                recordNum=Middle+1;
            }
        }

        // Convert string IDs to integers and compare
        try {
            int middleIdInt = stoi(MiddleId);
            int targetIdInt = stoi(Id);

            // Check if the target ID is found
            if (middleIdInt == targetIdInt) {
                Found = true;
                recordNum = Middle; // Store the found record number
            } else if (middleIdInt < targetIdInt) {
                Low = Middle + 1; // Narrow the search range to upper half
            } else {
                High = Middle - 1; // Narrow the search range to lower half
            }
        } catch (const std::invalid_argument&) {
            // Handle invalid or empty records
            High = Middle - 1; // Update the high index
        }
    }

    if (Found)
        return true; // Return true if ID is found
    else {
        cout << "Could not get record " << Id << endl;
        return false; // Return false if ID is not found
    }
}

int Database::findNearestNonEmpty(int start, int lowLimit, int highLimit) {
    // Initialize steps for backward and forward search
    int backStep = 1;
    int forwardStep = 1;

    while (true) {
        // Search for non-empty record in backward direction
        if (start - backStep >= lowLimit) {
            string id, firstName, lastName, age, ticketnum, fare, dateOfPurchase;
            if (readRecord(start - backStep, id, firstName, lastName, age, ticketnum, fare, dateOfPurchase) && id != "_empty_") {
                return start - backStep; // Return index of non-empty record
            }
            backStep += 1; // Increase step for backward search
        }

        // Search for non-empty record in forward direction
        if (start + forwardStep <= highLimit) {
            string id, firstName, lastName, age, ticketnum, fare, dateOfPurchase;
            if (readRecord(start + forwardStep, id, firstName, lastName, age, ticketnum,fare, dateOfPurchase) && id != "_empty_") {
                return start + forwardStep; // Return index of non-empty record
            }
            forwardStep += 1; // Increase step for forward search
        }

        // Terminate the search if limits are reached
        if (start - backStep < lowLimit && start + forwardStep > highLimit) {
            break;
        }
    }
    return -1; // Return -1 if no non-empty record is found
}