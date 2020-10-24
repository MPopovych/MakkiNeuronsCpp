#include "Brain.h"

BrainStructure *Brain::GetStructure()
{
    int currentCount = layers.size();
    if (currentCount == 0)
    {
        return NULL;
    }
    int count = (currentCount + 1) / 2;
    int *arr = (int *)malloc(sizeof(int) * count);
    for (int i = 0; i < count; i++)
    {
        arr[i] = layers[i * 2]->GetWidth();
    }
    return new BrainStructure{ count, arr };
}

BrainFunction *Brain::GetFunction()
{
    return function;
}

BrainLayer *Brain::GetWeightLayer(int index)
{
    return layers[index * 2 + 1];
}

BrainLayer *Brain::GetLayer(int index)
{
    return layers[index * 2];
}

int Brain::GetLayerCount()
{
    return (layers.size() + 1) / 2;
}

int Brain::GetWeightLayerCount()
{
    return (layers.size() - 1) / 2;
}

void Brain::SetDebug(bool d)
{
    debug = d;
}

void Brain::Append(int count)
{
    this->Append(count, NULL);
}

void Brain::Append(int count, ValueSupplier *bSupplier)
{
    layerCount++;

    int lastSize = -1;
    if (layers.size() > 0)
    {
        lastSize = layers[layers.size() - 1]->GetWidth();
    }
    if (lastSize > 0)
    {
        layers.push_back(new BrainLayer(count, lastSize, supplier)); // weight layer
    }
    layers.push_back(new BrainLayer(count, 1, NULL, bSupplier)); // hidden layer
}

void Brain::SetFunction(BrainFunction *f)
{
    this->function = f;
}

void Brain::SetInput(float source[], size_t len)
{
    if (layers.size() <= 0)
    {
        std::cout << "Brain layer size is 0 or less" << std::endl;
        throw;
    }

    BrainLayer *first = layers[0];
    if (first->GetNodeCount() != len)
    {
        std::cout << "Mismatch of layer nodes and input count" << first->GetNodeCount() << " vs " << len << std::endl;
        throw;
    }
    first->SetValues(source, len);
}

void Brain::SetInput(ValueSupplier *supplier)
{
    if (layers.size() <= 0)
    {
        std::cout << "Brain layer size is 0 or less" << std::endl;
        throw;
    }

    BrainLayer *first = layers[0];
    for (int i = 0; i < first->GetHeight(); i++)
    {
        first->SetValue(0, i, supplier->GetValue(i, 0, i));
    }
}

void Brain::Calculate(float dst[], size_t len)
{
    int layer = 0;
    int weight = 0;

    for (int i = 0; i < layerCount - 1; i++)
    {
        layer = i * 2;
        weight = layer + 1;

        if (debug)
        {
            std::cout << "LAYER L" << layer << std::endl;
            layers[layer]->Print();

            std::cout << "LAYER W" << weight << std::endl;
            layers[weight]->Print();
        }

        BrainLayer *target = layers[weight + 1];
        if (weight + 1 == layers.size())
        {
            target->SetToZeros();
        }
        else
        {
            target->SetToBias();
        }

        layers[layer]->Multiply(layers[weight], target);

        for (int j = 0; j < target->GetWidth(); j++)
        {
            target->SetValue(j, 0, function->Apply(target->GetValue(j, 0)));
        }
    }

    BrainLayer *last = layers[weight + 1];

    for (int i = 0; i < len; i++)
    {
        dst[i] = last->GetValue(i, 0);
    }
}
