#include<stdio.h>
#include <iostream>
#include "AGV.h"
#include<Windows.h>
#define USERNAME "agv"
#define PASSWORD "tt24"
using namespace std;
int IDi = 0;
// TẠO PRODUCT NULL

// ============= Hàm Menu trả về giá trị mode 1 ->5 =============
int Menu()
{
	int M;
	cout << "*================================================*" << endl;
	cout << "|-----                [MENU]                -----|" << endl;
	cout << " 1.***   [          Add Products         ]   ***\n";
	cout << " 2.***   [        Collect Products       ]   ***\n";
	cout << " 3.***   [         Move Products         ]   ***\n";
	cout << " 4.***   [        Adjust Map Size        ]   ***\n";
	cout << " 5.***   [  Check Product's Information  ]   ***\n";
	cout << " 6.***   [       Exit AGV Program        ]   ***\n";
	cout << "         ---------------------------------" << endl;
	cout << "	 Choose your mode: ";
	cin >> M;
	cout << "<===================  [Menu " << M << "]  ===================>" << endl << endl;
	
	while (M < 1 || M>6)
	{
		cout << "Please choose modes from 1 to 6 !!!" << endl;
		cout << "Choose your mode again ! ";
		cin >> M;
	}
	return M;
}
// ============= Hàm CreMap trả về Matrix size row x col =============
struct Product** CreMap(int row, int col)
{
	Product** Storage;
	Storage = (Product * *)malloc(row * sizeof(Product*));			//cap phat de tao row hang
	for (int i = 0; i < row; i++)
	{
		Storage[i] = (Product*)malloc(col * sizeof(Product));						//cap phat de tao col. Moi hang lai duoc tao col cot
	}
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			Storage[i][j].ID = 0;
			strcpy(Storage[i][j].Name, "");
			strcpy(Storage[i][j].Detail, "");
		}
	}
	return Storage;
}
// ============= Hàm InputProduct trả về biến Product =============
 Product InputProduct(int row, int col)
{
	Product P;
	P.ID = ++IDi;
	//cout << "		Coordinate <row & column>: " << endl;
	P.T.x = row;
	P.T.y = col;
	cout << "		Input Name: ";		
	cin >> P.Name;
	cout << "		Input Detail: ";	
	cin >> P.Detail;
	cout << "		Product " << P.ID << " has been saved at position [" << row+1 << "][" << col+1 << "]" << endl;
	cout << "		----------------------- " << endl;
	return P;
}

//============= Hàm SignIn return 1 nếu nhập đúng, 0 nếu nhập sai ================
int SignIn()
{
	char UserName[100];
	char PassWord[100];
	int a = 0;
	cout << "================_____*SIGN IN_____================\n";

	while (a < 3)
	{
		cout << "USER NAME: ";	cin >> UserName;
		cout << "PASS WORD: ";	cin >> PassWord;
		if (!strcmp(UserName, USERNAME) && !strcmp(PassWord, PASSWORD))
		{
			cout << "\nLogging";
			for (int i = 0; i < 5; i++)
			{
				Sleep(500);
				cout << ".";
			}
			cout << endl;
			cout << "WELCOME TO PROGRAM AGV !\n";
			return 1;
		}
		else
		{
			cout << "Error!\n\n";
			a++;
		}
	}
	cout << "You can not be logged in, please contact the manager !";
	return 0;
}
int CheckID(int id_, int Tx, int Ty, Product** Map)
{
	if (id_ == 0)
	{
		return 0;
	}
	else if (id_ < 0)
	{
		return -1;
	}
	else if (id_ > 0)
	{
		for (int i = 0; i < Tx; i++)
		{
			for (int j = 0; j < Ty; j++)
			{
				if (id_ == Map[i][j].ID)
				{
					return 1;
				}
			}
		}
		return 0;
	}
}

void PrintMap(int Tx, int Ty, Product** Map, int count2)
{
	time_t rawtime;
	struct tm* timeinfo;
	time(&rawtime);
	timeinfo = localtime(&rawtime);

	string Mappath = "Map.txt";
	string SCount2 = to_string(count2);
	Mappath.insert(3, SCount2);
	char CMP[20];
	strcpy(CMP, Mappath.c_str());
	FILE* FileMap;
	FileMap = fopen(CMP, "w");
	if (FileMap == NULL)
	{
		cout << "ERROR in creating file Map !\n" << endl;
	}
	else
	{
		cout << "Your change has been saved into file " << CMP << "\n" << endl;
	}
	fprintf(FileMap, "========= *** %s *** ==========\n", CMP);
	fprintf(FileMap, "Updated time: %s\n", asctime(timeinfo));
	fprintf(FileMap, "\n");
	Sleep(500);
	cout << "	========= *** "<< CMP << " *** ==========" << endl;
	cout << "	Updated time: " << asctime(timeinfo) << endl;
	cout << endl;
	for (int i = 0; i < Ty; i++)
	{
		fprintf(FileMap, "	%d", i + 1);
	}
	fprintf(FileMap, "\n");
	for (int i = 0; i < Ty; i++)
	{
		fprintf(FileMap, "--------------");
	}
	fprintf(FileMap, "\n\n");
	
	//					MATRIX LƯU FILE					//
	for (int i = 0; i < Tx; i++)
	{
		fprintf(FileMap, "%d|", i + 1);
		for (int j = 0; j < Ty; j++)
		{
			fprintf(FileMap, "	%d", Map[i][j].ID);
			printf("	%d", Map[i][j].ID);
		}
		fprintf(FileMap, "\n\n");
		cout << "\n\n";
	}
	fclose(FileMap);
}

