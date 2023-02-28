#include "LoginManager.h"

// checks if user exists within a file
bool LoginManager::checkForUser(string inputParam, string fileName)
{
	bool valueExists = false;
	ifstream file;
	string line;

	file.open(fileName);
	// read untill the end of the file(or untill suitable value(string) found)
	while (file.peek() != EOF)
	{
		getline(file, line);
		// checking if string exists within the file
		if (inputParam == line)
		{
			valueExists = true;
			file.close();
			break;
		}
	}
	file.close();

	return valueExists;
}

// checks if password exists within a file
bool LoginManager::checkForPassword()
{
	fstream file;
	string line, password;
	bool isPasswordCorrect = false;

	file.open(usersFile, ios::in);

	// read untill the end of the file
	while (file.peek() != EOF)
	{
		getline(file, line);

		// checking if record exists within the file
		if (currentUser == line)
		{
			// reading untill ';'
			getline(file, line, ';');

			// user has maximum 3 appempts
			for (int i = 0; i < 3; i++)
			{
				cout << "Enter password: ";
				cin >> password;
				cout << "\n";

				if (line == password)
				{
					isPasswordCorrect = true;

					break;
				}
				else
				{
					isPasswordCorrect = false;
					cout << "Password '" << password << "' is not correct.\n";

					if ((i + 1) > 2)
					{
						cout << "You've entered wrong password too many times.\n";

						break;
					}
				}
			}
			break;
		}
	}
	file.close();

	return isPasswordCorrect;
}

// login function
bool LoginManager::login()
{
	cout << "Please enter your user login \nLogin:";
	cin >> inputLogin;

	// user check
	if (checkForUser(inputLogin, usersFile))
	{
		cout << "\nUser found\n";

		currentUser = inputLogin;

		// password check
		if (checkForPassword())
		{
			isLoggedIn = true;

			/*  Renaming the 'accountsFile' variable every time user logs in.
				This means that each user's records file has different names.
				This was mainly made to improve app stability.
			*/
			accountsFile = currentUser + "_accounts.dat";
		}
	}
	else
	{
		cout << "\nNo such user\n";
		isLoggedIn = false;
	}

	return isLoggedIn;
}

// add user function
void LoginManager::addUser()
{
	while (true)
	{
		string newUserName, newUserPassword;

		// getting username and password
		cout << "\nEnter new user's name: ";
		cin >> newUserName;

		if (checkForUser(newUserName, usersFile))
		{
			cout << "This user already exists.\n";

			break;
		}
		else
		{
			cout << "\nNow enter a password: ";
			cin >> newUserPassword;
		}

		// putting username and password into appropriate files
		addLine(usersFile, "\n" + newUserName);
		addLine(usersFile, newUserPassword + ";");

		cout << "User added successfully :)\n";

		break;
	}
}

// add line function. This function adds specified content to file
void LoginManager::addLine(string fileName, string content)
{
	fstream file;

	// opening file and going to the end of it
	file.open(fileName, ios::out | ios::app);

	if (file.is_open())
	{
		file << content << "\n";
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
	bool valueExists = false;

	file.open(accountsFile, ios::in);

	// read untill the end of the file
	while (file.peek() != EOF)
	{
		getline(file, line);

		// checking if record exists within the file
		if ((currentUser == line) && isLoggedIn)
		{
			getline(file, line, ';');

			cout << line << "\n";
			valueExists = true;
		}
	}

	if (!valueExists)
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

	if (!checkForUser(newServiceName, accountsFile))
	{
		cout << "Enter account's login: ";
		cin >> newLogin;
		cout << "Enter account's password: ";
		cin >> newPassword;

		addLine(accountsFile, '\n' + currentUser + "\n+----------------------+\n" + newServiceName + 
			"\n###############\n" + newLogin + '\n' + newPassword + "\n+----------------------+\n;");
	}
	else
	{
		cout << "This record already exists.\n";
	}
}

/// checks if a string has certain content. The last parameter is the delimiter.
/// To find a word use ' ', for line use \n with single quotes.
bool LoginManager::hasContent(string sourceString, string contentToFind, char delimiter)
{
	string word;
	bool isRecordToRemove = false;
	istringstream inputStream(sourceString);

	while (getline(inputStream, word, delimiter))
	{
		if (word == contentToFind)
		{
			isRecordToRemove = true;
			break;
		}
		else
		{
			isRecordToRemove = false;
		}
	}

	return isRecordToRemove;
}

// removes account record for the user
void LoginManager::removeAccount()
{
	fstream mainFile;
	ofstream tempFile;
	string line, recordToRemove;
	int countRecordsToRemove = 0;

	cout << "Enter the name of the service account that you would like to delete: ";
	cin >> recordToRemove;

	mainFile.open(accountsFile, ios::in);
	tempFile.open("temp.dat", ios::app);

	// read untill the end of the file
	while (mainFile.peek() != EOF)
	{
		getline(mainFile, line, ';');

		if (line == "\n" && mainFile.peek() == EOF)
		{
			break;
		}

		// checking if the line doesn't contain parameter 'recordsToRemove'
		if (hasContent(line, currentUser, '\n') && !hasContent(line, recordToRemove, '\n'))
		{
			tempFile << line << ';';
		}
		else
		{
			countRecordsToRemove++;
		}

	}

	if (countRecordsToRemove <= 0)
	{
		cout << "There is no '" << recordToRemove << "' record for current user.\n";
	}
	mainFile.close();
	tempFile.close();

	remove(accountsFile.c_str());
	bool isRenameSuccessful = rename("temp.dat", accountsFile.c_str());
}

// removes current user and it's accounts file
void LoginManager::removeUser()
{
	fstream mainFile;
	ofstream tempFile;
	char input;
	string line;

	cout << "Would you like to delete this user?\n"
		 << "Note that accounts for this user will also be deleted.\n"
		 << "To continue enter Y/y, to stop - anything else: ";
	cin >> input;

	if ((input == 'Y') || (input == 'y'))
	{
		mainFile.open(usersFile, ios::in);
		tempFile.open("temp.dat", ios::app);

		// read untill the end of the file
		while (mainFile.peek() != EOF)
		{
			getline(mainFile, line, ';');

			if (line == "\n" && mainFile.peek() == EOF)
			{
				break;
			}

			// checking if the line doesn't contain parameter 'recordsToRemove'
			if (!hasContent(line, currentUser, '\n'))
			{
				tempFile << line << ';';
			}

		}
		mainFile.close();
		tempFile.close();

		remove(usersFile.c_str());
		remove(accountsFile.c_str());
		bool isRenameSuccessful = rename("temp.dat", usersFile.c_str());
	}
}
