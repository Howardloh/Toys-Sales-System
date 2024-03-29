#include <iostream>
#include <string>
#include <fstream>
#include <chrono> 
#include <ctime>
using namespace std;
/***************************************************Structures****************************************************************/
//Struture for Toys
struct Toys{
  string name;
  int quantity;
  double price;
};

//Structure for Billing
struct Billing{
  string name;
  int quantity;
  double price;
};
/*****************************************************************************************************************************/
/*************************************************Add items and bills*********************************************************/
//Add new item to the store
Toys* addItem(Toys t[], int size){
  cout<<"\t\t\t\t\t"<<"Name: ";
  cin>> t[size].name;

  cout<<"\t\t\t\t\t"<<"Quantity: ";
  cin>> t[size].quantity;
  // Input validation
  while(true){
        if(cin.fail()){
          cin.clear();
          cin.ignore(numeric_limits<streamsize>::max(),'\n');
          cout<<"\t\t\t\t\t"<<"Please enter a valid quantity : ";
          cin>>t[size].quantity;
        }
        if(!cin.fail()){
          break;
        }
      }
  cout<<"\t\t\t\t\t"<<"Price: ";
  cin>> t[size].price;
  // Input validation
  while(true){
        if(cin.fail()){
          cin.clear();
          cin.ignore(numeric_limits<streamsize>::max(),'\n');
          cout<<"\t\t\t\t\t"<<"Please enter a valid price : ";
          cin>>t[size].price;
        }
        if(!cin.fail()){
          break;
        }
      }

  return t;
}

// Add an item to the billing statement
Billing* addBill(Billing b[], Toys t[], int num, int quantity, int size){
  b[size].name = t[num].name;
  b[size].quantity = quantity;
  b[size].price = t[num].price;
  return b;
}
/****************************************************************************************************************************/
/*************************************************Display items and bills****************************************************/
// Display all the current items in the store
void displayItems(Toys t[], int size){
  double total =0;
  cout<<"\t\t\t\t\t"<<"   List of items in Toys store"<<endl;
  cout<<"\t\t\t\t"<<"----------------------------------------------------"<<endl;
  cout<<"\t\t\t\t"<<"\tName\t\tQuantity\tPrice"<<endl;

  for(int i = 0 ; i < size+1 ; i++){
    if(t[i].quantity==0){
      cout<<"\t\t\t\t"<< t[i].name << " is out of stock."<<endl;
      continue;
    }else{
      cout<<"\t\t\t\t"<<i+1<<".\t"<< t[i].name <<"\t\t  "<< t[i].quantity <<"\t\t "<< t[i].price <<"\t  "<<endl;
    }
  }
  cout<<endl;
}

// Display billing statement
void displayBill(Billing b[], int size){
double total =0;
cout<<"\t\t\t\t"<<"\tName\t\tQuantity\tPrice\tTotalPrice"<<endl;

for(int i = 0 ; i < size+1 ; i++){
  cout<<"\t\t\t\t"<<i+1<<".\t"<< b[i].name <<"\t\t  "<< b[i].quantity <<"\t\t "<< b[i].price <<"\t  "<< b[i].price*b[i].quantity <<endl;
  total += b[i].price*b[i].quantity;
}
cout<<endl;
cout<<"\t\t\t\t"<<"----------------------------------------------------------------"<<endl;
cout<<"\t\t\t\t"<<"Total :\t\t\t\t\t\t  "<<total<<endl;
cout<<"\t\t\t\t"<<"----------------------------------------------------------------"<<endl;
}
/****************************************************************************************************************************/
/*************************************Update necessary information for items and bills***************************************/
// Update existing items
Toys* updateItem(Toys t[], int num){
    Toys* ptr;
    ptr = t;
    ptr = addItem(t, num);
    return ptr;
}

// Update quantity of the items after adding the selected item to the billing statement
Toys* updateQuantity(Toys t[], int num, int quantity){
  t[num].quantity = t[num].quantity - quantity;
  return t;
}

// Update the toys data
void updateData(Toys t[], int size){
  ofstream writeFile;
  writeFile.open("StockList.txt", ios::trunc);
  writeFile<<"Name\tQuantity\tPrice"<<endl;

  for(int i =0; i < size + 1; i++){
    if( i == size){
    writeFile<< t[i].name <<"\t"<< t[i].quantity <<"\t\t"<< t[i].price;
    }else{
    writeFile<< t[i].name <<"\t"<< t[i].quantity <<"\t\t"<< t[i].price <<endl;
    }
  }
  writeFile.close();
}

