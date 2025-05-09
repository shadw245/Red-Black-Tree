#pragma once
#include <string>
#include <vector>
using namespace std;
class AnimationSteps {
private:

    vector<pair<string, int>> steps;

public:
    // Add a step to the animation log
    void AddStep(const string& action, int value) {
        steps.emplace_back(action, value);
    }

    // Clear all animation steps
    void Clear() {
        steps.clear();
    }

    // Get all animation steps
    const vector<pair<string, int>>& GetSteps() const {
        return steps;
    }
};
