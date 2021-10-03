#include <iostream>
#include <string.h>
#include <sstream>
#include <time.h>
#include<Windows.h>
extern int IDi;
//int IDi;				// cho ID lúc đầu bằng 0, khi input shelves thì ID sẽ tự động +1;
struct Coordinate
{
	int x;		//Row
	int y;		//Col
};
struct Product
{
	struct Coordinate T;
	int ID;
	char Name[100];
	char Detail[100];
};
int Menu();
int SignIn();
int CheckID(int id_, int Tx, int Ty, Product** Map);
struct Product** CreMap(int row, int col);
void ProductInfoPos(Product Proinfo, int Tx, int Ty, int row, int col);
void proInfoID(Product** Storage, int id_, int row, int col);
struct Product InputProduct(int row, int col);
void PrintMap(int Tx, int Ty, Product** Map, int count2);
void CopyProduct(Product** Storage, Product NewProduct, int ID_, int row, int col);
int deleteProduct(Product** Storage, int row, int col, int ID_);
void freeStorage(int row, int col, Product** Storage);
int validInputChS(int x1_in, int y1_in, int row, int col);
void formPosition(int* x1, int* y1, int* x2, int* y2);
void swapPosition(int* numb1, int* numb2);
int CountProduct(Product** Map, int Tx, int Ty);

void CreProduct(Product** Map, Coordinate T1, int C1);