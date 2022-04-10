// Factory_02_팩토리메서드_팩터리.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>

//팩터리 메서드 
//class Point
//{
//public:
//	float x, y;
//
//protected:
//	Point(const float x,const float y): x(x),y(y)
//	{ }
//
//public:
//	static Point NewCartesian(float x, float y)
//	{
//		return {x, y};
//	}
//	static Point NewPolar(float r, float theta)
//	{
//		return { r * cos(theta) , r * sin(theta) };
//	}
//	//여기서 이 static 함수들을 팩터리 메서드라고 불린다.
//	friend std::ostream& operator<<(std::ostream& os, const Point& pos);
//};
//
//std::ostream& operator<<(std::ostream& os, const Point& pos)
//{
//	os << pos.x << " , " << pos.y << std::endl;
//	return os;
//}

////////////팩터리///////////// 
//class Point
//{
//public:
//	float x, y;
//	friend class PointFactory;
//	friend std::ostream& operator<<(std::ostream& os, const Point& pos);
//private:
//	Point(float x, float y): x(x),y(y)
//	{ }
//};
//
//
//std::ostream& operator<<(std::ostream& os, const Point& pos)
//{
//	os << pos.x << " , " << pos.y << std::endl;
//	return os;
//}
//
//class PointFactory
//{
//public:
//	static Point NewCartesian(float x, float y)
//	{
//		return Point{ x,y };
//	}
//	static Point Newpolar(float r, float theta)
//	{
//		return Point{ r * cos(theta), r * sin(theta) };
//	}
//};

//내부팩터리 
class Point
{
private:
	Point(float x,float y):x(x),y(y)
	{ }
	class PointFactory
	{
	private:
		PointFactory() { }

	public:
		static Point NewCartesian(float x,float y)
		{
			return { x,y };
		}
		static Point NewPolat(float r, float theta)
		{
			return { r * sin(theta), r * cos(theta)};
		}
	};
public:
	float x, y;
	static PointFactory Factory;
	friend std::ostream& operator<<(std::ostream& os, const Point& pos);
};
//클래스에서 정적 멤버란 클래스에는 속하지만,객체 별로 할당 되지 않고 클래스의 모든객체가 공유하는 멤버를 의미한다. 
//멤버 변수가 정적(static)으로 선언되면, 해당 클래스의 모든 객체에 대해 하나의 데이터만이 유지 관리 된다. 

//정적 맴버 변수에도 클래스의 멤버의 접근 제한 규칙이 적용되는 것이 중요 클래스의 멤버 함수나 프렌드만이 접근할수 있다. 
//하지만 정적 멤버 변수를 외부에서도 접근할 수 있게 하고 싶으면, 정적 멤버 변수를 public으로 선언 하면 된다. 

std::ostream& operator<<(std::ostream& os, const Point& pos)
{
	os << pos.x << " , " << pos.y << std::endl;
	return os;
}

int main()
{
	//팩터리 메서드를 이용한 인스턴스 생성 
	/*auto p = Point::NewPolar(5, M_PI_4);
	std::cout << p;*/
	

	//팩터리를 이용한 인스턴스 생성 
	/*auto my_point = PointFactory::NewCartesian(3, 4);
	std::cout << my_point;*/

	//내부 팩터리를 이용한 인스턴스 생성 
	//auto pp = Point::PointFactory::NewCartesian(2, 3);
	//::을 이용해 생성을 하고싶다면 위에 팩터리를 public으로 빼면 된다. 

	//만약 안에 있는 static 팩터리를 사용하고 싶다면 
	auto pp = Point::Factory.NewCartesian(2, 3);
	std::cout << pp;
	//이런식으로 진행되는것 그럼 해당 내부 팩터리는 대체 왜쓰는것이냐 사용자 Point::했을때 나오기를 바라는 느낌으로 
	//기대할수 있는것 

	//만약 난 Point가 두번 나오는것도 맘에 안든다면 typedef PointFactory Factory이런식으로 변경가능 


	return 0;
}

