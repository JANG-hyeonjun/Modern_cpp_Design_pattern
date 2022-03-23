#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <memory>

//���������� �׸��� ���� 2���� ������Ʈ�� �����ؾ� �Ѵٰ� �ϸ� ������ ���� ����� �ִ�.


class HtmlBuilder;

class HtmlElement
{
public:
	std::string name;
	std::string text;
	std::vector<HtmlElement> elements;
	const size_t indent_size = 2;

	HtmlElement() { }
	HtmlElement(const std::string& name, const std::string& text) : name(name), text(text){ }

	std::string  str(int indent = 0) const
	{
		std::ostringstream oss;
		std::string i(indent_size * indent, ' ');
		oss << i << "<" << name << ">" << std::endl;
		if (text.size() > 0)
			oss << std::string(indent_size * (indent + 1), ' ') << text <<std::endl;

		for (const auto& e : elements)
		{
			oss << (std::string)"1!!!!!" << std::endl;
			oss << e.str(indent + 1);
		}
	
		oss << i << "</" << name << ">" << std::endl;
		return oss.str();
	}
	
	/*static std::unique_ptr<HtmlBuilder> build(std::string root_name)
	{
		return std::make_unique<HtmlBuilder>(root_name);
	}*/

};

//�ܼ� ���� ���� 2022.03.23
class HtmlBuilder
{
public:
	HtmlElement root;

	HtmlBuilder(std::string root_name)
	{
		root.name = root_name;
	}

	void add_child(std::string child_name, std::string child_text)
	{
		HtmlElement e(child_name, child_text);
		root.elements.emplace_back(e);
	}

	std::string str()
	{
		return root.str();
	}
};


int main()
{

	std::string words[] = { "hello", "world" };
	std::ostringstream oss;

	/*oss << "<ul>";
	for (auto w : words)
	{
		oss << " <li>" << w << "</li>";
	}
	oss << "</ul>";

	printf(oss.str().c_str());
	
	std::cout << std::endl;
	*/
	//�̷��� ������ ���� �տ����� ��ų� ������� ��ȣ�� �Űܾ� �Ѵٸ� ��� ����? -> ����� ����� 
	//�׷��� class�� �ѹ� �����غ��� ������ ����. 

	/*HtmlElement list{ "ul","" };

	for (auto w : words)
	{
		list.elements.emplace_back(HtmlElement{"li",w});
	}

	printf(list.str().c_str());*/

	//�ܼ� ���� Ŭ���� ��� 
	HtmlBuilder builder("ul");
	builder.add_child("li", "hello");
	builder.add_child("li", "world");
	std::cout << builder.str() << std::endl;

	


	return 0;
}