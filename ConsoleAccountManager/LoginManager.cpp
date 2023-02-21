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

			cout << "Enter password: ";
			cin >> password;
			cout << "\n";

			countAttempts++;

			if (line == password)
			{
				isPasswordCorrect = true;

				break;
			}
			else
			{
				isPasswordCorrect = false;
				cout << "Password " << password << " is not correct\n";

				if (countAttempts > 3)
				{
					cout << "You've entered wrong password too many times.\n";
					countAttempts = 0;

					break;
				}

				checkForPassword();
			}
		}
	}
	file.close();

	return isPasswordCorrect;
}

// login function
void LoginManager::login()
{
	cout << "Please enter your user login \nLogin:";
	cin >> inputLogin;
	// user check
	if (checkForUser(inputLogin, usersFile))
	{
		cout << "\nUser found\n";
		currentUser = inputLogin;

		// password check
		checkForPassword() ? isLoggedIn = true : isLoggedIn = false;
	}
	else
	{
		cout << "\nNo such user\n";
		isLoggedIn = false;
	}

}

// add user function
void LoginManager::addUser()
{
	string newUserName, newUserPassword;

	// getting username and password
	cout << "\nEnter new user's name: ";
	cin >> newUserName;

	cout << "\nNow enter a password: ";
	cin >> newUserPassword;

	// putting username and password into appropriate files
	addLine(usersFile, newUserName);
	addLine(usersFile, newUserPassword + ";");

	cout << "User added successfully :)\n";
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
void LoginManager::addAccount(string userName, string serviceName, string login, string password)
{
	addLine(accountsFile, userName);
	addLine(accountsFile, "+----------------------+");
	addLine(accountsFile, serviceName);
	addLine(accountsFile, "###############");
	addLine(accountsFile, login);
	addLine(accountsFile, password);
	addLine(accountsFile, "+----------------------+\n;");
}