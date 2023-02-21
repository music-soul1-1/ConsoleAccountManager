#include "LoginManager.h"

int main()
{
    LoginManager app;

    int menuCursor = 1;

    while (menuCursor != 0) {
        cout << "Choose an action: \n\n";

        cout << "1) Log in into the app \n";
        cout << "2) Add new user \n\n";

        cout << "0) Exit \n";
        cin >> menuCursor;

        switch (menuCursor)
        {
            // login
            case 1:
            {
                app.login();

                if (app.LoginManager::isLoggedIn)
                {
                    while (menuCursor != 3)
                    {
                        cout << "Choose an action: \n\n";

                        cout << "1) Read account records \n";
                        cout << "2) Add new account \n\n";

                        cout << "3) Go back \n";
                        cin >> menuCursor;

                        switch (menuCursor)
                        {
                            // reading and displaying account records for current user
                            case 1:
                            {
                                app.readAccounts();
                                break;
                            }

                            // adding new account records
                            case 2:
                            {
                                string newLogin, newPassword, newServiceName;

                                cout << "Enter the name of the service (e.g. Gmail): ";
                                cin >> newServiceName;
                                cout << "Enter account's login: ";
                                cin >> newLogin;
                                cout << "Enter account's password: ";
                                cin >> newPassword;

                                app.addAccount(app.LoginManager::currentUser, newServiceName, newLogin, newPassword);

                                break;
                            }
                        }
                        system("PAUSE");
                        system("CLS");
                    }
                }
                else
                {
                    cout << "You're not logged in.\n";
                }

                break;
            }

            // add user
            case 2:
            {
                app.addUser();
                break;
            }
        }
        system("PAUSE");
        system("CLS");
    }

    cin.get();
}