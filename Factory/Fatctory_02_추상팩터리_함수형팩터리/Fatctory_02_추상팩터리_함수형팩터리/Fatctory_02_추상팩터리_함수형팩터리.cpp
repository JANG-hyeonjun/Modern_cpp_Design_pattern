// Fatctory_02_추상팩터리_함수형팩터리.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <map>

class HotDrink
{
public:
    virtual void prepare(int volume) = 0;
};

class Tea : public HotDrink
{
    void prepare(int volume) override
    {
        std::cout << "Take tea bag, boil water,pour " << volume << "ml, add some lemon" << std::endl;
    }
};

class Coffee : public HotDrink
{
    void prepare(int volume) override
    {
        std::cout << "Grind some beans, boil water, pour " << volume << "ml,add creame, enjoy!" << std::endl;
    }
};
//음료를 추상화 한 개념 

//std::unique_ptr<HotDrink>make_drink(std::string type)
//{
//    std::unique_ptr<HotDrink> drink;
//    if (type == "tea")
//    {
//        drink = std::make_unique<Tea>();
//        drink->prepare(200);
//    }
//    else
//    {
//        drink = std::make_unique<Coffee>();
//        drink->prepare(50);
//    }
//    return drink;
//}
//이렇게 만들수도 있지만 차를 만드는 장비와 커피를 만드는 장비가 다르다면 

class HotDrinkFactory
{
public:
    virtual std::unique_ptr<HotDrink> make() const = 0;
};

class TeaFactory : public HotDrinkFactory
{
public:
    std::unique_ptr<HotDrink> make() const override
    {
        return std::make_unique<Tea>();
    }
};

class CoffeeFactory : public HotDrinkFactory
{
public:
    std::unique_ptr<HotDrink> make() const override
    {
        return std::make_unique<Coffee>();
    }
};

class DrinkFactory
{
    std::map < std::string, std::unique_ptr<HotDrinkFactory>> hot_factories;
public:
    DrinkFactory()
    {
        hot_factories["coffee"] = std::make_unique<CoffeeFactory>();
        hot_factories["Tea"] = std::make_unique<TeaFactory>();
    }

    std::unique_ptr<HotDrink> make_drink(const std::string& name)
    {
        auto drink = hot_factories[name]->make();
        drink->prepare(200);
        return drink;
    }
};

int main()
{
    DrinkFactory df;
    df.make_drink("Tea");

}

//2022-04-10 추상 팩터리 까지 작성 내일은 함수형 팩터리를 진행 해볼것  

