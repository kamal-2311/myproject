#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <fstream>
#include <cctype>
#include <iomanip>
using namespace std;

void nothing()
{
	
}

const string clientsfile = "Clients.txt";
const string usersfile = "Users.txt";

enum userchoice { eShowClients = 1, eAdd, eDelete, eUpdate, eFind, eTransactions, eMangeUsers, eLogout };

enum usertransferchoice { eDeposit = 1, eWithDraw, eTotalBalance, eMainscreen, };

enum manageuser { eShowUsers = 1, eAddUser, eDeleteUser, eUpdateUser, eFindUser, eMain };

struct clientinfo {
	string accountnumber;
	string pincode;
	string name;
	string phone;
	string balance;
};

struct userinfo {
	string name;
	string password;
	int permissions;
};

void Login();

void BANK(vector<string>, userinfo);

vector<string> FileToVector(string);

void VectorToFile(vector<string>, string);

int ReadNumber(string, int, int);

float ReadFloat(string);

string structtostring_client(clientinfo, string);

clientinfo stringtostruct_client(string, string);

void PrintClientInfo(clientinfo);

bool CheckAnswer(string);

bool IsClientExist(vector<string>, string, short& position);

void FindClient(vector<string>, short& position);

void Title(string);

void MainScreen();

void ShowClientList(vector<string>);

void AddClient(vector <string>);

string ReadString(string);

bool IsClientExist(vector<string>, string);

void FindClient(vector<string>vbank);

void Press();

void DeleteClient(vector<string>);

void UpdateClient(vector<string>);

void Transactions(vector <string>);

void DepositInClientAccount(vector <string>);

void WithDrawInClientAccount(vector<string>);

void TransactionScreen();

void ShowTotalBalance(vector<string>);

float CalculateTotalBalance(vector<string>);

bool AreUserInfoCorrect(vector<string>, userinfo&);

userinfo stringtostruct_user(string, string);

string structtostring_user(userinfo, string);

userinfo ReadUserInfo(vector<string>);

void ManageUsers(vector<string>&);

bool HaveAccessToThisPermission(userinfo, short);

short Power(short, short);

void ManageUsersScreen();

void ShowUsersList(vector<string>);

void AddNewUser(vector<string>);

bool IsUserExist(vector<string>, string);

void DeleteUser(vector<string>);

bool IsUserExist(vector<string>, string, short&);

void UpdateUser(vector<string>);

void FindUser(vector<string>);

void PrintUserInfo(userinfo);

short ReadPermissionToSet();

int main()
{
	Login();

	return 0;
}

void Login()
{
	do
	{
		vector <string> vuser = FileToVector(usersfile);
		userinfo user;
		Title("Login Screen");
		user = ReadUserInfo(vuser);
		system("cls");
		BANK(vuser, user);
	} while (1);
}

void BANK(vector<string>vuser, userinfo user)
{
	vector<string> vbank;
	userchoice choice;
	bool exit = false;
	do
	{
		system("cls");
		vbank = FileToVector(clientsfile);
		MainScreen();
		choice = (userchoice)ReadNumber("Choose What Do You Want To Do? [1 to 8]: ", 1, 8);
		system("cls");
		if (choice == eLogout || HaveAccessToThisPermission(user, Power(2, (short)choice - 1)) || user.permissions == -1)
		{
			switch (choice)
			{
			case eShowClients:
				ShowClientList(vbank);
				Press();

				break;

			case eAdd:
				AddClient(vbank);
				Press();

				break;

			case eDelete:
				DeleteClient(vbank);
				Press();

				break;

			case eUpdate:
				UpdateClient(vbank);
				Press();

				break;

			case eFind:
				FindClient(vbank);
				Press();

				break;


			case eTransactions:
				Transactions(vbank);

				break;

			case eMangeUsers:
				ManageUsers(vuser);

				break;


			case eLogout:
				exit = true;
				cout << "\n-------------------------------------" << endl;
				cout << "          Program Ends !             " << endl;
				cout << "-------------------------------------\n\n\n";

				break;

			}
		}
		else
		{
			cout << "\n---------------------------------------------\n";
			cout << "Access Deniend." << endl;
			cout << "You Don't Have The Permission To Do This." << endl;
			cout << "Please Contact Your Admin.";
			cout << "\n---------------------------------------------\n";
			Press();
		}
	} while (!exit);

}

