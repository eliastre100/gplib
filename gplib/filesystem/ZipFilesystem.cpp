#include <iostream>
#include <unordered_map>
#include <filesystem/ZipFilesystem.hpp>

#include "filesystem/ZipFilesystem.hpp"
#include "exceptions/NoSuchFile.hpp"
#include "exceptions/BadFileFormat.hpp"

static std::unordered_map<int, std::string> libZipErrors{
        { ZIP_ER_EXISTS, "The file already exist" },
        { ZIP_ER_INCONS, "Inconsistencies were found in the file" },
        { ZIP_ER_MEMORY, "Required memory could not be allocated" },
        { ZIP_ER_NOENT, "The file specified by path does not exist" },
        { ZIP_ER_NOZIP, "The file specified is not a zip archive" },
        { ZIP_ER_OPEN, "The file specified by path could not be opened" },
        { ZIP_ER_READ, "The file specified by path could not be read" },
        { ZIP_ER_SEEK, "The file specified by path does not allow seeks" },
        { ZIP_ER_EOF, "Unexpected end-of-file found while reading from a file" },
        { ZIP_ER_INTERNAL, "The callback function of an added or replaced file returned an error but failed to report which" },
        { ZIP_ER_INVAL, "The path argument is NULL" },
        { ZIP_ER_RENAME, "A temporary file could not be renamed to its final name" },
        { ZIP_ER_TMPOPEN, "A temporary file could not be created" },
        { ZIP_ER_WRITE, "A file write failed" },
        { ZIP_ER_ZLIB, "An error occurred while (de)compressing a stream with zlib" }
};

void gplib::filesystem::ZipFilesystem::open(const std::string &file) {
    int status;

    _zipfile = zip_open(file.c_str(), ZIP_RDONLY, &status);
    if (_zipfile == nullptr) {
        throwLibZipError(status, file);
    }
}

bool gplib::filesystem::ZipFilesystem::isOpen() const {
    return _zipfile != nullptr;
}

std::vector<std::string> gplib::filesystem::ZipFilesystem::getFileNames() const {
    std::vector<std::string> files;
    zip_int64_t num_entries = zip_get_num_entries(_zipfile, 0);

    for (zip_uint64_t i = 0; i < num_entries; ++i) {
        std::string filename(zip_get_name(_zipfile, i, 0));
        if (filename.back() != '/') {
            files.emplace_back(filename);
        }
    }
    return files;
}

gplib::filesystem::ZipFilesystem::~ZipFilesystem() {
    close();
}

void gplib::filesystem::ZipFilesystem::close() {
    if (_zipfile != nullptr) {
        int status = zip_close(_zipfile);
        if (status != 0)
            throwLibZipError(status);
        _zipfile = nullptr;
    }
}

void gplib::filesystem::ZipFilesystem::throwLibZipError(int status, const std::string &file) const {
    switch (status) {
        case ZIP_ER_NOENT:
            throw gplib::exceptions::NoSuchFile(file);
        case ZIP_ER_NOZIP:
            throw gplib::exceptions::BadFileFormat(file, "ZIP");
        default:
            throw std::runtime_error(libZipErrors.at(status));
    }
}

std::vector<std::string> gplib::filesystem::ZipFilesystem::getFolderNames() const {
    std::vector<std::string> files;
    zip_int64_t num_entries = zip_get_num_entries(_zipfile, 0);

    for (zip_uint64_t i = 0; i < num_entries; ++i) {
        std::string filename(zip_get_name(_zipfile, i, 0));
        if (filename.back() == '/') {
            filename.pop_back();
            files.emplace_back(filename);
        }
    }
    return files;}
