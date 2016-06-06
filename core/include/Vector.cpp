/**
 * @file Vector.cpp
 * @author Raoul Harel
 * @url github.com/rharel/cpp-k-means-clustering
 *
 * Class Vector.
 */


#include "Vector.hpp"


template<typename T, size_t D>
cluster::Vector<T, D>::Vector(T value)
{
    std::fill_n(data_.begin(), D, value);
}
template<typename T, size_t D>
cluster::Vector<T, D>::Vector(std::initializer_list<T> list)
    : Vector(0)
{
    std::copy_n
    (
        list.begin(), 
        std::min(list.size(), D), 
        data_.begin()
    );
}

template<typename T, size_t D>
cluster::Vector<T, D>
cluster::Vector<T, D>::scale(const float s)
{
    Vector<T, D> result;
    for (size_t i = 0; i < D; ++i)
    {
        result[i] = (*this)[i] * s;
    }
    return result;
}

template<typename T, size_t D>
float 
cluster::Vector<T, D>::dot(const Vector<T, D>& other) const
{
    float result = 0.0f;
    for (size_t i = 0; i < D; ++i)
    {
        result += (*this)[i] * other[i];
    }
    return result;
}

// unary //

template<typename T, size_t D>
cluster::Vector<T, D>
cluster::Vector<T, D>::operator-() const
{
    Vector<T, D> result;
    for (size_t i = 0; i < D; ++i)
    {
        result[i] = -(*this)[i];
    }
    return result;
}

// binary //

template<typename T, size_t D>
cluster::Vector<T, D>
cluster::Vector<T, D>::operator+(const Vector<T, D>& rhs) const
{
    Vector<T, D> result;
    for (size_t i = 0; i < D; ++i)
    {
        result[i] = (*this)[i] + rhs[i];
    }
    return result;
}
template<typename T, size_t D>
cluster::Vector<T, D>
cluster::Vector<T, D>::operator-(const Vector<T, D>& rhs) const
{
    return (*this) + (-rhs);
}
template<typename T, size_t D>
cluster::Vector<T, D>
cluster::Vector<T, D>::operator*(const Vector<T, D>& rhs) const
{
    Vector<T, D> result;
    for (size_t i = 0; i < D; ++i)
    {
        result[i] = (*this)[i] * rhs[i];
    }
    return result;
}
template<typename T, size_t D>
cluster::Vector<T, D>
cluster::Vector<T, D>::operator/(const Vector<T, D>& rhs) const
{
    Vector<T, D> result;
    for (size_t i = 0; i < D; ++i)
    {
        result[i] = (*this)[i] / rhs[i];
    }
    return result;
}

// comparison //

template<typename T, size_t D>
bool
cluster::Vector<T, D>::operator==(const Vector<T, D>& rhs) const
{
    for (size_t i = 0; i < D; ++i)
    {
        if ((*this)[i] != rhs[i]) { return false; }
    }
    return true;
}
template<typename T, size_t D>
bool
cluster::Vector<T, D>::operator!=(const Vector<T, D>& rhs) const
{
    return !((*this) == rhs);
}

// member access //

template<typename T, size_t D>
T&
cluster::Vector<T, D>::operator[](const size_t index)
{
    return data_.at(index);
}
template<typename T, size_t D>
T
cluster::Vector<T, D>::operator[](const size_t index) const
{
    return data_.at(index);
}

// assignment //

template<typename T, size_t D>
cluster::Vector<T, D>&
cluster::Vector<T, D>::operator=(const Vector<T, D>& rhs)
{
    for (size_t i = 0; i < D; ++i)
    {
        (*this)[i] = rhs[i];
    }
    return *this;
}
template<typename T, size_t D>
cluster::Vector<T, D>&
cluster::Vector<T, D>::operator+=(const Vector<T, D>& rhs)
{
    return (*this) = ((*this) + rhs);
}
template<typename T, size_t D>
cluster::Vector<T, D>&
cluster::Vector<T, D>::operator-=(const Vector<T, D>& rhs)
{
    return (*this) = ((*this) - rhs);
}
template<typename T, size_t D>
cluster::Vector<T, D>&
cluster::Vector<T, D>::operator*=(const Vector<T, D>& rhs)
{
    return (*this) = ((*this) * rhs);
}
template<typename T, size_t D>
cluster::Vector<T, D>&
cluster::Vector<T, D>::operator/=(const Vector<T, D>& rhs)
{
    return (*this) = ((*this) / rhs);
}