vector<string> FileToVector(string filename)
{
	fstream fbank;
	vector<string> vbank;
	string line;
	fbank.open(filename, ios::in);
	if (fbank.is_open())
	{
		while (getline(fbank, line))
		{
			vbank.push_back(line);
		}
		fbank.close();
	}
	return vbank;
}

void VectorToFile(vector<string> vbank, string filename)
{
	fstream fbank;
	fbank.open(filename, ios::out);
	if (fbank.is_open())
	{
		for (string& line : vbank)
		{
			fbank << line << endl;
		}
		fbank.close();
	}
}

int ReadNumber(string message, int from = 0, int to = 99999)
{
	int num;
	do {
		cout << message;
		cin >> num;
		while (cin.fail())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid Value! Please Enter a number: ";
			cin >> num;
		}
	} while (num < from || num > to);
	return num;
}

float ReadFloat(string message)
{
	float num;
	cout << message;
	cin >> num;
	while (cin.fail())
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Invalid Value! Please Enter a number: ";
		cin >> num;
	}

	return num;
}

string structtostring_client(clientinfo clientstruct, string sign)
{
	string clientstring = "";

	clientstring = clientstruct.accountnumber + sign + clientstruct.pincode + sign + clientstruct.name + sign + clientstruct.phone + sign + clientstruct.balance;

	return clientstring;
}

clientinfo stringtostruct_client(string clientstring, string sign)
{
	clientinfo clientstruct;
	short i = 1;
	short pos;
	while ((pos = (short)clientstring.find(sign)) != clientstring.npos)
	{
		switch (i)
		{
		case 1: clientstruct.accountnumber = clientstring.substr(0, pos);i++;break;
		case 2: clientstruct.pincode = clientstring.substr(0, pos);i++;break;
		case 3: clientstruct.name = clientstring.substr(0, pos);i++;break;
		default: clientstruct.phone = clientstring.substr(0, pos);
		}
		clientstring.erase(0, pos + sign.length());
	}
	clientstruct.balance = clientstring;

	return clientstruct;
}

void PrintClientInfo(clientinfo client)
{
	cout << "The Following Are The Client Details:\n";
	cout << "--------------------------------------\n";
	cout << "Account Number  : " << client.accountnumber << endl;
	cout << "Pin Code        : " << client.pincode << endl;
	cout << "Name            : " << client.name << endl;
	cout << "Phone           : " << client.phone << endl;
	cout << "Account Balance : " << client.balance << endl;
	cout << "--------------------------------------\n";

}

bool CheckAnswer(string message)
{
	char answer;
	cout << message;
	cin >> answer;
	if (tolower(answer) == 'y')
	{
		return true;
	}
	else
	{
		return false;
	}
}

string ReadAccountNumber()
{
	string accountnumber;

	cout << "\nPlease Enter Account Number: ";
	cin >> accountnumber;

	return accountnumber;
}

bool IsClientExist(vector<string> vbank, string accountnumber, short& position)
{
	position = 0;
	clientinfo client;
	for (string& line : vbank)
	{
		client = stringtostruct_client(line, "#//#");
		if (client.accountnumber == accountnumber)
		{
			return true;
		}
		else
		{
			position++;
		}
	}
	return false;
}

bool IsClientExist(vector<string> vbank, string accountnumber)
{

	clientinfo client;
	for (string& line : vbank)
	{
		client = stringtostruct_client(line, "#//#");
		if (client.accountnumber == accountnumber)
		{
			return true;
		}
	}
	return false;
}

void FindClient(vector<string>vbank, short& position)
{
	Title("Find Clinet Screen");
	string accountnumber = ReadAccountNumber();

	if (!(IsClientExist(vbank, accountnumber, position)))
	{
		cout << "\n\nClient With Account Number " << accountnumber << " Is Not Found!\n";
	}
	else
	{
		cout << endl << endl;
		PrintClientInfo(stringtostruct_client(vbank.at(position), "#//#"));
	}
}

void FindClient(vector<string>vbank)
{
	short position;
	Title("Find Clinet Screen");
	string accountnumber = ReadAccountNumber();

	if (!(IsClientExist(vbank, accountnumber, position)))
	{
		cout << "\n\nClient With Account Number " << accountnumber << " Is Not Found!\n";
	}
	else
	{
		cout << endl << endl;
		PrintClientInfo(stringtostruct_client(vbank.at(position), "#//#"));
	}
}

void Title(string message)
{
	cout << "--------------------------------------\n";
	cout << "         " << message << "           \n";
	cout << "--------------------------------------\n";
}

