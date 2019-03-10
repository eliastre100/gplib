#ifndef GPLIB_BADFILEFORMAT_HPP
#define GPLIB_BADFILEFORMAT_HPP

#include <stdexcept>
#include <string>

namespace gplib {
    namespace exceptions {
        class BadFileFormat : public std::runtime_error {
        private:
            std::string _filename;
            std::string _expectedFormat;

        public:
            explicit BadFileFormat(const std::string &filename, const std::string &expectedFormat);

            const std::string &getFilename() const;
            const std::string &getExpectedFormat() const;
        };
    };
}


#endif //GPLIB_BADFILEFORMAT_HPP
