#include <iostream>
#include <ctime>

class ValueSupplier
{
public:
    virtual float GetValue(int index, int x, int y)
    {
        std::cout << "ValueSupplier::GetValue Should not be called\n"
                  << std::endl;
        throw;
    };
};

class ZeroSupplier : public ValueSupplier
{
public:
    float GetValue(int index, int x, int y)
    {
        return 0.0;
    };
};

class RandomSupplier : public ValueSupplier
{
public:
    RandomSupplier()
    {
        srand((unsigned int)time(NULL));
    }
    float GetValue(int index, int x, int y)
    {
        return static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    };
};

class RandomRangeSupplier : public ValueSupplier
{
public:
    RandomRangeSupplier()
    {
        srand((unsigned int)time(NULL));
    }
    float GetValue(int index, int x, int y)
    {
        return (static_cast<float>(rand()) / static_cast<float>(RAND_MAX)) * 2 - 1.0;
    };
};


class ArraySupplier : public ValueSupplier
{
private:
    float *p_values;

public:
    ArraySupplier(float values[], int size)
    {
        this->p_values = (float *)malloc(sizeof(float) * size);
        for (int i = 0; i < size; i++)
        {
            this->p_values[i] = values[i];
        }
    }
    ~ArraySupplier()
    {
        free(this->p_values);
    }
    float GetValue(int index, int x, int y)
    {
        std::cout << "index " << index << " value " << this->p_values[index] << std::endl;
        return this->p_values[index];
    };
};