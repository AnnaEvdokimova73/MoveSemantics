﻿#include <iostream>
#include <vector>

void moveVectors(std::vector<std::string>& vecLeft, std::vector<std::string>& vecRight)
{
    std::vector<std::string> temp = std::move(vecLeft);
    vecLeft = std::move(vecRight);
    vecRight = std::move(temp);
}

int main()
{
    std::vector <std::string> one = { "test_string1", "test_string2" };
    std::vector <std::string> two;
    std::cout << "Before move semantics:\n";
    std::cout << "Vector one: ";
    std::cout << (!one.empty() ? one.at(0) + " " + one.at(1) : "vector one is empty") << std::endl;
    std::cout << "Vector two: ";
    std::cout << (!two.empty() ? two.at(0) + " " + two.at(1) : "vector two is empty") << std::endl;
    moveVectors(one, two);
    std::cout << "After move semantics:\n";
    std::cout << "Vector one: ";
    std::cout << (!one.empty() ? one.at(0) + " " + one.at(1) : "vector one is empty") << std::endl;
    std::cout << "Vector two: ";
    std::cout << (!two.empty() ? two.at(0) + " " + two.at(1) : "vector two is empty") << std::endl;
}
