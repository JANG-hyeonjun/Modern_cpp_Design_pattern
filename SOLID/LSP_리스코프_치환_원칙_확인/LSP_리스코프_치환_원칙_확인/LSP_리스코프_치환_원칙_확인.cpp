// LSP_리스코프_치환_원칙_확인.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>


class Rectangle
{
protected:
	int width, height;
public:
	Rectangle(const int width,const int height) : width(width),height(height)
	{ }
	
	int get_width() { return width; }
	virtual void set_width(const int width) 
	{ 
		if (is_square() == false)
		{
			this->width = width;
		}
		else
		{
			this->width = height = width;
		}
	}
	int get_height() { return height; }
	virtual void set_height(const int height) 
	{ 
		if (is_square() == false)
		{
			this->height = height; 
		}
		else
		{
			this->height = width = height;
		}
	}

	int area(){ return width * height;}

	bool is_square() const
	{
		return width == height;
	}
};

//class Square : public Rectangle
//{
//public:
//	Square(int size) : Rectangle(size,size)
//	{ }
//	virtual void set_width(const int width) override
//	{
//		this->width = height = width;
//	}
//	virtual void set_height(const int height) override
//	{
//		this->height = width = height;
//	}
//};

void process(Rectangle& r)
{
	int w = r.get_width();
	r.set_height(10);
	// 이원칙에서 책에서 설명하고자 했던건 
	// Rectangle 참조형 객체를 받으니까 높이만 10으로 설정 되겠지 싶지만 
	//실질적으로는 가상함수는 현재 참조 하고 있는 객체의 메서드를 이용하기때문에
	// 다음과 같이 의도치 않은 것이 될수가 있다는 것이다.

	std::cout << "Expected Area = " << (w * 10) << ", got " << r.area() << std::endl;
}
//그래서 서브클래스를 만들지 않고 다음과 같이 팩토리 패턴을 이용한다. 

struct RectangleFactory
{
	static Rectangle create_rectangle(int w, int h);
	static Rectangle create_square(int size);
};

Rectangle RectangleFactory::create_rectangle(int w, int h)
{
	Rectangle R(w, h);
	return R;
}

Rectangle RectangleFactory::create_square(int size)
{
	Rectangle S(size, size);
	return S;
}

int main()
{
	
	RectangleFactory R_Factory;
	Rectangle Rectangle1 = R_Factory.create_rectangle(5, 10);
	std::cout << Rectangle1.area() << std::endl;
	Rectangle1.set_width(3);
	std::cout << Rectangle1.area() << std::endl;


	Rectangle Square1 = R_Factory.create_square(5);
	std::cout << Square1.area() << std::endl;
	Square1.set_width(3);
	std::cout << Square1.area() << std::endl;

	return 0;
}

