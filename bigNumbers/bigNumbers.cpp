#include <iostream>
#include <vector>
#include <string>
typedef long long ll;

class BigInteger {

public:
    // конструктор стандартный
    BigInteger(std::string str) 
    {
        if (str.length() == 0)
        {
            throw std::runtime_error("Error! Number can't be empty!");
        }
        else
        {            
            if (str.length() != 0)
            {
                // запишем числа в вектор в обратном порядке
                // для простоты арифметических операций
                for (ll i = str.length() - 1; i >= 0; --i)
                {
                    if (isdigit(str[i]))
                    {
                        _vecInt.push_back(str[i] - '0');
                    }
                    else
                    {
                        throw std::runtime_error("Error! String contains symbol other then number!");
                    }
                }
                //_vecInt.shrink_to_fit();
            }
            else
            {
                throw std::runtime_error("Error! Symbol '-' can't be a number!");
            }
        }
    }

    // конструтор перемещения
    BigInteger(BigInteger&& other)
    {
        _vecInt = std::move(other._vecInt);
    }

    // перемещающий оператор присваивания
    BigInteger& operator=(BigInteger&& other)
    {
        if (this == &other)
        {
            return *this;
        }

        _vecInt = std::move(other._vecInt);
        return *this;

        // BigInteger(other); // почему так нельзя??
    }

    // оператор сложения двух больших чисел
    BigInteger operator+(const BigInteger& right) const
    {
        std::vector<uint8_t> vecTemp;
        uint8_t extra = 0;
        auto itLeft = _vecInt.begin();
        auto itRight = right._vecInt.begin();
        
        while (itLeft != _vecInt.end() && itRight != right._vecInt.end())
        {
            uint8_t sum = *itLeft + *itRight + extra;
            int curNum = sum % 10; // получаем вторую цифру
            vecTemp.push_back(curNum);
            extra = sum / 10;
            ++itLeft;
            ++itRight;
        }

        while (itLeft != _vecInt.end())
        {
            vecTemp.push_back(*itLeft + extra);
            extra = 0;
            ++itLeft;
        }

        while (itRight != right._vecInt.end())
        {
            vecTemp.push_back(*itRight + extra);
            extra = 0;
            ++itRight;
        }

        std::string strRes;
        for (auto it = vecTemp.rbegin(); it != vecTemp.rend(); ++it)
        {
            strRes += std::to_string(*it);
        }
        return BigInteger(strRes);
    }

    // оператор умножения на число
    BigInteger operator*(const int num)
    {
        std::vector<uint8_t> vecTemp;
        uint8_t extra = 0;
        auto itLeft = _vecInt.begin();

        while (itLeft != _vecInt.end())
        {
            uint8_t sum = *itLeft * num + extra;
            int curNum = sum % 10; // получаем вторую цифру
            vecTemp.push_back(curNum);
            extra = sum / 10;
            ++itLeft;
        }

        if (extra != 0)
        {
            vecTemp.push_back(extra);
        }

        std::string strRes;
        for (auto it = vecTemp.rbegin(); it != vecTemp.rend(); ++it)
        {
            strRes += std::to_string(*it);
        }
        return BigInteger(strRes);
    }
    friend std::ostream& operator<<(std::ostream& out, const BigInteger& number);

private:
    std::vector<uint8_t> _vecInt;
};

std::ostream& operator<<(std::ostream& out, const BigInteger& number)
{
    for (auto it = number._vecInt.rbegin(); it != number._vecInt.rend(); ++it)
    {
        out << std::to_string(*it);
    }
    return out;
}

int main()
{
    try
    {
        auto number1 = BigInteger("114575");
        auto number2 = BigInteger("78524");
        auto sum = number1 + number2;
        std::cout << "Result of sum: " << sum << std::endl; // 193099
        auto mult = number1 * 7;
        std::cout << "Result of multiplication: " << mult << std::endl; // 802025
    }
    catch (std::runtime_error& err)
    {
        std::cout << err.what() << std::endl;
    }
}
