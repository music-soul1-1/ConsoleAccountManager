#include "LoginManager.h"

// checks if user exists within a file.
// Returns true if user was found.
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
			line += decrypt(tempChar, inputParam);
		}
	}
	file.close();

	return valueExists;
}

// checks if content for current user exists within a file
bool LoginManager::checkContent(string fileName, string contentToCheck, string decryptionKey)
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
			line += decrypt(tempChar, decryptionKey);
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

	isLoggedIn = checkContent(usersFile, currentPassword, currentUser) ? true : false;

	return isLoggedIn;
}

// adds user
void LoginManager::addUser()
{
	string newUserName, newUserPassword;

	// getting username and password
	cout << "\nEnter new user's name: ";
	cin >> currentUser;

	if (checkForUserName(usersFile, currentUser))
	{
		cout << "This user already exists.\n";
	}
	else
	{
		cout << "\nNow enter a password: ";
		cin >> newUserPassword;

		// putting username and password into appropriate files
		addLine(usersFile, currentUser, currentUser, '1');
		addLine(usersFile, newUserPassword, currentUser);

		cout << "User added successfully :)\n";
	}
}

void LoginManager::addLine(string fileName, string content, string encryptionKey, char delimiter, char endWith)
{
	fstream file;

	// opening file and going to the end of it
	file.open(fileName, ios::out | ios::app);

	if (file.is_open())
	{
		for (int i = 0; i < content.length(); i++)
		{
			file << encrypt(content[i], encryptionKey) << endWith;
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

// displays all records for current user
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
			line += decrypt(tempChar, currentUser + currentPassword);
		}
	}

	if (!recordExists)
	{
		cout << "There are no records for user '" << currentUser << "' \n";
	}

	file.close();
}

// adds new account records for the current user
void LoginManager::addAccount()
{
	string newLogin, newPassword, newServiceName;

	cout << "Enter the name of the service (e.g. Gmail): ";
	cin >> newServiceName;

	if (!checkContent(accountsFile, newServiceName, currentUser + currentPassword))
	{
		cout << "Enter account's login: ";
		cin >> newLogin;
		cout << "Enter account's password: ";
		cin >> newPassword;

		addLine(accountsFile, currentUser, currentUser + currentPassword, '1');
		addLine(accountsFile, "+----------------------------+", currentUser + currentPassword);
		addLine(accountsFile, newServiceName, currentUser + currentPassword);
		addLine(accountsFile, "############################", currentUser + currentPassword);
		addLine(accountsFile, newLogin, currentUser + currentPassword);
		addLine(accountsFile, newPassword, currentUser + currentPassword);
		addLine(accountsFile, "+----------------------------+", currentUser + currentPassword);
		addLine(accountsFile, "", currentUser + currentPassword, ' '); // just adding a new line
	}
	else
	{
		cout << "This record already exists.\n";
	}
}

// removes account record for the current user
void LoginManager::removeAccount()
{
	fstream mainFile;
	ofstream tempFile;
	string decryptedLine, recordToRemove, user, separator;
	long long tempChar = 0;
	bool isUserCorrect = false, isBeginningOfRecord = false,
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
			isUserCorrect = (currentUser == decryptedLine);
			
			isBeginningOfRecord = true;
			isNeededToSkip = false;

			user = decryptedLine;
			decryptedLine.erase();
		}
		else if (tempChar == 0)
		{
			// check if line is "+----------------------------+"
			isSeparator = (decryptedLine.length() == 30 && decryptedLine[0] == decryptedLine[decryptedLine.length() - 1]);
			if (isSeparator)
			{
				separator = decryptedLine;
				for (int i = 1; i < decryptedLine.length() - 2; i++)
				{
					if (decryptedLine[i] != decryptedLine[static_cast <char> (i + 1)])
					{
						isSeparator = false;
						separator.erase();
						break;
					}
				}
			}

			if (decryptedLine == recordToRemove && isUserCorrect)
			{
				isNeededToSkip = true;
				decryptedLine.erase();

				continue;
			}

			if ((isSeparator && isBeginningOfRecord) || isNeededToSkip)
			{
				decryptedLine.erase();

				continue;
			}
			else if (decryptedLine != recordToRemove)
			{
				if (isBeginningOfRecord)
				{
					addLine(temporaryFile, user, currentUser + currentPassword, '1');
					user.erase();

					addLine(temporaryFile, separator, currentUser + currentPassword);
					isBeginningOfRecord = false;
				}
				addLine(temporaryFile, decryptedLine, currentUser + currentPassword);
			}
			decryptedLine.erase();
		}
		else
		{
			decryptedLine += decrypt(tempChar, currentUser + currentPassword);
		}
	}
	addLine(temporaryFile, "", currentUser + currentPassword, ' '); // just adding a new line

	mainFile.close();
	tempFile.close();

	remove(accountsFile.c_str());

	if (rename(temporaryFile, accountsFile.c_str())) // rename returns 0 if successfull
	{
		cout << "Error renaming 'temp.datafile' file\n\n";
	}
}

// removes current user and it's accounts file
bool LoginManager::removeUser()
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
		#pragma region Removing account records

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
					isUserCorrect = isNeededToSkip = true;
				}
				else
				{
					isUserCorrect = isNeededToSkip = false;

					addLine(temporaryFile, decryptedLine, currentUser + currentPassword, '1');
				}
				decryptedLine.erase();
			}
			else if (tempChar == 0)
			{
				if (!isNeededToSkip)
				{
					addLine(temporaryFile, decryptedLine, currentUser + currentPassword);
				}

				decryptedLine.erase();
			}
			else
			{
				decryptedLine += decrypt(tempChar, currentUser + currentPassword);
			}
		}
		decryptedLine.erase();

		recordsFile.close();
		tempFile.close();

		remove(accountsFile.c_str());

		if (rename(temporaryFile, accountsFile.c_str())) // rename returns 0 if successfull
		{
			cout << "Error renaming temporary file\n\n";
		}
		#pragma endregion

		#pragma region Removing user

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
					addLine(temporaryFile, decryptedLine, currentUser, '1');
				}
				decryptedLine.erase();
			}
			else if (tempChar == 0)
			{
				if (!isNeededToSkip)
				{
					addLine(temporaryFile, decryptedLine, currentUser);
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
				decryptedLine += decrypt(tempChar, currentUser);

			}
		}
		userFile.close();
		tempFile.close();

		remove(usersFile.c_str());

		if (rename(temporaryFile, usersFile.c_str())) // rename returns 0 if successfull
		{
			cout << "Error renaming file\n\n";
		}
		#pragma endregion

		return true;
	}
	else
	{
		return false;
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
			result += static_cast <int> (pow(key[i], 3));
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
			result -= static_cast <int> (pow(key[i], 3));
		}

		return static_cast <char> (input + result);
	}
}
