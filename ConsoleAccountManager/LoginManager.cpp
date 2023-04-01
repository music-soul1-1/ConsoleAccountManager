#include "LoginManager.h"

// checks if user exists within a file
bool LoginManager::checkForUserName(string fileName, string inputParam)
{
	bool valueExists = false;
	ifstream file;
	string line;
	long long tempChar = 0;

	file.open(fileName);
	// read untill the end of the file(or untill suitable value(string) found)
	while (file.peek() != EOF)
	{
		file >> tempChar;

		// 1 is a dilimiter for user logins
		if (tempChar == 1)
		{
			if (inputParam == line)
			{
				valueExists = true;
				file.close();
				return true;
			}
			else
			{
				line.erase(line.begin(), line.end());
			}
		}
		// 0 is delimiter for the whole user record
		else if (tempChar == 0)
		{
			line.erase(line.begin(), line.end());
		}
		else
		{
			line += decrypt(tempChar, currentPassword);
		}
	}
	file.close();

	return valueExists;
}

// checks if content for current user exists within a file
bool LoginManager::checkUser(string fileName, string contentToCheck)
{
	fstream file;
	string line;
	bool isContentCorrect = false, isUserCorrect = false;
	long long tempChar = 0;

	file.open(fileName, ios::in);

	// read untill the end of the file
	while (file.peek() != EOF)
	{
		file >> tempChar;

		// 1 is a dilimiter for user logins
		if (tempChar == 1)
		{
			if (currentUser == line)
			{
				isUserCorrect = true;
			}
			else
			{
				isUserCorrect = false;
			}
			line.erase(line.begin(), line.end());
		}
		// 0 is delimiter for the whole user record
		else if (tempChar == 0 && isUserCorrect)
		{
			if (contentToCheck == line)
			{
				isContentCorrect = true;

				file.close();
				return true;
			}
			else
			{
				line.erase();
				isContentCorrect = false;
			}
		}
		else if (tempChar == 0)
		{
			line.erase();
		}
		else
		{
			line += decrypt(tempChar, currentPassword);
		}
	}
	file.close();

	return isContentCorrect;
}

// login function
bool LoginManager::login()
{
	cout << "Please enter your user login \nLogin:";
	cin >> currentUser;

	cout << "\nEnter password: ";
	cin >> currentPassword;
	cout << "\n";

	checkUser(usersFile, currentPassword) ? isLoggedIn = true : isLoggedIn = false;

	return isLoggedIn;
}

// add user function
void LoginManager::addUser()
{
	string newUserName, newUserPassword;
	bool isUsed = false;

	// getting username and password
	cout << "\nEnter new user's name: ";
	cin >> newUserName;

	if (checkForUserName(usersFile, newUserName))
	{
		cout << "This user already exists.\n";
		isUsed = true;
	}
	else
	{
		cout << "\nNow enter a password: ";
		cin >> currentPassword;
	}

	// putting username and password into appropriate files
	if (!isUsed)
	{
		addLine(usersFile, newUserName, '1');
		addLine(usersFile, currentPassword);

		cout << "User added successfully :)\n";
	}
}

void LoginManager::addLine(string fileName, string content, char delimiter, char endWith)
{
	fstream file;

	// opening file and going to the end of it
	file.open(fileName, ios::out | ios::app);

	if (file.is_open())
	{
		for (int i = 0; i < content.length(); i++)
		{
			file << encrypt(content[i], currentPassword) << endWith;
		}
		if (delimiter == ' ')
		{
			file << '\n';
		}
		else
		{
			file << '\n' << delimiter << '\n';
		}
	}
	else
	{
		cout << "Error occupied while opening '" << fileName << "' file.";
	}

	file.close();
}

