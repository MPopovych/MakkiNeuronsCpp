#include <iomanip>
#include "BrainLayer.h"

void BrainLayer::init(int w, int h, ValueSupplier *supplier,  ValueSupplier *bSupplier)
{
    this->height = h;
    this->width = w;
    this->p_values = (float *)malloc(sizeof(float) * width * height);

    if (supplier != NULL)
    {
        for (int x = 0; x < w; x++)
        {
            for (int y = 0; y < h; y++)
            {
                int i = x * this->height + y;
                this->p_values[i] = supplier->GetValue(i, x, y);
            }
        }
    } else //supplier is null, might use mem set or analog in future
    {
        for (int x = 0; x < w; x++)
        {
            for (int y = 0; y < h; y++)
            {
                int i = x * this->height + y;
                this->p_values[i] = 0;
            }
        }
    }

    if (bSupplier != NULL)
    {
        this->p_bias_values = (float *)malloc(sizeof(float) * width * height);
        for (int x = 0; x < w; x++)
        {
            for (int y = 0; y < h; y++)
            {
                int i = x * this->height + y;
                this->p_bias_values[i] = bSupplier->GetValue(i, x, y);
            }
        }
    }
}

void BrainLayer::Multiply(BrainLayer *target, BrainLayer *destination)
{
    const int thisX = this->width;
    const int thisY = this->height;
    const int targetX = target->width;
    const int targetY = target->height;
    const int destinationX = destination->width;
    const int destinationY = destination->height;

    if (thisX != targetY)
    {
        std::cout << "CONFLICT OF " << thisX << " TARGET " << targetY << "." << std::endl;
        throw;
    }

    float value = 0;
    float *p_dest = destination->p_values;
    float *p_target = target->p_values;
    float *p_this = p_values;
    for (int i = 0; i < thisY; i++)
    {
        for (int j = 0; j < targetX; j++)
        {
            value = p_dest[j * destinationY + i];
            for (int k = 0; k < thisX; k++)
            { 
                value += p_this[k * thisY + i] * p_target[j * targetY + k];
            }
            p_dest[j * destinationY + i] = value;
        }
    }
}

float BrainLayer::GetValue(int x, int y)
{
    return this->p_values[x * this->height + y];
}

void BrainLayer::SetValue(int x, int y, float value)
{
    this->p_values[x * this->height + y] = value;
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

void BrainLayer::SetToBias()
{
    if (this->p_bias_values == NULL)
    {
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

float BrainLayer::GetBiasValue(int x, int y) 
{
    if (p_bias_values == NULL) {
        return 0;
    }
    return p_bias_values[x * this->height + y];
}
void BrainLayer::SetBiasValue(int x, int y, float value)
{
    if (p_bias_values == NULL) {
        return;
    }
    p_bias_values[x * this->height + y] = value;
}
bool BrainLayer::IsBiased()
{
    return p_bias_values != NULL;
}

int BrainLayer::GetNodeCount()
{
    return this->height * this->width;
}

int BrainLayer::GetHeight()
{
    return this->height;
}
int BrainLayer::GetWidth()
{
    return this->width;
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