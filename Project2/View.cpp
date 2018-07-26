#include "View.h"
#include "Controller.h"
#include "Model.h"
#include <iostream>
#include <thread>
#include <Windows.h>
using namespace std;
Controller controller1;
int choice_v = 0;
Model conn1;
HANDLE Thread1,Thread2;
DWORD ThreadId;
 DWORD WINAPI ThreadProc1(LPVOID param)
{
	
	conn1.SQL_Reg(conn1.db,controller1.username,controller1.password,controller1.sex,controller1.birthday,controller1.fullname,controller1.address);
	return 1;
}
 DWORD WINAPI ThreadProc2(LPVOID param)
{
	conn1.Insert_maskuser(conn1.db,controller1.id_mask,controller1.fullname,controller1.sex,controller1.address);
	return 1;
}
void View::send_fr() {
	int chon;
	cout << "-------MENU ------\n"
                "1.SEND MESS TO FRIEND\n"
                "2.EXIT\n"
                "-----------------------\n";
	while (1)
	{
		cout << "==>Choose: ";
		cin >> chon;
		switch (chon) {
		case 1:
			controller1.Detail_Reply(controller1.id);
			cout << "-----------------------" << endl;
			break;
		case 2:
			return;
		}
	}
}
void  View::Ctrl_R() {
	int chon;
	while (1)
	{
		cout << "-------MENU------\n"
                "1.Reply Friend\n"
                "2.EXIT\n"
                "-----------------------\n";
		cout << "==>Choose: ";
		cin >> chon;
		switch (chon) {
		case 1:
			controller1.Reply(controller1.id);
			cout << "-----------------------" << endl;
			break;
		case 2:
			return;
		}
	}
}
void View::send() {
	int chon;
	while (1)
	{
		cout << "-------MENU------\n"
                "1.SEND MESS\n"
                "2.Ctrl L To SEND\n"
                "3.Exit\n"
                "-----------------------\n";
		cout << "==>Choose: ";
		cin >> chon;
		switch (chon) {
		case 1:
			controller1.SendMess(controller1.id);
			cout << "-----------------------" << endl;
			break;
		case 2:
			controller1.SendMess_ctr_l(controller1.id);
			cout << "-----------------------" << endl;
			break;
		case 3:
			return;
		}
	}
}
void View::showmess() {
	int chon;
	while (1)
	{
		cout << "-------MENU------\n"
                "1.SEND MESS\n"
                "2.RECEIVED MESSAGE\n"
                "3.EXIT\n"
                "-----------------------\n";
		cout << "==>Choose: ";
		cin >> chon;
		switch (chon) {
		case 1:
			controller1.ShowMess_send(controller1.id);
			cout << "-----------------------" << endl;
			break;
		case 2:
			controller1.ShowMess_rec(controller1.id);
			cout << "-----------------------" << endl;
			break;
		case 3:
			return;
		}
	}
}
void View::login() {
	int chon;

	while (1)
	{

		cout << "-------MENU ------\n"
                "1.Show Mess\n"
                "2.Detail Mess\n"
                "3.Send Mess\n"
                "4.Add Friend\n"
                "5.Show Friend\n"
                "6.Block Friend\n"
                "7.Update Friend\n"
                "8.Detail Friend\n"
                "9.Exit\n"
                "-----------------------\n";
		cout << "==>Choose: ";
		cin >> chon;
		switch (chon) {
			case 1:
				showmess();
				break;
			case 2:
				controller1.ShowMessDetail(controller1.id);
				if (controller1.Detail) {
					Ctrl_R();
				}
				break;
			case 3:
				send();
				break;
			case 4:
				controller1.AddFriend(controller1.id);
				break;
			case 5:
				controller1.ShowFriend_ctr_C(controller1.id);
				break;
			case 6:
				controller1.BlockFriend(controller1.id);
				break;
			case 7:
				controller1.Update_fr(controller1.id);
				break;
			case 8:
				controller1.Detail_fr(controller1.id);
				if (controller1.Detail) {
					send_fr();
				}
				break;
			case 9:
				break;
			default:
				printf("\r\n>> ERROR, Reselect..");
				system("pause");
		}
		if (chon == 9)
		{
			break;
		}
	}
}


void View::print_menu() {
	cout << "----MESSENGER APP-----\n";
	cout << "1. SIGN UP\n";
	cout << "2. LOGIN\n";
	cout << "3. LOGOUT\n";
	cout << "4. EXIT\n";
	cout << "\nChoose: ";
}

void View::choose_menu()
{
label1:
	print_menu();
	cin>>choice_v;
	thread t2;
	switch (choice_v)
	{
	case 1:
		
		controller1.SignUp();
		conn1.Open();
		if (conn1.Select_all(conn1.db,controller1.username)>0) {
		cout << "user exist" << endl;
		}
		else
		{
		controller1.id_mask = conn1.Select_mask(conn1.db) + 1;
		
		CreateThread(NULL,0,(LPTHREAD_START_ROUTINE) ThreadProc1,NULL,0,NULL);
		CreateThread(NULL,0,(LPTHREAD_START_ROUTINE) ThreadProc2,NULL,0,NULL);
		
		/*thread sql_re(&Model::SQL_Reg,,db1,,ref(username),ref(password),ref(sex),ref(birthday),ref(fullname),ref(address));
		sql_re.detach();*/
		/*thread insert_mask(&Model::Insert_maskuser,db1,id_mask,fullname,sex,address);
		
		insert_mask.detach();*/
		/*conn.SQL_Reg(conn.db, username, password, sex, birthday, fullname, address);
		int id_mask = conn.Select_mask(conn.db);
		conn.Insert_maskuser(conn.db, id_mask, fullname,sex, address);*/
		
		cout << "DONE" << endl;
		system("pause");
		}
		system("cls");
		goto label1;
			break;
	case 2:
		controller1.SignIn();
		
		if (controller1.check) {
				login();
			}
			break;

	case 3:
		controller1.SignOut();
			break;
	case 4:
	default:
		cout<<"Khong hop le\n";
		break;
	}
	
	
}
