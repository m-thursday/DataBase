#include "DB.h"
#include <iomanip>


//set the max limit
const int Id_size = 5;
const int lName_size = 12;
const int fName_size = 16;
const int age_size = 5;
const int tNum_size = 17;
const int fare_size = 6;
const int dop_size = 9;

int numRec;
int recSize = Id_size + lName_size + fName_size + age_size + tNum_size + fare_size + dop_size + 1;

  DB db;    //creates the database with empty records

// replace spaces with underscores
void score(string &str){
  string score = "_";
  char space = ' ';
  int length = str.length();
    for (int i = 0; i < length; i++){
      if (str[i] == space){
          str.replace(i, 1, score);
      }
    }
}

// replace underscores with spaces
void space(string &str){
  char score = '_';
  string space = " ";
  int length = str.length();
    for (int i = 0; i < length; i++){
      if (str[i] == score){
          str.replace(i, 1, space);
      }
    }
}


// function to read in the csv file
void readCSV(ifstream &Din, string &id, string &last, string &first, string &age, string &ticket, string &fare, string &date) {
    getline(Din, id, ',');
    getline(Din, last, ',');
    getline(Din, first, ',');
    getline(Din, age, ',');
    getline(Din, ticket, ',');
    getline(Din, fare, ',');
    getline(Din, date);
}



// Write a fixed length record to the file.  
void writeRecord(ofstream &Dout, const string &Id, const string &lName, 
                 const string &fName, const string &age, const string &tNum, 
                 const string &fare, const string &dop) {
    // Write ID
    Dout << setw(Id_size) << left << Id.substr(0, Id_size);
    
    // Write Last Name
    Dout << setw(lName_size) << left << lName.substr(0, lName_size);
    
    // Write First Name
    Dout << setw(fName_size) << left << fName.substr(0, fName_size);
    
    // Write Age
    Dout << setw(age_size) << left << age.substr(0, age_size);
    
    // Write Ticket Numeber
    Dout << setw(tNum_size) << left << tNum.substr(0, tNum_size);

    // Write Fare
    Dout << setw(fare_size) << left << fare.substr(0, fare_size);

    // Write Date of Purchase
    Dout << setw(dop_size) << left << dop.substr(0, dop_size) << endl;

    numRec ++;
}

void createDB(const string inFilename)
{
ifstream Din;   // the csv file
ofstream Dout;  // the data file
ofstream ConfigOut;  // the config file
string Id = "ID";
string lName = "LAST NAME";
string fName = "FIRST NAME";
string age = "AGE";
string tNum = "TICKET NUMBER";
string fare = "FARE";
string dop = "DATE OF PURCHASE";


   Din.open  (inFilename + ".csv");
   Dout.open(inFilename + ".data");

   
   while (!Din.eof())  
   {
      // read csv file
      readCSV(Din, Id, lName, fName, age, tNum, fare, dop);

      // change spaces to underscores
      score(fName);
      score(tNum);

      //write record
      writeRecord (Dout, Id, lName, fName, age, tNum, fare, dop);

      //write an empty record
      writeRecord (Dout, "NA", "NA", "NA", "NA", "NA", "NA", "NA");

   }
   Din.close();
   Dout.close();

   Dout.open(inFilename + ".config");
   Dout  << "Record Size: " << recSize << endl << "Number of Records: " << numRec << endl;
   Dout.close();

}

// displays choices for the user
void menu() {
    cout << "\n" << "\n";
    cout << "-------Options-------" << endl;
    cout << "1. Create Database" << endl;
    cout << "2. Open Database" << endl;
    cout << "3. Close Database" << endl;
    cout << "4. Display Record" << endl;
    cout << "5. Update Record" << endl;
    cout << "6. Create Report" << endl;
    cout << "7. Add Record" << endl;
    cout << "8. Delete Record" << endl;
    cout << "9. Quit" << endl;

}

