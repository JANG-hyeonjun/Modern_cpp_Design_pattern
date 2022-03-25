#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <memory>

//웹페이지를 그리기 위해 2개의 컴포넌트를 생성해야 한다고 하면 다음과 같이 만들수 있다.


class HtmlBuilder;

class HtmlElement
{
public:
	std::string name;
	std::string text;
	std::vector<HtmlElement> elements;
	const size_t indent_size = 2;

	//API 사용 의도 알려주기

	std::string  str(int indent = 0) const
	{
		std::ostringstream oss;
		std::string i(indent_size * indent, ' ');
		oss << i << "<" << name << ">" << std::endl;
		if (text.size() > 0)
			oss << std::string(indent_size * (indent + 1), ' ') << text << std::endl;

		for (const auto& e : elements)
		{
			//oss << (std::string)"1!!!!!" << std::endl;
			oss << e.str(indent + 1);
		}

		oss << i << "</" << name << ">" << std::endl;
		return oss.str();
	}


	static std::unique_ptr<HtmlBuilder> build(std::string root_name) 
	{
		
		return std::make_unique<HtmlBuilder>(root_name);
	}
	HtmlElement() { }
	HtmlElement(const std::string& name, const std::string& text) : name(name), text(text){ }

};

//단순 빌더 패턴 2022.03.23
//class HtmlBuilder
//{
//public:
//	HtmlElement root;
//
//	HtmlBuilder(std::string root_name)
//	{
//		root.name = root_name;
//	}
//
//	void add_child(std::string child_name, std::string child_text)
//	{
//		HtmlElement e(child_name, child_text);
//		root.elements.emplace_back(e);
//	}
//
//	std::string str()
//	{
//		return root.str();
//	}
//};

//흐름식 빌더 패턴 2022.03.25
//만약 빌더 add_child 함수를 자기 자신의 클래스를 참조로 리턴 되게 하면 꼬리를 무는 흐름식 인터페이스가 가능하다.
class HtmlBuilder 
{
public:
	HtmlElement root;

	operator HtmlElement() const
	{ 
		return root; 
	}

	HtmlBuilder(std::string root_name) 
	{
		root.name = root_name;
	}

	HtmlBuilder& add_child(std::string child_name, std::string child_text)
	{
		HtmlElement e(child_name, child_text);
		root.elements.emplace_back(e);
		return *this;
	}

	//포인터로도 가능 이는 개발자의 자유이다.
	HtmlBuilder* add_child2(std::string child_name, std::string child_text)
	{
		HtmlElement e(child_name, child_text);
		root.elements.emplace_back(e);
		return this;
	}


	std::string str()
	{
		return root.str();
	}
};



int main()
{

	//std::string words[] = { "hello", "world" };
	//std::ostringstream oss;

	/*oss << "<ul>";
	for (auto w : words)
	{
		oss << " <li>" << w << "</li>";
	}
	oss << "</ul>";

	printf(oss.str().c_str());
	
	std::cout << std::endl;
	*/
	//이러한 구조는 만약 앞에점을 찍거나 순서대로 번호를 매겨야 한다면 어떻게 수정? -> 상당히 힘들다 
	//그래서 class를 한번 정의해보면 다음과 같다. 

	/*HtmlElement list{ "ul","" };

	for (auto w : words)
	{
		list.elements.emplace_back(HtmlElement{"li",w});
	}

	printf(list.str().c_str());*/

	//단순 빌더 패턴 사용 
	/*HtmlBuilder builder("ul");
	builder.add_child("li", "hello");
	builder.add_child("li", "world");
	std::cout << builder.str() << std::endl;*/

	//흐름식 빌더 패턴 사용 
	/*HtmlBuilder builder("ul");
	builder.add_child("li", "hello").add_child("li", "world");
	std::cout << builder.str() << std::endl;

	HtmlBuilder* builder2 = new HtmlBuilder("ul");
	builder2->add_child2("li", "hello")->add_child2("li", "world");
	std::cout << builder2->str() << std::endl;*/

	//의도를 알려주기 
	auto builder2 = HtmlElement::build("ul");
	builder2->add_child2("li", "hello")->add_child2("li", "world");
	std::cout << builder2->str() << std::endl;

	return 0;
}