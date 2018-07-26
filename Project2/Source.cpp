#include <iostream>
#include <string>
#include <ctime>
#include <sqlite3.h>
#include "Controller.h"
#include "Model.h"
#include <stdlib.h>
#include <Windows.h>
#include "View.h"
#define _VARIADIC_MAX 10
using namespace std;
int choice_m = 0;
View view1;
int main()
{
	view1.choose_menu();
	system("pause");
	return 0;
}