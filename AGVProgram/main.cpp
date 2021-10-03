#include "AGV.h"
#include <string.h>
#include <sstream>
using namespace std;

int main()
{
	int C1 = 0, count1 = 0, count2 = 0;
	int colAddLeft = 0, colAddRight = 0, rowAddUp = 0, rowAddDown = 0;
	//int a = SignIn();			//Login
	//if (!a)
	//{
	//	return 0;
	//}
	//Sleep(500);
	//system("cls");

	Coordinate T1;
	cout << "***================== [SETTING YOUR MAP] ==================***\n";
	cout << "Create your Map:\n Input the map size (Row & Column): ";
	cin >> T1.x;
	cin >> T1.y;
	Product** Map = CreMap(T1.x, T1.y);
	cout << "Your factory map has been created !" << endl;

	///============== *** Create FILEMAP and input file *** ================= 
	PrintMap(T1.x, T1.y, Map, count2);

	//================= *** INPUTING PRODUCTS *** ===================
	cout << "Do you want to input your products to your factory ? \n<Yes (1)/ No (0)> :";
	cin >> C1;
	int C2 = C1;
	
	CreProduct(Map, T1, C1);
	cout << "<-------- Finished inputing products -------->\n" << endl;
	if (C2)
	{
		PrintMap(T1.x, T1.y, Map, ++count2);  //Map after adding
	}
	int flag = 0;
	while (1)
	{
		int M = Menu();
		switch (M)
		{
			int id_, select03;
			case 1:
			{
				cout << "*-------------------------------------------------*" << endl;
				cout << "|===                Input Products             ===|" << endl;
				cout << "*-------------------------------------------------*" << endl;
				CreProduct(Map, T1, C1);
				PrintMap(T1.x, T1.y, Map, ++count2);
				break;
			}
			case 2:
			{
				int flag1;
				cout << "*-------------------------------------------------*" << endl;
				cout << "|===             Collecting Products           ===|" << endl;
				cout << "*-------------------------------------------------*" << endl;
				do
				{
					printf("\nInput product ID: "); scanf_s("%d", &id_);
					flag = deleteProduct(Map, T1.x, T1.y, id_);
					if (flag == 1)
					{
						cout << "<-------- Product " << id_ << " has been collected ! -------->" << endl;
						count2++;
						PrintMap(T1.x, T1.y, Map, count2);
					}
					else if (flag == 2)
					{
						cout << "There is no product has ID = "<< id_ << endl;
					}
					else if (flag == 0)
					{
						cout << "The ID must be > 0" << endl;
					}
					cout << "Do you want to collect another product ? <Yes (1)/ No (0)> : ";
					cin >> flag1;
				} while (flag1 == 1);
				break;
			}
			case 3:
			{
				int flacIDin = 0, flacID = 0, flacC = 0;
				int pos_x, pos_y;
				cout << "*-------------------------------------------------*" << endl;
				cout << "|===              Moving Products              ===|" << endl;
				cout << "*-------------------------------------------------*" << endl;
				do
				{
					printf("\nInput product ID: ");
					fflush(stdin);
					cin >> id_;
					flacID = CheckID(id_, T1.x, T1.y, Map);
					if (flacID == 1)		// Có ID
					{
						do // Nhập Pos
						{
							cout << "\nInput new position <row/Col> : ";
							cin >> pos_x;
							cin >> pos_y;
							if (pos_x > T1.x || pos_x <= 0 || pos_y > T1.y || pos_y <= 0)
							{
								cout << "	Unavailble, input again: ";
							}
							else
							{
								if (Map[pos_x - 1][pos_y - 1].ID == 0)		// Nếu không trùng
								{
									//CopyProduct(Map, Map[pos_x - 1][pos_y - 1], id_, T1.x, T1.y);
									for (int i = 0; i < T1.x; i++)
									{
										for (int j = 0; j < T1.y; j++)
										{
											if (Map[i][j].ID == id_)
											{
												Map[pos_x - 1][pos_y - 1].ID = Map[i][j].ID;
												strcpy(Map[pos_x - 1][pos_y - 1].Name, Map[i][j].Name);
												strcpy(Map[pos_x - 1][pos_y - 1].Detail, Map[i][j].Detail);
											}
										}
									}
									deleteProduct(Map, T1.x, T1.y, id_);
									cout << "<-------- Your product has been moved to the new position ! -------->" << endl;
									count2++;
									PrintMap(T1.x, T1.y, Map, count2);
								}
								else
								{																// Nếu trùng
									cout << "\nThis position has already contained another product! \n";
									cout << "	1. Choose another position" << endl;
									cout << "	2. Replace product in the destination" << endl;
									cout << "	3.	Go back to Menu" << endl;
									cout << "Choose your option : ";
									cin >> flacC;
									if (flacC == 2)
									{
										//CopyProduct(Map, Map[pos_x - 1][pos_y - 1], id_, T1.x, T1.y);
										// Check
										/*for (int i = 0; i < T1.x; i++)
										{
											for (int j = 0; j < T1.y; j++)
											{
												if (Map[i][j].ID == id_)
												{
													Map[pos_x - 1][pos_y - 1].ID = Map[i][j].ID;
													strcpy(Map[pos_x - 1][pos_y - 1].Name, Map[i][j].Name);
													strcpy(Map[pos_x - 1][pos_y - 1].Detail, Map[i][j].Detail);
												}
											}
										}*/
										deleteProduct(Map, T1.x, T1.y, Map[pos_x - 1][pos_y - 1].ID);
										for (int i = 0; i < T1.x; i++) {
											for (int j = 0; j < T1.y; j++) {
												if (Map[i][j].ID == id_) {
													Map[pos_x - 1][pos_y - 1].ID = id_;
													Map[i][j].ID = 0;
													strcpy(Map[pos_x][pos_y].Name, Map[i][j].Name);
													strcpy(Map[pos_x][pos_y].Detail, Map[i][j].Detail);
													strcpy(Map[i][j].Name, "");
													strcpy(Map[i][j].Detail, "");
												}
											}
										}
										// Check
										deleteProduct(Map, T1.x, T1.y, id_);
										cout << "<-------- Your product has been moved to the new position ! -------->" << endl;
										count2++;
										PrintMap(T1.x, T1.y, Map, count2);
									}
									if (flacC == 3)
									{
										cout << "You have not moved any products !" << endl;
										break;			// GO BACK TO MENU
									}
								}
							}														
						} while (pos_x > T1.x || pos_x <= 0 || pos_y > T1.y || pos_y <= 0 || flacC == 1);
					}
					if (flacID == 0)
					{
						cout << "This product does not exsist !" << endl;
					}
					if (flacC != 3)
					{
						printf("\nDo you want to move another product?");
						printf("\n<Yes (1)/ No (0)> : ");
						cin >> flacIDin;
					}
					else
					{
						flacIDin = 0;
					}
				} while (flacIDin == 1);
				break;
			}	// Case 2
			case 4:
			{
				cout << "*-------------------------------------------------*" << endl;
				cout << "|===             Adjusting map size             ===|" << endl;
				cout << "*-------------------------------------------------*" << endl;
				printf("\n	1: Expand Map\n	2: Shrink Map\n	3: Go back to Menu\n	Enter your choice :  ");
				scanf_s("%d", &select03);
				cout << "	----------------------" << endl;
				Product** MapBuffer = CreMap(T1.x, T1.y);
				Coordinate Tbuf;
				Tbuf = T1;
				for (int i = 0; i < T1.x; i++)
				{
					for (int j = 0; j < T1.y; j++)
					{
						MapBuffer[i][j].ID = Map[i][j].ID;
						strcpy(MapBuffer[i][j].Name, Map[i][j].Name);
						strcpy(MapBuffer[i][j].Detail, Map[i][j].Detail);
					}
				}
				switch (select03)
				{
				case 1:				// Expand Map
				{
					printf("\nNumber of Cols You Want to Expand to the Left (>= 0): ");		scanf_s("%d", &colAddLeft);
					while (colAddLeft < 0)
					{
						printf("\n	Unavailble, input again : ");						scanf_s("%d", &colAddLeft);
					}
					printf("\nNumber of Cols You Want to Expand to the Right (>= 0): ");	scanf_s("%d", &colAddRight);
					while (colAddRight < 0)
					{
						printf("\n	Unavailble, input again : ");						scanf_s("%d", &colAddRight);
					}
					printf("\nNumber of Rows You Want to Expand to Upper (>= 0): ");		scanf_s("%d", &rowAddUp);
					while (rowAddUp < 0)
					{
						printf("\n	Unavailble, input again : ");						scanf_s("%d", &rowAddUp);
					}
					printf("\nNumber of Rows You Want to Expand to Below (>= 0): ");		scanf_s("%d", &rowAddDown);
					while (rowAddUp < 0)
					{
						printf("\n	Unavailble, input again : ");						scanf_s("%d", &rowAddDown);
					}
					if (rowAddDown == 0 && rowAddUp == 0 && colAddLeft == 0 && colAddRight == 0)
					{
						printf("\n<-------- Your map has not been changed size ! -------->");
						count2++;
						PrintMap(T1.x, T1.y, Map, count2);
					}
					else
					{
						freeStorage(T1.x, T1.y, Map);
						T1.x = T1.x + rowAddDown + rowAddUp;
						T1.y = T1.y + colAddLeft + colAddRight;
						Map = CreMap(T1.x, T1.y);

						for (int i = rowAddUp; i < T1.x - rowAddDown; i++)
						{
							for (int j = colAddLeft; j < T1.y - colAddRight; j++)
							{
								Map[i][j].ID = MapBuffer[i - rowAddUp][j - colAddLeft].ID;
								strcpy(Map[i][j].Name, MapBuffer[i - rowAddUp][j - colAddLeft].Name);
								strcpy(Map[i][j].Detail, MapBuffer[i - rowAddUp][j - colAddLeft].Detail);
							}
						}
						cout << "\n		Processing";
						for (int i = 0; i < 10; i++)
						{
							Sleep(100);
							cout << ".";
						}
						cout << endl;
						cout << "<-------- Your map has been expanded ! -------->" << endl;
						count2++;
						PrintMap(T1.x, T1.y, Map, count2);
					}
					break;
				}
				case 2:			// Shrink Map
				{
					int x1_in, y1_in, x2_in, y2_in;
					do
					{
						printf("\nInput the first position <row/col> : ");			//First point
						scanf_s("%d", &x1_in);
						scanf_s("%d", &y1_in);
					} while (!validInputChS(x1_in, y1_in, T1.x, T1.y));			//Check the value of the input
					do
					{
						printf("\nInput the second position <row/col> : ");		//Second point
						scanf_s("%d", &x2_in);
						scanf_s("%d", &y2_in);
					} while (!validInputChS(x2_in, y2_in, T1.x, T1.y));

					freeStorage(T1.x, T1.y, Map);
					formPosition(&x1_in, &y1_in, &x2_in, &y2_in);									//Convert 2 conner random point to fixed form - up left conner and down right conner
					T1.x = x2_in - x1_in + 1;																// Number of rows of new Size
					T1.y = y2_in - y1_in + 1;																// Number of cols of new Size
					Map = CreMap(T1.x, T1.y);																// Create with new size

					for (int i = 0; i < T1.x; i++)
					{
						for (int j = 0; j < T1.y; j++)
						{
							Map[i][j].ID = MapBuffer[i + x1_in][j + y1_in].ID;
							strcpy(Map[i][j].Name, MapBuffer[i + x1_in][j + y1_in].Name);
							strcpy(Map[i][j].Detail, MapBuffer[i + x1_in][j + y1_in].Detail);
						}
					}
					cout << "\n		Processing";
					for (int i = 0; i < 10; i++)
					{
						Sleep(100);
						cout << ".";
					}
					cout << endl;
					cout << "<-------- Your map has been shrunk ! -------->" << endl;
					count2++;
					PrintMap(T1.x, T1.y, Map, count2);
					break;
				}
				case 3:			// Go back to Menu
					break;
				}
				freeStorage(Tbuf.x, Tbuf.y, MapBuffer);
				break;
			}	// Case 3
			case 5:
			{
				cout << "*-------------------------------------------------*" << endl;
				cout << "|===        Check Product's Information        ===|" << endl;
				cout << "*-------------------------------------------------*" << endl;
				int id_ = 0, mode = 0, flacID = 0, flacMore = 1, flagPos = 0;
				Coordinate Pos;
				cout << "Do you want to check by ID <1> or position <2> : ";
				cin >> mode;
				if (mode == 1)
				{
					do
					{
						cout << "Input the ID: ";
						cin >> id_;
						flacID = CheckID(id_, T1.x, T1.y, Map);
						if (flacID == 1)
						{
							count2++;
							proInfoID(Map, id_, T1.x, T1.y);
						}
						else if(flacID == -1)
						{
							cout << "The product whose ID " << id_ << " does not exsist !" << endl;
						}
						else if (flacID == 0)
						{
							cout << "The ID must be >0" << endl;
						}
						cout << "Do you want to check more product's information by ID?" << endl;
						cout << "	<Yes (1)/ No (0)> : ";
						cin >> flacMore;
					} while (flacMore == 1);
				}
				else if (mode == 2)
				{
					do
					{
						cout << "	Input position (row/col): ";
						cin >> Pos.x;
						cin >> Pos.y;
						if (Pos.x < T1.x +1 && Pos.x > 0 && Pos.y < T1.y +1 && Pos.y > 0)
						{
							count2++;
							//PrintMap(T1.x, T1.y, Map, count2);
							ProductInfoPos(Map[Pos.x - 1][Pos.y - 1], Pos.x, Pos.y, T1.x, T1.y);
						}
						else
						{
							cout << "	Unavailble position !" << endl;
						}
						cout << "Do you want to check more product's information by position ?" << endl;
						cout << "	<Yes (1)/ No (0)> : ";
						cin >> flacMore;
					} while (flacMore);
				}
				break;
			}
			case 6: 
			{
				cout << "*-------------------------------------------------*" << endl;
				cout << "|===           Exitting AGV Program           ===|" << endl;
				for (int i = 0; i < 50; i++)
				{
					Sleep(50);
					cout << "-";
				}
				freeStorage(T1.x, T1.y, Map);
				cout << "\n		Good bye and see you again !" << endl;
				cout << "*-------------------------------------------------*" << endl;
				freeStorage(T1.x, T1.y, Map);
				return 0;
			}
		}
	}
	freeStorage(T1.x, T1.y, Map);
	return 0;
}
