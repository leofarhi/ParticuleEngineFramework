#ifndef MATRIX_HPP
#define MATRIX_HPP

template <typename T>
class Matrix
{
public:
    T *data;
    int rows;
    int cols;

    Matrix();
    Matrix(int rows, int cols);
    Matrix(int rows, int cols, T *data);
    ~Matrix();
    void Set(int row, int col, T value);
    T Get(int row, int col);
    Matrix &operator=(const Matrix &other);
    Matrix operator+(const Matrix &other) const;
    Matrix operator-(const Matrix &other) const;
    Matrix operator*(const Matrix &other) const;
    Matrix operator*(T scalar) const;
    Matrix operator/(T scalar) const;
    bool operator==(const Matrix &other) const;
    bool operator!=(const Matrix &other) const;
    //operator [,] set and get
    T &operator()(int row, int col);
    const T &operator()(int row, int col) const;
    Matrix Transpose() const;
};

template <typename T>
Matrix<T>::Matrix()
{
    this->rows = 0;
    this->cols = 0;
    this->data = nullptr;
}

template <typename T>
Matrix<T>::Matrix(int rows, int cols)
{
    this->rows = rows;
    this->cols = cols;
    this->data = new T[rows * cols];
    for (int i = 0; i < rows * cols; i++)
        this->data[i] = 0;
}

template <typename T>
Matrix<T>::Matrix(int rows, int cols, T *data)
{
    this->rows = rows;
    this->cols = cols;
    this->data = new T[rows * cols];
    for (int i = 0; i < rows * cols; i++)
        this->data[i] = data[i];
}

template <typename T>
Matrix<T>::~Matrix()
{
    delete[] this->data;
}

template <typename T>
void Matrix<T>::Set(int row, int col, T value)
{
    this->data[row * this->cols + col] = value;
}

template <typename T>
T Matrix<T>::Get(int row, int col)
{
    return this->data[row * this->cols + col];
}

template <typename T>
Matrix<T> &Matrix<T>::operator=(const Matrix &other)
{
    if (this == &other)
    {
        return *this;
    }

    // Libérer la mémoire existante
    delete[] this->data;

    // Copier les dimensions
    this->rows = other.rows;
    this->cols = other.cols;

    // Allouer de la nouvelle mémoire
    this->data = new T[rows * cols];

    // Copier les éléments
    for (int i = 0; i < rows * cols; i++)
    {
        this->data[i] = other.data[i];
    }

    return *this;
}

template <typename T>
Matrix<T> Matrix<T>::operator+(const Matrix &other) const
{
    Matrix<T> result(rows, cols);
    for (int i = 0; i < rows * cols; i++)
        result.data[i] = this->data[i] + other.data[i];
    return result;
}

template <typename T>
Matrix<T> Matrix<T>::operator-(const Matrix &other) const
{
    Matrix<T> result(rows, cols);
    for (int i = 0; i < rows * cols; i++)
        result.data[i] = this->data[i] - other.data[i];
    return result;
}

template <typename T>
Matrix<T> Matrix<T>::operator*(const Matrix &other) const
{
    Matrix<T> result(rows, other.cols);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < other.cols; j++)
        {
            for (int k = 0; k < cols; k++)
            {
                result.data[i * other.cols + j] += this->data[i * cols + k] * other.data[k * other.cols + j];
            }
        }
    }
    return result;
}

template <typename T>
Matrix<T> Matrix<T>::operator*(T scalar) const
{
    Matrix<T> result(rows, cols);
    for (int i = 0; i < rows * cols; i++)
        result.data[i] = this->data[i] * scalar;
    return result;
}

template <typename T>
Matrix<T> Matrix<T>::operator/(T scalar) const
{
    Matrix<T> result(rows, cols);
    for (int i = 0; i < rows * cols; i++)
        result.data[i] = this->data[i] / scalar;
    return result;
}

template <typename T>
bool Matrix<T>::operator==(const Matrix &other) const
{
    if (this->rows != other.rows || this->cols != other.cols)
        return false;
    for (int i = 0; i < rows * cols; i++)
    {
        if (this->data[i] != other.data[i])
            return false;
    }
    return true;
}

template <typename T>
bool Matrix<T>::operator!=(const Matrix &other) const
{
    return !(*this == other);
}

template <typename T>
T &Matrix<T>::operator()(int row, int col)
{
    return data[row * cols + col];
}

template <typename T>
const T &Matrix<T>::operator()(int row, int col) const
{
    return data[row * cols + col];
}

template <typename T>
Matrix<T> Matrix<T>::Transpose() const
{
    Matrix<T> result(cols, rows);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            result.data[j * rows + i] = this->data[i * cols + j];
        }
    }
    return result;
}

#endif // MATRIX_HPP