// this function displays all records for current user
void LoginManager::readAccounts()
{
	fstream file;
	string line;
	bool isCurrentUser = false, recordExists = false;
	long long tempChar = 0;

	// opening accounts file in input mode
	file.open(accountsFile, ios::in);

	// read untill the end of the file
	while (file.peek() != EOF)
	{
		// writing characters from file to tempChar variable
		file >> tempChar;

		// 1 is a dilimiter for user logins
		if (tempChar == 1)
		{
			if (currentUser == line)
			{
				isCurrentUser = true;
				recordExists = true;
			}
			else
			{
				isCurrentUser = false;
			}
			line.erase();
		}
		else if (tempChar == 0)
		{
			if (isCurrentUser)
			{
				cout << line << '\n';
			}
			line.erase();
		}
		else
		{
			line += decrypt(tempChar, currentPassword);
		}
	}

	if (!recordExists)
	{
		cout << "There are no records for user '" << currentUser << "' \n";
	}

	file.close();
}

// this function adds new account records for the current user
void LoginManager::addAccount()
{
	string newLogin, newPassword, newServiceName;

	cout << "Enter the name of the service (e.g. Gmail): ";
	cin >> newServiceName;

	if (!checkUser(accountsFile, newServiceName))
	{
		cout << "Enter account's login: ";
		cin >> newLogin;
		cout << "Enter account's password: ";
		cin >> newPassword;

		addLine(accountsFile, currentUser, '1');
		addLine(accountsFile, "+----------------------+");
		addLine(accountsFile, newServiceName);
		addLine(accountsFile, "###############");
		addLine(accountsFile, newLogin);
		addLine(accountsFile, newPassword);
		addLine(accountsFile, "+----------------------+");
		addLine(accountsFile, "", ' '); // just adding a new line
	}
	else
	{
		cout << "This record already exists.\n";
	}
}

// removes account record for the user
void LoginManager::removeAccount()
{
	fstream mainFile;
	ofstream tempFile;
	string decryptedLine, recordToRemove, user, separator;
	long long tempChar = 0;
	bool isUserCorrect = false, isBeginning = false,
		 isNeededToSkip = false, isSeparator = false;

	cout << "Enter the name of the service you would like to delete: ";
	cin >> recordToRemove;

	mainFile.open(accountsFile, ios::in);

	// needed to create file
	tempFile.open(temporaryFile, ios::out); 

	// read untill the end of the file
	while (mainFile.peek() != EOF)
	{
		mainFile >> tempChar;

		if (tempChar == 1)
		{
			// checking username
			if (currentUser == decryptedLine)
			{
				isUserCorrect = true;
			}
			else
			{
				isUserCorrect = false;
			}
			isBeginning = true;
			isNeededToSkip = false;

			user = decryptedLine;
			decryptedLine.erase();
		}
		else if (tempChar == 0)
		{
			// if line is "+----------------------+"
			if (decryptedLine.length() == 24 && decryptedLine[0] == decryptedLine[decryptedLine.length() - 1])
			{
				for (int i = 1; i < decryptedLine.length() - 2; i++)
				{
					if (decryptedLine[i] != decryptedLine[static_cast <char> (i + 1)])
					{
						isSeparator = false;
						separator.erase();
					}
					else
					{
						separator = decryptedLine;
						isSeparator = true; // line is "+----------------------+"
					}
				}
			}
			else
			{
				isSeparator = false;
			}

			if (decryptedLine == recordToRemove && isUserCorrect)
			{
				isNeededToSkip = true;
				decryptedLine.erase();

				continue;
			}

			if ((isSeparator && isBeginning) || isNeededToSkip)
			{
				decryptedLine.erase();

				continue;
			}
			else if (decryptedLine != recordToRemove)
			{
				if (isBeginning)
				{
					addLine(temporaryFile, user, '1');
					user.erase();

					addLine(temporaryFile, separator);
					isBeginning = false;
				}
				addLine(temporaryFile, decryptedLine);
			}
			decryptedLine.erase();
		}
		else
		{
			decryptedLine += decrypt(tempChar, currentPassword);
		}
	}
	addLine(temporaryFile, "", ' '); // just adding a new line

	mainFile.close();
	tempFile.close();

	remove(accountsFile.c_str());
	bool isRenameSuccessful = rename(temporaryFile, accountsFile.c_str());
	if (isRenameSuccessful) // rename returns 0 if successfull
	{
		cout << "Error renaming 'temp.dat' file\n\n";
	}
}

