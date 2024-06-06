#ifndef LAMBDA_FUNCTION_HPP
#define LAMBDA_FUNCTION_HPP

class LambdaFunction
{
public:
    void (*function)(void* data);
    void* data;

    LambdaFunction();
    LambdaFunction(void (*function)(void* data), void* data);
    ~LambdaFunction();
    LambdaFunction(const LambdaFunction &other);
    LambdaFunction &operator=(const LambdaFunction &other);
    void operator()();
};

#endif // LAMBDA_FUNCTION_HPP