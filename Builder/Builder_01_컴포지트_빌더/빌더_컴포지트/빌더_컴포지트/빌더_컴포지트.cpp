// 빌더_컴포지트.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <sstream>
#include <string>

using namespace std;

class PersonAddressBuilder;
class PersonJobBuilder;
class PersonBuilder;
class PersonBuilderBase;

class Person
{
private:
	//주소
	string street_address, post_code, city;

	//직업 관련 
	string company_name, position;
	int annual_income = 0;

	Person() {}

public:
	~Person(){}

	static PersonBuilder create();

	Person(Person&& other): street_address(other.street_address),post_code(other.post_code),
	city(other.city),company_name(other.company_name),position(other.position),annual_income(other.annual_income)
	{}

	//대입 연산자를 오버로딩한 복사 생성자
	Person& operator=(Person&& other)
	{
		if (this == &other)
		{
			return *this;
		}
		else
		{
			street_address = move(other.street_address);
			post_code = move(other.post_code);
			city = move(other.city);
			company_name = move(other.company_name);
			position = move(other.position);
			annual_income = move(other.annual_income);
			return *this;
		}
	}

	friend ostream& operator<<(ostream& os, const Person& obj)
	{
		os << "street_address: " << obj.street_address << std::endl;
		os << "post_code: " << obj.post_code << std::endl;
		os << "city: " << obj.city << std::endl;
		os << "company_name: " << obj.company_name << std::endl;
		os << "position: " << obj.position << std::endl;
		os << "annual_income: " << obj.annual_income << std::endl;
		
		return os;
	}
	friend class PersonJobBuilder;
	friend class PersonAddressBuilder;
	friend class PersonBuilder;
};

class PersonBuilderBase
{
protected:
	Person* person;
	explicit PersonBuilderBase(Person* person):person(person)
	{ }

public:
	operator Person() const
	{
		return move(*person);
	}

	PersonAddressBuilder lives() const;
	PersonJobBuilder works() const;
};

class PersonBuilder : public PersonBuilderBase
{
public:
	PersonBuilder(Person* p) : PersonBuilderBase(p)
	{ }
};

class PersonAddressBuilder : public PersonBuilderBase
{
	typedef PersonAddressBuilder Self;
public:
	explicit PersonAddressBuilder(Person* person) : PersonBuilderBase(person)
	{ }

	Self& at(string street_address)
	{
		person->street_address = street_address;
		return *this;
	}

	Self& with_postcode(string post_code)
	{
		person->post_code = post_code;
		return *this;
	}

	Self& in(string city)
	{
		person->city = city;
		return *this;
	}
};

class PersonJobBuilder : public PersonBuilderBase
{
	typedef PersonJobBuilder Self;

public:
	explicit PersonJobBuilder(Person* person): PersonBuilderBase(person)
	{}

	Self& at(string company_name)
	{
		person->company_name = company_name;
		return *this;
	}

	Self& as_a(string position)
	{
		person->position = position;
		return *this;
	}

	Self& earning(int annual_income)
	{
		person->annual_income = annual_income;
		return *this;
	}
};

PersonBuilder Person::create()
{
	return PersonBuilder(new Person);
}

PersonAddressBuilder PersonBuilderBase::lives() const
{
	return PersonAddressBuilder(person);
}

PersonJobBuilder PersonBuilderBase::works() const
{
	return PersonJobBuilder(person);
}




int main()
{
	Person p = Person::create().lives().at("123 London Road").with_postcode("SW1 1GB").in("London")
		.works().at("program soft").as_a("consultant").earning(10e6);
	cout << p << endl;

	//위에 연산자 오버로딩 ()왜 만들었냐 생각할수 있지만 = 는 ()과 같다.
	//거기서 R-value로 바꾸어 메모리를 절약하는 것 

	return 0;
}