// removes current user and it's accounts file
void LoginManager::removeUser()
{
	fstream recordsFile, userFile;
	ofstream tempFile;
	char input;

	string decryptedLine;
	long long tempChar = 0;
	bool isUserCorrect = false, isNeededToSkip = false;

	cout << "Would you like to delete this user?\n"
		 << "Note that accounts for this user will also be deleted.\n"
		 << "To continue enter Y/y, to stop - anything else: ";
	cin >> input;

	if ((input == 'Y') || (input == 'y'))
	{
		/* Removing account records */
		recordsFile.open(accountsFile, ios::in);
		tempFile.open(temporaryFile, ios::app);

		// read untill the end of the file
		while (recordsFile.peek() != EOF)
		{
			recordsFile >> tempChar;

			if (tempChar == 1)
			{
				// checking username
				if (currentUser == decryptedLine)
				{
					isUserCorrect = true;
					isNeededToSkip = true;
				}
				else
				{
					isUserCorrect = false;
					isNeededToSkip = false;

					addLine(temporaryFile, decryptedLine, '1');
				}
				decryptedLine.erase();
			}
			else if (tempChar == 0)
			{
				if (!isNeededToSkip)
				{
					addLine(temporaryFile, decryptedLine);
				}

				decryptedLine.erase();
			}
			else
			{
				decryptedLine += decrypt(tempChar, currentPassword);
			}
		}
		decryptedLine.erase();

		recordsFile.close();
		tempFile.close();

		remove(accountsFile.c_str());
		bool isRenameSuccessful = rename(temporaryFile, accountsFile.c_str());

		/* Removing user */
		isUserCorrect = isNeededToSkip = false;

		userFile.open(usersFile, ios::in);
		tempFile.open(temporaryFile, ios::app);

		// read untill the end of the file
		while (userFile.peek() != EOF)
		{
			userFile >> tempChar;

			if (tempChar == 1)
			{
				if (currentUser == decryptedLine)
				{
					isUserCorrect = true;
					isNeededToSkip = true;
				}
				else
				{
					isUserCorrect = false;
					isNeededToSkip = false;
					addLine(temporaryFile, decryptedLine, '1');
				}
				decryptedLine.erase();
			}
			else if (tempChar == 0)
			{
				if (!isNeededToSkip)
				{
					addLine(temporaryFile, decryptedLine);
					decryptedLine.erase();
				}
				else
				{
					decryptedLine.erase();
					continue;
				}

			}
			else
			{
				decryptedLine += decrypt(tempChar, currentPassword);

			}
		}
		userFile.close();
		tempFile.close();

		remove(usersFile.c_str());
		isRenameSuccessful = rename(temporaryFile, usersFile.c_str());

		if (isRenameSuccessful) // rename returns 0 if successfull
		{
			cout << "Error renaming file\n\n";
		}
	}
}

/* ENCRYPION AND DECRYPTION */

long long LoginManager::encrypt(int input, string key)
{
	// key is "" when the second parameter is not used
	if (key == "")
	{
		return input;
	}
	else
	{
		long long result = 0;
		
		for (int i = 0; i < key.length(); i++)
		{
			result += pow(key[i], 2);
		}

		return input + result;
	}
}

char LoginManager::decrypt(long long input, string key)
{
	// key is "" when the second parameter is not used
	if (key == "")
	{
		return static_cast <char> (input);
	}
	else
	{
		long long result = 0;

		for (int i = 0; i < key.length(); i++)
		{
			result -= pow(key[i], 2);
		}

		return static_cast <char> (input + result);
	}
}
