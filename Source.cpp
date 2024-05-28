#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<windows.h>
#include<conio.h>
#include<stdio.h>
#include<cstdlib>
#include"talha.h"
using namespace std;


// created by Talha Rana student of UET



// To use this code youe have to make a admin file named as ad_info and the extension 
// will be txt and in that you have to write the username and the password like this 
// talha,123a the first one is name and after comma the string is password.
// By admin you can control every single thing




//Customer function

void available();
void rent();
void rental_report();
void menu();
void new_login();
void return_car();
void customer_portal();
void c_login();

//Admin function

void update_detail();
void add_car();
void utilization();
void a_menu();
void over_all();
void a_login();
void remove_customer();
void show_car();
void maintain();
void remove_car();
void customer_show();
void change_password();
void update_customer();
void report_line();
void ut_read();


//file related function

void cus_line();
void car_line();
void ad_line();
string get(string line, int field);
void cus_read();
void car_read();
void ad_read();
void cus_write();
void car_write();
void report_write();
void report_read();
void utilization_line();
void utilization_write();
void admin_write();

ifstream fin;
ofstream fout;
int customer_index = 0;			// store customer index to which the customer login
int car_choice;						// to store the car choice of the customer
int hr = 0;				// to store the number of hrs to which the car is rented
int bill = 0;				 // to check the customer bill
int total_bill = 0;		// to store total bill
int car_index = 0;				// to store the car index which the customer selected
int car_number;		// for total number of the cars
int c;		 // the index to which the customer data is store
int  report1;    // the index to which the report data is store
int utilize; // the index to which the utilization of car data is store
// the struct to for report
struct report
{
	string name;
	string num;
	string car;
	int rent = 0;
};
// struct for car data
struct car
{
	string car_name;
	string color;
	string fuel_type;
	string max_speed;
	string number_plate;
	int price = 0;
	float travel = 0;
	bool rented = false;
	int number_of_time = 0;
	string date;
	int hr = 0;
};
// struct for customer data
struct customer {
	string name;
	string password;
	string num;
	string cnic;
	string address;
	string cars;
	int rent = 0;
};
// struct for admin data
struct admin
{
	string name;
	string password;
	string num;
	string cnic;
};
customer* cus_p; //  pointer for dynamic array of customer type for customers
car* add_car_p; //  pointer for dynamic array of car type for car
car* ut; //pointer for dynamic array of utilization of car and the type of array is car
admin* ad; // pointer for dynamic array of admin type for admin
report* rep; // pointer for dynamic array of report of type report
// counters for all the files to count the number of lines in every file in specific variable
int counter_cus = 0, counter_car = 0, counter_ad = 0, counter_report = 0, counter_ut = 0;
int main()
{
	fout.open("cus_info.txt", ios::app);
	fout.close();
	fout.clear();
	fout.open("car_info.txt", ios::app);
	fout.close();
	fout.clear();
	fout.open("ad_info.txt", ios::app);
	fout.close();
	fout.clear();
	fout.open("report.txt", ios::app);
	fout.close();
	fout.clear();
	fout.open("utilization.txt", ios::app);
	fout.close();
	fout.clear();
	cus_line();// to read number of customer
	c = counter_cus; /*this is because c is the index where we store customer data when counter_cus is equal
							to c so memory will be allocated as per requirement*/
	car_line();
	car_number = counter_car; /*this is because car_number is the index where we store cars data when counter_car
								is equal to car_number so memory will be allocated as per requirement*/
	ad_line();
	report_line();
	report1 = counter_report; /* this is because report1 is the index where we store report data when counter_report
										is equal to report1 so memory will be allocated as per requirement*/
	utilization_line();
	utilize = counter_ut;  /*this is because utilize is the index where we store rented car data  when counter_ut
										is equal to utilize so memory will be allocated as per requirement*/
	rep = new report[counter_report];
	cus_p = new customer[counter_cus];// dynamically memory allocated according to the number of line in file
	add_car_p = new car[counter_car];
	ut = new car[counter_ut];
	ad = new admin[counter_ad];
	cus_read();
	car_read(); // to read the data from different file
	ad_read();
	report_read();
	ut_read();


	system("color 0e");
	int choice;
	int end;
	char choice_mas;
	system("cls");
	cout << "\t\t\t\t***********************************************************\n";
	cout << "\t\t\t\t************** TR Car Rental Management System ************\n";
	cout << "\t\t\t\t***********************************************************\n";
	//cout << "\n\n\nEnter your domain:\n1.As a customer.\n2.As a admin.\n";
	cout << "\n\n\nEnter your domain:";
	string arr[] = { "1.As a customer","2.As a admin." };
	choice =complete_menu(arr, 2); 
	cout << "\n\n";
	if (choice == 1) {
		customer_portal(); // for customer login or for new login
	}
	else
	{
		if (choice == 2) {
			do {
				system("cls");
				a_login(); // for admin login
				cout << "\n\n\n\t\t\t\t\t1.If you want to enter another ID and Password.\n\t\t\t\t\t2.Exit.";
				cin >> end;
			} while (end == 1);
			cout << "\n\n\n\t\t\t\t\tDo you want to change your domain[y/n]:";
			cin >> choice_mas;
			if (choice_mas == 'y' || choice_mas == 'Y')
			{
				customer_portal();
			}
			else
			{
				system("cls");
				cout << "\t\t\t\t***********************************************************\n";
				cout << "\t\t\t\t******************* Ending Portal *************************\n";
				cout << "\t\t\t\t***********************************************************\n\n\n";
				cout << "\n\n\n\t\t\t\t\tThank you for getting our services.\n\n";
			}
		}
	}


	cus_write();
	car_write(); // to write data in the files 
	report_write();
	utilization_write();
	admin_write();
	delete[]cus_p;
	delete[]add_car_p;
	delete[]rep;       // delete the dynamic array after the data is write in the files
	delete[]ad;
	delete[]ut;
	return 0;
}
void cus_line()
{
	string line;
	fin.open("cus_info.txt");
	if (fin.is_open())
	{
		while (getline(fin, line))
		{
			counter_cus++;
		}
	}
	fin.close();
	fin.clear(); /* we are controlling all the files with only two variable one for ifstream and one for ofstream so
				  it is necessary to clear the varibale for next file */
}
void utilization_line()
{
	string line;
	fin.open("utilization.txt");
	if (fin.is_open())
	{
		while (getline(fin, line))
		{
			counter_ut++;
		}
	}
	fin.close();
	fin.clear();
}
void report_line()
{
	string line;
	fin.open("report.txt");
	if (fin.is_open())
	{
		while (getline(fin, line))
		{
			counter_report++;
		}
	}
	fin.close();
	fin.clear();
}
void car_line()
{
	string line;
	fin.open("car_info.txt");
	if (fin.is_open())
	{
		while (getline(fin, line))
		{
			counter_car++;
		}
	}
	fin.close();
	fin.clear();
}
void ad_line()
{
	string line;
	fin.open("ad_info.txt");
	if (fin.is_open())
	{
		while (getline(fin, line))
		{
			counter_ad++;
		}
	}
	fin.close();
	fin.clear();
}
string get(string line, int field)
{
	string item;
	int comma = 1;
	for (int i = 0; i < line.length(); i++)
	{
		if (line[i] == ',')
		{
			comma++;
		}
		else if (comma == field)
		{
			item = item + line[i];
		}
	}
	return item;
}
void cus_read()
{											// reading data from customer file
	string line;
	fin.open("cus_info.txt");
	if (fin.is_open())
	{
		int i = 0;
		while (getline(fin, line))
		{
			cus_p[i].name = get(line, 1);
			cus_p[i].password = get(line, 2);
			cus_p[i].num = get(line, 3);
			cus_p[i].cnic = get(line, 4);
			cus_p[i].address = get(line, 5);
			i++;
		}
		fin.close();
		fin.clear();
	}
}
void car_read()
{
	string line;
	fin.open("car_info.txt");
	if (fin.is_open())
	{
		int i = 0;
		while (getline(fin, line))
		{
			add_car_p[i].car_name = get(line, 1);
			add_car_p[i].color = get(line, 2);
			add_car_p[i].fuel_type = get(line, 3);
			add_car_p[i].max_speed = get(line, 4);
			add_car_p[i].number_plate = get(line, 5);
			add_car_p[i].price = stoi(get(line, 6));
			add_car_p[i].travel = stof(get(line, 7));
			istringstream(get(line, 8)) >> add_car_p[i].rented;  /* sstream library built in function to convert
																				string into bool*/
			add_car_p[i].number_of_time = stoi(get(line, 9));  // convert string into int built in string library function
			add_car_p[i].date = get(line, 10);
			add_car_p[i].hr = stoi(get(line, 11));
			i++;
		}
		fin.close();
		fin.clear();
	}
}
void ad_read()
{
	string line;						// to read admin data
	fin.open("ad_info.txt");
	if (fin.is_open())
	{
		int i = 0;
		while (getline(fin, line))
		{
			ad[i].name = get(line, 1);
			ad[i].password = get(line, 2);
			ad[i].num = get(line, 3);
			ad[i].cnic = get(line, 4);
			i++;
		}
		fin.close();
		fin.clear();
	}
}
void report_read()
{								// to read report dta for report file
	string line;
	fin.open("report.txt");
	if (fin.is_open())
	{
		int i = 0;
		while (getline(fin, line))
		{
			rep[i].name = get(line, 1);
			rep[i].num = get(line, 2);
			rep[i].car = get(line, 3);
			rep[i].rent = stoi(get(line, 4));
			i++;
		}
		fin.close();
		fin.clear();
	}
}
void ut_read()
{							// data of rented cars
	string line;
	fin.open("utilization.txt");
	if (fin.is_open())
	{
		int i = 0;
		while (getline(fin, line))
		{
			ut[i].car_name = get(line, 1);
			ut[i].color = get(line, 2);
			ut[i].fuel_type = get(line, 3);
			ut[i].max_speed = get(line, 4);
			ut[i].number_plate = get(line, 5);
			ut[i].price = stoi(get(line, 6));
			ut[i].travel = stof(get(line, 7));
			istringstream(get(line, 8)) >> ut[i].rented;
			ut[i].number_of_time = stoi(get(line, 9));
			i++;
		}
		fin.close();
		fin.clear();
	}
}
void customer_portal()
{
	int end;
	do
	{
		system("cls");
		cout << "\t\t\t\t***************************************************\n";
		cout << "\t\t\t\t*************** Customer  portal ******************\n";
		cout << "\t\t\t\t***************************************************\n";
		int ch;
		//cout << "\n1.Already have an account\n2.As a new entry";
		string arr[] = { "1.Already have an account","2.As a new entry" };
		ch = complete_menu(arr, 2);
		system("cls");
		if (ch == 1)
			c_login();
		else
		{
			new_login(); // for new entry
			c_login; // login function for customer
		}
		cout << "\n\n\n\t\t\t\t\t1.If you want enter from another ID and Password.\n\t\t\t\t\t2.Exit.";
		cin >> end;
	} while (end == 1);
	if (end == 2)		// in case of exit
	{
		system("cls");

		cout << "\t\t\t\t***********************************************************\n";
		cout << "\t\t\t\t******************* Ending Portal *************************\n";
		cout << "\t\t\t\t***********************************************************\n\n\n";
		cout << "\n\n\n\t\t\t\t\tThank you for getting our services.\n\n";
	}
}
void new_login()
{
	if (counter_cus == 0) // to add customer data
	{
		cus_p = new customer[1];
		counter_cus = 1;
	}
	else
	{
		customer* temp = new customer[counter_cus + 1];
		for (int i = 0; i < counter_cus; i++)
		{
			temp[i] = cus_p[i];
		}
		counter_cus++;
		delete[]cus_p;
		cus_p = temp;
	}


	cout << "\t\t\t\t***********************************************************\n";
	cout << "\t\t\t\t******************** New login portal *********************\n";
	cout << "\t\t\t\t***********************************************************\n";
	cin.ignore();
	cout << "\n\n\t\t\t\t\tEnter your name:\n\t\t\t\t\t";
	getline(cin, cus_p[c].name);
	cout << "\n\n\t\t\t\t\tEnter your CNIC:\n\t\t\t\t\t";
	getline(cin, cus_p[c].cnic);
	cout << "\n\n\t\t\t\t\tEnter your Phone Number:\n\t\t\t\t\t";
	getline(cin, cus_p[c].num);
	cout << "\n\n\n\t\t\t\t\tEnter your address:\n\t\t\t\t\t";
	getline(cin, cus_p[c].address);
	cout << "\n\n\t\t\t\t\tEnter your password:\n\t\t\t\t\t";
	getline(cin, cus_p[c].password);
	c++;
}
void menu()
{     // menu for customer
	char another;
	do
	{
		system("cls");
		cout << "\t\t\t\t*****************************************************\n";
		cout << "\t\t\t\t************** Menu For Customer ********************\n";
		cout << "\t\t\t\t*****************************************************\n";
		int  choice;
		cout << "\n\n\nMenu for customer";
		//cout << "\n1.To rent a car.\n2.To return a car.\n3.View available car.\n4.Generate rental reports.\n5.Log out.";
		string arr[] = { "1.To rent a car","2.To return a car","3.View available car","4.Generate rental reports","5.Log out" };
		choice = complete_menu(arr, 5);
		//cin >> choice;   // customer function choice
		switch (choice) {
		case 1:
			system("cls");
			rent();       // rent the car
			break;
		case 2:
			system("cls");
			cout << "\t\t\t\t*******************************************************\n";
			cout << "\t\t\t\t*************** Returning car portal ******************\n";
			cout << "\t\t\t\t*******************************************************\n";
			return_car();
			break;
		case 3:
			system("cls");
			available();     // available cars
			break;
		case 4:
			system("cls");
			cout << "\t\t\t\t***********************************************************\n";
			cout << "\t\t\t\t**************** Generate Rental Report *******************\n";
			cout << "\t\t\t\t***********************************************************\n";
			rental_report();
			break;
		case 5:
			system("cls");
			cout << "\t\t\t\t***************************************************\n";
			cout << "\t\t\t\t*************** Log out portal ********************\n";
			cout << "\t\t\t\t***************************************************\n";
			cout << "\n\n\t\t\t\t\tYou are successfully log out.\n";
			return;
		default:
			cout << "\n\n\t\t\t\t\tInvalid input.";
			break;
		}
		cout << "\n\n\n\t\t\t\t\tDo you want to again go to Menu[y/n].";
		cin >> another;
	} while (another == 'y' || another == 'Y');
}
void c_login()
{
	cout << "\t\t\t\t***************************************************\n";
	cout << "\t\t\t\t********** Customer login portal ******************\n";
	cout << "\t\t\t\t***************************************************\n";
	string email, pass;
	cin.ignore(); // to ignore the enter 
	cout << "\n\n\n\t\t\t\t\tEnter User ID:\n\t\t\t\t\t";
	getline(cin, email);										// for customer login
	cout << "\n\n\n\t\t\t\t\tEnter password:\n\t\t\t\t\t";
	getline(cin, pass);
	int j = 0; // to check whether the account matches or not
	for (int i = 0; i < counter_cus; i++) {
		if (cus_p[i].name == email && cus_p[i].password == pass)
		{
			customer_index = i;
			cout << "\t\t\t\t\tSuccessfully login.";
			menu();
			break;
		}
		else
		{
			j++;
		}
	}
	if (j == counter_cus) // when password or username is invalid
	{
		system("cls");
		cout << "\t\t\t\t***************************************************\n";
		cout << "\t\t\t\t********** Customer login portal ******************\n";
		cout << "\t\t\t\t***************************************************\n";
		cout << "\t\t\t\t\tInvalid Password or ID.\n";
	}
}
void a_login()
{
	cout << "\t\t\t\t***************************************************\n";
	cout << "\t\t\t\t************* Admin login portal ******************\n";
	cout << "\t\t\t\t***************************************************\n";
	string email, pass;
	cout << "\n\n\n\t\t\t\t\tEnter User ID:\n\t\t\t\t\t";			// for admin login
	cin >> email;
	cout << "\n\n\n\t\t\t\t\tEnter password:\n\t\t\t\t\t";
	cin >> pass;
	int j = 0; // to check whether admin data is found or not
	for (int i = 0; i <= 9; i++) {
		if (ad[i].name == email && ad[j].password == pass)
		{
			cout << "\t\t\t\t\tSuccessfully login.";
			a_menu();
			break;
		}
		else
		{
			j++;
		}
	}
	if (j == 10)
	{						//when username or password is invalid
		system("cls");
		cout << "\t\t\t\t***************************************************\n";
		cout << "\t\t\t\t************* Admin login portal ******************\n";
		cout << "\t\t\t\t***************************************************\n";
		cout << "\t\t\t\t\tInvalid Password or ID.\n";
	}
}
void a_menu()
{
	char choice_menu;    // admin function menu
	do
	{
		system("cls");
		cout << "\t\t\t\t*****************************************************\n";
		cout << "\t\t\t\t*************** Menu For Admin **********************\n";
		cout << "\t\t\t\t*****************************************************\n";
		int  choice;
		cout << "\n\n\nMenu for Admin";
		//cout << "\n1.To view all the customer.\n2.To view all customer rental reports.\n3.View available car.\n4.Add a customer.\n5.Remove a customer.\n6.Add a car.\n7.Remove a car\n8.Update the car data.\n9.Change admin password\n10.Update customer data\n11.Maintain cars\n12.Utilization report\n13.Log out.\n";
		string arr[] = { "1.To view all the customer","2.To view all customer rental reports","3.View available car","4.Add a customer","5.Remove a customer","6.Add a car","7.Remove a car","8.Update the car data","9.Change admin password","10.Update customer data","11.Maintain cars","12.Utilization report","13.Log out" };
		choice = complete_menu(arr, 13);
		//cin >> choice;  // admin function choice
		switch (choice) {
		case 1:
			system("cls");
			cout << "\t\t\t\t*************************************************************\n";
			cout << "\t\t\t\t******************* All customer portal *********************\n";
			cout << "\t\t\t\t*************************************************************\n";
			customer_show();   // show all customer
			break;
		case 2:
			system("cls");
			cout << "\t\t\t\t***********************************************************\n";
			cout << "\t\t\t\t*************** All rental report portal ******************\n";
			cout << "\t\t\t\t***********************************************************\n";
			over_all(); // show all customer rental reports
			break;
		case 3:
			system("cls");
			available();    // total cars available
			break;
		case 4:
			system("cls");
			new_login();    //to add customer at admin end
			break;
		case 5:
			system("cls");
			cout << "\t\t\t\t***************************************************\n";
			cout << "\t\t\t\t************** Remove Customer ********************\n";
			cout << "\t\t\t\t***************************************************\n";
			remove_customer();    // to remove the customer for admin end
			break;
		case 6:
			system("cls");
			cout << "\t\t\t\t***************************************************\n";
			cout << "\t\t\t\t******************* New Car ***********************\n";
			cout << "\t\t\t\t***************************************************\n";
			add_car();   // add new car
			break;
		case 7:
			system("cls");
			remove_car();   // remove available car 
			break;
		case 8:
			system("cls");
			cout << "\t\t\t\t***************************************************\n";
			cout << "\t\t\t\t***************** Update Data *********************\n";
			cout << "\t\t\t\t***************************************************\n";
			update_detail();   // update the car data
			break;
		case 9:
			system("cls");
			cout << "\t\t\t\t***************************************************\n";
			cout << "\t\t\t\t**************** Change Password ******************\n";
			cout << "\t\t\t\t***************************************************\n";
			change_password(); // change the password of the admin
			break;
		case 10:
			system("cls");
			cout << "\t\t\t\t***************************************************\n";
			cout << "\t\t\t\t***************** Update Data *********************\n";
			cout << "\t\t\t\t***************************************************\n";
			update_customer();   // to update the data of the customer
			break;
		case 11:
			maintain();
			break;
		case 12:
			system("cls");

			cout << "\t\t\t\t*******************************************************\n";
			cout << "\t\t\t\t*************** Utilization report ********************\n";
			cout << "\t\t\t\t*******************************************************\n";
			utilization();
			break;
		case 13:
			system("cls");

			cout << "\t\t\t\t***************************************************\n";
			cout << "\t\t\t\t*************** Log out portal ********************\n";
			cout << "\t\t\t\t***************************************************\n";
			cout << "\n\n\t\t\t\t\tYou are successfully log out.\n";   // to logout from the admin portal
			return;
		default:
			cout << "\n\n\t\t\t\t\tInvalid input.";
			break;
		}
		cout << "\n\n\n\t\t\t\t\tDo you want to go back to menu[y/n]:";
		cin >> choice_menu;
	} while (choice_menu == 'y' || choice_menu == 'Y');
}
void add_car()
{
	if (counter_car == 0)
	{
		add_car_p = new car[1];					// to add new cars
		counter_car = 1;
	}
	else
	{
		car* temp = new car[counter_car + 1];
		for (int i = 0; i < counter_car; i++)
		{
			temp[i] = add_car_p[i];
		}
		counter_car++;
		delete[]add_car_p;
		add_car_p = temp;
	}
	cout << "Enter the details for car" << endl;
	cin.ignore();
	cout << "Enter the name of the car:";
	getline(cin, add_car_p[car_number].car_name);
	cout << "Enter the color of thr car: ";
	getline(cin, add_car_p[car_number].color);
	cout << "Enter the fuel type of the cars:";
	getline(cin, add_car_p[car_number].fuel_type);
	cout << "Enter the maximum speed of the car in km/h:";
	getline(cin, add_car_p[car_number].max_speed);
	cout << "Enter the number plate of the car:";
	getline(cin, add_car_p[car_number].number_plate);
	cout << "Enter the rent of the car per hour in rupees:";
	cin >> add_car_p[car_number].price;
	cout << "Enter the kilometer do you travel:";
	cin >> add_car_p[car_number].travel;
	add_car_p[car_number].rented = false;
	add_car_p[car_number].number_of_time = 0;
	add_car_p[car_number] = add_car_p[car_number];
	car_number++;
}
void show_car()
{
	int number = 1;
	for (int i = 0; i < counter_car; i++)
	{
		cout << "\n\n\n\t\t\t\t";       // show cars which are available
		if (!add_car_p[i].car_name.empty() && !add_car_p[i].rented)
		{
			cout << number << "." << add_car_p[i].car_name << endl;
			number++;
		}
	}
}
void available()
{
	if (counter_car == 0)    // when thers is no car in the file
	{
		cout << "\t\t\t\t*******************************************************\n";
		cout << "\t\t\t\t**************** Available car portal *****************\n";
		cout << "\t\t\t\t*******************************************************\n";
		cout << "\n\n\n\t\t\t\t\tSorry no cars are available right now.\n";
	}
	else
	{
		char details_choice;
		do
		{
			cout << "\t\t\t\t*******************************************************\n";
			cout << "\t\t\t\t**************** Available car portal *****************\n";
			cout << "\t\t\t\t*******************************************************\n";
			show_car();
			int choice;
			cout << "\n\n\n\t\t\t\t\tIf you don't want to see the details press 0.\n\n\n\t\t\t\t\tEnter the number of car do you want to see details:";
			cin >> choice;
			if (choice == 0)
			{
				system("cls");
				cout << "\t\t\t\t*******************************************************\n";
				cout << "\t\t\t\t**************** Available car portal *****************\n";
				cout << "\t\t\t\t*******************************************************\n";
				return;
			}
			else if (choice > 0 && choice <= counter_car)
			{
				if (!add_car_p[choice - 1].car_name.empty())
				{
					system("cls");
					cout << "\t\t\t\t*******************************************************\n";
					cout << "\t\t\t\t******************** Car Details **********************\n";
					cout << "\t\t\t\t*******************************************************\n";
					cout << "\n\n\n\n";
					// to see the details of the cars
					cout << "\t\t\t\t\tName                :\t\t" << add_car_p[choice - 1].car_name << "\n\n";
					cout << "\t\t\t\t\tColor               :\t\t" << add_car_p[choice - 1].color << "\n\n";
					cout << "\t\t\t\t\tFuel type           :\t\t" << add_car_p[choice - 1].fuel_type << "\n\n";
					cout << "\t\t\t\t\tMaximum Speed       :\t\t" << add_car_p[choice - 1].max_speed << " km/h\n\n";
					cout << "\t\t\t\t\tCar Number          :\t\t" << add_car_p[choice - 1].number_plate << "\n\n";
					cout << "\t\t\t\t\tPrice per hour      :\t\t" << add_car_p[choice - 1].price << "Rs\n\n";
					cout << "\n\n\n\t\t\t\tDo you want to see details of another car[y/n]:";
					cin >> details_choice;
					system("cls");
				}
			}
		} while (details_choice == 'y' || details_choice == 'Y');
		if (details_choice != 'y' || details_choice != 'Y')
		{
			cout << "\t\t\t\t*******************************************************\n";
			cout << "\t\t\t\t**************** Available car portal *****************\n";
			cout << "\t\t\t\t*******************************************************\n";
		}
	}
}
void update_detail()
{
	string car_name;    // update the car data
	int choice;
	if (counter_car > 0)
	{
		show_car();
		cin.ignore();
		cout << "Enter the name of the car do you want to update:";
		getline(cin, car_name);
		for (int i = 0; i < counter_car; i++)
		{
			if (car_name == add_car_p[i].car_name)
			{
				cout << "Update Menu....";
				cout << "\n\n\n1.Update name of the car.\n2.Update fuel type of the car.\n3.Update maximum speed of the car.\n4.Update number plate of the car.\n5.Update color of the car.\n6.Update price of the car.\n7.Update whole details of the car";
				cin >> choice;
				switch (choice)
				{
				case 1:
					cout << "Enter the name of the car:";
					cin >> add_car_p[i].car_name;
					break;
				case 2:
					cout << "Enter the fuel type of the car:";
					cin >> add_car_p[i].fuel_type;
					break;
				case 3:
					cout << "Enter the maximum speed of the car:";
					cin >> add_car_p[i].max_speed;
					break;
				case 4:
					cout << "Enter the number of the car:";
					cin >> add_car_p[i].number_plate;
					break;
				case 5:
					cout << "Enter the color of the car:";
					cin >> add_car_p[i].color;
					break;
				case 6:
					cout << "Enter the price of rent per hour of the car:";
					cin >> add_car_p[i].price;
					break;
				case 7:
					cout << "Enter the name of the car:";
					cin >> add_car_p[i].car_name;
					cout << "Enter the fuel type of the car:";
					cin >> add_car_p[i].fuel_type;
					cout << "Enter the maximum speed of the car:";
					cin >> add_car_p[i].max_speed;
					cout << "Enter the number of the car:";
					cin >> add_car_p[i].number_plate;
					cout << "Enter the color of the car:";
					cin >> add_car_p[i].color;
					cout << "Enter the price of rent per hour of the car:";
					cin >> add_car_p[i].price;
					break;
				default:
					cout << "\n\n\n\t\t\t\t\tInvalid input\n\n";
					break;
				}
				cout << "Name                :\t" << add_car_p[i].car_name << "." << endl;
				cout << "Color               :\t" << add_car_p[i].color << "." << endl;
				cout << "Fuel type           :\t" << add_car_p[i].fuel_type << "." << endl;
				cout << "Maximum Speed       :\t" << add_car_p[i].max_speed << " km/h." << endl;
				cout << "Car Number          :\t" << add_car_p[i].number_plate << endl;
				cout << "Price per hour      :\t" << add_car_p[i].price << "Rs." << endl;
			}
		}
	}
	else
	{
		cout << "\n\n\n\t\t\t\t\tSorry no cars are available right now.";
	}
}
void rent()
{
	char another;
	if (counter_car != 0)
	{
		do
		{
			system("cls");
			cout << "\t\t\t\t*******************************************************\n";
			cout << "\t\t\t\t******************* Rent car portal *******************\n";
			cout << "\t\t\t\t*******************************************************\n";
			show_car();
			cout << "\n\nEnter your choice to want rent:";
			cin >> car_choice;
			system("cls");
			cout << "\t\t\t\t*****************************************************\n";
			cout << "\t\t\t\t************* Price of Car rented  ******************\n";
			cout << "\t\t\t\t*****************************************************\n";
			cout << "\n\n\n\t\t\t\tName                     :\t\t" << add_car_p[car_choice - 1].car_name << endl;
			cout << "\n\n\n\t\t\t\tRent per hr              :\t\t" << add_car_p[car_choice - 1].price << endl;
			char hr_choice;
			do
			{
				cout << "\n\n\n You can only rent a car for maximum 5hr.\n\nFor how many hours do you want to rent a car:";
				cin >> hr;
				if (hr <= 5 && hr >= 1)
				{
					bill = hr * add_car_p[car_choice - 1].price;
					cout << "\n\n\n\t\t\t\t\tYour bill is " << bill << endl;
					char confirm;
					cout << "Do you still want to rent this car[y/n]:";
					cin >> confirm;
					cin.ignore();
					if (confirm == 'y' || confirm == 'Y')
					{
						system("cls");
						cout << "\t\t\t\t*******************************************************\n";
						cout << "\t\t\t\t******************* Rent car portal *******************\n";
						cout << "\t\t\t\t*******************************************************\n";
						cout << "\n\n\n\n";
						cout << "Name           :\t  " << add_car_p[car_choice - 1].car_name << "\n";
						cout << "Status         :\t  " << "Rented\n";
						cout << "Hours          :\t  " << hr << "\n";
						cout << "Bill           :\t  " << bill << "\n";
						cus_p[customer_index].cars = add_car_p[car_choice - 1].car_name;
						cus_p[customer_index].rent = bill;
						car_index = car_choice - 1;
						add_car_p[car_choice - 1].rented = true;
						add_car_p[car_choice - 1].number_of_time++;
						cout << "\n\n\n\t\t\t\t\t Enter Date (dd/mm/yyyy):";
						getline(cin, add_car_p[car_choice - 1].date);
						add_car_p[car_choice - 1].hr = hr;
						car_number--;
						if (counter_report == 0)
						{
							rep = new report[1];
							counter_report = 1;
						}
						else
						{
							report* temp = new report[counter_report + 1];
							for (int i = 0; i < counter_report; i++)
							{
								temp[i] = rep[i];
							}
							counter_report++;
							delete[]rep;
							rep = temp;
						}
						rep[report1].name = cus_p[customer_index].name;
						rep[report1].num = cus_p[customer_index].num;
						rep[report1].car = cus_p[customer_index].cars;
						rep[report1].rent = cus_p[customer_index].rent;
						report1++;
						if (counter_ut == 0)
						{
							ut = new car[1];
							counter_ut = 1;
						}
						else
						{
							car* temp = new car[counter_ut + 1];
							for (int i = 0; i < counter_ut; i++)
							{
								temp[i] = ut[i];
							}
							counter_ut++;
							delete[]ut;
							ut = temp;
						}
						ut[utilize].car_name = add_car_p[car_choice - 1].car_name;
						ut[utilize].color = add_car_p[car_choice - 1].color;
						ut[utilize].fuel_type = add_car_p[car_choice - 1].fuel_type;
						ut[utilize].max_speed = add_car_p[car_choice - 1].max_speed;
						ut[utilize].number_plate = add_car_p[car_choice - 1].number_plate;
						ut[utilize].price = add_car_p[car_choice - 1].price;
						ut[utilize].travel = add_car_p[car_choice - 1].travel;
						ut[utilize].rented = add_car_p[car_choice - 1].rented;
						ut[utilize].number_of_time = add_car_p[car_choice - 1].number_of_time;
						ut[utilize].date = add_car_p[car_choice - 1].date;
						if (car_number == 0)
						{
							cout << "\n\n\n\t\t\t\t\tThis is the last car.Now,no car is available\n";
							return;
						}
						if (car_number == 0)
						{
							cout << "\n\n\n\t\t\t\t\tSorry no cars are available right now.\n\n";
						}
					}
					else
					{
						system("cls");
						cout << "\t\t\t\t*******************************************************\n";
						cout << "\t\t\t\t******************* Rent car portal *******************\n";
						cout << "\t\t\t\t*******************************************************\n";
						cout << "\n\n\n\n";
						cout << "Name             :\t  " << add_car_p[car_choice - 1].car_name << "\n";
						cout << "Status           :\t  " << " Not Rented";
						cout << "Hours:           :\t  " << hr << "\n";
					}
				}
				else
				{
					system("cls");
					cout << "\t\t\t\t*******************************************************\n";
					cout << "\t\t\t\t******************* Rent car portal *******************\n";
					cout << "\t\t\t\t*******************************************************\n";
					cout << "Number of hours you enter is allowed.";
				}
				cout << "\n\n\t\t\t\t\tDo you again want to enter hours again[y/n]:";
				cin >> hr_choice;
			} while (hr_choice == 'y' || hr_choice == 'Y');
			cout << "\n\n\n\t\t\t\t\tDo you want to rent another car[y/n]:";
			cin >> another;
		} while (another == 'y' || another == 'Y');
	}
	else
	{
		cout << "\n\n\n\t\t\t\t\tSorry no cars are available right now.\n\n";
	}
}
void remove_car()
{
	char another;
	do
	{
		system("cls");
		cout << "\t\t\t\t***************************************************\n";
		cout << "\t\t\t\t************** Remove Customer ********************\n";
		cout << "\t\t\t\t***************************************************\n";
		show_car();
		int index = 0;
		string number;
		cout << "\n\n\n\t\t\t\t\tEnter the number plate of the car to remove: ";
		cin >> number;
		for (int i = 0; i < car_number; i++)
		{
			if (number == add_car_p[i].number_plate)
			{
				add_car_p[i].color = "-1";
			}
		}
		cout << "\n\n\n\t\t\t\t\tCar has been successfully removed.\n";
		cout << "\n\n\n\t\t\t\t\tDo you again want  to remove an other car[y/n]:";
		cin >> another;
	} while (another == 'y' || another == 'Y');
	if (counter_car == -1)
		cout << "\n\n\n\t\t\t\t\tSorry no cars are available.";
}
void customer_show()
{
	int d = 0;
	if (counter_cus == 0)
	{
		cout << "\n\n\n\t\t\t\t\t\t\t\tNO CUSTOMER\n\n\n";
		return;
	}
	for (int i = 0; i < counter_cus; i++)
	{
		if (cus_p[i].name != "-1" && !cus_p[i].name.empty())
		{
			cout << "\n\n\t\t\t\t\tName               :\t\t" << cus_p[i].name << "\n";
			cout << "\n\n\t\t\t\t\tAddress            :\t\t" << cus_p[i].address << "\n";
			cout << "\n\n\t\t\t\t\tCNIC Number        :\t\t" << cus_p[i].cnic << "\n";
			cout << "\n\n\t\t\t\t\tPhone number       :\t\t" << cus_p[i].num << "\n";
			cout << "\n\n\t\t\t\t\tPassword           :\t\t" << cus_p[i].password << "\n";
			cout << "\n\n\t\t\t-------------------------------------------------------------------\n\n";
		}
		d++;
	}
}
void change_password()
{
	string name, cnic, password;
	cin.ignore();
	cout << "\n\n\n\t\t\t\t\tEnter your name:";
	getline(cin, name);
	cout << "\n\n\n\t\t\t\t\tEnter your CNIC number:";
	getline(cin, cnic);
	for (int i = 0; i < 10; i++)
	{
		if (ad[i].name == name && ad[i].cnic == cnic)
		{
			cout << "\n\n\n\t\t\t\t\tEnter your new password:";
			cin >> ad[i].password;
			cout << "\n\n\n\t\t\t\t\tEnter the new password again for confirmation:";
			cin >> password;
			if (ad[i].password == password)
			{
				cout << "\n\n\n\t\t\t\t\tYour password is changed successfully.";
			}
			else
			{
				system("cls");
				cout << "\t\t\t\t***************************************************\n";
				cout << "\t\t\t\t**************** Change Password ******************\n";
				cout << "\t\t\t\t***************************************************\n";
				cout << "\n\n\n\t\t\t\t\tNew password and confirm password is not matched.Please enter the password again.";
				cout << "\n\n\n\t\t\t\t\tEnter your new password:";
				cin >> ad[i].password;
				cout << "\n\n\n\t\t\t\t\tEnter the new password again for confirmation:";
				cin >> password;
				if (ad[i].password == password)
					cout << "\n\n\n\t\t\t\t\tYour password is changed successfully.";
			}
		}
	}
}
void remove_customer()
{
	char num[30];
	cout << "\n\n\n\t\t\tEnter the number of the customer do you want to remove:\n\n\t\t\t";
	cin >> num;
	for (int i = 0; i < counter_cus; i++)
	{
		if (cus_p[i].num == num)
		{
			cus_p[i].name = "-1";
		}
	}
	c--;
	system("Pause");
	cout << "\n\n\n\t\t\t\tCustomer has been removed successfully.\n\n\t\t\t\t";
}
void update_customer()
{
	char another = 'n';
	int choice;
	do
	{
		system("cls");
		cout << "\t\t\t\t***************************************************\n";
		cout << "\t\t\t\t***************** Update Data *********************\n";
		cout << "\t\t\t\t***************************************************\n";
		int cus_counter = 1;
		char num[20];
		cout << "\n\n\n\t\t\t\t\tEnter the phone number of the customer:\n\n\n\t\t\t\t\t";
		cin >> num;
		for (int i = 0; i < counter_cus; i++)
		{
			if (num == cus_p[i].num)
			{

				cout << "Updating menu...";
				cout << "\n1.To change name of the customer\n\n2.To change CNIC of the customer\n\n3.To change the address of the customer\n\n4.To change the password\n\n5.To change the phone number of the customer\n\n6.To change the whole data of the customer\n\n";
				cout << "\n\n\nEnter the your choice:";
				cin >> choice;
				switch (choice)
				{
				case 1:
					cout << "Enter the name of the customer:";
					cin >> cus_p[i].name;
					break;
				case 2:
					cout << "Enter the CNIC of the customer:";
					cin >> cus_p[i].cnic;
					break;
				case 3:
					cout << "Enter the address of the customer:";
					cin >> cus_p[i].address;
					break;
				case 4:
					cout << "Enter the password of the customer:";
					cin >> cus_p[i].password;
					break;
				case 5:
					cout << "Enter the phone number of the customer:";
					cin >> cus_p[i].num;
					break;
				case 6:
					cout << "Enter the price of rent per hour of the car:";
					cin >> add_car_p[i].price;
					break;
				case 7:
					cout << "Enter the name of the car:";
					cin >> add_car_p[i].car_name;
					cout << "Enter the fuel type of the car:";
					cin >> add_car_p[i].fuel_type;
					cout << "Enter the maximum speed of the car:";
					cin >> add_car_p[i].max_speed;
					cout << "Enter the number of the car:";
					cin >> add_car_p[i].number_plate;
					cout << "Enter the color of the car:";
					cin >> add_car_p[i].color;
					cout << "Enter the price of rent per hour of the car:";
					cin >> add_car_p[i].price;
					break;
				default:
					cout << "\n\n\n\t\t\t\t\tInvalid input\n\n";
					break;
				}
			}
			cus_counter++;
		}
		if (counter_cus == 0)
		{
			cout << "\n\n\n\t\t\t\t\tNo customer.\n\n\n";
		}
		if (cus_counter == counter_cus)
		{
			cout << "\n\n\n\t\t\t\t\tCustomer does not found.\n\n\n";
			cout << "Do you want to enter the phone number again[y/n]:";
			cin >> another;
		}
	} while (another == 'y' || another == 'Y');
}
void rental_report()
{
	for (int i = 0; i < counter_report; i++)
	{
		if (rep[i].name == cus_p[customer_index].name)
		{
			cout << "\n\n\n\t\t\t\t\tName                     :    " << cus_p[customer_index].name;
			cout << "\n\n\n\t\t\t\t\t Phone Number            :    " << cus_p[customer_index].num;
			cout << "\n\n\t\t\t-------------------------------------------------------------------\n\n";
			cout << "\n\n\n\t\t\t\t\tCar                   :    " << cus_p[customer_index].cars;
			cout << "\n\n\n\t\t\t\t\tRent                  :    " << cus_p[customer_index].rent;
			cout << "\n\n\t\t\t-------------------------------------------------------------------\n\n";
			total_bill += cus_p[customer_index].rent;
			cout << "\n\n\n\t\t\t\t\tYour total bill is " << total_bill;
			cout << "\n\n\t\t\t\t\t\t\t\t\t\tDownload Report";
		}
	}
	if (counter_report == 0)
	{
		cout << "\n\n\n\t\t\t\t\tName                     :    " << cus_p[customer_index].name;
		cout << "\n\n\n\t\t\t\t\t Phone Number            :    " << cus_p[customer_index].num;
		cout << "\n\n\t\t\t-------------------------------------------------------------------\n\n";
		cout << "\n\n\n\t\t\t\t\tCar                   :    " << cus_p[customer_index].cars;
		cout << "\n\n\n\t\t\t\t\tRent                  :    " << cus_p[customer_index].rent;
		cout << "\n\n\t\t\t-------------------------------------------------------------------\n\n";
		total_bill += cus_p[customer_index].rent;
		cout << "\n\n\n\t\t\t\t\tYour total bill is " << total_bill;
		cout << "\n\n\t\t\t\t\t\t\t\t\t\tDownload Report";

	}
}
void return_car()
{
	if (cus_p[customer_index].cars == "-1")
	{
		cout << "\n\n\n\t\t\t\t\tNO CARS REMAINING\n\n";
		return;
	}
	float travel = 0;
	cout << "\n\n\n\t\t\t\t\tName                  :      " << cus_p[customer_index].name;
	if (cus_p[customer_index].cars != "-1")
	{
		cout << "\n\n\n\t\t\t\t\tCar                   :    " << cus_p[customer_index].cars;
		cout << "\n\n\n\t\t\t\t\tRent                  :    " << cus_p[customer_index].rent;
		cout << "\n\n\t\t\t-------------------------------------------------------------------\n\n";
		total_bill += cus_p[customer_index].rent;
	}
	cout << "Number of kilo-meter for car " << "\n";
	cout << "Enter the number of kilometer does the car travel:";
	cin >> travel;
	add_car_p[car_index].travel = add_car_p[car_index].travel + travel;
	//ut[car_index].rented = false;
	for (int i = 0; i < counter_ut; i++)
	{
		if (add_car_p[car_index].number_plate == ut[i].number_plate)
		{
			ut[i].rented = false;
		}
	}
	for (int i = 0; i < counter_report; i++)
	{
		if (cus_p[customer_index].num == rep[i].num)
		{
			rep[i].car = "-1";
		}
	}
	cus_p[customer_index].cars = "-1";
	system("Pause");
	cout << "\n\n\n\t\t\t\t\tThank you getting our service.\n\n\n";
}
void over_all()
{
	if (counter_report == 0)
	{
		cout << "\n\n\n\t\t\t\tNO REPORTS PENDING\n\n";
		return;
	}
	for (int i = 0; i < counter_report; i++)
	{
		cout << "\n\n\n\t\t\t\t\tName                     :    " << rep[i].name;
		cout << "\n\n\n\t\t\t\t\t Phone Number            :    " << rep[i].num;
		cout << "\n\n\n\t\t\t\t\tCar                      :    " << rep[i].car;
		cout << "\n\n\n\t\t\t\t\tRent                     :    " << rep[i].rent;
		cout << "\n\n\t\t\t-------------------------------------------------------------------\n\n";
	}
}
void maintain()
{
	if (counter_car == 0)
	{
		cout << "\n\n\n\n\t\t\t\t\tNO CARS FOR MAINTAINENCE\n\n";
		return;
	}
	int choice, inc = 0;
	system("cls");
	cout << "\t\t\t\t****************************************************\n";
	cout << "\t\t\t\t***************** Maintain car *********************\n";
	cout << "\t\t\t\t****************************************************\n";
	for (int i = 0; i < counter_car; i++)
	{
		if (add_car_p[i].travel > 150)
		{
			cout << "\n\n\n\t\t\t\t\t";
			cout << i + 1 << "." << add_car_p[i].car_name << endl;
		}
		inc++;
	}
	if (inc == counter_car)
	{
		cout << "\n\n\n\n\t\t\t\t\tNO CARS FOR MAINTAINENCE\n\n";
		return;
	}
	cout << "\n\n\n\t\t\t\t\t";
	cout << "Enter the number of car of car do you want to send to maintainence:";
	cin >> choice;
	cout << "\n\n\n\t\t\t\t\t\tThe car with name " << add_car_p[choice - 1].car_name << "were send for maintainence." << "\n\n\n";
	add_car_p[choice - 1].travel = 0;
}
void utilization()
{
	cout << "\n\n\n\t\t\t\t\t\tNUMBER OF TIME CAR IS RENTED\n\n";
	for (int i = 0; i < counter_car; i++)
	{
		if (add_car_p[i].rented == true)
		{
			cout << "\n\n\n\t\t\t\t\t\tName                 :\t" << add_car_p[i].car_name << "\n";
			cout << "\n\n\n\t\t\t\t\t\tNumber of time       :\t" << add_car_p[i].number_of_time << "\n";
		}
		cout << "\n\n\n\t\t\t\t\t\t\t---------------------------\n\n";
	}
}
void cus_write()
{
	fout.open("cus_info.txt", ios::trunc);
	fout.close();
	fout.clear();
	fout.open("cus_info.txt", ios::app);
	if (fout.is_open())
	{
		for (int i = 0; i < counter_cus; i++)
		{
			if (cus_p[i].name != "-1" && !cus_p[i].name.empty())
			{
				fout << cus_p[i].name << ",";
				fout << cus_p[i].password << ",";
				fout << cus_p[i].num << ",";
				fout << cus_p[i].cnic << ",";
				fout << cus_p[i].address << ",";
				if (cus_p[i].cars != "-1")
				{
					fout << cus_p[i].cars << ",";
					fout << cus_p[i].rent << ",";
				}
			}
			fout << endl;
		}
	}
	fout.close();
	fout.clear();
}
void car_write()
{
	fout.open("car_info.txt", ios::trunc);
	fout.close();
	fout.clear();
	fout.open("car_info.txt", ios::app);
	if (fout.is_open())
	{
		for (int i = 0; i < counter_car; i++)
		{
			if (add_car_p[i].color != "-1" && (add_car_p[i].rented == false && !add_car_p[i].car_name.empty()))
			{
				fout << add_car_p[i].car_name << ",";
				fout << add_car_p[i].color << ",";
				fout << add_car_p[i].fuel_type << ",";
				fout << add_car_p[i].max_speed << ",";
				fout << add_car_p[i].number_plate << ",";
				fout << add_car_p[i].price << ",";
				fout << add_car_p[i].travel << ",";
				fout << add_car_p[i].rented << ",";
				fout << add_car_p[i].number_of_time << ",";
				fout << add_car_p[i].date;
				fout << endl;
			}
		}
		for (int i = 0; i < counter_ut; i++)
		{
			if (ut[i].rented == false)
			{
				fout << ut[i].car_name << ",";
				fout << ut[i].color << ",";
				fout << ut[i].fuel_type << ",";
				fout << ut[i].max_speed << ",";
				fout << ut[i].number_plate << ",";
				fout << ut[i].price << ",";
				fout << ut[i].travel << ",";
				fout << ut[i].rented << ",";
				fout << ut[i].number_of_time << ",";
				fout << ut[i].date;
				fout << endl;
			}
		}
	}
	fout.close();
	fout.clear();
}
void report_write()
{
	fout.open("report.txt", ios::trunc);
	fout.close();
	fout.clear();
	fout.open("report.txt", ios::app);
	if (fout.is_open())
	{
		for (int i = 0; i < counter_report; i++)
		{
			if (rep[i].car != "-1" && !rep[i].car.empty())
			{
				fout << rep[i].name << ",";
				fout << rep[i].num << ",";
				fout << rep[i].car << ",";
				fout << rep[i].rent;
				fout << endl;
			}
		}
	}
	fout.close();
	fout.clear();
}
void utilization_write()
{
	fout.open("utilization.txt", ios::trunc);
	fout.close();
	fout.clear();
	fout.open("utilization.txt", ios::app);
	if (fout.is_open())
	{
		for (int i = 0; i < counter_car; i++)
		{
			if (add_car_p[i].rented == true)
			{
				fout << add_car_p[i].car_name << ",";
				fout << add_car_p[i].color << ",";
				fout << add_car_p[i].fuel_type << ",";
				fout << add_car_p[i].max_speed << ",";
				fout << add_car_p[i].number_plate << ",";
				fout << add_car_p[i].price << ",";
				fout << add_car_p[i].travel << ",";
				fout << add_car_p[i].rented << ",";
				fout << add_car_p[i].number_of_time;
				fout << endl;
			}
		}
	}
	fout.close();
	fout.clear();
}
void admin_write()
{
	fout.open("ad_info.txt", ios::trunc);
	fout.close();
	fout.clear();
	fout.open("ad_info.txt", ios::app);
	if (fout.is_open())
	{
		for (int i = 0; i < counter_ad; i++)
		{
			fout << ad[i].name << ",";
			fout << ad[i].password << ",";
			fout << ad[i].num << ",";
			fout << ad[i].cnic << ",";
			fout << endl;
		}
	}
	fout.close();
	fout.clear();
}