// takes the users choice
int getChoice() {
  int value;
  cout << "\n";
  cout << "choose an option please" << endl;
  cout << ">>>  ";
  cin >> value;
  do {
      if (value > 9 || value < 1){
    cout << "Does not match criteria, please try again" << endl;
    cout << ">>>  ";
    cin >> value;
  }
  } while (value > 9 || value < 1);
  
  return value;
}

int main(int argc, char const *argv[])
{
  string Id = "ID";
  string lName = "LAST NAME";
  string fName = "FIRST NAME";
  string age = "AGE";
  string tNum = "TICKET NUMBER";
  string fare = "FARE";
  string dop = "DATE OF PURCHASE";
  int recordNum;
  int choice;
  string fileName;




  do {
    // calls menu and choice functions
    menu();
    choice = getChoice();

  switch (choice){
  
    case 1:   // create database
      cout << "Option 1: create database" << endl;
      cout << "what file would you like to use?" << endl << ">>>   ";
      cin >> fileName;

      createDB(fileName);
      break;

    case 2:   // open database
      cout << "Option 2: open database " << endl;
      cout << "What database would you like to open?" << endl;

      // private helper method DBisOpen, implement to check for opening a new database
      // add replacement function for underscore to space


      cout << ">>>   " ;
      cin >> fileName;

      db.open(fileName + ".data");

      break;

    case 3:   // close database
      cout << "Option 3: close database" << endl;

      db.close();
      
      break;

    case 4:   // display record
      cout << "Option 4: display record" << endl;

      break;

    case 5:   // update record
      cout << "Option 5: update record" << endl;

      break;

    case 6:   // create record
      cout << "Option 6: create record" << endl;

      break;

    case 7:   // add record
      cout << "Option 7: add record" << endl;

      break;

    case 8:   // delete record
      cout << "Option 8: delete record" << endl;

      break;

  }

  } while (choice != 9);


  // calls constructor
 
 

  // opens "input.data"
  db.open(fileName + ".data");

  cout << "\n------------- Testing readRecord ------------\n";

  // Reads record 0
  // Then prints the values of the 7 fields to the screen with the name of the
  // field and the values read from the record, i.e.,

  recordNum = 0;
  if (db.readRecord(recordNum, Id, lName, fName, age, tNum, fare, dop)){
    space(fName);
    space(tNum);
    cout << "recordNum: " << recordNum << ", Id: " << Id
         << ", Last Name: " << lName << ", First Name: " << fName
         << ", Age: " << age << ", Ticket Number:" << tNum 
         << ", Fare: " << fare << ", Date of Purchase:" << dop << "\n\n";
  }
  else
    cout << "Could not get record " << recordNum << ".\n\n";

  // Reads record 19 (last real (non-empty)record)
  recordNum = 19;
  if (db.readRecord(recordNum, Id, lName, fName, age, tNum, fare, dop)){
    space(fName);
    space(tNum);
    cout << "recordNum: " << recordNum << ", Id: " << Id
         << ", Last Name: " << lName << ", First Name: " << fName
         << ", Age: " << age << ", Ticket Number:" << tNum 
         << ", Fare: " << fare << ", Date of Purchase:" << dop << "\n\n";
  }
  else
    cout << "Could not get record " << recordNum << ".\n\n";

  // Reads record 6 (last(empty)record)
  recordNum = 6;
  if (db.readRecord(recordNum, Id, lName, fName, age, tNum, fare, dop)){
    space(fName);
    space(tNum);
    cout << "recordNum: " << recordNum << ", Id: " << Id
         << ", Last Name: " << lName << ", First Name: " << fName
         << ", Age: " << age << ", Ticket Number:" << tNum 
         << ", Fare: " << fare << ", Date of Purchase:" << dop << "\n\n";
  }
  else
    cout << "Could not get record " << recordNum << ".\n\n";

  // Reads record -1 (last(empty)record)
  recordNum = -1;
  if (db.readRecord(recordNum, Id, lName, fName, age, tNum, fare, dop)){
    space(fName);
    space(tNum);
    cout << "recordNum: " << recordNum << ", Id: " << Id
         << ", Last Name: " << lName << ", First Name: " << fName
         << ", Age: " << age << ", Ticket Number:" << tNum 
         << ", Fare: " << fare << ", Date of Purchase:" << dop << "\n\n";
  }
  else
    cout << "Could not get record " << recordNum << ".\n\n";

  // Reads record 1000 (last(empty)record)
  recordNum = 1000;
  if (db.readRecord(recordNum, Id, lName, fName, age, tNum, fare, dop)){
    space(fName);
    space(tNum);
    cout << "recordNum: " << recordNum << ", Id: " << Id
         << ", Last Name: " << lName << ", First Name: " << fName
         << ", Age: " << age << ", Ticket Number:" << tNum 
         << ", Fare: " << fare << ", Date of Purchase:" << dop << "\n\n";
  }
  else
    cout << "Could not get record " << recordNum << ".\n\n";

  // cout << "\n------------- Testing binarySearch ------------\n";

  // // Find record with id 42 (should not be found)
  // Id = "00010";
  // cout << "Looking for Id: " << Id << endl;
  // bool found = db.binarySearch(Id,recordNum, lName, fName, age, tNum, fare, dop);
  // if (found){

  //   cout << "recordNum: " << recordNum << ", Id: " << Id
  //        << ", Last Name: " << lName << ", First Name: " << fName
  //        << ", Age: " << age << ", Ticket Number:" << tNum 
  //        << ", Fare: " << fare << ", Date of Purchase:" << dop << "\n\n";
  // }
  // else
  //   cout << "Record " << Id << " not found."<<"Location for insert: "<<recordNum<<endl;

  // // Find record with id 00000 (the first one in the file)
  // Id = "00000";
  // cout << "Looking for Id: " << Id << endl;
  // // update the value of recordnum if found, populate the fields
  // found = db.binarySearch(Id,recordNum, lName, fName, age, tNum, fare, dop);
  // if (found){
  //   cout << "recordNum: " << recordNum << ", Id: " << Id
  //        << ", Last Name: " << lName << ", First Name: " << fName
  //        << ", Age: " << age << ", Ticket Number:" << tNum 
  //        << ", Fare: " << fare << ", Date of Purchase:" << dop << "\n\n";
  // }
  // else
  //   cout << "Record " << Id << " not found."<<"Location for insert: "<<recordNum<<endl;

  // // Find record with id 00015 (the last one in the file)
  // Id = "00015";
  // cout << "Looking for Id: " << Id << endl;
  // found = db.binarySearch(Id,recordNum, lName, fName, age, tNum, fare, dop);
  // if (found){
  //   cout << "recordNum: " << recordNum << ", Id: " << Id
  //        << ", Last Name: " << lName << ", First Name: " << fName
  //        << ", Age: " << age << ", Ticket Number:" << tNum 
  //        << ", Fare: " << fare << ", Date of Purchase:" << dop << "\n\n";
  // }
  // else
  //   cout << "Record " << Id << " not found."<<"Location for insert: "<<recordNum<<endl;

  // // Find record with id 00006 (somewhere in the middle)
  // Id = "000006";
  // cout << "Looking for Id: " << Id << endl;
  // found = db.binarySearch(Id,recordNum, lName, fName, age, tNum, fare, dop);
  // if (found){
  //   cout << "recordNum: " << recordNum << ", Id: " << Id
  //        << ", Last Name: " << lName << ", First Name: " << fName
  //        << ", Age: " << age << ", Ticket Number:" << tNum 
  //        << ", Fare: " << fare << ", Date of Purchase:" << dop << "\n\n";
  // }
  // else
  //   cout << "Record " << Id << " not found."<<"Location for insert: "<<recordNum<<endl;

  // Close database
  db.close();

  return 0;
}
