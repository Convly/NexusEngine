#ifndef NEXUS_ENGINE__MODULE_PHYSICS_FORCE2D_HPP_
#define NEXUS_ENGINE__MODULE_PHYSICS_FORCE2D_HPP_

#include <iostream>
#include "Nexus/modules/maths/maths.hpp"

namespace nx {
namespace physics {
    class Force2d {
    /* Constructors / Destructor */
    public:
        Force2d() : velocity_(0), inertia_(0) {}
        Force2d(const double vx, const double vy) : velocity_(vx, vy), inertia_(0) {}
        Force2d(const nx::maths::Vector2f& velocity) : velocity_(velocity), inertia_(0) {}
        Force2d(const nx::maths::Vector2f& velocity, const nx::maths::Vector2f& inertia) : velocity_(velocity), inertia_(inertia) {}
        ~Force2d() {}

    /* Operators */
    public:
        Force2d& operator=(const Force2d& other) {
            if (&other != this) {
                velocity_ = other.velocity();
                inertia_ = other.inertia();
            }

            return *this;
        }

        bool operator==(const Force2d& other) {
            return velocity_ == other.velocity();
        }

        bool operator!=(const Force2d& other) {
            return velocity_ != other.velocity();            
        }

        Force2d operator+(const Force2d& other) {
            return Force2d(velocity_ + other.velocity());
        }

        Force2d operator+(const double value) {
            return Force2d(velocity_ + value);
        }

        Force2d& operator+=(const Force2d& other) {
            velocity_ += other.velocity_;
        }

        Force2d operator-(const Force2d& other) {
            return Force2d(velocity_ - other.velocity());
        }

        Force2d operator-(const double value) {
            return Force2d(velocity_ - value);
        }

        Force2d operator*(const double k) {
            return Force2d(velocity_ * k);
        }

        Force2d operator/(const double k) {
            return Force2d(velocity_ / k);
        }

        Force2d& operator/=(const double k) {
            velocity_ /= k;
            return *this;
        }
        
    /* Getters */
    public:
        const double vxConst() const {
            return velocity_.x;
        }

        double vx() {
            return velocity_.x;
        }

        const double vyConst() const {
            return velocity_.y;
        }

        double vy() {
            return velocity_.y;
        }

        const nx::maths::Vector2f& velocity() const {
            return velocity_;
        }

        const nx::maths::Vector2f& inertia() const {
            return inertia_;
        }

    /* Setters */
    public:
        void setVX(const double value) {
            velocity_.x = value;
        }

        void setVY(const double value) {
            velocity_.y = value;
        }

        void setVelocity(const nx::maths::Vector2f& velocity) {
            velocity_ = velocity;
        }

        void setInertia(const nx::maths::Vector2f& inertia) {
            inertia_ = inertia;
        }

    /* Other */
    public:
        void reset(const nx::maths::Vector2f& velocity) {
            velocity_ = velocity;
        }

        void reset(const nx::maths::Vector2f& velocity, const nx::maths::Vector2f& inertia) {
            velocity_ = velocity;
            inertia_ = inertia;
        }

        void reset(const bool preserverInertia = false) {
            velocity_.reset();
            if (!preserverInertia)
                inertia_.reset();
        }

    /* Members */
    private:
        nx::maths::Vector2f velocity_;
        nx::maths::Vector2f inertia_;
    };

    inline std::ostream& operator<<(std::ostream& os, const nx::physics::Force2d& item) {
        std::cout << "f2d(" << item.vxConst() << ", " << item.vyConst() << ")[each_f+" << item.inertia() << "]";
        return os;
    }
}
}

#endif