#include "AppMenu.h"
#include "LoginManager.h"

void AppMenu::AppUI()
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
                if (app.login())
                {
                    while (menuCursor != 5)
                    {
                        cout << "Choose an action: \n\n";

                        cout << "1) Read account records \n";
                        cout << "2) Add new account \n";
                        cout << "3) Remove account \n";
                        cout << "4) Remove current user \n\n";

                        cout << "5) Go back \n";
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
                                app.addAccount();

                                break;
                            }

                            // removing specific record
                            case 3:
                            {
                                app.removeAccount();

                                break;
                            }
                            
                            // removing current user and it's accounts
                            case 4:
                            {
                                app.removeUser();
                                menuCursor = 5;

                                break;
                            }
                        }
                        system("PAUSE");
                        system("CLS");
                    }
                    break;
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
