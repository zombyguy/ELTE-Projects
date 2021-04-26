#include <iostream>
#include <vector>

std::string to_string(std::vector<int> v);

int main()
{
  std::vector<int> v = {0};
  std::string s = to_string(v);
  std::cout << s << '\n';
  return 0;
}

std::string to_string(std::vector<int> v)
{
    std::string result;
    unsigned int skipped = 0;
    bool first = true;

    for ( int i = v.size() - 1; i >= 0 ; --i )
    {   
        if ( v[i] != 0 )
        {
            if ( v[i] < 0 )
            {
                result += std::to_string(v[i]);
            }
            else
            {
                if ( ! first )
                    result += "+";
                
                result += std::to_string(v[i]);
            }

            first = false;

            switch (i) 
            {
                case 0: result += ""; break;
                case 1: result += "x"; break;
                default: result += "x^" + std::to_string(i); break;
            }
        }
        else
        {
            ++skipped;
        }
    }

    if ( v.size() == skipped )
    {
        result += '0';
    }

    return result;
}
