#include "exceptions/NoSuchFile.hpp"
#include "exceptions/NoSuchFile.hpp"

gplib::exceptions::NoSuchFile::NoSuchFile(const std::string &filename)
        : runtime_error("No such file or directory " + filename),
          _filename(filename) {}

const std::string &gplib::exceptions::NoSuchFile::getFilename() const {
    return _filename;
}
