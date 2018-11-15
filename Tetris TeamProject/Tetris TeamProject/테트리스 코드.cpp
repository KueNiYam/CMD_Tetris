#include <iostream>
#include <conio.h> // Ű���� �Է��� ���� �������
#include <time.h> // ������ ���� �������
#include <Windows.h> // gotoxy �Լ� ������ �� �ʿ�
using namespace std;

// Ű���� �Է°� ���� or etc
#define UP 72
#define DOWN 80
#define RIGHT 77
#define LEFT 75
#define ESC 27
#define SPACEBAR 32
#define SPEED 100
#define X object_point.x
#define Y object_point.y
#define TotalY 30
#define TotalX 17
#define MAP Map.field
/* Ŭ���� ���� */
class Point // [y][x]!!! x, y ��ǥ ���� ������ ������, �Ʒ� ����
{
public:
	int x;
	int y;
};
class Object_shape // ��� Ŭ����
{
public:
	int shape_part[3][3]; // ���� ������ ������, �Ʒ� ����; �߾��� [1][1]
};
/* 7���� ��� ���� */
Object_shape Type[7] = {
	{ 0,1,0,0,1,0,0,1,0 }, // �� 0
	{ 0,1,0,1,1,1,0,0,0 },  // �� 1
	{ 0,1,0,0,1,0,0,1,1 }, // �� 2
	{ 0,1,0,0,1,1,0,0,1 }, // ���� 3
	{ 1,0,0,1,1,1,0,0,0 }, // �� ���� ��� 4
	{ 0,0,1,0,1,1,0,1,0, }, // ���� �ݴ� 5
	{ 0,1,1,0,1,1,0,0,0 }, // �׸� 6
};
class Object
{
private:
	bool life;
	int mode; // 0 ~ 6 ����
	Object_shape shape; // ���
	Point object_point; // ��ü �߾��� ����Ʈ
	int oMap[TotalY][TotalX]; // �ʿ����� ��ġ
							  //int bug_fix_left;
							  //int bug_fix_right;
public:
	Object(); // ������
	Object& operator= (const Object& right_class);
	void new_oMap(int tempMap[TotalY][TotalX]); // �ʿ����� ��ǥ
												//accessor
	bool get_life() const; // return life
	int get_oMap(int i, int j) const; // return oMap[i][j]
									  //move
	void spin(); // ȸ��
	void down(); // �ð��� �帧�� ���� ������
	void fest_down(int tempMap[TotalY][TotalX]); // ������ ������
	void left();
	void right();
};
class Base // �⺻ �� Ŭ����
{
public:
	int field[TotalY][TotalX];
	Base& operator=(const Base& p);
	Base& operator=(int tempMap[TotalY][TotalX]);
	Base& operator=(const Object& o);
};
/* ��������, �Լ� ���� */
int LIFE = 1;
void display(int temp_map[TotalY][TotalX]); // ȭ�� ������
void gotoxy(int x, int y); // Ŀ�� ��ġ ���� �Լ�
void keyboard(Object&, int tempMap[TotalY][TotalX]); // key�Է°�
bool clearValue(int* p);

