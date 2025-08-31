#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include <limits>
#include <bitset>

using namespace std;

const string ClientFileName = "C:\\Users\\User\\Desktop\\MyProjects\\MyCV\\Projects_Course_5\\Projects_C_5\\Bink\\Clients.txt";
const string UsersFileName = "C:\\Users\\User\\Desktop\\MyProjects\\MyCV\\Projects_Course_5\\Projects_C_5\\Bink\\Users.txt";

enum enUserChoices {View = 1, Add = 2, Delete = 3, Update = 4, Find = 5,Transactions = 6,ManageUsers = 7, Logout = 8};
enum enTransactions {Deposit = 1, Withdraw = 2, TotalBalance = 3, MainMune = 4};
enum enManageUsers { List = 1, AddUser = 2, DeleteUser = 3, UpdateUser = 4, FindUser = 5, MainMuneFromManage = 6 };
enum enPermissions {PAll = -1, PView = 1, PAdd = 2, PDelete = 4, PUpdate = 8, PFind = 16, PTransactions = 32, PManageUsers = 64 };
struct stClientData
{
	string AccountNumber;
	string PineCode;
	string Name;
	string PhoneNumber;
	double AccountBalance;
	bool MarkForDelete = false;
};
struct stUserData
{
	string UserName;
	string Password;
	int Permissions;
	bool MarkForDelete = false;
};
stUserData CurrentUser;
void Login();
void ShowNotAllAcessMessage()
{
	cout << "==================================\n";
	cout << "Access Denied,\n";
	cout << "You dont Have Permission To Do This,\n";
	cout << "Please Contact Your Admine.\n";
	cout << "==================================\n" << endl;
}
bool CheckAccessPermission(enPermissions Permission)
{
	if (CurrentUser.Permissions == enPermissions::PAll)
		return true;

	if ((Permission & CurrentUser.Permissions) == Permission)
		return true;

	return false;
	
}
void ClearInputBuffer()
{
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
void ResetScreen()
{
	system("cls");
	system("color 0F");
}
void Pause()
{
	system("pause>0");
}
vector<string> Split(string str, string delim)
{
	short pos;
	string Sword;
	vector<string> Vstr;
	while (((pos = (str.find(delim))) != string::npos))
	{
		Sword = str.substr(0, pos);

		if (Sword != "")
		{
			Vstr.push_back(Sword);
		}

		str.erase(0, pos + delim.length());
	}
	if (str != "")
	{
		Vstr.push_back(str);
	}
	return Vstr;
}
stClientData ReadClientDataToUpdata(string AccountNumber)
{
	stClientData Client;

	Client.AccountNumber = AccountNumber;

	cout << "Enter Your PineCode :\n";
	getline(cin >> ws, Client.PineCode);

	cout << "Enter Your Name :\n";
	getline(cin, Client.Name);

	cout << "Enter Your Phone Number :\n";
	getline(cin, Client.PhoneNumber);

	cout << "Enter Your Account Balance :\n";
	cin >> Client.AccountBalance;

	return Client;
}
void PrintAddClientScreenLogo()
{
	cout << "==================================\n";
	cout << "     Add New Clients Screen\n";
	cout << "==================================\n" << endl;
}
void PrintAddUserScreenLogo()
{
	cout << "==================================\n";
	cout << "     Add New Users Screen\n";
	cout << "==================================\n" << endl;
}
void PrintWithdrawScreen()
{
	cout << "==================================\n";
	cout << "     \tWithdraw Screen\n";
	cout << "==================================\n" << endl;
}
void PrintLoginScreen()
{
	cout << "==================================\n";
	cout << "\t   Login Screen\n";
	cout << "==================================\n" << endl;
}
void ShowTransactionsMenuScreen()
{
	cout << "==================================\n";
	cout << "    \tTransactions Screen\n";
	cout << "==================================" << endl;

	cout << "\t[1] Deposit.\n";
	cout << "\t[2] Withdraw.\n";
	cout << "\t[3] Total Balance.\n";
	cout << "\t[4] Main Mune." << endl;

	cout << "==================================\n";

}
void ShowManageMenuScreen()
{
	cout << "==================================\n";
	cout << "    Manage Users Menu Screen\n";
	cout << "==================================" << endl;

	cout << "\t[1] List Users.\n";
	cout << "\t[2] Add New User.\n";
	cout << "\t[3] Delete User.\n";
	cout << "\t[4] Update User.\n";
	cout << "\t[5] Find User.\n";
	cout << "\t[6] Main Menu." << endl;
	cout << "==================================\n";

}
bool IsInsideVector(string AccountNumber, vector<stClientData> VClients)
{

	for (stClientData& C : VClients)
	{
		if (C.AccountNumber == AccountNumber)
		{
			return true;
		}
	}
	return false;
}
int ReadPermissions()
{
	stUserData User;
	char Answer = 'n';
	short Permissions = 0;

	cout << "\nDo You Want To Give Full Access y/n ? :\n";
	cin >> Answer;

	if (toupper(Answer) == 'Y')
		return -1;

	cout << "\nDo You Want To Give Access To : \n\n";

	cout << "Show Client List y/n ? ";
	cin >> Answer;
	if (toupper(Answer) == 'Y')
		Permissions += enPermissions::PView;

	cout << "\nAdd New Client y/n ? ";
	cin >> Answer;
	if (toupper(Answer) == 'Y')
		Permissions += enPermissions::PAdd;

	cout << "\nDelete Client y/n ? ";
	cin >> Answer;
	if (toupper(Answer) == 'Y')
		Permissions += enPermissions::PDelete;

	cout << "\nUpdate Client y/n ? ";
	cin >> Answer;
	if (toupper(Answer) == 'Y')
		Permissions += enPermissions::PUpdate;

	cout << "\nFind Client y/n ? ";
	cin >> Answer;
	if (toupper(Answer) == 'Y')
		Permissions += enPermissions::PFind;

	cout << "\nTransactions y/n ? ";
	cin >> Answer;
	if (toupper(Answer) == 'Y')
		Permissions += enPermissions::PTransactions;

	cout << "\nManage Client y/n ? ";
	cin >> Answer;
	if (toupper(Answer) == 'Y')
		Permissions += enPermissions::PManageUsers;

	return Permissions;

}
stUserData ReadUserDataToUpdate(stUserData User)
{
	cout << "Enter Password :\n";
	getline(cin >> ws, User.Password);

	User.Permissions = ReadPermissions();

	return User;
}
void PrintFindClientScreenLogo()
{
	cout << "==================================\n";
	cout << "     Find Client Screen\n";
	cout << "==================================\n" << endl;
}
void PrintFindUserScreenLogo()
{
	cout << "==================================\n";
	cout << "     Find User Screen\n";
	cout << "==================================\n" << endl;
}
void PrintDepositScreen()
{
	cout << "==================================\n";
	cout << "     \tDeposit Screen\n";
	cout << "==================================\n" << endl;
}
void PrintDeleteClientScreenLogo()
{
	cout << "==================================\n";
	cout << "     Delete Client Screen\n";
	cout << "==================================\n" << endl;
}
void PrintDeleteUserScreenLogo()
{
	cout << "==================================\n";
	cout << "     Delete User Screen\n";
	cout << "==================================\n" << endl;
}
void PrintUpdataClientScreenLogo()
{
	cout << "==================================\n";
	cout << "     Updata Client Info Screen\n";
	cout << "==================================\n" << endl;
}
void PrintUpdataUserScreenLogo()
{
	cout << "==================================\n";
	cout << "     Updata User Info Screen\n";
	cout << "==================================\n" << endl;
}
stUserData ConvertUsresLineToRecord(string Line, string Delim = "#//#")
{
	stUserData User;
	vector<string>Vstring;
	Vstring = Split(Line, Delim);

	User.UserName = Vstring[0];
	User.Password = Vstring[1];
	User.Permissions = stoi(Vstring[2]);

	return  User;
}
vector<stUserData> LoadUsersDataFromFile(string fileName)
{
	fstream MyFile;
	MyFile.open(fileName, ios::in);
	vector<stUserData> VUsers;

	if (MyFile.is_open())
	{
		string Line;
		stUserData User;
		while (getline(MyFile, Line))
		{
			User = ConvertUsresLineToRecord(Line);
			VUsers.push_back(User);
		}

		MyFile.close();
	}
	return VUsers;
}
string ConvertClientDataToLine(stClientData Client, string Delim = "#//#")
{
	string str;
	str += Client.AccountNumber + Delim;
	str += Client.PineCode + Delim;
	str += Client.Name + Delim;
	str += Client.PhoneNumber + Delim;
	str += to_string(Client.AccountBalance);

	return str;
}
string ConvertUserDataToLine(stUserData User, string Delim = "#//#")
{
	string str;
	str += User.UserName + Delim;
	str += User.Password + Delim;
	str += to_string(User.Permissions);

	return str;
}
bool FindClientByAccountNumber(string AccountNumber, stClientData& Client, vector<stClientData> VClients)
{

	for (stClientData& C : VClients)
	{
		if (C.AccountNumber == AccountNumber)
		{
			Client = C;
			return true;
		}
	}
	return false;
}
bool FindUserByUserNameAndPassword(string UserName, string Password,stUserData& User)
{
	vector<stUserData> VUsers = LoadUsersDataFromFile(UsersFileName);

	for (stUserData& U : VUsers)
	{
		if (U.UserName == UserName && U.Password == Password)
		{
			User = U;
			return true;
		}
	}
	return false;
}
bool FindUserByUserName(stUserData& User, vector<stUserData> VUsers)
{

	for (stUserData& U : VUsers)
	{
		if (U.UserName == User.UserName)
		{
			User = U;
			return true;
		}
	}
	return false;
}
stClientData ConvertLineToRecord(string Line, string Delim = "#//#")
{
	stClientData Client;
	vector<string>Vstring;
	Vstring = Split(Line, Delim);

	Client.AccountNumber = Vstring[0];
	Client.PineCode = Vstring[1];
	Client.Name = Vstring[2];
	Client.PhoneNumber = Vstring[3];
	Client.AccountBalance = stod(Vstring[4]);

	return  Client;
}
vector<stClientData> LoadClientsDataFromFile(string fileName)
{
	fstream MyFile;
	MyFile.open(fileName, ios::in);
	vector<stClientData> VClients;

	if (MyFile.is_open())
	{
		string Line;
		stClientData Client;
		while (getline(MyFile, Line))
		{
			Client = ConvertLineToRecord(Line);
			VClients.push_back(Client);
		}

		MyFile.close();
	}
	return VClients;
}
bool IsUserInsideVector(string UserName, vector<stUserData> VUsers)
{
	for (stUserData& U : VUsers)
	{
		if (U.UserName == UserName)
		{
			return true;
		}
	}
	return false;
}
stClientData ReadClientData(vector<stClientData> VClients)
{
	stClientData Client;

	cout << "Enter Your AccountNumber :\n";
	getline(cin >> ws, Client.AccountNumber);

	while (IsInsideVector(Client.AccountNumber, VClients))
	{
		cout << "Account Number is Inside Vector Plsease Enter Another Account Number :\n";

		getline(cin >> ws, Client.AccountNumber);
	}

	cout << "Enter Your PineCode :\n";
	getline(cin, Client.PineCode);

	cout << "Enter Your Name :\n";
	getline(cin, Client.Name);

	cout << "Enter Your Phone Number :\n";
	getline(cin, Client.PhoneNumber);

	cout << "Enter Your Account Balance :\n";
	cin >> Client.AccountBalance;

	return Client;
}
stUserData ReadUserData(vector<stUserData> VUsers)
{
	stUserData User;
	char FullAccess = 'n';

	cout << "Enter UserName :\n";
	getline(cin >> ws, User.UserName);

	while (IsUserInsideVector(User.UserName, VUsers))
	{
		
		cout << "\nUserName is Inside Vector Plsease Enter Another UserName :\n";

		getline(cin >> ws, User.UserName);
	}

	cout << "\nEnter Password :\n";
	getline(cin, User.Password);

		User.Permissions = ReadPermissions();

	return User;
}
void AddClientDataToFile(string FileName, string stDataLine)
{
	fstream Myfile;

	Myfile.open(FileName, ios::out | ios::app);

	if (Myfile.is_open())
	{
		Myfile << stDataLine << endl;

		Myfile.close();
	}

}
void AddNewClient(vector<stClientData>& VClients)
{
	stClientData Client;
	Client = ReadClientData(VClients);
	AddClientDataToFile(ClientFileName, ConvertClientDataToLine(Client, "#//#"));

	VClients = LoadClientsDataFromFile(ClientFileName);

}
void AddClients(vector<stClientData> VClients)
{
	char Again = 'y';
	do
	{
		ResetScreen();
		PrintAddClientScreenLogo();
		cout << "Please Enter Client Data\n\n";

		AddNewClient(VClients);

		cout << "Client Add Successfully, do you want to add more clients?\n";
		cin >> Again;
	} while (toupper(Again) == 'Y');

	ClearInputBuffer();
}
void HandleAddClientsScreen(vector<stClientData> VClients)
{
	if (!CheckAccessPermission(enPermissions::PAdd))
	{
		ResetScreen();
		ShowNotAllAcessMessage();
		return;
	}

	AddClients(VClients);
}
void AddUsertDataToFile(string FileName, string stDataLine)
{
	fstream Myfile;

	Myfile.open(FileName, ios::out | ios::app);

	if (Myfile.is_open())
	{
		Myfile << stDataLine << endl;

		Myfile.close();
	}

}
void AddNewUser(vector<stUserData>& VUsers)
{
	stUserData User;
	User = ReadUserData(VUsers);
	AddUsertDataToFile(UsersFileName, ConvertUserDataToLine(User, "#//#"));

	VUsers = LoadUsersDataFromFile(UsersFileName);

}
void AddUsers(vector<stUserData>& VUsers)
{
	char Again = 'y';
	do
	{
		ResetScreen();
		PrintAddUserScreenLogo();
		cout << "Please Enter User Data\n\n";

		AddNewUser(VUsers);

		cout << "\nUser Add Successfully, do you want to add more Users y/n ?";
		cin >> Again;
	} while (toupper(Again) == 'Y');

	ClearInputBuffer();
}
void HandleAddUsersScreen(vector<stUserData>& VUsers)
{
	AddUsers(VUsers);
}
void ShowTheMainMenuScreen()
{
	cout << "==================================\n";
	cout << "\tMain Menu Screen\n";
	cout << "==================================\n";

	cout << "\t[1] Show Clients List.\n";
	cout << "\t[2] Add New Client.\n";
	cout << "\t[3] Delete Client.\n";
	cout << "\t[4] Update Client Info.\n";
	cout << "\t[5] Find Client.\n";
	cout << "\t[6] Transactions.\n";
	cout << "\t[7] Manage Users.\n";
	cout << "\t[8] Logout." << endl;

	cout << "==================================\n";

}
short ReadUserChoice()
{
	short Userchoice;
	cout << "Choice What Do You Want To Do ? ";
	cin >> Userchoice;

	return Userchoice;
}
void PrintTheMainLogo(short NumberOfClients)
{

	cout << right << setw(44) << "Client List (" << NumberOfClients << ") Client(s).\n";
	cout << "------------------------------------------------------------------------------------------" << endl;
	cout << "|" << left << setw(16) << " AccountNumber";
	cout << "|" << left << setw(10) << " PineCode";
	cout << "|" << left << setw(28) << " Name";
	cout << "|" << left << setw(15) << " PhoneNumber";
	cout << "|" << left << setw(9) << " AccountBalance";
	cout << "|" << endl;
	cout << "------------------------------------------------------------------------------------------" << endl;

}
void PrintTheMainLogoForViewUsers(short NumberOfClients)
{
	cout << right << setw(44) << "Users List (" << NumberOfClients << ") User(s).\n";
	cout << "------------------------------------------------------------------------------------------" << endl;
	cout << "| " << left << setw(25) << "UserName";
	cout << "| " << left << setw(19) << "Password";
	cout << "| " << left << setw(28) << "Permissions" << endl;
	cout << "------------------------------------------------------------------------------------------" << endl;

}
void PrintTheMainLogoForTotalBalanceScreen(short NumberOfClients)
{

	cout << right << setw(44) << "Client List (" << NumberOfClients << ") Client(s).\n";
	cout << "------------------------------------------------------------------------------------------" << endl;
	cout << "|" << left << setw(29) << " AccountNumber";
	cout << "|" << left << setw(29) << " PhoneNumber";
	cout << "|" << left << setw(28) << " AccountBalance";
	cout << "|" << endl;
	cout << "------------------------------------------------------------------------------------------" << endl;

}
void PrintTheMainClientDataForTotalBalanceScreen(stClientData Client)
{
	cout << "|" << left << setw(29) << Client.AccountNumber;
	cout << "|" << left << setw(29) << Client.Name;
	cout << "|" << left << setw(28) << Client.AccountBalance;
	cout << "|" << endl;

}
void PrintTheMainClientData(stClientData Client)
{
	cout << "|" << left << setw(16) << Client.AccountNumber;
	cout << "|" << left << setw(10) << Client.PineCode;
	cout << "|" << left << setw(28) << Client.Name;
	cout << "|" << left << setw(15) << Client.PhoneNumber;
	cout << "|" << left << setw(15) << Client.AccountBalance;
	cout << "|" << endl;

}
void PrintTheMainUserData(stUserData User)
{
	cout << "| " << left << setw(25) << User.UserName;
	cout << "| " << left << setw(19) << User.Password;
	cout << "| " << left << setw(28) << User.Permissions << endl;

}
void SaveClientDataToFile(string FileName, vector<stClientData> VClients)
{
	fstream Myfile;

	Myfile.open(FileName, ios::out);

	string DataLine;

	if (Myfile.is_open())
	{
		for (stClientData C : VClients)
		{
			if (C.MarkForDelete == false)
			{
				DataLine = ConvertClientDataToLine(C);
				Myfile << DataLine << endl;
			}
		}
		Myfile.close();
	}

}
void SaveUsersDataToFile(string FileName, vector<stUserData> VUsers)
{
	fstream Myfile;

	Myfile.open(FileName, ios::out);

	string DataLine;

	if (Myfile.is_open())
	{
		for (stUserData C : VUsers)
		{
			if (C.MarkForDelete == false)
			{
				DataLine = ConvertUserDataToLine(C);
				Myfile << DataLine << endl;
			}
		}
		Myfile.close();
	}

}
string ReadAccountNumber()
{
	string AccountNumber;
	cout << "Please Enter Account Number : \n";
	getline(cin >> ws, AccountNumber);

	return AccountNumber;
}
string ReadUserName()
{
	string UserName;
	cout << "Please Enter UserName : \n";
	getline(cin >> ws, UserName);

	return UserName;
}
void PrintClientData(stClientData Client)
{

	cout << "Account Number  : " << Client.AccountNumber << endl;
	cout << "Pine Code       : " << Client.PineCode << endl;
	cout << "Name            : " << Client.Name << endl;
	cout << "Phone Number    : " << Client.PhoneNumber << endl;
	cout << "Account Balance : " << Client.AccountBalance << endl;
}
void PrintUserData(stUserData User)
{

	cout << "UserName    : " << User.UserName << endl;
	cout << "Password    : " << User.Password << endl;
	cout << "Permissions : " << User.Permissions << endl;
}
bool MarkClientForDeleteByAccountNumber(vector<stClientData>& VClients, string AccountNumber)
{
	for (stClientData& C : VClients)
	{
		if (C.AccountNumber == AccountNumber)
		{
			C.MarkForDelete = true;
			return true;
		}
	}
	return false;
}
bool MarkUserForDeleteByUserName(vector<stUserData>& VUsers, string UserName)
{
	for (stUserData& U : VUsers)
	{
		if (U.UserName == UserName)
		{
			U.MarkForDelete = true;
			return true;
		}
	}
	return false;
}
void DeleteClientDataByAccountNumber(vector<stClientData>& VClients, string AccountNumber)
{
	char Answer = 'n';
	stClientData Client;

	if (FindClientByAccountNumber(AccountNumber, Client, VClients))
	{
		cout << endl;
		PrintClientData(Client);
		cout << endl;

		cout << "Do You Want To Remove This Data ? \n";
		cin >> Answer;

		cout << endl;

		if (tolower(Answer) == 'y')
		{
			MarkClientForDeleteByAccountNumber(VClients, AccountNumber);
			SaveClientDataToFile(ClientFileName, VClients);

			VClients = LoadClientsDataFromFile(ClientFileName);

			cout << "Delete Client Successful\n";
		}
		else
		{
			cout << "Delete Client Not Successful\n";
			ClearInputBuffer();
		}
	}
	else
	{
		cout << "\nClient With Account Number (" << AccountNumber << ") Is Not Found!" << endl;
	}

}
void DeleteUserDataByUserName(vector<stUserData>& VUsers, string UserName)
{
	char Answer = 'n';
	stUserData User;
	User.UserName = UserName;

	if (FindUserByUserName(User, VUsers))
	{
		cout << endl;
		PrintUserData(User);
		cout << endl;

		cout << "Do You Want To Remove This Data ? \n";
		cin >> Answer;

		cout << endl;

		if (tolower(Answer) == 'y')
		{
			MarkUserForDeleteByUserName(VUsers,User.UserName);
			SaveUsersDataToFile(UsersFileName, VUsers);

			VUsers = LoadUsersDataFromFile(UsersFileName);

			cout << "Delete User Successful\n";
		}
		else
		{
			cout << "Delete User Not Successful\n";
			ClearInputBuffer();
		}
	}
	else
	{
		cout << "\nUser With Account Number (" << UserName << ") Is Not Found!" << endl;
	}

}
void UpdataClientDataByAccountNumber(vector<stClientData>& VClients, string AccountNumber)
{
	char Answer = 'n';
	stClientData Client;

	if (FindClientByAccountNumber(AccountNumber, Client, VClients))
	{
		cout << endl;
		PrintClientData(Client);
		cout << endl;

		cout << "Do You Want To Updata This Data ? \n";
		cin >> Answer;

		if (tolower(Answer) == 'y')
		{
			for (stClientData& C : VClients)
			{
				if (C.AccountNumber == AccountNumber)
				{
					C = ReadClientDataToUpdata(AccountNumber);
				}
			}
			SaveClientDataToFile(ClientFileName, VClients);
			cout << "\nUpdate Client Successful\n\n";
		}
		else
		{
			cout << "\nUpdate Client Not Successful\n\n";
			ClearInputBuffer();
		}
	}
	else
	{
		cout << "\nClient With Account Number (" << AccountNumber << ")Is not found!\n\n";
	}

}
void UpdataUserDataByUserName(vector<stUserData>& VUsers, string UserName)
{
	char Answer = 'n';
	stUserData User;
	User.UserName = UserName;

	if (FindUserByUserName(User, VUsers))
	{
		cout << endl;
		PrintUserData(User);
		cout << endl;

		cout << "Do You Want To Updata This Data ? \n";
		cin >> Answer;

		if (tolower(Answer) == 'y')
		{
			for (stUserData& U : VUsers)
			{
				if (U.UserName == UserName)
				{
					U = ReadUserDataToUpdate(User);
				}
			}
			SaveUsersDataToFile(UsersFileName, VUsers);
			cout << "\nUpdate User Successful\n\n";
		}
		else
		{
			cout << "\nUpdate User Not Successful\n\n";
			ClearInputBuffer();
		}
	}
	else
	{
		cout << "\nUser With UserName (" << UserName << ")Is not found!\n\n";
	}

}
void HandleUpdataClientDataScreen(vector<stClientData>& Clients)
{
	if (!CheckAccessPermission(enPermissions::PUpdate))
	{
		ResetScreen();
		ShowNotAllAcessMessage();
		return;
	}

	ResetScreen();
	PrintUpdataClientScreenLogo();

	string AccountNumber = ReadAccountNumber();

	UpdataClientDataByAccountNumber(Clients, AccountNumber);

}
void HandleUpdataUserDataScreen(vector<stUserData>& VUsers)
{
	ResetScreen();
	PrintUpdataUserScreenLogo();

	string UserName = ReadUserName();

	UpdataUserDataByUserName(VUsers, UserName);
}
void HandleDeleteScreen(vector<stClientData>& Clients)
{
	if (!CheckAccessPermission(enPermissions::PDelete))
	{
		ResetScreen();
		ShowNotAllAcessMessage();
		return;
	}

	ResetScreen();
	PrintDeleteClientScreenLogo();

	string AccountNumber = ReadAccountNumber();

	DeleteClientDataByAccountNumber(Clients,AccountNumber);
}
void HandleDeleteScreenForUsers(vector<stUserData>& VUsers)
{
		ResetScreen();
		PrintDeleteUserScreenLogo();

		string UserName = ReadUserName();

		DeleteUserDataByUserName(VUsers, UserName);

}
void HandleViewScreen(vector<stClientData> Clients)
{
	if (!CheckAccessPermission(enPermissions::PView))
	{
		ResetScreen();
		ShowNotAllAcessMessage();
		return;
	}
		ResetScreen();
		PrintTheMainLogo(Clients.size());

		for (stClientData& Client : Clients)
		{
			PrintTheMainClientData(Client);
		}
		cout << "------------------------------------------------------------------------------------------" << endl;	
}
void HandleViewScreenForUsers(vector<stUserData> VUsers)
{
		ResetScreen();
		PrintTheMainLogoForViewUsers(VUsers.size());

		for (stUserData& User : VUsers)
		{
			PrintTheMainUserData(User);
		}
		cout << "------------------------------------------------------------------------------------------" << endl;
}
void HandleFindClientScreen(vector<stClientData> VClients)
{
	stClientData Client;

	if (!CheckAccessPermission(enPermissions::PFind))
	{
		ResetScreen();
		ShowNotAllAcessMessage();
		return;
	}

	ResetScreen();
	PrintFindClientScreenLogo();
	string AccountNumber = ReadAccountNumber();

	if (FindClientByAccountNumber(AccountNumber, Client,VClients))
	{
		cout << endl;
		PrintClientData(Client);
	}
	else
	{
		cout << "\nClient With Account Number (" << AccountNumber << ") Not Found!\n\n";
	}
}
void HandleFindUserScreen(vector<stUserData> VUsers)
{
	stUserData User;

	ResetScreen();
	PrintFindUserScreenLogo();
	string UserName = ReadUserName();
	User.UserName = UserName;

	if (FindUserByUserName(User, VUsers))
	{
		cout << endl;
		PrintUserData(User);
	}
	else
	{
		cout << "\nUser With Account Number (" << UserName << ") Not Found!\n\n";
	}

}
void PerformDeposit(vector<stClientData>& VClients)
{
	string AccountNumber;
	stClientData Client;
	double Amount;
	char Perform;

	cout << "Enter Your AccountNumber :\n";
	getline(cin >> ws, AccountNumber);

	while (!(FindClientByAccountNumber(AccountNumber,Client, VClients)))
	{
		cout << "\nAccount Number Is Not Exit\n\nPlsease Enter Account Number :\n";

		getline(cin >> ws, AccountNumber);
	}

	cout << endl;
	PrintClientData(Client);
	cout << endl;

	cout << "Please Enter Deposit Amount ?" << endl;
	cin >> Amount;

	cout << "Are You Sure You Want Perform This Transaction ? y/n" << endl;
	cin >> Perform;

	if (tolower(Perform) == 'y')
	{
		if (Amount > 0)
		{
			for (stClientData& C : VClients)
			{
				if (C.AccountNumber == AccountNumber)
				{
					C.AccountBalance = Client.AccountBalance + Amount;
				}

			}

		}

		cout << "Depstion is Successfull\n";

		SaveClientDataToFile(ClientFileName, VClients);
	}
	else
	{
		cout << "\nDepstion is not Successfull\n";
	}

}
void PerformWithdraw(vector<stClientData>& VClients)
{
	string AccountNumber;
	stClientData Client;
	double Amount;
	char Perform;
	cout << "Enter Your AccountNumber :\n";
	getline(cin >> ws, AccountNumber);

	while (!(FindClientByAccountNumber(AccountNumber, Client, VClients)))
	{
		cout << "\nAccount Number Is Not Exit\n\nPlsease Enter Account Number :\n";

		getline(cin >> ws, AccountNumber);
	}

	cout << endl;

	PrintClientData(Client);

	cout << "\nPlease Enter Withdraw Amount ?" << endl;
	cin >> Amount;

	while (Amount > Client.AccountBalance)
	{
		cout << "Amount Exceeds the balance, you can withdraw up to :" <<  Client.AccountBalance;
		cout << "\nPlease Enter Another Amount?\n";
		cin >> Amount;	
	}

	cout << "Are You Sure You Want Perform This Transaction ? y/n" << endl;
	cin >> Perform;

	if (tolower(Perform) == 'y')
	{
		if (Amount > 0)
		{
			for (stClientData& C : VClients)
			{
				if (C.AccountNumber == AccountNumber)
				{
					C.AccountBalance = Client.AccountBalance - Amount;
				}

			}
		}
		cout << "\nWithdraw is Successfull\n";

		SaveClientDataToFile(ClientFileName, VClients);
	}
	else
	{
		cout << "\nWithdraw is not Successfull\n";
		ClearInputBuffer();
	}

}
void HandleDepositScreen(vector<stClientData>& Clients)
{
	ResetScreen();
	PrintDepositScreen();
	PerformDeposit(Clients);
}
void HanldeWithdrawScreen(vector<stClientData>& Clients)
{
	ResetScreen();
	PrintWithdrawScreen();
	PerformWithdraw(Clients);
}
double GetTotalBalanceOfClients(vector<stClientData>& Clients)
{
	double TotalBalance = 0;

	for (stClientData& C : Clients)
	{
		TotalBalance += C.AccountBalance;
	}
	return TotalBalance;
}
void HandleTotalBalanceScreen(vector<stClientData>& Clients)
{
	ResetScreen();
	PrintTheMainLogoForTotalBalanceScreen(Clients.size());
	for (stClientData& Client : Clients)
	{
		PrintTheMainClientDataForTotalBalanceScreen(Client);
	}
	cout << "------------------------------------------------------------------------------------------" << endl;
	cout << "\t\t\t\t TotalBalance = " << GetTotalBalanceOfClients(Clients) << endl;
}
void HandleTransactionChoice(enTransactions UserChoice, bool* ptr, vector<stClientData>& Clients)
{
	switch (UserChoice)
	{
	case enTransactions::Deposit:
		HandleDepositScreen(Clients);
		break;
	case enTransactions::Withdraw:
		HanldeWithdrawScreen(Clients);
		break;
	case enTransactions::TotalBalance:
		HandleTotalBalanceScreen(Clients);
		break;
	case enTransactions::MainMune:
		*ptr = false;
		break;
	default:
		cout << "\nYou Entered a Number Out Of The Range!\n";
		break;
	}
}
void HandleManageChoice(enManageUsers UserChoice, bool* ptr)
{
	vector<stUserData> VUsers = LoadUsersDataFromFile(UsersFileName);

	switch (UserChoice)
	{
	case enManageUsers::List:
		HandleViewScreenForUsers(VUsers);
		break;
	case enManageUsers::AddUser:
		HandleAddUsersScreen(VUsers);
		break;
	case enManageUsers::DeleteUser:
		HandleDeleteScreenForUsers(VUsers);
		break;
	case enManageUsers::UpdateUser:
		HandleUpdataUserDataScreen(VUsers);
		break;
	case enManageUsers::FindUser:
		HandleFindUserScreen(VUsers);
		break;
	case enManageUsers::MainMuneFromManage:
		*ptr = false;
		break;
	default:
		cout << "\nYou Entered a Number Out Of The Range!\n";
		ClearInputBuffer();
		break;
	}
}
void HandleTransactionsScreen(vector<stClientData>& Clients)
{
	if (!CheckAccessPermission(enPermissions::PTransactions))
	{
		ResetScreen();
		ShowNotAllAcessMessage();
		return;
	}

	bool Again = true;
	enTransactions UserChoice;

	do
	{
		ResetScreen();
		ShowTransactionsMenuScreen();
		UserChoice = (enTransactions)ReadUserChoice();
		HandleTransactionChoice(UserChoice, &Again,Clients);
		if (Again)
		{
			cout << "\nPress any key to go back to the Transaction menu...";
			Pause();
		}
	} while (Again);

}
void HandleManageUsersScreen()
{
	if (!CheckAccessPermission(enPermissions::PManageUsers))
	{
		ResetScreen();
		ShowNotAllAcessMessage();
		return;
	}
	bool Again = true;
	enManageUsers UserChoice;
		
	do
	{
		ResetScreen();
		ShowManageMenuScreen();
		UserChoice = (enManageUsers)ReadUserChoice();
		HandleManageChoice(UserChoice, &Again);
		if (Again)
		{
			cout << "\nPress any key to go back to the Manage menu...";
			Pause();
		}
	} while (Again);
	
}
void HandleUserChoice(enUserChoices UserChoice,bool* ptr)
{
	vector<stClientData> Clients = LoadClientsDataFromFile(ClientFileName);

	if (UserChoice == enUserChoices::Logout)
	{
		*ptr = false;
		return;
	}

	switch (UserChoice)
	{
	case enUserChoices::View:
		HandleViewScreen(Clients);
		break;
	case enUserChoices::Add:
		HandleAddClientsScreen(Clients);
		break;
	case enUserChoices::Delete:
		HandleDeleteScreen(Clients);
		break;
	case enUserChoices::Update:
		HandleUpdataClientDataScreen(Clients);
		break;
	case enUserChoices::Find:
		HandleFindClientScreen(Clients);
		break;
	case enUserChoices::Transactions:
		HandleTransactionsScreen(Clients);
		break;
	case enUserChoices::ManageUsers:
		HandleManageUsersScreen();
		break;
	default:
		cout << "\nYou Entered a Number Out Of The Range!\n";
		ClearInputBuffer();
		break;
	}
}
void StartUsingBankSystem()
{
	bool Again = true;
	enUserChoices UserChoice;
	do
	{
		ResetScreen();
		ShowTheMainMenuScreen();
		UserChoice = (enUserChoices)ReadUserChoice();
		HandleUserChoice(UserChoice, &Again);
		if (Again)
		{
		cout << "\nPress any key to go back to the main menu...";
		Pause();
		}
	} while (Again);

	Login();
}
bool LoadUserInfo(string UserName, string Password)
{
	if (FindUserByUserNameAndPassword(UserName, Password, CurrentUser))
		return true;

	return false;
}
void Login()
{
	string UserName, Password;

	bool LoginFaild = false;
	do
	{

		ResetScreen();
		PrintLoginScreen();

		if (LoginFaild)
			cout << "Invaild Username/Password\n\n";

		cout << "Enter UserName?\n";
		cin >> UserName;

		cout << "\nEnter Password?\n";
		cin >> Password;

		LoginFaild = !LoadUserInfo(UserName, Password);
	} while (LoginFaild);

	StartUsingBankSystem();

}
int main()
{
	Login();
	
	return 0;
}