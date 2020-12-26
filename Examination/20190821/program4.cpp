#include <fstream>
#include <map>
#include <string>
#include <iostream>
#include <vector>

/* Testcase:

achieve my advise -> put my tell
my extraordinary walk is gradual -> my amazing move is slow
the evil diagram -> the ugly plan
I consider a microscopic cloak to be irritable -> I think a little hide to be moody

 */

int main()
{
    // 1. open SYNONYMS
    std::ifstream synonyms;
    synonyms.open("SYNONYMS.txt");
    // 2. read the synonyms into the synonyms map
    std::map<std::string, std::string> synonym_map;

    std::string line{};
    // while(std::getline(synonyms, line))
    // {

    //     synonym_map::insert()

    // }
    while (synonyms >> line)
    {
        std::pair<std::string, std::string> pair;
        std::string first{};
        std::string second{};
        bool f{true};

        for (auto ch : line)
        {
            if (ch != '=' && f)
            {
                first.push_back(ch);
            }
            else if (ch == '=')
            {
                f = false;
            }
            else if (!f)
            {
                second.push_back(ch);
            }
        }
        pair.first = first;
        pair.second = second;
        synonym_map.insert(pair);
    }
    for (auto pair : synonym_map)
    {
        std::cout << pair.first << "  " << pair.second << std::endl;
    }
    // 3. read text from cin into the vector words, replacing each
    //    possible word, leaving the rest as-is
    std::vector<std::string> words{};
    std::string word{};
    // NOTE: you need to push "Ctrl + d" to exit this loop.
    while(std::cin >> word)
    {
        words.push_back(word);
    }
    for (unsigned i{}; i < words.size(); ++i)
    {
        if (synonym_map.count(words[i])) {

            auto it = synonym_map.find(words[i]);
            words[i] = it->second;
        }
    }
    
    // 4. print the text stored in words
    for (auto a : words)
    {
        std::cout << a << std::endl;
    }
}