void MainScreen()
{
	cout << "=========================================\n";
	cout << "             Main Menue Screen           \n";
	cout << "=========================================\n";
	cout << "       [1] Show Clinet List." << endl;
	cout << "       [2] Add New Client." << endl;
	cout << "       [3] Delete Client." << endl;
	cout << "       [4] Update CLient Info." << endl;
	cout << "       [5] Find Client." << endl;
	cout << "       [6] Transactions. " << endl;
	cout << "       [7] Manage Users. " << endl;
	cout << "       [8] Logout." << endl;
	cout << "=========================================\n";
}

void ShowClientList(vector<string> vbank)
{
	clientinfo client;
	cout << "\n                                  Client List (" << vbank.size() << ") Client(s)" << endl << endl;
	cout << "____________________________________________________________________________________________________________\n\n";
	cout << setw(18) << left << "| Account Number";
	cout << setw(14) << left << "| Pin Code";
	cout << setw(40) << left << "| Client Name";
	cout << setw(15) << left << "| Phone";
	cout << setw(15) << left << "| Balance" << endl;
	cout << "____________________________________________________________________________________________________________\n\n";


	for (string& line : vbank)
	{
		client = stringtostruct_client(line, "#//#");
		cout << "| " << setw(16) << left << client.accountnumber;
		cout << "| " << setw(12) << left << client.pincode;
		cout << "| " << setw(38) << left << client.name;
		cout << "| " << setw(13) << left << client.phone;
		cout << "| " << setw(13) << left << client.balance << endl;
	}
	cout << "____________________________________________________________________________________________________________\n";

}

void AddClient(vector <string>vbank)
{
	clientinfo client;
	do
	{
		system("cls");
		Title("Add New Client Screen");
		cout << "Adding a New Client:" << endl;
		client.accountnumber = ReadString("\nEnter Account Number: ");

		while (IsClientExist(vbank, client.accountnumber))
		{
			cout << "\nClient With [" << client.accountnumber << "] Already Exists! Enter Another Account Number: ";
			client.accountnumber = ReadString("");
		}
		client.pincode = to_string(ReadNumber("Enter PinCode: "));
		client.name = ReadString("Enter Name: ");
		client.phone = ReadString("Enter Phone: ");
		client.balance = to_string(ReadFloat("Enter AccountBalance: "));
		vbank.push_back(structtostring_client(client, "#//#"));
		VectorToFile(vbank, clientsfile);
	} while (CheckAnswer("\nClient Added Successfully,Do You Want To Add More Client? y/n: "));
}

string ReadString(string message)
{
	string astring;
	cout << message;
	getline(cin >> ws, astring);
	return  astring;
}

void Press()
{
	cout << endl << endl << endl << "Press Any Key To Go Back To Menue...";
	system("pause");
}

void DeleteClient(vector<string> vbank)
{
	vector<string>::iterator itr;
	Title("Delete Client Screen");
	short position;
	string accountnumber = ReadString("\nPlease Enter Account Number: ");

	if (IsClientExist(vbank, accountnumber, position))
	{
		cout << endl;
		PrintClientInfo(stringtostruct_client(vbank.at(position), "#//#"));
		if (CheckAnswer("\nAre You Sure You Want To Delete This Client? y/n: "))
		{
			itr = vbank.begin();
			itr += position;
			vbank.erase(itr);
			VectorToFile(vbank, clientsfile);
			cout << "\n\nClient Deleted Successfuly.";

		}
	}
	else
	{
		cout << "\n\nClient With Account Number (" << accountnumber << ") Is Not Found!\n";
	}

}

void UpdateClient(vector<string> vbank)
{
	vector<string>::iterator itr;
	Title("Update Client Screen");
	short position;
	string accountnumber = ReadString("\nPlease Enter Account Number: ");
	clientinfo client;

	if (IsClientExist(vbank, accountnumber, position))
	{
		cout << endl;
		PrintClientInfo(stringtostruct_client(vbank.at(position), "#//#"));

		if (CheckAnswer("\nAre You Sure You Want To Update This Client? y/n: "))
		{
			itr = vbank.begin();
			itr += position;
			client = stringtostruct_client(*itr, "#//#");
			client.pincode = to_string(ReadNumber("\nEnter PinCode: "));
			client.name = ReadString("Enter Name: ");
			client.phone = ReadString("Enter Phone: ");
			client.balance = ReadString("Enter AccountBalance: ");

			*itr = structtostring_client(client, "#//#");

			VectorToFile(vbank, clientsfile);

			cout << "\n\nClient Updated Successfuly.";
		}
	}
	else
	{
		cout << "\n\nClient With Account Number (" << accountnumber << ") Is Not Found!\n";
	}
}

