#ifndef NEXUS_ENGINE__KEYBOARD_HPP
# define NEXUS_ENGINE__KEYBOARD_HPP

#include <algorithm>
#include <unordered_map>

#include "Nexus/log.hpp"

namespace nx {
namespace env {
    class Keyboard
    {
        struct EnumClassHash
        {
            template <typename T>
            std::size_t operator()(T t) const
            {
                return static_cast<std::size_t>(t);
            }
        };

        public:
            enum  	Key { 
                Unknown = -1, A = 0, B, C, 
                D, E, F, G, 
                H, I, J, K, 
                L, M, N, O, 
                P, Q, R, S, 
                T, U, V, W, 
                X, Y, Z, Num0, 
                Num1, Num2, Num3, Num4, 
                Num5, Num6, Num7, Num8, 
                Num9, Escape, LControl, LShift, 
                LAlt, LSystem, RControl, RShift, 
                RAlt, RSystem, Menu, LBracket, 
                RBracket, SemiColon, Comma, Period, 
                Quote, Slash, BackSlash, Tilde, 
                Equal, Dash, Space, Return, 
                BackSpace, Tab, PageUp, PageDown, 
                End, Home, Insert, Delete, 
                Add, Subtract, Multiply, Divide, 
                Left, Right, Up, Down, 
                Numpad0, Numpad1, Numpad2, Numpad3, 
                Numpad4, Numpad5, Numpad6, Numpad7, 
                Numpad8, Numpad9, F1, F2, 
                F3, F4, F5, F6, 
                F7, F8, F9, F10, 
                F11, F12, F13, F14, 
                F15, Pause, KeyCount 
            };

        typedef std::unordered_map<nx::env::Keyboard::Key, bool, nx::env::Keyboard::EnumClassHash> Keymap;            

        public:
            Keyboard()
            {
                for (int k = -1; k <= nx::env::Keyboard::Key::KeyCount; ++k)
                    keys_[static_cast<Key>(k)] = false;
            }

            Keyboard(const Keyboard& other)
            {
                const auto& okeys = other.getKeys(); 
                std::for_each(okeys.begin(), okeys.end(), [&](const Keymap::value_type& item) {
                    setKeyState(item.first, item.second);
                });
            }

            Keyboard& operator=(const Keyboard& other)
            {
                if (&other != this)
                {
                    const auto& okeys = other.getKeys(); 
                    std::for_each(okeys.begin(), okeys.end(), [&](const Keymap::value_type& item) {
                        setKeyState(item.first, item.second);
                    });
                }

                return *this;
            }

            bool compare(const Keyboard& other)
            {
                const auto& okeys = other.getKeys();
                for (const auto& item : keys_)
                {
                    if (item.second != okeys.at(static_cast<Key>(item.first)))
                        return false;
                }
                return true;
            }

            bool operator==(const Keyboard& other)
            {
                return compare(other);
            }

            bool operator!=(const Keyboard& other)
            {
                return !compare(other);
            }

            ~Keyboard() {}

        private:
            nx::env::Keyboard::Keymap keys_;

        public:
            const Keymap& getKeys() const
            {
                return keys_;
            }

        public:
            void setKeyState(int key, bool state)
            {
                if (key < -1 || key > Key::KeyCount)
                {
                    nx::Log::warning("Invalid key for setter (" + std::to_string(key) + ")", "BAD_SET_KEY_STATE");
                    return;
                }

                keys_[static_cast<Key>(key)] = state;
            }

            bool getKeyState(int key)
            {
                if (key < -1 || key > Key::KeyCount)
                {
                    nx::Log::warning("Invalid key for setter (" + std::to_string(key) + ")", "BAD_SET_KEY_STATE");
                    return false;
                }

                return keys_.at(static_cast<Key>(key));
            }

            void print()
            {
                nx::Log::debug("Printing keymap...");
                for (int k = -1; k <= nx::env::Keyboard::Key::KeyCount; ++k)
                    nx::Log::debug("Key." + std::to_string(k) + ": " + std::to_string(keys_.at(static_cast<Key>(k))));
                nx::Log::debug("--End of print--");
            }
    };
}
}

#endif