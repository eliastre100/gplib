#include "exceptions/BadFileFormat.hpp"
#include "exceptions/BadFileFormat.hpp"

gplib::exceptions::BadFileFormat::BadFileFormat(const std::string &filename, const std::string &expectedFormat)
        : _filename(filename), _expectedFormat(expectedFormat),
          runtime_error(filename + " is not of the expected " + expectedFormat + " format"){

}

const std::string &gplib::exceptions::BadFileFormat::getFilename() const {
    return _filename;
}

const std::string &gplib::exceptions::BadFileFormat::getExpectedFormat() const {
    return _expectedFormat;
}
