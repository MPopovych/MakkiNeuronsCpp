#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "ValueSupplier.h"

class BrainLayer
{
private:
    int width;
    int height;
    float *p_values;
    float *p_bias_values = NULL;
    void init(int w, int h, ValueSupplier *supplier, bool biased);

public:
    BrainLayer(int w, int h, ValueSupplier *supplier, bool biased)
    {
        init(w, h, supplier, biased);
    }
    BrainLayer(int w, int h, bool biased)
    {
        ZeroSupplier supplier;
        init(w, h, &supplier, biased);
    }
    ~BrainLayer()
    {
        free(p_values);
        free(p_bias_values);
    }
    void SetToBias();
    void SetToZeros();
    void SetValues(ValueSupplier *supplier);
    void SetValues(float source[], size_t len);
    void SetValue(int x, int y, float value);
    float GetValue(int x, int y);
    int GetHeight();
    int GetWidth();
    int GetNodeCount();
    void Multiply(BrainLayer *target, BrainLayer *destination);
    void Print();
    void PrintRotated();
};