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
    void init(int w, int h, ValueSupplier *supplier, ValueSupplier *bSupplier);

public:
    BrainLayer(int w, int h, ValueSupplier *supplier, ValueSupplier *bSupplier)
    {
        init(w, h, supplier, bSupplier);
    }
    BrainLayer(int w, int h, ValueSupplier *supplier)
    {
        init(w, h, supplier, NULL);
    }
    BrainLayer(int w, int h)
    {
        ZeroSupplier supplier;
        init(w, h, &supplier, NULL);
    }
    ~BrainLayer()
    {
        free(p_values);
        free(p_bias_values);
    }
    void Multiply(BrainLayer *target, BrainLayer *destination);
    float GetValue(int x, int y);
    void SetValue(int x, int y, float value);
    void SetValues(float source[], size_t len);
    void SetValues(ValueSupplier *supplier);
    void SetToBias();
    void SetToZeros();
    float GetBiasValue(int x, int y);
    void SetBiasValue(int x, int y, float value);
    bool IsBiased();
    int GetNodeCount();
    int GetHeight();
    int GetWidth();
    void Print();
    void PrintRotated();
};