void Transactions(vector <string> vbank)
{
	bool keep = true;
	do
	{
		TransactionScreen();
		usertransferchoice choice = (usertransferchoice)ReadNumber("", 1, 4);
		system("cls");
		switch (choice)
		{
		case eDeposit:
			DepositInClientAccount(vbank);
			Press();
			break;

		case eWithDraw:
			WithDrawInClientAccount(vbank);
			Press();

			break;

		case eTotalBalance:
			ShowTotalBalance(vbank);
			Press();
			break;

		case eMainscreen:
			keep = false;
			break;
		}
		system("cls");
	} while (keep);
}

void DepositInClientAccount(vector <string> vbank)
{
	system("cls");
	Title("Deposit Screen");
	vector<string>::iterator itr = vbank.begin();
	clientinfo client;
	string message;
	short position;
	float toadd;
	string accountnumber = ReadAccountNumber();
	while (!(IsClientExist(vbank, accountnumber, position)))
	{
		cout << "Client With Account Number (" << client.accountnumber << ") Is Not Found\n\n";
		accountnumber = ReadAccountNumber();
	}


	itr += position;
	client = stringtostruct_client(*itr, "#//#");
	PrintClientInfo(client);
	toadd = ReadFloat("\nPlease Enter Deposit Amount: ");
	message = "\nAre You Sure You Want To Perfrom This Transaction? [y/n]: ";
	if (CheckAnswer(message))
	{
		toadd += stof(client.balance);
		client.balance = to_string(toadd);
		*itr = structtostring_client(client, "#//#");
		cout << "Done Successfuly! New Blanace Of Client (" << client.accountnumber << ") Is " << client.balance << endl << endl;

		VectorToFile(vbank, clientsfile);
	}


}

void WithDrawInClientAccount(vector<string> vbank)
{
	system("cls");
	Title("WithDraw Screen");
	string message;
	short position;
	clientinfo client;
	vector <string>::iterator itr = vbank.begin();
	float tocost;
	string accountnumber = ReadAccountNumber();

	while (!(IsClientExist(vbank, accountnumber, position)))
	{
		cout << "Client With Account Number (" << client.accountnumber << ") Is Not Found\n\n";
		accountnumber = ReadAccountNumber();
	}


	itr += position;
	client = stringtostruct_client(*itr, "#//#");
	PrintClientInfo(client);
	tocost = ReadFloat("\nPlease Enter WithDraw Amount: ");
	while (tocost >= stof(client.balance))
	{
		cout << "\nAmount Exceeds The Balance! You Can WithDraw up To: " << client.balance;
		tocost = ReadFloat("\nPlease Enter WithDraw Amount: ");
	}
	message = "\nAre You Sure You Want To Perfrom This Transaction? [y/n]: ";
	if (CheckAnswer(message))
	{
		client.balance = to_string(stof(client.balance) - tocost);
		*itr = structtostring_client(client, "#//#");
		cout << "\n\nDone Successfuly! New Blanace Of Client (" << client.accountnumber << ") Is " << client.balance << endl << endl;

		VectorToFile(vbank, clientsfile);

	}

}

void TransactionScreen()
{
	cout << "=========================================\n";
	cout << "             Transactions Screen           \n";
	cout << "=========================================\n";
	cout << "       [1] Deposit." << endl;
	cout << "       [2] WithDraw. " << endl;
	cout << "       [3] Total Balances." << endl;
	cout << "       [4] Main Menue. " << endl;
	cout << "=========================================\n";
	cout << "Choose What Do You Want To Do? [1-4]: ";
}

void ShowTotalBalance(vector <string>vbank)
{
	clientinfo client;
	cout << "\n                                  Balances List (" << vbank.size() << ") Client(s)" << endl << endl;
	cout << "____________________________________________________________________________________________________________\n\n";
	cout << setw(18) << left << "| Account Number";
	cout << setw(40) << left << "| Client Name";
	cout << setw(15) << left << "| Balance" << endl;
	cout << "____________________________________________________________________________________________________________\n\n";


	for (string& line : vbank)
	{
		client = stringtostruct_client(line, "#//#");
		cout << "| " << setw(16) << left << client.accountnumber;
		cout << "| " << setw(38) << left << client.name;
		cout << "| " << setw(13) << left << client.balance << endl;
	}
	cout << "____________________________________________________________________________________________________________\n\n";
	cout << "                                       Total Balances = " << CalculateTotalBalance(vbank) << endl << endl;;
}

