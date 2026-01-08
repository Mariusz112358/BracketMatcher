#ifndef BRACKETMATCHER_H
#define BRACKETMATCHER_H

#include <vector>

class BracketMatcher
{
public:
    BracketMatcher();

    bool matchWithRecursive(const char* pattern);
    bool matchWithStack(const char* pattern);
    bool matchWithProcessedArray(const char* pattern);

private:
    //bool matchWithProcessedArray(const char* pattern);
    bool allProcessed(const std::vector<bool>& processedPart) const;
    int evaluateNextPosition(const std::vector<bool>& processedPart, int currentFirstPos) const;
    int evaluatePreviosPosition(const std::vector<bool>& processedPart, int currentFirstPos) const;
    bool contains(const std::vector<char>& container, const char target) const;

    //bool matchWithStack(const char* pattern);

};

#endif // BRACKETMATCHER_H
