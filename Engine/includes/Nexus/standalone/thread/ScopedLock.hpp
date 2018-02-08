#ifndef NEXUS_ENGINE__SCOPED_LOCK
#define NEXUS_ENGINE__SCOPED_LOCK

#include <mutex>

namespace nx {
namespace thread{
    class ScopedLock {
        public:
            ScopedLock()
            {
                m_.lock();
            }

            ~ScopedLock()
            {
                m_.unlock();
            }

        private:
            std::mutex m_;
    };
}
}

#endif