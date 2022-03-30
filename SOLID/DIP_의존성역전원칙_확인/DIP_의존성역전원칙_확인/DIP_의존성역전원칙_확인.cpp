// DIP_의존성역전원칙_확인.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>


class Car
{
public:
    virtual void Drive() = 0;
};

class Avante : public Car
{
public:
    Avante() {}
    virtual void Drive() { std::cout << "Drive a Avante" << std::endl; }
};

class Sonata : public Car
{
public:
    Sonata() {}
    virtual void Drive() { std::cout << "Drive a sonata" << std::endl; }
};

class Driver
{
public:
    Driver(const std::shared_ptr<Car>& car) : mCar(car) { }
    void Drive() { mCar->Drive();}

private:
    std::shared_ptr<Car> mCar;
};


int main()
{
    Driver Tom(std::static_pointer_cast<Car>(std::make_shared<Avante>()));
    Tom.Drive();

    Driver Alice(std::static_pointer_cast<Car>(std::make_shared<Sonata>()));
    Alice.Drive();


    return 0;
}