// Delete selected item from the billing statement and update the latest billing statement
Billing* deleteBill(Billing b[],int num, int size){
  for(int i = num ; i < size ; i++){
    b[i].name = b[i+1].name;
    b[i].quantity = b[i+1].quantity;
    b[i].price = b[i+1].price;
  }
  return b;
}

// Clear the billing statement after the purchase is made
Billing* clear(Billing b[], int size){
  for(int i = 0 ; i < size ; i++){
    b[i].name = "null";
    b[i].quantity = 0;
    b[i].price = 0;
  }
  return b;
}
/****************************************************************************************************************************/
/*************************************Print and Display transaction history**************************************************/
// Display current transaction and write the billing statement to the TransactionHistory file
void printTransaction(Billing b[], int size, int discount, int transaction, double payment){
  double total =0;

  time_t now = time(0);
  char* dt = ctime(&now);

  cout<<"\t\t\t"<<"************************************************************"<<endl;
  cout<<"\t\t\t\t\tTransaction Number :\t#"<<transaction<<endl;
  cout<<"\t\t\t\t\t   "<<dt<<endl;
  cout<<"\t\t\t"<<"\tName\t\tQuantity\tPrice\tTotalPrice"<<endl;
  for(int i = 0 ; i < size+1 ; i++){
    cout<<"\t\t\t"<<i+1<<".\t"<< b[i].name <<"\t\t  "<< b[i].quantity <<"\t\t "<< b[i].price <<"\t  "<< b[i].price*b[i].quantity <<endl;
    total += b[i].price*b[i].quantity;
  }
  total = total *(100-discount)/100;
  int change = payment - total;
  cout<<endl;
  cout<<"\t\t\t"<<"------------------------------------------------------------"<<endl;
  cout<<"\t\t\t"<<"Discount \t\t\t\t\t  "<< discount <<"%"<<endl;
  cout<<"\t\t\t"<<"Total \t\t\t\t\t\t  "<< total <<endl;
  cout<<"\t\t\t"<<"Payment \t\t\t\t\t  "<< payment <<endl;
  cout<<"\t\t\t"<<"Change \t\t\t\t\t\t  "<< change <<endl;
  cout<<"\t\t\t"<<"************************************************************"<<endl;
  cout<<endl;
  cout<<endl;

  // Write file
  ofstream writeFile;
  writeFile.open("TransactionHistory.txt", ios::app);
  writeFile<<"************************************************************"<<endl;
  writeFile<<"\t\tTransaction Number :\t#"<<transaction<<endl;
  writeFile<<"\t\t   "<<dt<<endl;
  writeFile<<"\tName\t\tQuantity\tPrice\tTotalPrice"<<endl;
  for(int i =0; i < size + 1; i++){
    writeFile<<i+1<<".\t"<< b[i].name <<"\t\t  "<< b[i].quantity <<"\t\t "<< b[i].price <<"\t  "<< b[i].price*b[i].quantity <<endl;
  }
  writeFile<<endl;
  writeFile<<"------------------------------------------------------------"<<endl;
  writeFile<<"Discount \t\t\t\t\t  "<< discount <<"%"<<endl;
  writeFile<<"Total \t\t\t\t\t\t  "<< total <<endl;
  writeFile<<"Payment \t\t\t\t\t  "<< payment <<endl;
  writeFile<<"Change \t\t\t\t\t\t  "<< change <<endl;
  writeFile<<"************************************************************"<<endl;
  writeFile<<endl;
  writeFile<<endl;
  writeFile<<endl;
}

// Display all the transactions made
void showTransactionHistory(){
  string txt;

  // Read file
  ifstream readFile;
  readFile.open("TransactionHistory.txt", ios::in);
   
  while (getline (readFile, txt)) {
      cout << txt <<endl;
  }
}

/****************************************************************************************************************************/
/****************************************Obtain necessary data for the system************************************************/
// Read the data
Toys* readData(Toys t[]){
    string txt;
    ifstream readFile;
    readFile.open("StockList.txt", ios::in);
    int i = 0;
    getline(readFile, txt); // Skip one line
    while(!readFile.eof()){
      readFile >> t[i].name; readFile >> t[i].quantity; readFile >> t[i].price;
      i++;        
    }
    readFile.close();
    return t;
}

