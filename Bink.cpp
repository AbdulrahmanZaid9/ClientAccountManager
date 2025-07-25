#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

const string ClientFileName = "C:\\Users\\User\\Desktop\\MyProjects\\MyCV\\Projects_Course_5\\Projects_C_5\\Bink\\Clients.txt";

enum enUserChoices {View = 1, Add = 2, Delete = 3, Update = 4, Find = 5,Transactions = 6, Exit = 7};
enum enTransactions {Deposit = 1, Withdraw = 2, TotalBalance = 3, MainMune = 4};
struct stClientData
{
	string AccountNumber;
	string PineCode;
	string Name;
	string PhoneNumber;
	double AccountBalance;
	bool MarkForDelete = false;
};
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
void PrintWithdrawScreen()
{
	cout << "==================================\n";
	cout << "     \tWithdraw Screen\n";
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
void PrintFindClientScreenLogo()
{
	cout << "==================================\n";
	cout << "     Find Client Screen\n";
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
void PrintUpdataClientScreenLogo()
{
	cout << "==================================\n";
	cout << "     Updata Client Info Screen\n";
	cout << "==================================\n" << endl;
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
	AddClients(VClients);
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
	cout << "\t[7] Exit." << endl;

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
string ReadAccountNumber()
{
	string AccountNumber;
	cout << "Please Enter Account Number : \n";
	getline(cin >> ws, AccountNumber);

	return AccountNumber;
}
void PrintClientData(stClientData Client)
{

	cout << "Account Number  : " << Client.AccountNumber << endl;
	cout << "Pine Code       : " << Client.PineCode << endl;
	cout << "Name            : " << Client.Name << endl;
	cout << "Phone Number    : " << Client.PhoneNumber << endl;
	cout << "Account Balance : " << Client.AccountBalance << endl;
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
void HandleUpdataClientDataScreen(vector<stClientData>& Clients)
{
	ResetScreen();
	PrintUpdataClientScreenLogo();

	string AccountNumber = ReadAccountNumber();

	UpdataClientDataByAccountNumber(Clients, AccountNumber);
}
void HandleDeleteScreen(vector<stClientData>& Clients)
{
	ResetScreen();
	PrintDeleteClientScreenLogo();

	string AccountNumber = ReadAccountNumber();

	DeleteClientDataByAccountNumber(Clients,AccountNumber);
}
void HandleViewScreen(vector<stClientData> Clients)
{
	ResetScreen();
	PrintTheMainLogo(Clients.size());

	for (stClientData& Client : Clients)
	{
		PrintTheMainClientData(Client);
	}
	cout << "------------------------------------------------------------------------------------------" << endl;
}
void HandleFindClientScreen(vector<stClientData> VClients)
{
	stClientData Client;
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
void HandleTransactionsScreen(vector<stClientData>& Clients)
{
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
void HandleUserChoice(enUserChoices UserChoice,bool* ptr)
{
	vector<stClientData> Clients = LoadClientsDataFromFile(ClientFileName);

	if (UserChoice == enUserChoices::Exit)
	{
		*ptr = false;
		cout << "\nExit is Successful\n";
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
	default:
		cout << "\nYou Entered a Number Out Of The Range!\n";
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
}
int main()
{
	StartUsingBankSystem();
}