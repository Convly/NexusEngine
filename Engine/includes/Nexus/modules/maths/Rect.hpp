#ifndef NX_ENGINE__MODULE_MATHS_RECT_HPP_
#define NX_ENGINE__MODULE_MATHS_RECT_HPP_

#include <iostream>
#include "Vector2f.hpp"

namespace nx {
namespace maths {

class Rect {
/* Constructors && Destructor */
public:
    Rect() {}
    Rect(const Vector2f& position) : position_(position) {}
    Rect(const Vector2f& position, const Vector2f& size) : position_(position), size_(size) {}
    Rect(const Vector2f& position, const Vector2f& size, const Vector2f& origin) : position_(position), size_(size), origin_(origin) {} 
    ~Rect() {}

/* Setters */
public:
    void setPosition(const Vector2f& position) {
        position_ = position;
    }

    void setSize(const Vector2f& size) {
        size_ = size;
    }

    void setWidth(const double width) {
        size_.x = width;
    }

    void setHeight(const double height) {
        size_.y = height;
    }

    void setOrigin(const Vector2f& origin) {
        origin_ = origin;
    }

/* Getters */
public:
    const Vector2f& position() const {
        return position_;
    }

    const Vector2f& size() const {
        return size_;
    }

    const Vector2f& origin() const {
        return origin_;
    }

    const double width() const {
        return size_.x;
    }

    const double height() const {
        return size_.y;
    }

/* Members */
private:
    Vector2f position_;
    Vector2f size_;
    Vector2f origin_;
};
    inline std::ostream& operator<<(std::ostream& os, const nx::maths::Rect& item) {
        std::cout << "Rect(" << item.position() << ", " << item.size() << ")based_on[" << item.origin() << "]";
        return os;
    }
}
}

#endif