#include <iostream>

class BrainFunction
{
public:
    virtual float Apply(float value) {
        std::cout << "BrainFunction::Apply Should not be called\n" << std::endl;
        throw;
    };
};

static const float LEAK_VALUE = 0.015f;
class LeakyReLuFunction : public BrainFunction
{
public:
    float Apply(float value) {
        if (value >= 0) {
            return value;
        }
        return LEAK_VALUE * value;
    };
};

class ReLuFunction : public BrainFunction
{
public:
    float Apply(float value) {
        if (value >= 0) {
            return value;
        }
        return 0.0;
    };
};