// get the numbers of types of the toys in the store
int getSize(Toys t[]){
  string txt;
  ifstream readFile;
  readFile.open("StockList.txt", ios::in);
  getline(readFile, txt);// Skip one line
  int i = 0;
  int size = 0;
  while(!readFile.eof()){
    readFile >> t[i].name;
    readFile >> t[i].quantity;
    readFile >> t[i].price;
    i++;
    size++;        
  }
  readFile.close();
  return size;
}

// Get the transaction number
int getTransactionNumber(){
  string line;
  ifstream readFile;
  readFile.open("TransactionHistory.txt");
  int num = 0;
  if(readFile.is_open()){
    while (getline(readFile, line)){
      auto position = line.find("#");

      if( position <= line.size() )
      {
        num= stoi( line.substr( position + 1));
      }
    }
  }else{
    num = 11035;
  }

  num++;
  readFile.close();
  return num;
}
/****************************************************************************************************************************/
/************************************************************MAIN************************************************************/
int main(){
  // For toys
  Toys t[100];
  //Toys b[100]; 
  Toys* ptr;  
  // Toys* ptrB;
  // ptrB = b;  
  ptr = t;      
  ptr = readData(ptr);
  int input = 0;
  int size = getSize(ptr);
  int number =0;

  // For bills
  Billing b[100];
  Billing* ptrB;
  ptrB = b;
  int sizeB = 0;
  int quantity = 0;
  int discount = 0;
  int transaction = getTransactionNumber(); // Auto-increment Transaction number
  double payment = 0;

  string tab = "\t\t\t\t\t";

// Do while loop for user to select the available options
    do{
      cout<<"\n\n"<<tab<<" Welcome to the POS System\n"<<endl;
      cout<<tab<< "1. View all toys information" <<endl;
      cout<<tab<< "2. Add new item to the store" <<endl;
      cout<<tab<< "3. Update item" <<endl;
      cout<<tab<< "4. Billing System"<<endl;
      cout<<tab<< "5. Show transaction history"<<endl;
      cout<<tab<< "6. Exit"<<endl;
      cout<<tab<< "Option : ";
      cin>>input;
      // Input validation
      while(true){
        if(cin.fail()){
          cin.clear();
          cin.ignore(numeric_limits<streamsize>::max(),'\n');
          cout<<tab<<"Please enter the available option : ";
          cin>>input;
        }
        if(!cin.fail()){
          break;
        }
      }
      cout<<endl;
      cout<<endl;
      switch(input){
        case 1 :// Display all the toys information
                displayItems(ptr, size-1);
                break;

        case 2 ://add new item
                ptr = addItem(ptr, size);
                cout<<endl;
                cout<<"\t\t\t\t"<<" *** New "<<t[size].quantity<<" <"<<t[size].name<<"> are added to the store ***"<<endl;
                size++;

                //Update the StockList file
                updateData(ptr, size-1);
                break;

        case 3://update existing item    
                displayItems(ptr, size-1);
                number = size + 1;
                // while loop for repeating input until it is valid
                while(number>size){
                cout<<"\t\t\t\t"<<"Which item (no.) do you wish to update : ";
                cin>> number;
                // Input validation
                while(true){
                  if(cin.fail()){
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(),'\n');
                    cout<<tab<<"Please enter a valid no. : ";
                    cin>>number;
                  }
                  if(!cin.fail()){
                    break;
                  }
                
                }

                if(number>size){
                  cout<<"\t\t\t\t"<<"Invalid option. Please select the current available option."<<endl;
                  cout<<endl;
                  continue;
                }
                ptr = updateItem(ptr, number-1);
                //Update the StockList file
                updateData(ptr, size-1);
                cout<<endl;
                cout <<"\t\t\t\t"<<"The list has updated to the latest information."<<endl;
                }
                break;

        case 4:// Managing the billing statement
                do{
                  cout<<tab<<"\tBilling System\n"<<endl;
                  cout<<tab<< "1. Select item to the bill" <<endl;
                  cout<<tab<< "2. Delete item from the bill" <<endl;
                  cout<<tab<< "3. Calculate and print the bill" <<endl;
                  cout<<tab<< "4. Exit Billing Menu" <<endl;
                  cout<<tab<< "Option : ";
                  cin>>input;
                  cout<<endl;
                  switch(input){
                    case 1: // Select item into billing statement
                            displayItems(ptr, size-1);
                            cout<<"\t\t\t\t"<<"Type -1 to exit this section"<<endl;

                            // While loop to continue inserting selected item to the billing statement 
                            while(number!=-1){
                              cout<<"\t\t\t\t"<<"Select an item (no.) to be added to the bill : ";
                              cin >> number;
                              // Input validation
                              while(true){
                                if(cin.fail()){
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(),'\n');
                                cout<<"\t\t\t\t"<<"Please enter a valid no. : ";
                                cin>>number;
                                }
                                if(!cin.fail()){
                                  break;
                                }
                              }

                              if(number>size){
                                cout<<"\t\t\t\t"<<"Invalid option. Please select the current available option."<<endl;
                                cout<<endl;
                                break;
                              }else if(number<0){
                                cout<<endl;
                                cout<<endl;
                                break;
                              }

                              cout<<"\t\t\t\t"<<"Quantity to be sold : ";
                              cin >> quantity;
                              // Input validation
                              while(true){
                                if(cin.fail()){
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(),'\n');
                                cout<<"\t\t\t\t"<<"Please enter a valid quantity : ";
                                cin>>quantity;
                                }
                                if(!cin.fail()){
                                  break;
                                }
                              }
                              cout<<endl;

                              //Insert selected item into the billing statement
                              ptrB = addBill(ptrB, ptr, number-1, quantity, sizeB);
                              ptr = updateQuantity(ptr, number-1, quantity);
                              sizeB++;
                            }

                            updateData(ptr, size-1);
                            displayBill(ptrB, sizeB-1);
                            number = 0;
                            cout<<endl;
                            cout<<endl;
                            cout<<endl;
                            break;

                    case 2: // Select item to be delected from the billing statement
                            displayBill(ptrB, sizeB-1);
                            cout<<"\t\t\t\t"<<"Select which item (no.) to be deleted from the bill : ";
                            cin >> number;
                            // Input validation
                            while(true){
                                if(cin.fail()){
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(),'\n');
                                cout<<"\t\t\t\t"<<"Please enter a valid no. : ";
                                cin>>number;
                                }
                                if(!cin.fail()){
                                  break;
                                }
                              }

                            // Delete selected item from the billing statement
                            ptrB = deleteBill(ptrB, number-1, sizeB);
                            sizeB--;
                            displayBill(ptrB, sizeB-1);
                            break;

                    case 3: // Finalize the billing statement with required inputs(discount, payment)
                            cout<<tab<<"Discount % : ";
                            cin >> discount;
                            // Input validation
                            while(true){
                                if(cin.fail()){
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(),'\n');
                                cout<<tab<<"Please enter a valid discount % (0-100) : ";
                                cin>>discount;
                                }
                                if(!cin.fail()){
                                  break;
                                }
                              }
                            cout<<tab<<"Amount Paid : ";
                            cin >> payment;
                            // Input validation
                            while(true){
                                if(cin.fail()){
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(),'\n');
                                cout<<tab<<"Please enter a valid amount of payment : ";
                                cin>>payment;
                                }
                                if(!cin.fail()){
                                  break;
                                }
                              }
                            cout<<endl;

                            // Print current transaction and write the details into TransactionHistory file
                            printTransaction(ptrB, sizeB-1, discount,transaction,payment);
                            transaction++;

                            //Clear the billing statement
                            ptrB = clear(ptrB, sizeB);
                            sizeB = sizeB - sizeB;
                            input = 4;
                            break;
                    
                    case 4:// Exit Billing system
                            cout<<tab<<"Exiting Billing System...."<<endl;
                            break;
                            
                    default:
                            cout<<tab <<"Please enter the available option."<<endl;
                            break;
                      

                        }

                      }while(input!=4);
                            
                break;
                
        case 5:// Display all the transactions made
                showTransactionHistory();
                break;

        case 6://Exit POS System
                cout<<tab<< "Exiting...";
                break;

        default:
                cout<<tab<< "Please enter the available option.";
                break;
    }
            
  }while(input!=6);

   return 0;
 
}

