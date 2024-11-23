//-----------------------------------------------------
// Example code to read from fixed length records (random access file
// Author:  Susan Gauch
// Last updated:  Jan. 20, 2022
//-----------------------------------------------------

#include "DB.h"

DB::DB()
{
  num_records = 0;
}

DB::~DB() {}

    /**
   * Opens the file in read/write mode
   * 
   * @param filename (e.g., input.data)
   * @return status true if operation successful
   */

void DB::open(string filename){
    // bool to check if open
  
if (Open == false){

    // Set the number of records
    num_records = NUM_RECORDS;

    // Open file in read/write mode
    Din.open(filename.c_str(), fstream::in | fstream::out | fstream::app);
    Open = true;
}

  else {
    cout << "Database already open, please close and try again" << endl;
  }

}

void DB::close()
{
    Open = false;
    Din.close();
}

// void readCSV(string filename, string id, string last, string first, string age, string ticket, string fare, string date) {
//     ifstream Din;
//     Din.open(filename);
//     getline(Din, id, ',');
//     getline(Din, last, ',');
//     getline(Din, first, ',');
//     getline(Din, age, ',');
//     getline(Din, ticket, ',');
//     getline(Din, fare, ',');
//     getline(Din, date);
// }


    // Notes
    // -----------------------------------------------------------------------
   /*
   * Get record number n (Records numbered from 0 to NUM_RECORDS-1)
   * 
   * @param record_num
   * @return values of the fields with the name of the field and
   *         the values read from the record
   */
    // -----------------------------------------------------------------------

bool DB::readRecord(const int RecordNum,
                    string &Id, string &lName, string &fName, string &age, string &tNum, string &fare, string &dop)
{
  bool status = false;

  if ((0 <= RecordNum) && (RecordNum < NUM_RECORDS))
  {
    Din.seekg(RecordNum * RECORD_SIZE, ios::beg);
    Din >> Id >> lName >> fName >> age >> tNum >> fare >> dop;
    status = true;
  }
  else
    cout << "Record " << RecordNum << " out of range.\n";

  return status;
}

    /**
   * Binary Search by id with possible empty records
   * returns true if the id is found, false otherwise
   * sets recordNum to the record number of the id (if found)
   * else, sets recordNum to the recordNumber of record after where the id was expected
   * @param id
   */


bool DB::binarySearch(const string Id, int &recordNum,
                      string &lName, string &fName, string &age, string &tNum, string &fare, string &dop)
{
    // Initialize low and high indices for binary search
    int Low = 0;
    int High = NUM_RECORDS - 1;
    bool Found = false;

    while (!Found && High >= Low)
    {
        // Calculate middle index for current search range
        int Middle = (Low + High) / 2;
        string MiddleId;

        // Update recordNum to current middle index
        recordNum = Middle;

        // Read record at middle index
        if (!readRecord(Middle, MiddleId, lName, fName, age, tNum, fare, dop)) {
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
            if (!readRecord(Middle, MiddleId, lName, fName, age, tNum, fare, dop)) {
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

int DB::findNearestNonEmpty(int start, int lowLimit, int highLimit) {
    // Initialize steps for backward and forward search
    int backStep = 1;
    int forwardStep = 1;

    while (true) {
        // Search for non-empty record in backward direction
        if (start - backStep >= lowLimit) {
            string id, fN, lN, old, tN, fa, dp;
            if (readRecord(start - backStep, id, fN, lN, old, tN, fa, dp) && id != "_empty_") {
                return start - backStep; // Return index of non-empty record
            }
            backStep += 1; // Increase step for backward search
        }

        // Search for non-empty record in forward direction
        if (start + forwardStep <= highLimit) {
            string id, fN, lN, old, tN, fa, dp;
            if (readRecord(start + forwardStep, id, fN, lN, old, tN, fa, dp) && id != "_empty_") {
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
