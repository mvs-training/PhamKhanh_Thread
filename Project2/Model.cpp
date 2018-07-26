#include "Model.h"
#include "View.h"
#include <iostream>
#include <windows.h>
#include <sstream>
#include <sqlite3.h>
#define _VARIADIC_MAX 10
using namespace std;

void Model::Open() {
	rc = sqlite3_open("tinnhan.db", &db);
	if (rc) {
		cout << "Can't connect database" << sqlite3_errmsg(db) << endl;
		exit(0);
	}else {}
}
int Model::SQL_login(sqlite3 *db, char *username, char *password) {
	int id = 0;
	szSQL = "SELECT * FROM  user WHERE username = ? and password = ? ";
	rc = sqlite3_prepare(db, szSQL, strlen(szSQL), &stmt, &pzTest);
	if (rc == SQLITE_OK) {
		// bind the value
		sqlite3_bind_text(stmt, 1, username, strlen(username), 0);
		sqlite3_bind_text(stmt, 2, password, strlen(password), 0);
		// commit
		while (sqlite3_step(stmt) == SQLITE_ROW) {
			stringstream str;
			str << sqlite3_column_text(stmt, 0);
			str >> id;
		}
		sqlite3_finalize(stmt);
	}
	/*else {
		cout << "SQL error: " << zErrMsg << endl;
		sqlite3_free(zErrMsg);
	}*/
	return id;
}
void Model::SQL_Reg(sqlite3 *db, char *username, char *password,char *gender, char *birthday, char *fullname,char *address) {
	szSQL = "insert into user (username, password,sex,birth,name,address) values (?,?,?,?,?,?)";
	rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);
	if (rc == SQLITE_OK) {
		sqlite3_bind_text(stmt, 1, username, strlen(username), 0);
		sqlite3_bind_text(stmt, 2, password, strlen(password), 0);
		sqlite3_bind_text(stmt, 3, gender,strlen(gender),0);
		sqlite3_bind_text(stmt, 4, birthday, strlen(birthday), 0);
		sqlite3_bind_text(stmt, 5, fullname, strlen(fullname), 0);
		sqlite3_bind_text(stmt, 6, address,strlen(address),0);
		sqlite3_step(stmt);
		sqlite3_finalize(stmt);
	}
	/*else {
		cout << "SQL error: " << zErrMsg << endl;
		sqlite3_free(zErrMsg);
	}*/
}
void Model::SQL_Mess_receive(sqlite3 *db, int zID) {
	if (!db)return;
	szSQL = "select message.content from message,user where user.id=message.idrec and user.id=?";
	rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);
	if (rc == SQLITE_OK) {
		sqlite3_bind_int(stmt, 1, zID);
		while (sqlite3_step(stmt) == SQLITE_ROW) {
			answer.push_back(string((const char *)sqlite3_column_text(stmt, 0)));
		}
		sqlite3_finalize(stmt);
		cout << "-----List Received-------\n";
		for (list<std::string>::const_iterator it = answer.begin(); it != answer.end(); it++)
			cout <<"-"<< *it << endl;
	}
	/*else {
		cout << "SQL error: " << zErrMsg << endl;
		sqlite3_free(zErrMsg);
	}*/
}
void Model::SQL_Mess_send(sqlite3 *db, int zID) {
	if (!db)return;
	szSQL = "select message.content from message,user where user.id=message.idsen and user.id=?";
	rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);
	if (rc == SQLITE_OK) {
		sqlite3_bind_int(stmt, 1, zID);
		while (sqlite3_step(stmt) == SQLITE_ROW) {
			answer.push_back(string((const char *)sqlite3_column_text(stmt, 0)));
		}
		sqlite3_finalize(stmt);
		cout << "-----LIST SEND-------\n";
		for (list<std::string>::const_iterator it = answer.begin(); it != answer.end(); it++)
			cout <<"-"<< *it << endl;
	}
	/*else {
		cout << "SQL error: " << zErrMsg << endl;
		sqlite3_free(zErrMsg);
	}*/
}
int Model::Seach_fr(char *frien) {
	int id2 = -1;
	szSQL = "SELECT id FROM user WHERE username = ?";
	rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);
	if (rc == SQLITE_OK) {
		sqlite3_bind_text(stmt, 1, frien, strlen(frien), 0);
		if (sqlite3_step(stmt) == SQLITE_ROW) {
			stringstream str;
			str << sqlite3_column_text(stmt, 0);
			str >> id2;
		}
		sqlite3_finalize(stmt);
	}
	/*else {
		cout << "SQL error: " << zErrMsg << endl;
		sqlite3_free(zErrMsg);
	}*/
	return id2;
}
void Model::ShowMessDetail(sqlite3 *db, int id1, int id2) {
	if (!db)return;
	cout << "--------Detail--------\n";
	szSQL = "SELECT * FROM message,user WHERE(idsen = ? OR idsen = ?) AND(idrec = ? OR idrec = ?) and user.id = message.idsen";
	rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);

	if (rc == SQLITE_OK) {
		// bind the value
		sqlite3_bind_int(stmt, 1, id1);
		sqlite3_bind_int(stmt, 2, id2);
		sqlite3_bind_int(stmt, 3, id1);
		sqlite3_bind_int(stmt, 4, id2);
		// commit
		while (sqlite3_step(stmt) == SQLITE_ROW) {
			cout << string((const char *)sqlite3_column_text(stmt, 7)) << ": " << endl;
			cout <<"Content:"<< string((const char *)sqlite3_column_text(stmt, 2)) << "\n ";
			cout <<"Time:"<< string((const char *)sqlite3_column_text(stmt, 3)) << endl;

		}
		sqlite3_finalize(stmt);
	}
	/*else {
		cout << "SQL error: " << zErrMsg << endl;
		sqlite3_free(zErrMsg);
	}*/
}
bool Model::CheckFriend(sqlite3 *db, int id1, int id2) {
	int isFriend = 0;
	szSQL = "SELECT * FROM friend WHERE ( id1 = ? AND id2 = ?) OR ( id1 = ? AND id2 = ?)";
	rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);
	if (rc == SQLITE_OK) {
		// bind the value
		sqlite3_bind_int(stmt, 1, id1);
		sqlite3_bind_int(stmt, 2, id2);
		sqlite3_bind_int(stmt, 3, id2);
		sqlite3_bind_int(stmt, 4, id1);
		// commit
		if (sqlite3_step(stmt) == SQLITE_ROW) {
			stringstream str;
			str << sqlite3_column_text(stmt, 0);
			str >> isFriend;
			if (isFriend != 0) isFriend = 1;
			else isFriend = 0;
			sqlite3_finalize(stmt);
		}
	}
	/*else {
		cout << "SQL error: " << zErrMsg << endl;
		sqlite3_free(zErrMsg);
	}*/
	return isFriend;
}
bool Model::CheckBlock(sqlite3 *db, int id1, int id2) {
	int isblock = 0;
	if (!db)return 0;
	szSQL = "SELECT isblock FROM friend WHERE (id1 = ? AND id2 = ?)";
	rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);
	if (rc == SQLITE_OK) {
		// bind the value
		sqlite3_bind_int(stmt, 1, id2);
		sqlite3_bind_int(stmt, 2, id1);
		// commit
		if (sqlite3_step(stmt) == SQLITE_ROW) {
			stringstream str;
			str << sqlite3_column_text(stmt, 0);
			str >> isblock;
		}
		sqlite3_finalize(stmt);
	}
	/*else {
		cout << "SQL error: " << zErrMsg << endl;
		sqlite3_free(zErrMsg);
	}*/
	return isblock;
}
void Model::WriteToFriend(sqlite3 *db, int id1, int id2) {
	if (!db)return;
	szSQL = "INSERT INTO friend VALUES (?,?,?),(?,?,?)";
	rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);
	if (rc == SQLITE_OK) {
		// bind the value
		int isblock = 0;
		sqlite3_bind_int(stmt, 1, id1);
		sqlite3_bind_int(stmt, 2, id2);
		sqlite3_bind_int(stmt, 3, isblock);
		sqlite3_bind_int(stmt, 4, id2);
		sqlite3_bind_int(stmt, 5, id1);
		sqlite3_bind_int(stmt, 6, isblock);
		// commit
		sqlite3_step(stmt);
		sqlite3_finalize(stmt);
	}
	/*else {
		cout << "SQL error: " << zErrMsg << endl;
		sqlite3_free(zErrMsg);
	}*/
}
void Model::ShowFriend(sqlite3 *db, int id1) {
	cout << "-------List Friends-----------\n";
	if (!db)return;
	szSQL = "SELECT user.name FROM friend left JOIN message on message.idrec = friend.id2 join user on user.id = friend.id2 where id1 = ? AND isblock = 0 group by id2 order by time desc";
	rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);
	if (rc == SQLITE_OK) {
		// bind the value
		sqlite3_bind_int(stmt, 1, id1);
		// commit
		int a = 0;
		while (sqlite3_step(stmt) == SQLITE_ROW) {
			int cols = sqlite3_column_count(stmt);
			for (int i = 0; i <cols; i++) {
				a++;
				cout << a << ": ";
				printf("%s \n", sqlite3_column_text(stmt, i));
			}
		}
		sqlite3_finalize(stmt);
		cout << "-------------------------------------\n";
	}
	/*else {
		cout << "SQL error: " << zErrMsg << endl;
		sqlite3_free(zErrMsg);
	}*/
}
int Model::ShowaaFriend(sqlite3 *db, int id1,int n) {
	int id = 0;
	if (!db) return id;
	szSQL = "SELECT id FROM(SELECT * FROM friend where(id1 = ?) AND isblock = 0) as A LEFT JOIN user ON(A.id2 = user.id)";
	rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);
	if (rc == SQLITE_OK) {
		// bind the value
		sqlite3_bind_int(stmt, 1, id1);
		// commit
		int a = 0;
		while (sqlite3_step(stmt) == SQLITE_ROW) {
			int cols = sqlite3_column_count(stmt);
			for (int i = 0; i <cols; i++) {
				a++;
				if (n==a) {
					stringstream str;
					str << sqlite3_column_text(stmt, 0);
					str >> id;
				}
			}
		}
		sqlite3_finalize(stmt);
		cout << "-------------------------------------\n";
	}
	/*else {
		cout << "SQL error: " << zErrMsg << endl;
		sqlite3_free(zErrMsg);
	}*/
	return id;
}
void Model::BlockFriend(sqlite3 *db, int id1, int id2) {
	if (!db)return;
	szSQL = "UPDATE friend SET isblock = 1 WHERE id1 = ? AND id2 = ?";
	rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);
	if (rc == SQLITE_OK) {
		// bind the value
		sqlite3_bind_int(stmt, 1, id1);
		sqlite3_bind_int(stmt, 2, id2);
		// commit
		sqlite3_step(stmt);
		sqlite3_finalize(stmt);
	}
	/*else {
		cout << "SQL error: " << zErrMsg << endl;
		sqlite3_free(zErrMsg);
	}*/
}
void Model::WriteToMess(sqlite3 *db, int id1, int id2, char *mes, char *tim,int tt,int sec) {
	szSQL = "INSERT INTO message VALUES (?,?,?,?,?,?)";
	rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);
	if (rc == SQLITE_OK) {
		// bind the value
		sqlite3_bind_int(stmt, 1, id1);
		sqlite3_bind_int(stmt, 2, id2);
		sqlite3_bind_text(stmt, 3, mes, strlen(mes), 0);
		sqlite3_bind_text(stmt, 4, tim, strlen(tim), 0);
		sqlite3_bind_int(stmt, 5, tt);
		sqlite3_bind_int(stmt, 6, sec);
		// commit
		sqlite3_step(stmt);
		sqlite3_finalize(stmt);
	}
	/*else {
		cout << "SQL error: " << zErrMsg << endl;
		sqlite3_free(zErrMsg);
	}*/
}
void Model::update_tt(sqlite3 *db, int id1, int id2) {
	if (!db)return;
	szSQL = "UPDATE message SET status = 0 WHERE idsen = ? AND idrec = ?";
	rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);
	if (rc == SQLITE_OK) {
		// bind the value
		sqlite3_bind_int(stmt, 1, id2);
		sqlite3_bind_int(stmt, 2, id1);
		// commit
		sqlite3_step(stmt);
		sqlite3_finalize(stmt);
	}
	/*else {
		cout << "SQL error: " << zErrMsg << endl;
		sqlite3_free(zErrMsg);
	}*/
}
int Model::Select_all(sqlite3 *db,char *us) {
	int id = 0;
	szSQL = "select * from user where username = ?";
	rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);
	if (rc == SQLITE_OK) {
		// bind the value
		sqlite3_bind_text(stmt, 1, us, strlen(us), 0);
		// commit
		if (sqlite3_step(stmt) == SQLITE_ROW) {
			stringstream str;
			str << sqlite3_column_text(stmt, 0);
			str >> id;
			sqlite3_finalize(stmt);
		}
	}
	/*else {
		cout << "SQL error: " << zErrMsg << endl;
		sqlite3_free(zErrMsg);
	}*/
	return id;
}
int Model::Select_mask(sqlite3 *db) {
	int id = 0;
	szSQL = "select max(id) from user";
	rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);
	if (rc == SQLITE_OK) {
		if (sqlite3_step(stmt) == SQLITE_ROW) {
			stringstream str;
			str << sqlite3_column_text(stmt, 0);
			str >> id;
			sqlite3_finalize(stmt);
		}
	}
	/*else {
		cout << "SQL error: " << zErrMsg << endl;
		sqlite3_free(zErrMsg);
	}*/
	return id;
}
void Model::Insert_maskuser(sqlite3 *db, int id1,char *na,char *se,char *add) {
	if (!db)return;
	szSQL = "INSERT INTO mask_user VALUES (?,?,?,?)";
	rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);
	if (rc == SQLITE_OK) {
		// bind the value
		int isblock = 0;
		sqlite3_bind_int(stmt, 1, id1);
		sqlite3_bind_text(stmt, 2, na,strlen(na),0);
		sqlite3_bind_text(stmt, 3, se,strlen(se),0);
		sqlite3_bind_text(stmt, 4, add,strlen(add),0);
		// commit
		sqlite3_step(stmt);
		sqlite3_finalize(stmt);
	}
	/*else {
		cout << "SQL error: " << zErrMsg << endl;
		sqlite3_free(zErrMsg);
	}*/

}
void Model::Update_fr(sqlite3 *db,char *fullname,char *gender,char *address,int id) {
	if (!db)return;
	szSQL = "UPDATE mask_user SET name = ?,sex=?,address=? WHERE id = ?";
	rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);
	if (rc == SQLITE_OK) {
		// bind the value
		sqlite3_bind_text(stmt, 1, fullname, strlen(fullname), 0);
		sqlite3_bind_text(stmt, 2, gender,strlen(gender),0);
		sqlite3_bind_text(stmt, 3, address,strlen(address),0);
		sqlite3_bind_int(stmt, 4, id);
		// commit
		sqlite3_step(stmt);
		sqlite3_finalize(stmt);
	}
	/*else {
		cout << "SQL error: " << zErrMsg << endl;
		sqlite3_free(zErrMsg);
	}*/
}
void Model::Detail_fr(sqlite3 *db,int id2) {
	if (!db)return;
	szSQL = "select mask_user.name,sex,address from Friend,mask_user where Friend.id2=mask_user.id and id2 = ?";
	rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);
	if (rc == SQLITE_OK) {
		// bind the value
		sqlite3_bind_int(stmt, 1, id2);
		// commit
		rc = sqlite3_step(stmt);
		if (rc == SQLITE_ROW)
		{
			int cols = sqlite3_column_count(stmt);
			for (int i = 0; i <cols; i++) {
				printf("%s: ", sqlite3_column_name(stmt, i));
				printf("%s \n", sqlite3_column_text(stmt, i));
			}
		}
		cout << "-------------------------------------\n";
		sqlite3_finalize(stmt);
	}
	/*else {
		cout << "SQL error: " << zErrMsg << endl;
		sqlite3_free(zErrMsg);
	}*/
}





