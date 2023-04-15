#include "AppMenu.h"
#include "LoginManager.h"

void AppMenu::AppUI()
{
    LoginManager app;

    int countLoginAttempts = 0;
    char menuCursor = 49;

    while (menuCursor != 48) {
        cout << "Choose an action: \n\n";

        cout << "1) Log in into the app \n";
        cout << "2) Add new user \n\n";

        cout << "0) Exit \n";

        cin >> menuCursor;

        switch (menuCursor)
        {
            #pragma region case 1
            case 49:
            {
                // login
                if (app.login())
                {
                    while (menuCursor != 53)
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
                            // case 1
                            case 49:
                            {
                                // reading and displaying account records for current user
                                app.readAccounts();

                                break;
                            }

                            // case 2
                            case 50:
                            {
                                // adding new account records
                                app.addAccount();

                                break;
                            }

                            // case 3
                            case 51:
                            {
                                // removing specific record
                                app.removeAccount();

                                break;
                            }
                            
                            // case 4
                            case 52:
                            {
                                // removing current user and it's accounts
                                if (app.removeUser())
                                {
                                    menuCursor = 53;
                                }
                                
                                break;
                            }
                            default:
                            {
                                if (menuCursor != 53)
                                {
                                    cout << "Invalid input\n";
                                }

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
                    if (countLoginAttempts >= 3)
                    {
                        cout << "Too many login attempts.\n"
                             << "Try next time.\n";

                        menuCursor = 48;
                    }
                    else
                    {
                        cout << "Login or password is not correct.\n" 
                             << "You're not logged in.\n";

                        countLoginAttempts++;
                    }
                }
                
                break;
            }
            #pragma endregion

            // case 2
            case 50:
            {
                app.addUser();

                break;
            }
            // case ?
            case 63:
            {
                cout << "App version:\n"
                     << "v.0.0.6-beta\n\n"
                     << "Made by:\n"
                     << "music-soul1-1\n\n"
                     << "To get the latest version, visit app's Github page:\n"
                     << "https://github.com/music-soul1-1/ConsoleAccountManager\n\n";

                break;
            }
            default:
            {
                if (menuCursor != 48)
                {
                    cout << "Invalid input\n";
                }

                break;
                
            }
        }
        system("PAUSE");
        system("CLS");
    }
    cin.get();
}
