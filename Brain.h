#include <iostream>
#include <vector>
#include "BrainLayer.cpp"
#include "BrainFunction.h"

struct BrainStructure 
{
    int len;
    int* array;
    ~BrainStructure() 
    {
        delete[] array;
    }
};

class Brain
{
private:
    BrainFunction *function;
    ValueSupplier *supplier;
    int layerCount = 0;
    bool debug = false;
    std::vector<BrainLayer*> layers;

public:
    Brain(BrainFunction *function, ValueSupplier *supplier)
    {
        this->function = function;
        this->supplier = supplier;
        this->layers = {};
    }
    ~Brain() {
        for (int i = 0; i < layers.size(); i++) 
        {
            delete(layers[i]);
        }
        layers.clear();
    }

    BrainStructure *GetStructure();
    BrainLayer *GetWeightLayer(int index);
    BrainLayer *GetLayer(int index);
    BrainFunction *GetFunction();
    int GetLayerCount();
    int GetWeightLayerCount();
    void SetDebug(bool d);
    void Append(int count);
    void Append(int count, ValueSupplier *bSupplier);
    void SetFunction(BrainFunction *function);
    void SetInput(float source[], size_t len);
    void SetInput(ValueSupplier *supplier);
    void Calculate(float dst[], size_t len);
};
