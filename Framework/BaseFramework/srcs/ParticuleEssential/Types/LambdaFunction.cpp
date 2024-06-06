#include "../../../includes/ParticuleEssential/Types/LambdaFunction.hpp"

LambdaFunction::LambdaFunction()
{
    this->function = nullptr;
}

LambdaFunction::LambdaFunction(void (*function)(void* data), void* data)
{
    this->function = function;
    this->data = data;
}

LambdaFunction::~LambdaFunction()
{
}

LambdaFunction::LambdaFunction(const LambdaFunction &other)
{
    this->function = other.function;
    this->data = other.data;
}

LambdaFunction &LambdaFunction::operator=(const LambdaFunction &other)
{
    if (this == &other)
    {
        return *this;
    }
    this->function = other.function;
    this->data = other.data;
    return *this;
}

void LambdaFunction::operator()()
{
    if (this->function != nullptr)
    {
        this->function(this->data);
    }
}