void display(int temp_map[TotalY][TotalX])
{
	
	int color;
	
	for (int i = 0; i < TotalY; i++)
	{
		for (int j = 0; j < TotalX; j++)
		{
			gotoxy(2 * (j + 1) + 30, i + 1);
			if (temp_map[i][j] != 0)
			{
				color = rand() % 2;
				if (color == 0)
				{
					cout << "��";
				}
				else if (color == 1)
				{
					cout << "��";
				}
			}
			if (temp_map[i][j] == 0)
			{
				cout << "��";
			}
		}
	}
	Sleep(SPEED);


}
void gotoxy(int x, int y)
{

	COORD Pos = { x - 1, y - 1 };

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
void keyboard(Object& c, int tempMap[TotalY][TotalX])
{
	int free_buffer;
	int ch;
	if (_kbhit())
	{
		ch = _getch();

		if (_kbhit()) // �ԷµǾ��ִ� ���۸� �����ش�.
		{
			ch = _getch();
			if (_kbhit())
			{
				free_buffer = _getch();
			}
		}


		switch (ch)
		{
		case UP:
			c.spin();
			break;
		case DOWN:
			c.down();
			break;
		case RIGHT:
			c.right();
			break;
		case LEFT:
			c.left();
			break;
		case SPACEBAR:
			c.fest_down(tempMap);
			break;
		default:
			break;
		}

	}



}
bool clearValue(int *p)
{
	int testNum;
	testNum = 0;
	for (int j = 1; j <= 15; j++)
	{
		testNum += *(p + j);
	}
	if (testNum == 30)
	{
		return true;
	}
	else return false;
}


/*------------------------------------------------------------------------------------*/
// Base Ŭ������ ��� �Լ���
Base& Base::operator=(const Base& p)
{
	for (int i = 0; i < TotalY; i++)
	{
		for (int j = 0; j < TotalX; j++)
		{
			field[i][j] = p.field[i][j];
		}
	}
	return *this;
}
Base& Base::operator=(int tempMap[TotalY][TotalX])
{
	for (int i = 0; i < TotalY; i++)
	{
		for (int j = 0; j < TotalX; j++)
		{
			field[i][j] = tempMap[i][j];
		}
	}
	return *this;
}
Base& Base::operator=(const Object& o)
{
	for (int i = 0; i < TotalY; i++)
	{
		for (int j = 0; j < TotalX; j++)
		{
			field[i][j] = o.get_oMap(i, j);
		}
	}

	return *this;
}

// Object Ŭ������ ��� �Լ���
Object::Object()
{
	life = 1;
	mode = rand() % 7;
	object_point.x = 8;
	object_point.y = 2;
	//bug_fix_left = 0;
	//bug_fix_right = 0;

	switch (mode)
	{
	case 0:
		shape = Type[0];
		break;
	case 1:
		shape = Type[1];
		break;
	case 2:
		shape = Type[2];
		break;
	case 3:
		shape = Type[3];
		break;
	case 4:
		shape = Type[4];
		break;
	case 5:
		shape = Type[5];
		break;
	case 6:
		shape = Type[6];
		break;
	}


}
Object& Object::operator= (const Object& rightClass)
{

	this->life = rightClass.life;
	this->mode = rightClass.mode; // 0 ~ 6 ����
	this->shape = rightClass.shape; // Object_shape
	this->object_point = rightClass.object_point; // Point
	for (int i = 0; i <= TotalY - 1; i++)
	{
		for (int j = 0; j <= TotalX - 1; j++)
		{
			this->oMap[i][j] = rightClass.oMap[i][j];
		}
	}

	return *this;
}
void Object::new_oMap(int tempMap[TotalY][TotalX])
{

	for (int i = 0; i < TotalY; i++) // �ϴ� ����.
	{
		for (int j = 0; j < TotalX; j++)
		{
			oMap[i][j] = tempMap[i][j];
		}
	}

	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			oMap[Y + i][X + j] = shape.shape_part[1 + i][1 + j];
		}
	}


	// �ܻ󳲴� ���� ���� Down
	if (oMap[Y - 2][X - 1] != 2)
	{
		oMap[Y - 2][X - 1] = 0;
	}
	if (oMap[Y - 2][X] != 2)
	{
		oMap[Y - 2][X] = 0;
	}
	if (oMap[Y - 2][X + 1] != 2)
	{
		oMap[Y - 2][X + 1] = 0;
	}
	if (Y >= 3)
	{
		if (oMap[Y - 3][X - 1] != 2)
		{
			oMap[Y - 3][X - 1] = 0;
		}
		if (oMap[Y - 3][X] != 2)
		{
			oMap[Y - 3][X] = 0;
		}
		if (oMap[Y - 3][X + 1] != 2)
		{
			oMap[Y - 3][X + 1] = 0;
		}
	}

	// �ܻ󳲴� ���� ���� Left
	if (oMap[Y - 2][X + 2] != 2)
	{
		oMap[Y - 2][X + 2] = 0;
	}
	if (oMap[Y - 1][X + 2] != 2)
	{
		oMap[Y - 1][X + 2] = 0;
	}
	if (oMap[Y][X + 2] != 2)
	{
		oMap[Y][X + 2] = 0;
	}
	if (oMap[Y + 1][X + 2] != 2)
	{
		oMap[Y + 1][X + 2] = 0;
	}
	//bug_fix_left-=1;

	// �ܻ󳲴� ���� ���� Right
	if (oMap[Y - 2][X - 2] != 2)
	{
		oMap[Y - 2][X - 2] = 0;
	}
	if (oMap[Y - 1][X - 2] != 2)
	{
		oMap[Y - 1][X - 2] = 0;
	}
	if (oMap[Y][X - 2] != 2)
	{
		oMap[Y][X - 2] = 0;
	}
	if (oMap[Y + 1][X - 2] != 2)
	{
		oMap[Y + 1][X - 2] = 0;
	}
	//bug_fix_right-=1;



}
bool Object::get_life() const
{
	return life;
}
int Object::get_oMap(int i, int j) const
{
	return oMap[i][j];
}
void Object::spin()
{
	for (int i = 0; i < 3; i++) // ���� ����
	{
		for (int j = 0; j < 3; j++)
		{
			if (shape.shape_part[i][j] == 2)
			{
				return;
			}
			if (oMap[Y + 2][X - 1] + oMap[Y + 2][X] + oMap[Y + 2][X + 1] >= 1)
			{
				return;
			}

		}
	}


	Object_shape temp;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			temp.shape_part[i][j] = shape.shape_part[i][j];
		}
	}
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			shape.shape_part[i][j] = temp.shape_part[j][2 - i];
		}
	}

}
void Object::down()
{
	Object_shape tempshape;

	for (int i = 0; i <= 2; i++)
	{
		for (int j = 0; j <= 2; j++)
		{
			tempshape.shape_part[i][j] = shape.shape_part[i][j];
		}
	}

	// �����ϴ� ��Ȳ�� 1
	if ((oMap[Y + 1][X - 1] == 1) && (oMap[Y + 2][X - 1] >= 1))
	{
		life = 0;
		return;
	}
	if ((oMap[Y + 1][X] == 1) && (oMap[Y + 2][X] >= 1))
	{
		life = 0;
		return;
	}
	if ((oMap[Y + 1][X + 1] == 1) && (oMap[Y + 2][X + 1] >= 1))
	{
		life = 0;
		return;
	}
	// �����ϴ� ��Ȳ�� 2
	for (int i = 0; i <= 1; i++)
	{
		for (int j = 0; j <= 2; j++)
		{
			if ((shape.shape_part[i][j] == 1) && shape.shape_part[i + 1][j] == 2)
			{
				life = 0;
				return;
			}

		}
	}

	// ��� �� ���� �� >=1 ��� �� ���� ���� �� >= 1 �� �� - ��翡 �߰�
	if (((oMap[Y + 1][X - 1] == 1) || (oMap[Y + 1][X] == 1) || (oMap[Y + 1][X + 1] == 1)) && ((oMap[Y + 2][X - 1] + oMap[Y + 2][X] + oMap[Y + 2][X + 1]) >= 1))
	{
		for (int i = 0; i <= 2; i++)  // ���� ��ü�� shape ���� ���� ����� ��
		{
			for (int j = 0; j <= 2; j++)
			{
				if (i >= 1)
				{
					if (shape.shape_part[i][j] == 2)
					{
						if (shape.shape_part[i - 1][j] == 0)
						{
							shape.shape_part[i - 1][j] = 2;
							shape.shape_part[i][j] = 0;
						}
					}
				}
				else if (i == 0)
				{
					if (shape.shape_part[i][j] == 2)
					{
						oMap[Y - 2][X + j - 1] = 2;
						shape.shape_part[i][j] = 0;
					}
				}
			}
		}

		if ((oMap[Y + 2][X - 1] >= 1) && (oMap[Y + 1][X - 1] != 1))
		{
			shape.shape_part[2][0] = 2;
		}
		if ((oMap[Y + 2][X] >= 1) && (oMap[Y + 1][X] != 1))
		{
			shape.shape_part[2][1] = 2;
		}
		if ((oMap[Y + 2][X + 1] >= 1) && (oMap[Y + 1][X + 1] != 1))
		{
			shape.shape_part[2][2] = 2;
		}

		object_point.y += 1;
		return;
	}
	// ��� �� ���� �� <=0 ��� �� ���� ���� �� >= 1 �� �� - ����� �Ʒ���
	if (((oMap[Y + 1][X - 1] + oMap[Y + 1][X] + oMap[Y + 1][X + 1]) <= 0) && ((oMap[Y + 2][X - 1] + oMap[Y + 2][X] + oMap[Y + 2][X + 1]) >= 1))
	{
		for (int i = 1; i <= 2; i++)
		{
			for (int j = 0; j <= 2; j++)
			{
				shape.shape_part[i][j] = tempshape.shape_part[i - 1][j];
			}
		}
		for (int j = 0; j <= 2; j++)
		{
			shape.shape_part[0][j] = 0;
		}
		//life = 0 �� ���� �ʰ� �����ؾ� ��!!!!
		return;
	}


	if (((oMap[Y + 2][X - 1] + oMap[Y + 2][X] + oMap[Y + 2][X + 1]) == 0)) // �ؿ� �ƹ��͵� ������ - �Ʒ��� ����
	{
		for (int i = 0; i <= 2; i++)  // ���� ��ü�� shape ���� ���� ����� ��
		{
			for (int j = 0; j <= 2; j++)
			{
				if (i >= 1)
				{
					if (shape.shape_part[i][j] == 2)
					{
						if (shape.shape_part[i - 1][j] == 0)
						{
							shape.shape_part[i - 1][j] = 2;
							shape.shape_part[i][j] = 0;

						}
					}
				}
				else if (i == 0)
				{
					if (shape.shape_part[i][j] == 2)
					{
						oMap[Y - 2][X + j - 1] = 2;
						shape.shape_part[i][j] = 0;
					}
				}
			}
		}


		object_point.y += 1;
		return;
	}
}
void Object::left()
{
	Object_shape tempshape;
	for (int i = 0; i <= 2; i++)
	{
		for (int j = 0; j <= 2; j++)
		{
			tempshape.shape_part[i][j] = shape.shape_part[i][j];
		}
	}

	// �� ���� ��Ȳ�� 1
	if ((oMap[Y - 1][X - 1] == 1) && (oMap[Y - 1][X - 2] >= 1))
	{
		return;
	}
	if ((oMap[Y][X - 1] == 1) && (oMap[Y][X - 2] >= 1))
	{
		return;
	}
	if ((oMap[Y + 1][X - 1] == 1) && (oMap[Y + 1][X - 2] >= 1))
	{
		return;
	}
	//������ ��Ȳ�� 2
	for (int i = 0; i <= 2; i++)
	{
		for (int j = 1; j <= 2; j++)
		{
			if ((shape.shape_part[i][j] == 1) && shape.shape_part[i][j - 1] == 2)
			{
				return;
			}

		}
	}


	// ��� �� ������ �� >=1 ��� �� ������ ������ �� >= 1 �� �� - ��翡 �߰�
	if (((oMap[Y - 1][X - 1] == 1) || (oMap[Y][X - 1] == 1) || (oMap[Y + 1][X - 1] == 1)) && ((oMap[Y - 1][X - 2] + oMap[Y][X - 2] + oMap[Y + 1][X - 2]) >= 1))
	{
		for (int i = 0; i <= 2; i++)  // ���� ��ü�� shape ���� ���� ����� ��
		{
			for (int j = 2; j >= 0; j--)
			{
				if (j <= 1)
				{
					if (shape.shape_part[i][j] == 2)
					{
						if (shape.shape_part[i][j + 1] == 0)
						{
							shape.shape_part[i][j + 1] = 2;
							shape.shape_part[i][j] = 0;
						}
					}
				}//
				else if (j == 2)
				{
					if (shape.shape_part[i][j] == 2)
					{
						oMap[Y + i - 1][X + j] = 2;
						shape.shape_part[i][j] = 0;
					}
				}

			}
		}

		if ((oMap[Y - 1][X - 2] >= 1) && (oMap[Y - 1][X - 1] != 1))
		{
			shape.shape_part[0][0] = 2;
		}
		if ((oMap[Y][X - 2] >= 1) && (oMap[Y][X - 1] != 1))
		{
			shape.shape_part[1][0] = 2;
		}
		if ((oMap[Y + 1][X - 2] >= 1) && (oMap[Y + 1][X - 1] != 1))
		{
			shape.shape_part[2][0] = 2;
		}
		object_point.x -= 1;
		//bug_fix_left += 2;
		return;
	}
	// ��� �� ���� �� <=0 ��� �� ���� ���� �� >= 1 �� �� - ����� �Ʒ���
	if (((oMap[Y - 1][X - 1] + oMap[Y][X - 1] + oMap[Y + 1][X - 1]) <= 0) && ((oMap[Y - 1][X - 2] + oMap[Y][X - 2] + oMap[Y + 1][X - 2]) >= 1))
	{
		for (int i = 0; i <= 2; i++)
		{
			for (int j = 0; j <= 1; j++)
			{
				shape.shape_part[i][j] = tempshape.shape_part[i][j + 1];
			}
		}
		for (int i = 0; i <= 2; i++)
		{
			shape.shape_part[i][2] = 0;
		}
		//life = 0 �� ���� �ʰ� �����ؾ� ��!!!!
		return;
	}


	if (((oMap[Y - 1][X - 2] + oMap[Y][X - 2] + oMap[Y + 1][X - 2]) == 0)) // ���ʿ� �ƹ��͵� ������ - �������� ������
	{
		for (int i = 0; i <= 2; i++)  // ���� ��ü�� shape ���� ���� ����� ��
		{
			for (int j = 2; j >= 0; j--)
			{
				if (j <= 1)
				{
					if (shape.shape_part[i][j] == 2)
					{
						if (shape.shape_part[i][j + 1] == 0)
						{
							shape.shape_part[i][j + 1] = 2;
							shape.shape_part[i][j] = 0;
						}
					}
				}//
				else if (j == 2)
				{
					if (shape.shape_part[i][j] == 2)
					{
						oMap[Y + i - 1][X + j] = 2;
						shape.shape_part[i][j] = 0;
					}
				}

			}
		}
		object_point.x -= 1;
		//bug_fix_left += 2;
		return;
	}
}
void Object::fest_down(int tempMap[TotalY][TotalX])
{
	Object shadow;
	shadow = *this;

	while (shadow.life)
	{
		shadow.new_oMap(tempMap);
		for (int i = 0; i < TotalY; i++) // ��ü�� ����� ���� �ӽ� �ʿ� ����
		{
			for (int j = 0; j < TotalX; j++)
			{
				tempMap[i][j] = shadow.get_oMap(i, j);
			}
		}
		shadow.down();

	}
	*this = shadow;

}
void Object::right()
{
	Object_shape tempshape;
	for (int i = 0; i <= 2; i++)
	{
		for (int j = 0; j <= 2; j++)
		{
			tempshape.shape_part[i][j] = shape.shape_part[i][j];
		}
	}

	// �� ���� ��Ȳ�� 1
	if ((oMap[Y - 1][X + 1] == 1) && (oMap[Y - 1][X + 2] >= 1))
	{
		return;
	}
	if ((oMap[Y][X + 1] == 1) && (oMap[Y][X + 2] >= 1))
	{
		return;
	}
	if ((oMap[Y + 1][X + 1] == 1) && (oMap[Y + 1][X + 2] >= 1))
	{
		return;
	}
	//������ ��Ȳ�� 2
	for (int i = 0; i <= 2; i++)
	{
		for (int j = 0; j <= 1; j++)
		{
			if ((shape.shape_part[i][j] == 1) && shape.shape_part[i][j + 1] == 2)
			{
				return;
			}

		}
	}


	// ��� �� �������� �� >=1 ��� �� �������� ������ �� >= 1 �� �� - ��翡 �߰�
	if (((oMap[Y - 1][X + 1] == 1) || (oMap[Y][X + 1] == 1) || (oMap[Y + 1][X + 1] == 1)) && ((oMap[Y - 1][X + 2] + oMap[Y][X + 2] + oMap[Y + 1][X + 2]) >= 1))
	{
		for (int i = 0; i <= 2; i++)  // ���� ��ü�� shape ���� ���� ����� ��
		{
			for (int j = 0; j <= 2; j++)
			{
				if (j >= 1)
				{
					if (shape.shape_part[i][j] == 2)
					{
						if (shape.shape_part[i][j - 1] == 0)
						{
							shape.shape_part[i][j - 1] = 2;
							shape.shape_part[i][j] = 0;
						}
					}
				}//
				else if (j == 0)
				{
					if (shape.shape_part[i][j] == 2)
					{
						oMap[Y + i - 1][X - 2] = 2;
						shape.shape_part[i][j] = 0;
					}
				}

			}
		}

		if ((oMap[Y - 1][X + 2] >= 1) && (oMap[Y - 1][X + 1] != 1))
		{
			shape.shape_part[0][2] = 2;
		}
		if ((oMap[Y][X + 2] >= 1) && (oMap[Y][X + 1] != 1))
		{
			shape.shape_part[1][2] = 2;
		}
		if ((oMap[Y + 1][X + 2] >= 1) && (oMap[Y + 1][X + 1] != 1))
		{
			shape.shape_part[2][2] = 2;
		}
		object_point.x += 1;
		//bug_fix_left += 2;
		return;
	}
	// ��� �� �������� �� <=0 ��� �� ���� ���� �� >= 1 �� �� - ����� ����������
	if (((oMap[Y - 1][X + 1] + oMap[Y][X + 1] + oMap[Y + 1][X + 1]) <= 0) && ((oMap[Y - 1][X + 2] + oMap[Y][X + 2] + oMap[Y + 1][X + 2]) >= 1))
	{
		for (int i = 0; i <= 2; i++)
		{
			for (int j = 1; j <= 2; j++)
			{
				shape.shape_part[i][j] = tempshape.shape_part[i][j - 1];
			}
		}
		for (int i = 0; i <= 2; i++)
		{
			shape.shape_part[i][0] = 0;
		}
		//life = 0 �� ���� �ʰ� �����ؾ� ��!!!!
		return;
	}


	if (((oMap[Y - 1][X + 2] + oMap[Y][X + 2] + oMap[Y + 1][X + 2]) == 0)) // �����ʿ� �ƹ��͵� ������ - ���������� ������
	{
		for (int i = 0; i <= 2; i++)  // ���� ��ü�� shape ���� ���� ����� ��
		{
			for (int j = 0; j <= 2; j++)
			{
				if (j >= 1)
				{
					if (shape.shape_part[i][j] == 2)
					{
						if (shape.shape_part[i][j - 1] == 0)
						{
							shape.shape_part[i][j - 1] = 2;
							shape.shape_part[i][j] = 0;
						}
					}
				}//
				else if (j == 0)
				{
					if (shape.shape_part[i][j] == 2)
					{
						oMap[Y + i - 1][X - 2] = 2;
						shape.shape_part[i][j] = 0;
					}
				}

			}
		}
		object_point.x += 1;
		//bug_fix_left += 2;
		return;
	}
}

