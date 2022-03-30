// 빌더패턴_그루비.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <vector>

struct Tag
{
    std::string name;
    std::string text;
    std::vector<Tag> children;
    std::vector<std::pair < std::string, std::string>> attributes;
    
    friend std::ostream& operator<<(std::ostream& os, const Tag& tag)
    {
        os << "<" << tag.name;

        for (const auto& att : tag.attributes)
        {
            os << " " << att.first << "=\"" << att.second << "\"";
        }
    
        if (tag.children.size() == 0 && tag.text.length() == 0)
        {
            os << "\>" << std::endl;
        }
        else
        {
            os << ">" << std::endl;

            if (tag.text.length())
            {
                os << tag.text << std::endl;
            }

            for (const auto& child : tag.children)
            {
                os << child;
                //여기서 재귀를 사용해서 한번자 연산자 오버로딩을 호출한것이다. 
            }
            os << "<\\" << tag.name << ">" << std::endl;
        }
        return os;
    }

protected:
    Tag(const std::string& name, const std::string& text) : name(name),text(text)
    { }

    Tag(const std::string& name, const std::vector<Tag>& children) : name(name),children(children)
    { }
};

struct P : Tag
{
    explicit P(const std::string& text) : Tag("p", text)
    { }
    P(std::initializer_list<Tag> children) : Tag("p",children)
    { }
};

struct IMG : Tag
{
    explicit IMG(const std::string& url) : Tag("img", "")
    {
        attributes.emplace_back(make_pair("src", url));
    }
};

int main()
{   
    std::cout << P{ IMG{"https://pokemon.com/pikachu.png"} } << std::endl;
    return 0;
}

