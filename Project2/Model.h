#pragma once
#include <iostream>
#include "sqlite3.h"
#include <vector>
#include <list>
using namespace std;
class Model
{
public:
	
	sqlite3 *db;
	char *zErrMs;
	int rc;
	const char *szSQL;
	const char *pzTest;
	sqlite3_stmt *stmt;
	list <string> answer;
public:
	void Open();
	int SQL_login(sqlite3 *db, char *username, char *password);
	void SQL_Reg(sqlite3 *db, char *username, char *password,char *gender, char *birthday, char *fullname,char *address);
	void SQL_Mess_send(sqlite3 *db, int id);
	void SQL_Mess_receive(sqlite3 *db, int id);
	int Seach_fr(char *frien);
	void ShowMessDetail(sqlite3 *db, int id1, int id2);
	bool CheckFriend(sqlite3 *db, int id1, int id2);
	bool CheckBlock(sqlite3 *db, int id1, int id2);
	void WriteToFriend(sqlite3 *db, int id1, int id2);
	void ShowFriend(sqlite3 *db, int id1);
	void BlockFriend(sqlite3 *db, int id1, int id2);
	void WriteToMess(sqlite3 *db, int id1, int id2, char *mes, char *tim,int tt, int sec);
	void update_tt(sqlite3 *db, int id1, int id2);
	int Select_all(sqlite3 *db,char *us);
	int Select_mask(sqlite3 *db);
	void Insert_maskuser(sqlite3 *db, int id1,char *,char *, char *);
	void Update_fr(sqlite3 *db, char *name, char *gender, char *address, int id);
	void Detail_fr(sqlite3 *db,int id2);
	int ShowaaFriend(sqlite3 *db, int id1, int n);
};