int deleteProduct(Product** Storage, int row, int col, int ID_) {
	if (ID_ <= 0)
	{
		return 0;
	}
	else
	{
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				if (Storage[i][j].ID == ID_)
				{
					Storage[i][j].ID = 0;
					strcpy(Storage[i][j].Name, "");
					strcpy(Storage[i][j].Detail, "");
					return 1;
				}
			}	
		}
		return 2;
	}
	return 0;
}
void CopyProduct(Product** Storage, Product NewProduct, int ID_, int row, int col )
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (Storage[i][j].ID == ID_)
			{
				NewProduct.ID = Storage[i][j].ID;
				strcpy(NewProduct.Name, Storage[i][j].Name);
				strcpy(NewProduct.Detail, Storage[i][j].Detail);
			}
		}
	}
}
void freeStorage(int row, int col, Product** Storage) 
{
	for (int i = 0; i < row; i++) 
	{
		free(Storage[i]);
	}
	free(Storage);
}
void ProductInfoPos(Product Proinfo, int Tx, int Ty, int row, int col)
{
	cout << "Information of Product " << Proinfo.ID << ":" << endl;
	cout << "	Position: [" << Tx << "][" << Ty << "]" << endl;
	cout << "	ID: " << Proinfo.ID << endl;
	cout << "	Name: " << Proinfo.Name << endl;
	cout << "	Detail: " << Proinfo.Detail << endl;
	cout << "	-----------------------" << endl;
}
void proInfoID(Product** Storage, int id_, int row, int col)
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (Storage[i][j].ID == id_)
			{
				cout << "Information of Product " << Storage[i][j].ID << ":" << endl;
				int Tx = Storage[i][j].T.x;
				int Ty = Storage[i][j].T.y;
				cout << "	Position: [" << Tx+1 << "][" << Ty+1 << "]" << endl;
				
				cout << "	ID: " << Storage[i][j].ID << endl;
				cout << "	Name: " << Storage[i][j].Name << endl;
				cout << "	Detail: " << Storage[i][j].Detail << endl;
				cout << "	-----------------------" << endl;
			}
		}
	}
}
int validInputChS(int x_in, int y_in, int row, int col) {

	if (x_in <= 0 || y_in <= 0 || x_in > row || y_in >col)
	{
		printf("	< Unavailble, input again! >");
		return 0;
	}
	return 1;
}
void swapPosition(int* numb1, int* numb2)
{
	int* swp = numb1;
	*numb1 = *numb2;
	*numb2 = *swp;
}
void formPosition(int* x1, int* y1, int* x2, int* y2) {
	if (*x1 > * x2&&* y1 > * y2) {
		swapPosition(x1, x2);
		swapPosition(y1, y2);
	}
	if (*x1 <*x2 && *y1 >* y2) {
		swapPosition(y1, y2);
	}
	if (*x1 > * x2&&* y1 < *y2) {
		swapPosition(x1, x2);
	}
	*x1 = *x1 - 1;
	*y1 = *y1 - 1;
	*x2 = *x2 - 1;
	*y2 = *y2 - 1;

}
int CountProduct(Product** Map, int Tx, int Ty)
{
	int Count = 0;
	for (int i = 0; i < Tx; i++)
	{
		for (int j = 0; j < Ty; j++)
		{
			if (Map[i][j].ID != 0)
			{
				Count++;
			}
		}
	}
	return Count;
}

void CreProduct(Product** Map, Coordinate T1, int C1)
{
	int Replace = 1, Title = 1;
	while (C1 == 1)
	{
		Coordinate T2;
		if (Title == 1)
		{
			cout << "		----------------------- " << endl;
			cout << "		CREATING PRODUCT " << IDi + 1 << ":" << endl;
		}
		// Replace = 1;
		Title = 1;
		cout << "		Coordinate <row & column>: ";
		cin >> T2.x;
		cin >> T2.y;
		// Vị trí hợp lệ
		if (T2.x <= T1.x && T2.x > 0 && T2.y <= T1.y && T2.y > 0)
		{
			if (Map[T2.x - 1][T2.y - 1].ID != 0)		// Check xem đã có sản phẩm ở vị trí này hay chưa
			{
				cout << "This position is containing another product.\nDo you want to replace it ?\t<Yes (1)/ No (0)> :";
				cin >> Replace;
				if (Replace)
				{
					Map[T2.x - 1][T2.y - 1] = InputProduct(T2.x - 1, T2.y - 1);
					//count1 = IDi + 1;
				}
				else
				{
					cout << "Choose another position !" << endl;
					Title = 0;
					continue;
				}
			}
			else												// Nếu chưa thì thêm bình thường
			{
				Map[T2.x - 1][T2.y - 1] = InputProduct(T2.x - 1, T2.y - 1);
				//count1 = IDi + 1;
			}
			cout << "Do you want to input more ?\n<Yes (1)/ No (0)> :";	cin >> C1;
		}
		else
		{
			cout << "Unavailble !!! The row must be ( >0, < " << T1.x << " ) and col must be ( >0, < " << T1.y << " )" << endl;
			cout << "	1. Input again\n	0. Go back to Menu" << endl;
			cout << "	Choose your option: ";
			cin >> C1;
			Title = !C1;
		}
		if (C1 && CountProduct(Map, T1.x, T1.y) == T1.x * T1.y)
		{
			cout << "WARNING: Your map is full ! \nIf you want to input more product, you must replace an exsisted product in the map!\n	<Yes (1)/ No (0)>: ";
			cin >> C1;
		}
	}
}