#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

class LoginManager
{
private:
	string inputLogin, userPassword,
		   usersFile = "users.dat",
		   accountsFile;

public:
	string currentUser;
	bool isLoggedIn = false;

	// checks if user exists within a file
	bool checkForUser(string inputParam, string fileName);

	// checks if password exists within a file
	bool checkForPassword();

	// login function
	bool login();

	// add user function
	void addUser();

	// add line function. This function adds specified content to file
	void addLine(string fileName, string content);

	// this function displays all records for current user
	void readAccounts();

	// this function adds new account records for the current user
	void addAccount();
	
	// removes account
	void removeAccount();

	// checks if a string has certain content
	bool hasContent(string sourceString, string contentToFind, char delimiter);

	// removes user and it's accounts file
	void removeUser();
};