#include <iostream>
#include <boost/serialization/access.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <memory>
#include <sstream>

namespace nx {
    class PlaceHolder
    {
    public:
        virtual ~PlaceHolder(){}
        PlaceHolder(){}
    private:
        friend class boost::serialization::access;
        template<class Archive>
        void serialize(Archive & ar, const unsigned int version)
        {
        }

    };

    template<typename T>
    class DerivedPlacedHolder:
        public PlaceHolder
    {
        public:
            DerivedPlacedHolder()
            {

            }
            DerivedPlacedHolder(T &value)
            {
                m_value = value;
            }
        T m_value;

    private:
        friend class boost::serialization::access;
        template<class Archive>
        void serialize(Archive & ar, const unsigned int version)
        {
            ar & boost::serialization::base_object<PlaceHolder>(*this);
            ar & m_value;
        }
    };

    class Any
    {
    public:
        Any()
        {

        }

        template<typename T>
        Any(const T &value)
        {
            m_placeholder.reset(new nx::DerivedPlacedHolder<T>(const_cast<T&>(value)));
        }

        template<typename T>
        void operator=(const T &value)
        {
            m_placeholder.reset(new nx::DerivedPlacedHolder<T>(const_cast<T&>(value)));
        }

    protected:
        friend class boost::serialization::access;
        template<class Archive>
        void serialize(Archive & ar, const unsigned int version)
        {
            ar & m_placeholder;
        }

        template<typename T>
        friend    T Anycast(Any &val);

        std::shared_ptr<PlaceHolder> m_placeholder;
    };

    template<typename T>
    T Anycast(Any &val)
    {
        std::shared_ptr<nx::DerivedPlacedHolder<T>> concrete = std::dynamic_pointer_cast<nx::DerivedPlacedHolder<T> >(val.m_placeholder);
        if (concrete.get()==NULL)
            throw std::invalid_argument("Not convertible");

        return concrete->m_value;
    }
}