#include <iomanip>
#include "BrainLayer.h"

void BrainLayer::init(int w, int h, ValueSupplier *supplier, bool biased)
{
    this->height = h;
    this->width = w;
    this->p_values = (float *)malloc(sizeof(float) * width * height);

    for (int x = 0; x < w; x++)
    {
        for (int y = 0; y < h; y++)
        {
            int i = x * this->height + y;
            this->p_values[i] = supplier->GetValue(i, x, y);
        }
    }

    if (biased)
    {
        this->p_bias_values = (float *)malloc(sizeof(float) * width * height);
        for (int x = 0; x < w; x++)
        {
            for (int y = 0; y < h; y++)
            {
                int i = x * this->height + y;
                this->p_bias_values[i] = supplier->GetValue(i, x, y);
            }
        }
    }
}

void BrainLayer::SetValues(ValueSupplier *supplier)
{
    for (int x = 0; x < this->width; x++)
    {
        for (int y = 0; y < this->height; y++)
        {
            int i = x * this->height + y;
            this->p_values[i] = supplier->GetValue(i, x, y);
        }
    }
}

void BrainLayer::SetValues(float source[], size_t len)
{
    if (this->GetNodeCount() != len)
    { //no need for this, but lets keep it for now
        std::cout << "Mismatch of node count, input size: " << len << std::endl;
        throw;
    }
    for (int x = 0; x < this->width; x++)
    {
        for (int y = 0; y < this->height; y++)
        {
            this->p_values[x * this->height + y] = source[x * this->height + y];
        }
    }
}

void BrainLayer::SetValue(int x, int y, float value)
{
    this->p_values[x * this->height + y] = value;
}

void BrainLayer::SetToBias()
{
    if (this->p_bias_values == NULL) {
        return;
    }
    for (int x = 0; x < this->width; x++)
    {
        for (int y = 0; y < this->height; y++)
        {
            int i = x * this->height + y;
            this->p_values[i] = this->p_bias_values[i];
        }
    }
}

void BrainLayer::SetToZeros() 
{
    for (int x = 0; x < this->width; x++)
    {
        for (int y = 0; y < this->height; y++)
        {
            p_values[x * this->height + y] = 0.0;
        }
    }
}

void BrainLayer::Multiply(BrainLayer *target, BrainLayer *destination)
{
    int thisX = this->width;
    int thisY = this->height;
    int targetX = target->width;
    int targetY = target->height;
    int destinationX = destination->width;
    int destinationY = destination->height;

    if (thisX != targetY)
    {
        std::cout << "CONFLICT OF " << thisX << " TARGET " << targetY << "." << std::endl;
        throw;
    }

    for (int i = 0; i < thisY; i++)
    { // aRow
        for (int j = 0; j < targetX; j++)
        { // bColumn
            for (int k = 0; k < thisX; k++)
            { // aColumn
                destination->p_values[j * destination->height + i] += p_values[k * height + i] * target->p_values[j * target->height + k];
            }
        }
    }
}

float BrainLayer::GetValue(int x, int y)
{
    return this->p_values[x * this->height + y];
}

int BrainLayer::GetHeight()
{
    return this->height;
}
int BrainLayer::GetWidth()
{
    return this->width;
}
int BrainLayer::GetNodeCount()
{
    return this->height * this->width;
}

void BrainLayer::Print()
{
    std::cout << std::setprecision(1) << std::fixed;
    for (int y = 0; y < this->height; y++)
    {
        for (int x = 0; x < this->width; x++)
        {
            std::cout << this->GetValue(x, y) << ' ';
        }
        std::cout << std::endl;
    }
}

void BrainLayer::PrintRotated()
{
    std::cout << std::setprecision(1) << std::fixed;
    for (int x = 0; x < this->width; x++)
    {
        for (int y = 0; y < this->height; y++)
        {
            std::cout << this->GetValue(x, y) << ' ';
        }
        std::cout << std::endl;
    }
}