float CalculateTotalBalance(vector<string> vbank)
{
	float total = 0;
	clientinfo client;
	for (string& line : vbank)
	{
		client = stringtostruct_client(line, "#//#");
		total += stof(client.balance);
	}
	return total;
}

bool AreUserInfoCorrect(vector<string> vuser, userinfo& usertochek)
{
	userinfo user;
	for (string line : vuser)
	{
		user = stringtostruct_user(line, "#//#");
		if (user.name == usertochek.name && user.password == usertochek.password)
		{
			usertochek.permissions = user.permissions;
			return true;
		}
	}
	return false;
}

userinfo stringtostruct_user(string userstring, string sign)
{
	short pos, i = 1;
	userinfo user;

	while ((pos = (short)userstring.find(sign)) != userstring.npos)
	{
		switch (i)
		{
		case 1: user.name = userstring.substr(0, pos);i++;break;
		case 2: user.password = userstring.substr(0, pos);i++;break;
		}
		userstring.erase(0, pos + sign.length());
	}
	user.permissions = stoi(userstring);

	return user;
}

string structtostring_user(userinfo user, string sign)
{
	return user.name + sign + user.password + sign + to_string(user.permissions);
}

userinfo ReadUserInfo(vector<string> vuser)
{
	userinfo user;
	user.name = ReadString("Enter Username: ");
	user.password = ReadString("Enter Password: ");
	while (!AreUserInfoCorrect(vuser, user))
	{
		system("cls");
		Title("Login Screen");
		cout << "Invalid Username/Password!" << endl;
		user.name = ReadString("Enter Username: ");
		user.password = ReadString("Enter Password: ");
	}
	return user;
}

void ManageUsers(vector<string>& vuser)
{
	manageuser choice;
	bool keep = true;
	do
	{
		system("cls");
		ManageUsersScreen();
		choice = (manageuser)ReadNumber("");
		system("cls");
		switch (choice)
		{
		case eShowUsers:
			ShowUsersList(vuser);
			Press();
			break;

		case eAddUser:
			AddNewUser(vuser);
			Press();
			break;

		case eDeleteUser:
			DeleteUser(vuser);
			Press();
			break;


		case eUpdateUser:
			UpdateUser(vuser);
			Press();
			break;

		case eFindUser:
			FindUser(vuser);
			Press();
			break;

		case eMain:
			keep = false;

		}
		vuser = FileToVector(usersfile);

	} while (keep);
}

bool HaveAccessToThisPermission(userinfo user, short access)
{
	return (user.permissions & access);
}

short Power(short num, short power)
{
	if (num == 0)
	{
		return 0;
	}
	if (power == 0)
	{
		return 1;
	}
	short sum = num;
	for (short i = 1;i < power; i++)
	{
		sum *= num;
	}
	return sum;
}

void ManageUsersScreen()
{
	cout << "=========================================\n";
	cout << "            Manage Users Screen          \n";
	cout << "=========================================\n";
	cout << "       [1] List Users." << endl;
	cout << "       [2] Add New User. " << endl;
	cout << "       [3] Delete User." << endl;
	cout << "       [4] Update User. " << endl;
	cout << "       [5] Find User. " << endl;
	cout << "       [6] Main Menue. " << endl;
	cout << "=========================================\n";
	cout << "Choose What Do You Want To Do? [1-6]: ";
}

void ShowUsersList(vector<string> vuser)
{
	userinfo user;
	cout << "\n                                  Users List (" << vuser.size() << ") User(s)" << endl << endl;
	cout << "____________________________________________________________________________________________________________\n\n";
	cout << setw(20) << left << "| User Name";
	cout << setw(15) << left << "| Password";
	cout << setw(15) << left << "| Permissions" << endl;
	cout << "____________________________________________________________________________________________________________\n\n";


	for (string& line : vuser)
	{
		user = stringtostruct_user(line, "#//#");
		cout << "| " << setw(18) << left << user.name;
		cout << "| " << setw(13) << left << user.password;
		cout << "| " << setw(13) << left << user.permissions << endl;
	}
	cout << "____________________________________________________________________________________________________________\n\n";
}

