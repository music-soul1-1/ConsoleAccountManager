#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <math.h>

using namespace std;

class LoginManager
{
private:
	string currentUser, currentPassword,
		   usersFile = "users.datafile", accountsFile = "accounts.datafile";
	const char* temporaryFile = "temp.datafile";

public:
	/* Variables and constants */
	bool isLoggedIn = false;

	/* Functions */

	// checks if user exists within a file.
	bool checkForUserName(string fileName, string inputParam);

	// checks if content for current user exists within a file
	bool checkContent(string fileName, string contentToCheck, string decryptionKey);

	// login function
	bool login();

	// adds user
	void addUser();

	// add line function. This function encrypts and adds specified content to file.
	// "encryptionKey" parameter is the key used for encrypting content.
	// "delimiter" parameter is printed after all the content. Default valuse is 0.
	// "endWith" parameter defines the ending of each character. Default value is ' '(space).
	void addLine(string fileName, string content, string encryptionKey, char delimiter = '0', char endWith = ' ');

	// displays all records for current user
	void readAccounts();

	// adds new account records for the current user
	void addAccount();
	
	// removes account record for the current user
	void removeAccount();

	// removes current user and it's accounts file
	bool removeUser();

	// Encryption function.
	// Second parameter is used as a key(password) for encrypting.
	long long encrypt(int input, string key = "");

	// Decryption function.
	// Second parameter is used as a key(password) for decrypting.
	char decrypt(long long input, string key = "");
};