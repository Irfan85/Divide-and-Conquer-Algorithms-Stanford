#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>

// This method computes the sum of two large numbers represented as strings
std::string sum(std::string &firstNum, std::string &secondNum)
{
    // Determining the big and small number (In terms of length)
    long long minLength = firstNum.length();
    std::string *bigNum = &secondNum;
    std::string *smallNum = &firstNum;

    if (minLength > secondNum.length())
    {
        minLength = secondNum.length();
        bigNum = &firstNum;
        smallNum = &secondNum;
    }

    short carry = 0;
    std::stringstream sumStringStream{""};

    // Traverse till the last digit of the smaller number
    long long bigI = bigNum->length() - 1;
    for (long long smallI = minLength - 1; smallI >= 0; smallI--)
    {
        short digitSum = (bigNum->at(bigI) - '0') + (smallNum->at(smallI) - '0') + carry;
        carry = digitSum / 10;

        sumStringStream << (digitSum % 10);

        bigI--;
    }

    // Now, traverse till the last digit of the big number while adding the carry
    while (bigI >= 0)
    {
        short digitsum = (bigNum->at(bigI) - '0') + carry;
        carry = digitsum / 10;

        sumStringStream << (digitsum % 10);

        bigI--;
    }

    // Even after traversing the big number, if any carry is still remaining, simply append it to the result string
    if (carry > 0)
    {
        sumStringStream << carry;
    }

    std::string sumString = sumStringStream.str();
    // Reverse the result string to get the result of the summation
    std::reverse(sumString.begin(), sumString.end());

    return sumString;
}

// This function returns the max of the two numbers. We have to implement this since the standard library function doesn't work
// for out numbers. Currently not in use
std::string maximumNumber(std::string &firstNum, std::string &secondNum)
{
    long long firstStart = 0;
    while (firstNum[firstStart] == '0')
    {
        firstStart++;
    }

    long long secondStart = 0;
    while (secondNum[secondStart] == '0')
    {
        secondStart++;
    }

    std::string tempFirst = firstNum.substr(firstStart);
    std::string tempSecond = secondNum.substr(secondStart);

    if (tempFirst.length() > tempSecond.length())
    {
        return firstNum;
    }
    else if (tempFirst.length() < tempSecond.length())
    {
        return secondNum;
    }
    else
    {
        // Lengths of both strings are equal in this case
        for (int i = 0; i < tempFirst.length(); i++)
        {
            if ((tempFirst[i] - '0') > (tempSecond[i] - '0'))
            {
                return firstNum;
            }
            else if ((tempFirst[i] - '0') < (tempSecond[i] - '0'))
            {
                return secondNum;
            }

            // If both digits are equal, continue
        }

        // Program will reach here if both numbers are equal. In that case, just return the first one
        return firstNum;
    }
}

// This method computes the substitution of two large numbers represented as strings
// We're assuming 'firstNum' is always >= 'secondNum' for simplicity
std::string sub(std::string &firstNum, std::string &secondNum)
{
    long long maxLength = std::max(firstNum.length(), secondNum.length());

    // Filling '0's in front of the small number to make sure both numbers are of the same length
    while (firstNum.length() < maxLength)
    {
        firstNum = "0" + firstNum;
    }

    while (secondNum.length() < maxLength)
    {
        secondNum = "0" + secondNum;
    }

    std::stringstream subStringStream{""};

    for (long long i = firstNum.length() - 1; i >= 0; i--)
    {
        short upperDigit = firstNum.at(i) - '0';
        short lowerDigit = secondNum.at(i) - '0';

        // If 'upperDigit' is smaller, we have to get a carry
        if (upperDigit < lowerDigit)
        {
            // Getting carry from a non zero digit. Keep looking to the left for a non zero digit to get a carry
            // Since, we're assuming the 'firstNum' is always bigger, we always should be able to get a carry if needed.
            // Hence, we don't have to worry about scenarios where no carry can be fetched.
            long long j = i - 1;
            while (j >= 0)
            {
                if (firstNum.at(j) != '0')
                {
                    firstNum[j] = ((firstNum[j] - '0') - 1) + '0';
                    upperDigit += 10;
                    // Since we got the carry, we don't have to continue
                    break;
                }

                // Turn all the '0's we encounter wile searching for carry to '9'. (Carry propagation)
                firstNum[j] = '9';
                j--;
            }
        }

        subStringStream << (upperDigit - lowerDigit);
    }

    std::string subString = subStringStream.str();
    // Reverse the result string to get the result of the summation
    std::reverse(subString.begin(), subString.end());

    return subString;
}

// This function implements the karatsuba's multiplication algorithm
std::string karatsuba(std::string &x, std::string &y)
{
    // Base case: If the two numbers are small like <= 2 digits, just multiply them in the regular way
    if (x.length() <= 2 && y.length() <= 2)
    {
        return std::to_string(std::atoi(x.c_str()) * std::atoi(y.c_str()));
    }

    // In order to use this algorithm, we've to make sure both numbers are of equal length
    long long maxLength = std::max(x.length(), y.length());

    // Filling '0's in front of the small number to make sure both numbers are of the same length
    while (x.length() < maxLength)
    {
        x = "0" + x;
    }

    while (y.length() < maxLength)
    {
        y = "0" + y;
    }

    std::string a = x.substr(0, (x.length() / 2));
    std::string c = y.substr(0, (y.length() / 2));
    // Step1: Recursively compute 'a*c'
    std::string ac = karatsuba(a, c);

    std::string b = x.substr((x.length() / 2));
    std::string d = y.substr((y.length() / 2));
    // Step2: Recursively compute 'b*d'
    std::string bd = karatsuba(b, d);

    // TODO: The gauss' trick is yet to implement. This algorithm is currently using the 4 recursion method
    // Step3: Recursively compute '(a+b)*(c+d)' using gauss' trick
    // std::string aPlusB = sum(a, b);
    // std::string cPlusD = sum(c, d);
    // std::string m = karatsuba(aPlusB, cPlusD);
    // // Now remove previously computed 'a*c' and 'b*d' from 'm' to get 'a*d + b*c'
    // std::string acPlusBD = sum(ac, bd);
    // std::string maxOP = maximumNumber(m, acPlusBD);
    // std::string minOP = m;
    // if (maxOP == m)
    // {
    //     minOP = acPlusBD;
    // }
    // // std::string adPlusBC = sub(maxOP, minOP);

    // Recursively compute a*d and b*c and determine a*d + b*c
    std::string ad = karatsuba(a, d);
    std::string bc = karatsuba(b, c);
    std::string adPlusBC = sum(ad, bc);

    // Put the 3 pieces together
    // Append n zeros at the end of ac
    for (int i = 0; i < x.length(); i++)
    {
        ac.push_back('0');
    }

    // Append n/2 zeros at the end of adPlusBC
    for (int i = 0; i < (x.length() / 2); i++)
    {
        adPlusBC.push_back('0');
    }

    // Adding them
    std::string result = sum(ac, adPlusBC);
    result = sum(result, bd);

    return result;
}

int main()
{
    std::string x = "3141592653589793238462643383279502884197169399375105820974944592";
    std::string y = "2718281828459045235360287471352662497757247093699959574966967627";

    // std::string x = "1234";
    // std::string y = "10";

    std::string result = karatsuba(x, y);
    std::cout << result << std::endl;

    return 0;
}