void AddNewUser(vector<string> vuser)
{
	userinfo user;
	do
	{
		system("cls");
		Title("Add New User Screen");
		cout << "Adding a New User:" << endl;
		user.name = ReadString("\nEnter User Name: ");

		while (IsUserExist(vuser, user.name))
		{
			cout << "\nUser With [" << user.name << "] Already Exist! Enter Another UserName: ";
			user.name = ReadString("");
		}
		user.password = to_string(ReadNumber("Enter Password: "));

		user.permissions = ReadPermissionToSet();

		vuser.push_back(structtostring_user(user, "#//#"));
		VectorToFile(vuser, usersfile);
	} while (CheckAnswer("\nUser Added Successfully,Do You Want To Add More User? y/n: "));
}

bool IsUserExist(vector<string> vuser, string username)
{
	userinfo user;
	for (string line : vuser)
	{
		user = stringtostruct_user(line, "#//#");
		if (user.name == username)
		{
			return true;
		}
	}
	return false;
}

bool IsUserExist(vector<string> vuser, string username, short& position)
{
	userinfo user;
	position = 0;
	for (string line : vuser)
	{
		user = stringtostruct_user(line, "#//#");
		if (user.name == username)
		{
			return true;
		}
		position++;
	}
	return false;
}

void DeleteUser(vector<string> vuser)
{
	vector<string>::iterator itr;
	Title("Delete User Screen");
	short position;
	string username = ReadString("\nPlease Enter Account Number: ");

	if (IsUserExist(vuser, username, position))
	{
		cout << endl;
		PrintUserInfo(stringtostruct_user(vuser.at(position), "#//#"));
		if (CheckAnswer("\nAre You Sure You Want To Delete This Client? y/n: "))
		{
			itr = vuser.begin();
			itr += position;
			vuser.erase(itr);
			VectorToFile(vuser, usersfile);
			cout << "\n\nUser Deleted Successfuly.";

		}
	}
	else
	{
		cout << "\n\nUser [" << username << "] Is Not Found!\n";
	}
}

void UpdateUser(vector<string> vuser)
{
	vector<string>::iterator itr;
	Title("Update User Screen");
	short position;
	string username = ReadString("\nPlease User Name: ");
	userinfo user;

	if (IsUserExist(vuser, username, position))
	{
		cout << endl;
		PrintUserInfo(stringtostruct_user(vuser.at(position), "#//#"));

		if (CheckAnswer("\nAre You Sure You Want To Update This User? y/n: "))
		{
			itr = vuser.begin();
			itr += position;
			user = stringtostruct_user(*itr, "#//#");
			user.password = ReadString("Enter User Password: ");

			user.permissions = ReadPermissionToSet();

			*itr = structtostring_user(user, "#//#");

			VectorToFile(vuser, usersfile);

			cout << "\n\nUser Updated Successfuly.";
		}
	}
	else
	{
		cout << "\n\nUser [" << username << "] Is Not Found!\n";
	}
}

void FindUser(vector<string> vuser)
{
	short position;
	Title("Find User Screen");
	string username = ReadString("\nEnter User Name: ");

	if (!(IsUserExist(vuser, username, position)))
	{
		cout << "\n\nUser " << username << " Is Not Found!\n";
	}
	else
	{
		cout << endl << endl;
		PrintUserInfo(stringtostruct_user(vuser.at(position), "#//#"));
	}
}

void PrintUserInfo(userinfo user)
{
	cout << "The Following Are The User Details:\n";
	cout << "--------------------------------------\n";
	cout << "User Name         : " << user.name << endl;
	cout << "User Password     : " << user.password << endl;
	cout << "User Permissions  : " << user.permissions << endl;
	cout << "--------------------------------------\n";
}

short ReadPermissionToSet()
{
	short permissions = 0;

	if (CheckAnswer("\nDo You Want To Give Full Access? y/n: "))
	{
		return -1;
	}

	cout << "\n\nDo You Want To Give Access To:\n";
	if (CheckAnswer("\nShow Client List? y/n: "))
		permissions = 1;

	if (CheckAnswer("\nAdd New Client? y/n: "))
		permissions += 2;

	if (CheckAnswer("\nDelete Client? y/n: "))
		permissions += 4;

	if (CheckAnswer("\nUpdate Client? y/n: "))
		permissions += 8;

	if (CheckAnswer("\nFind Client? y/n: "))
		permissions += 16;

	if (CheckAnswer("\nTransactions? y/n: "))
		permissions += 32;

	if (CheckAnswer("\nManage Users? y/n: "))
		permissions += 64;

	return permissions;
}
