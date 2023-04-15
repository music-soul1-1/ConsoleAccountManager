# Console Account Manager
#### This C++ console app allows you to store logins and passwords for different services.

Data files are stored in the app's folder.

### [See changelog](https://github.com/music-soul1-1/ConsoleAccountManager#changelog)

## Features:
* account manager
* multi-user app
* account records are only available for authorised users who created the records
* data files are encrypted
* names of the services are also stored
* data files are created automatically

## Usage:
1. Download the [latest release](https://github.com/music-soul1-1/ConsoleAccountManager/releases).
2. Unzip the folder.
3. Run "ConsoleAccountManager.exe".
4. To control the app you need to input numbers (e.g. 1 to log in)
5. Enjoy :)

## Screenshots:

![Знімок екрана_20230221_211513](https://user-images.githubusercontent.com/72669184/220441132-52ba0741-9d1d-4333-b4ad-87c95266ddf8.png)
![Знімок екрана_20230221_211736](https://user-images.githubusercontent.com/72669184/220441232-04baa18b-2111-41dd-b0ee-fa802a1a5d04.png)
![Знімок екрана 2023-03-31 215808](https://user-images.githubusercontent.com/72669184/229206636-2bbca4b3-ee2e-49ed-b68f-4a31ddcf703e.png)
![Знімок екрана_20230228_225115](https://user-images.githubusercontent.com/72669184/221977450-6bdfb750-f226-4548-b6e7-d00b3413f7b9.png)
![Знімок екрана_20230228_225116](https://user-images.githubusercontent.com/72669184/221977460-621cf01a-687c-4028-9e69-0b4bfe4d76f6.png)
![Знімок екрана 2023-04-08 142938](https://user-images.githubusercontent.com/72669184/230720159-d14a9ec9-3818-4c70-84a6-c3b8a2abcb3c.png)
![Знімок екрана_20230228_225114](https://user-images.githubusercontent.com/72669184/221977212-ff4c1418-bad8-40e4-be0c-6045644f28d3.png)




## Plans for the app:
* improve encryption/decryption security
* improve code readability
* find and fix bugs


## Changelog:

### v.0.0.6-beta:
* small improvements.
* now the user has only 3 attempts to log in. If exceeded, the programm exits.
* the length of separator lines was increased for readability.
* "ConsoleAccountManager.cpp" was renamed to "Main.cpp".

### v.0.0.5-beta:
* fixed bug when removing user, app would always exit to the main menu, even if the user chose not to.
* fixed bug when 2 or more identical users could be added.
* data file extention changed from .dat to .datafile
* encryption and decryption functions changed a bit

### v.0.0.4-beta:
* bug fix.
* encryption and decryption changed a bit.

### v.0.0.3-beta:
* BIG updade - encryption and decryption are added.  
They use input password as a key, so every record is secured.
* account records are now stored in one file again.
* invalid input fix.
* if you enter '?' in the main menu(before logging in), you will see app info.

### v.0.0.2-alpha:
* added ability to remove users and their account records
* accounts are now stored separately(one file for each user)
* now you cannot add the same services (e.g. if you already have 'gmail' record, you will have to name the next service 'gmail2')
* bug fix


Made by @music-soul1-1

2023
