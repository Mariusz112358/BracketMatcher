#include "bracketmatcher.h"

#include <algorithm>
#include <string.h>
#include <unordered_map>
#include <iostream>
#include <stack>

BracketMatcher::BracketMatcher() {}

bool recursiveProcess(const char *pattern, int &index, const char open_bracket)
{
    const auto isOpenBracket = [](const char c) -> bool {
        return c == '(' || c == '{' || c == '[';
    };
    const auto isCloseBracket = [](const char c) -> bool {
        return c == ')' || c == '}' || c == ']';
    };
    const auto isMatchingBracket = [](const char open, const char close) -> bool {
        if (open == '(') {
            return (close == ')');
        }
        else if (open == '{') {
            return (close == '}');
        }
        else if (open == '[') {
            return (close == ']');
        }

        return false;
    };

    const auto len = strlen(pattern);
    if (len == 0) {
        return true;
    }

    if (index < 0 || index >= len) {
        return false;
    }

    do {
        const auto bracket = pattern[index];
        if (isOpenBracket(bracket)) {
            index++;
            if (recursiveProcess(pattern, index, bracket)) {
                index++;
                continue;
            }
            return false;
        }
        else if (isCloseBracket(bracket)) {
            return isMatchingBracket(open_bracket, bracket);
        }

        index++;
    } while (index < len);

    return open_bracket == '\0';
}

bool BracketMatcher::matchWithRecursive(const char *pattern)
{
    int index = 0;
    return recursiveProcess(pattern, index, '\0');
}

bool BracketMatcher::matchWithStack(const char *pattern)
{
    const auto isOpenBracket = [](const char c) -> bool {
        return c == '(' || c == '{' || c == '[';
    };
    const auto isCloseBracket = [](const char c) -> bool {
        return c == ')' || c == '}' || c == ']';
    };
    const auto isMatchingBracket = [](const char open, const char close) -> bool {
        if (open == '(') {
            return (close == ')');
        }
        else if (open == '{') {
            return (close == '}');
        }
        else if (open == '[') {
            return (close == ']');
        }

        return false;
    };

    const auto len = strlen(pattern);

    std::stack<char> opened_brackets;
    for (auto i = 0; i < len; ++i) {
        const auto bracket = pattern[i];
        if (isOpenBracket(bracket)) {
            opened_brackets.push(bracket);
        }
        else if (isCloseBracket(bracket)) {
            if (opened_brackets.empty() == false && isMatchingBracket(opened_brackets.top(), bracket)) {
                opened_brackets.pop();
            }
            else {
                return false;
            }
        }
    }

    return opened_brackets.empty();
}

bool BracketMatcher::matchWithProcessedArray(const char *pattern)
{
    std::string testStr(pattern);
    if (testStr.empty()) {
        return true;
    }

    if (testStr.size() < 2) {
        return false;
    }

    const std::unordered_map<char, char> closeOpenMap{
        {')', '('},
        {']', '['},
        {'}', '{'}
    };

    std::vector<char> openings;
    openings.reserve(closeOpenMap.size());
    std::vector<char> closing;
    closing.reserve(closeOpenMap.size());
    for (auto& it: closeOpenMap) {
        closing.push_back(it.first);
        openings.push_back(it.second);
    }

    int firstPos = 0;
    std::vector<bool> processedPart(testStr.size(), false);
    for (int secondPos = 1; secondPos < testStr.size(); ++secondPos) {
        if (firstPos >= secondPos) {
            std::cout << "Something went wrong:" << firstPos << ", " << secondPos << std::endl;
            break;
        }

        const char firstCharacter = testStr[firstPos];
        const bool isFirstOpen = contains(openings, firstCharacter);
        const bool isFirstClose = contains(openings, firstCharacter);

        const char secondCharacter = testStr[secondPos];
        const bool isSecondOpen = contains(openings, secondCharacter);
        const bool isSecondClose = contains(closing, secondCharacter);

        std::cout << "Iteration: " << secondPos << std::endl;
        std::cout << "Test1: " << firstCharacter << ", " << firstPos << ", " << isFirstOpen << std::endl;
        std::cout << "Test2: " << secondCharacter << ", " << secondPos << ", " << isSecondOpen << ", " << isSecondClose << std::endl;

        if (isFirstOpen == false) {
            return false;
        } else if (isSecondOpen) {
            firstPos = evaluateNextPosition(processedPart, ++firstPos);
        } else {
            if (isSecondClose) {
                const auto matchingOpenCharacter = closeOpenMap.at(secondCharacter);
                if (matchingOpenCharacter == firstCharacter) {
                    processedPart[firstPos] = true;
                    processedPart[secondPos] = true;
                    firstPos = evaluatePreviosPosition(processedPart, --firstPos);
                    if (firstPos == (secondPos + 1)) {
                        ++secondPos;
                    }
                } else {
                    return false;
                }
            }
        }
    }

    return allProcessed(processedPart);
}

bool BracketMatcher::allProcessed(const std::vector<bool> &processedPart) const
{
    return std::all_of(processedPart.cbegin(), processedPart.cend(), [](const bool val){
        return val;
    });
}

int BracketMatcher::evaluateNextPosition(const std::vector<bool> &processedPart, int currentFirstPos) const
{
    while (currentFirstPos >= 0) {
        if (processedPart[currentFirstPos] == false) {
            break;
        }
        ++currentFirstPos;
    }

    return currentFirstPos;
}

int BracketMatcher::evaluatePreviosPosition(const std::vector<bool> &processedPart, int currentFirstPos) const
{
    while (currentFirstPos >= 0) {
        if (processedPart[currentFirstPos] == false) {
            break;
        }
        --currentFirstPos;
    }

    if (currentFirstPos < 0) {
        int i = 0;
        for (; i < processedPart.size(); ++i) {
            if (processedPart[i] == false) {
                break;
            }
        }

        currentFirstPos = i;
    }

    return currentFirstPos;
}

bool BracketMatcher::contains(const std::vector<char> &container, const char target) const
{
    return std::find_if(container.cbegin(), container.cend(), [target](const char character){
               return target == character;
           }) != container.cend();
}
