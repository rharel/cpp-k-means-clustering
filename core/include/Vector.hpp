#ifndef K_MEANS_VECTOR_H
#define K_MEANS_VECTOR_H
/**
 * @file Vector.hpp
 * @author Raoul Harel
 * @url github.com/rharel/cpp-k-means-clustering
 *
 * Class Vector.
 */


#include <array>
#include <type_traits>


namespace cluster
{
    /**
     * Basic vector class.
     * 
     * @tparam NumericType Data type.
     * @tparam Dimension   Data dimension.
     */
    template<typename NumericType, size_t Dimension>
    class Vector
    {
        static_assert(std::is_arithmetic<NumericType>::value, 
                      "not an arithmetic type");

        public:
        Vector(NumericType value = 0);
        Vector(std::initializer_list<NumericType> list);

        Vector<NumericType, Dimension> scale(float scalar);
        float dot(const Vector<NumericType, Dimension>& other) const;

        // unary
        Vector<NumericType, Dimension> operator-() const;
        
        // binary
        Vector<NumericType, Dimension> operator+(const Vector<NumericType, Dimension>& rhs) const;
        Vector<NumericType, Dimension> operator-(const Vector<NumericType, Dimension>& rhs) const;
        Vector<NumericType, Dimension> operator*(const Vector<NumericType, Dimension>& rhs) const;
        Vector<NumericType, Dimension> operator/(const Vector<NumericType, Dimension>& rhs) const;

        // comparison
        bool operator==(const Vector<NumericType, Dimension>& rhs) const;
        bool operator!=(const Vector<NumericType, Dimension>& rhs) const;

        // member access
        NumericType& operator[](size_t index);
        NumericType  operator[](size_t index) const;

        // assignment
        Vector<NumericType, Dimension>& operator= (const Vector<NumericType, Dimension>& rhs);
        Vector<NumericType, Dimension>& operator+=(const Vector<NumericType, Dimension>& rhs);
        Vector<NumericType, Dimension>& operator-=(const Vector<NumericType, Dimension>& rhs);
        Vector<NumericType, Dimension>& operator*=(const Vector<NumericType, Dimension>& rhs);
        Vector<NumericType, Dimension>& operator/=(const Vector<NumericType, Dimension>& rhs);

        private:
        std::array<NumericType, Dimension> data_;
    };
}


#include "Vector.cpp"


#endif  // K_MEANS_VECTOR_H