int main() // ���� �Լ�
{
	int forMap[TotalY][TotalX] =  /*0->'��', 1->��*/ // �߾� 8 /* ��ü 1 ����� 0 �� 2 */
	{ { 2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2 },
	{ 2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2 },
	{ 2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2 },
	{ 2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2 },
	{ 2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2 },
	{ 2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2 },
	{ 2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2 },
	{ 2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2 },
	{ 2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2 },
	{ 2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2 },
	{ 2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2 },
	{ 2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2 },
	{ 2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2 },
	{ 2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2 },
	{ 2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2 },
	{ 2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2 },
	{ 2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2 },
	{ 2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2 },
	{ 2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2 },
	{ 2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2 },
	{ 2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2 },
	{ 2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2 },
	{ 2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2 },
	{ 2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2 },
	{ 2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2 },
	{ 2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2 },
	{ 2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2 },
	{ 2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2 },
	{ 2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2 },
	{ 2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2 }
	};

	Base Map;
	Map = forMap;
	srand(time(NULL)); // ���� ����
	Object* user; // ��ü ���

	cout << "The TeamProject by the 4Team\n";
	cout << "Key : ����� Space-bar";

	user = new Object; // ù ��ü
	user->new_oMap(MAP); // ���� ��ü�� ����
	while (1) // �ݺ�
	{
		for (int i = 0; i < TotalY - 1; i++) // �� �� ������ ���ֱ�
		{
			if (clearValue(MAP[i]))
			{
				for (int j = 1; j <= 15; j++)
				{
					if (MAP[i][j] == 2)
					{
						MAP[i][j] = 0;
					}
					for (int a = i; a >= 1; a--)
					{
						if (MAP[a][j] != 1 || MAP[a - 1][j] != 1)
						{
							MAP[a][j] = MAP[a - 1][j];
						}
					}

				}
				user->new_oMap(MAP); // ���� ��ü�� ����

			}
		}

		if (user->get_life() == 0) // ���� ������
		{
			for (int i = 0; i < TotalY; i++) // ���� ����� ��� ���ܰ� ����Ƿ� ���� ó��.
			{
				for (int j = 0; j < TotalX; j++)
				{
					MAP[i][j] = user->get_oMap(i, j);

					if (MAP[i][j] > 0) // ��ü�� ���� ������ �� ���ڸ� ��� 2�� ����
					{
						MAP[i][j] = 2;
					}

				}
			}

			display(MAP);

			for (int i = 1; i <= 3; i++)
			{
				for (int j = 7; j <= 9; j++)
				{
					if (MAP[i][j] == 2)
					{
						LIFE = 0;
						gotoxy(32, 14);
						cout << "------------GAME OVER-------------";
						gotoxy(66, TotalY);
						return 0;
					}
				}
			}

			user = new Object;
			(*user).new_oMap(MAP);
		}


		/*for (int i = 0; i < TotalY; i++) // ��ü�� ����� ���� ����
		{
		for (int j = 0; j < TotalX; j++)
		{
		MAP[i][j] = user->get_oMap(i, j);
		}
		}*/
		Map = *user; // ��ü�� ����� ���� ����

		display(MAP); // SPEED�ӵ� ���� ���.

		keyboard(*user, MAP); // Ű���� �Է� �ް� �Լ� ȣ��
		user->new_oMap(MAP); // ���� ��ü�� ����
		user->down(); // ��ü�� �Ʒ��� �̵�
		user->new_oMap(MAP); // ���� ��ü�� ����



	}

	return 0;
}