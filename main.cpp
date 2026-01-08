#include <iostream>

#include "bracketmatcher.h"

struct TestCase {
    const char* input;
    bool expectedResult;
};

std::vector<TestCase> generateTestCases()
{
    std::vector<TestCase> testCases;

    // Valid cases (expectedResult = true)
    testCases.push_back({"()", true});                 // Simple valid case
    testCases.push_back({"{}", true});                 // Valid case with curly braces
    testCases.push_back({"[]", true});                 // Valid case with square brackets
    testCases.push_back({"({[]})", true});             // Valid nested brackets
    testCases.push_back({"(){}[]", true});             // Multiple valid bracket pairs
    testCases.push_back({"{[()]}", true});             // Another valid nesting case
    testCases.push_back({"((()))", true});             // Multiple same type nesting
    testCases.push_back({"[[[]]]", true});             // Multiple same type nested square brackets

    // Invalid cases (expectedResult = false)
    testCases.push_back({"(]", false});                // Mismatched brackets
    testCases.push_back({"{[}]", false});              // Mismatched brackets
    testCases.push_back({"((}", false});               // Unbalanced brackets
    testCases.push_back({"[[)", false});               // Mismatched and unbalanced
    testCases.push_back({"{", false});                 // Single open bracket
    testCases.push_back({")", false});                 // Single closing bracket
    testCases.push_back({"({[})]", false});            // Complex mismatched case
    testCases.push_back({"([)]", false});              // Crossed matching brackets
    testCases.push_back({"{[(])}", false});            // Misaligned nested brackets

    // Edge cases
    testCases.push_back({"", true});                   // Empty string (should be valid)
    testCases.push_back({" ", true});                  // String with space (no brackets)
    testCases.push_back({"a+b*(c-d)", true});          // No brackets to check, valid expression
    testCases.push_back({"(a+b)*[c-d]", true});        // Expression with valid brackets
    testCases.push_back({"([a+b]*{c-d})", true});      // Expression with nested valid brackets

    // More complex valid cases (expectedResult = true)
    testCases.push_back({"(({{[[[]]]}}))", true});             // Deeply nested with different bracket types
    testCases.push_back({"[{()}([])]", true});                 // Mixed types of brackets, valid nesting
    testCases.push_back({"{{([][])}()}", true});               // Nested valid case with complex structure
    testCases.push_back({"[([]){}]{}", true});                 // Multiple nesting and valid pairs
    testCases.push_back({"a*(b+c)-{d/[e+f-(g*h)]}", true});    // Complex expression with valid brackets

    // More complex invalid cases (expectedResult = false)
    testCases.push_back({"((({{{[[[]]]}}}))", false});         // Unbalanced deeply nested brackets (missing closing bracket)
    testCases.push_back({"[{)]}", false});                     // Misplaced brackets, interleaved wrong
    testCases.push_back({"[{(})]}", false});                   // Mixed types with misplaced closing brackets
    testCases.push_back({"[([]{})]}", false});                 // Extra closing bracket at the end
    testCases.push_back({"a*(b+c)-{d/[e+f-(g*h)]", false});    // Expression with missing closing curly brace

    // Edge cases with non-standard characters
    testCases.push_back({"[[[[[[[[[[[[[[]]]]]]]]]]]]]]]", false});  // Very deeply nested square brackets
    testCases.push_back({"(((((((((((())))))))))))", true});        // Very deeply nested parentheses
    testCases.push_back({"(((((((((((()))))))))))", false});        // Missing one closing parenthesis
    testCases.push_back({"[[{{(())}}]]", true});                    // Nested with minimal characters
    testCases.push_back({"[a+b*(c/d)-{e-f}]", true});               // Valid case with letters and math symbols

    return testCases;
}

int main()
{
    BracketMatcher bm;

    std::vector<TestCase> testCases = generateTestCases();

    std::cout << "Bracket Validation Test Cases (Input, Expected Result):" << std::endl;

    int errorCount = 0;
    for (size_t i = 0; i < testCases.size(); i++) {
        const auto result = bm.matchWithStack(testCases[i].input);
        if (result != testCases[i].expectedResult) {
            errorCount++;
        }

        std::cout << "Test Case " << i + 1 << ": \"" << testCases[i].input << "\", Expected: "
                  << (testCases[i].expectedResult ? "true" : "false") << ", Actual: "
                  << (result ? "true" : "false") << ", Outcome: " << (result == testCases[i].expectedResult ? "OK" : "ERROR!!!")
                  << std::endl;
    }

    std::cout << std::endl << "-----------------------------------------" << std::endl;
    std::cout << "Summary: ";
    if (errorCount) {
        std::cout << " found " << errorCount << " errors!";
    }
    else {
        std::cout << "OK";
    }
    std::cout << std::endl;
    return 0;

    return 0;
}
