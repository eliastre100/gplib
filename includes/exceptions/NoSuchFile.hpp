#ifndef GPLIB_NOSUCHFILEEXCEPTION_HPP
#define GPLIB_NOSUCHFILEEXCEPTION_HPP

#include <stdexcept>
#include <string>

namespace gplib {
    namespace exceptions {
        class NoSuchFile: public std::runtime_error {
        private:
            std::string _filename;

        public:
            explicit NoSuchFile(const std::string &filename);

            const std::string &getFilename() const;
        };
    }
}

#endif //GPLIB_NOSUCHFILEEXCEPTION_HPP
