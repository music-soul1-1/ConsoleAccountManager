#pragma once
#include <iostream>
#include <fstream>
#include <string>


using namespace std;

class LoginManager
{
private:
	string inputLogin, userPassword,
		   accountsFile = "accounts.dat",
		   usersFile = "users.dat";

	int countAttempts = 0;

public:
	string currentUser;
	bool isLoggedIn = false;

	// checks if user exists within a file
	bool checkForUser(string inputParam, string fileName);

	// checks if password exists within a file
	bool checkForPassword();

	// login function
	void login();

	// add user function
	void addUser();

	// add line function. This function adds specified content to file
	void addLine(string fileName, string content);

	// this function displays all records for current user
	void readAccounts();

	// this function adds new account records for the current user
	void addAccount(string userName, string serviceName, string login, string password);
};