#include <iostream>
#include <conio.h> // 키보드 입력을 위한 헤더파일
#include <time.h> // 난수를 위한 헤더파일
#include <Windows.h> // gotoxy 함수 정의할 때 필요
using namespace std;

// 키보드 입력값 정의 or etc
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
/* 클래스 모음 */
class Point // [y][x]!!! x, y 좌표 왼쪽 위부터 오른쪽, 아래 순서
{
public:
	int x;
	int y;
};
class Object_shape // 모양 클래스
{
public:
	int shape_part[3][3]; // 왼쪽 위부터 오른쪽, 아래 순서; 중앙은 [1][1]
};
/* 7가지 모양 정의 */
Object_shape Type[7] = {
	{ 0,1,0,0,1,0,0,1,0 }, // ㅣ 0
	{ 0,1,0,1,1,1,0,0,0 },  // ㅗ 1
	{ 0,1,0,0,1,0,0,1,1 }, // ㄴ 2
	{ 0,1,0,0,1,1,0,0,1 }, // 번개 3
	{ 1,0,0,1,1,1,0,0,0 }, // ㄴ 밑이 긴거 4
	{ 0,0,1,0,1,1,0,1,0, }, // 번개 반대 5
	{ 0,1,1,0,1,1,0,0,0 }, // 네모 6
};
class Object
{
private:
	bool life;
	int mode; // 0 ~ 6 까지
	Object_shape shape; // 모양
	Point object_point; // 객체 중앙의 포인트
	int oMap[TotalY][TotalX]; // 맵에서의 위치
							  //int bug_fix_left;
							  //int bug_fix_right;
public:
	Object(); // 생성자
	Object& operator= (const Object& right_class);
	void new_oMap(int tempMap[TotalY][TotalX]); // 맵에서의 좌표
												//accessor
	bool get_life() const; // return life
	int get_oMap(int i, int j) const; // return oMap[i][j]
									  //move
	void spin(); // 회전
	void down(); // 시간의 흐름에 따라 내려감
	void fest_down(int tempMap[TotalY][TotalX]); // 빠르게 내려감
	void left();
	void right();
};
class Base // 기본 맵 클래스
{
public:
	int field[TotalY][TotalX];
	Base& operator=(const Base& p);
	Base& operator=(int tempMap[TotalY][TotalX]);
	Base& operator=(const Object& o);
};
/* 전역변수, 함수 모음 */
int LIFE = 1;
void display(int temp_map[TotalY][TotalX]); // 화면 말끔히
void gotoxy(int x, int y); // 커서 위치 조정 함수
void keyboard(Object&, int tempMap[TotalY][TotalX]); // key입력값
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
					cout << "□";
				}
				else if (color == 1)
				{
					cout << "■";
				}
			}
			if (temp_map[i][j] == 0)
			{
				cout << "　";
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

		if (_kbhit()) // 입력되어있는 버퍼를 없애준다.
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
// Base 클래스의 멤버 함수들
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

// Object 클래스의 멤버 함수들
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
	this->mode = rightClass.mode; // 0 ~ 6 까지
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

	for (int i = 0; i < TotalY; i++) // 일단 복사.
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


	// 잔상남는 버그 방지 Down
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

	// 잔상남는 버그 방지 Left
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

	// 잔상남는 버그 방지 Right
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
	for (int i = 0; i < 3; i++) // 버그 방지
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

	// 정지하는 상황들 1
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
	// 정지하는 상황들 2
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

	// 모양 맨 밑의 합 >=1 모양 맨 밑의 밑의 합 >= 1 일 때 - 모양에 추가
	if (((oMap[Y + 1][X - 1] == 1) || (oMap[Y + 1][X] == 1) || (oMap[Y + 1][X + 1] == 1)) && ((oMap[Y + 2][X - 1] + oMap[Y + 2][X] + oMap[Y + 2][X + 1]) >= 1))
	{
		for (int i = 0; i <= 2; i++)  // 밖의 물체가 shape 영역 안을 통과할 때
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
	// 모양 맨 밑의 합 <=0 모양 맨 밑의 밑의 합 >= 1 일 때 - 모양을 아래로
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
		//life = 0 을 넣지 않고 리턴해야 됨!!!!
		return;
	}


	if (((oMap[Y + 2][X - 1] + oMap[Y + 2][X] + oMap[Y + 2][X + 1]) == 0)) // 밑에 아무것도 없을때 - 아래로 낙하
	{
		for (int i = 0; i <= 2; i++)  // 밖의 물체가 shape 영역 안을 통과할 때
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

	// 못 가는 상황들 1
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
	//못가는 상황들 2
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


	// 모양 맨 왼쪽의 합 >=1 모양 맨 왼쪽의 왼쪽의 합 >= 1 일 때 - 모양에 추가
	if (((oMap[Y - 1][X - 1] == 1) || (oMap[Y][X - 1] == 1) || (oMap[Y + 1][X - 1] == 1)) && ((oMap[Y - 1][X - 2] + oMap[Y][X - 2] + oMap[Y + 1][X - 2]) >= 1))
	{
		for (int i = 0; i <= 2; i++)  // 밖의 물체가 shape 영역 안을 통과할 때
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
	// 모양 맨 밑의 합 <=0 모양 맨 밑의 밑의 합 >= 1 일 때 - 모양을 아래로
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
		//life = 0 을 넣지 않고 리턴해야 됨!!!!
		return;
	}


	if (((oMap[Y - 1][X - 2] + oMap[Y][X - 2] + oMap[Y + 1][X - 2]) == 0)) // 왼쪽에 아무것도 없을때 - 왼쪽으로 움직임
	{
		for (int i = 0; i <= 2; i++)  // 밖의 물체가 shape 영역 안을 통과할 때
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
		for (int i = 0; i < TotalY; i++) // 객체가 적용된 맵을 임시 맵에 리턴
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

	// 못 가는 상황들 1
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
	//못가는 상황들 2
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


	// 모양 맨 오른쪽의 합 >=1 모양 맨 오른쪽의 왼쪽의 합 >= 1 일 때 - 모양에 추가
	if (((oMap[Y - 1][X + 1] == 1) || (oMap[Y][X + 1] == 1) || (oMap[Y + 1][X + 1] == 1)) && ((oMap[Y - 1][X + 2] + oMap[Y][X + 2] + oMap[Y + 1][X + 2]) >= 1))
	{
		for (int i = 0; i <= 2; i++)  // 밖의 물체가 shape 영역 안을 통과할 때
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
	// 모양 맨 오른쪽의 합 <=0 모양 맨 밑의 밑의 합 >= 1 일 때 - 모양을 오른쪽으로
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
		//life = 0 을 넣지 않고 리턴해야 됨!!!!
		return;
	}


	if (((oMap[Y - 1][X + 2] + oMap[Y][X + 2] + oMap[Y + 1][X + 2]) == 0)) // 오른쪽에 아무것도 없을때 - 오른쪽으로 움직임
	{
		for (int i = 0; i <= 2; i++)  // 밖의 물체가 shape 영역 안을 통과할 때
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

int main() // 메인 함수
{
	int forMap[TotalY][TotalX] =  /*0->'　', 1->□*/ // 중앙 8 /* 객체 1 빈공간 0 맵 2 */
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
	srand(time(NULL)); // 난수 랜덤
	Object* user; // 객체 용기

	cout << "The TeamProject by the 4Team\n";
	cout << "Key : ↑↓←→ Space-bar";

	user = new Object; // 첫 객체
	user->new_oMap(MAP); // 맵을 객체에 적용
	while (1) // 반복
	{
		for (int i = 0; i < TotalY - 1; i++) // 한 줄 꽉차면 없애기
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
				user->new_oMap(MAP); // 맵을 객체에 적용

			}
		}

		if (user->get_life() == 0) // 땅에 닿으면
		{
			for (int i = 0; i < TotalY; i++) // 땅에 닿았을 경우 예외가 생기므로 예외 처리.
			{
				for (int j = 0; j < TotalX; j++)
				{
					MAP[i][j] = user->get_oMap(i, j);

					if (MAP[i][j] > 0) // 객체가 땅에 닿으면 그 숫자를 모두 2로 변경
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


		/*for (int i = 0; i < TotalY; i++) // 객체가 적용된 맵을 리턴
		{
		for (int j = 0; j < TotalX; j++)
		{
		MAP[i][j] = user->get_oMap(i, j);
		}
		}*/
		Map = *user; // 객체가 적용된 맵을 리턴

		display(MAP); // SPEED속도 마다 출력.

		keyboard(*user, MAP); // 키보드 입력 받고 함수 호출
		user->new_oMap(MAP); // 맵을 객체에 적용
		user->down(); // 객체를 아래로 이동
		user->new_oMap(MAP); // 맵을 객체에 적용



	}

	return 0;
}