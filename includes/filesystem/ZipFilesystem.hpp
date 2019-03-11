#ifndef GPLIB_ZIPFILESYSTEM_H
#define GPLIB_ZIPFILESYSTEM_H

#include <string>
#include <zip.h>
#include <vector>

namespace gplib{
    namespace filesystem {
        class ZipFilesystem
        {

        private:
            zip_t *_zipfile = nullptr;

        public:
            virtual ~ZipFilesystem();

            void open(const std::string &file);
            bool isOpen() const;
            void close();

            std::vector<std::string> getFileNames() const;
            std::vector<std::string> getFolderNames() const;

        private:
            void throwLibZipError(int status, const std::string &file = "Unknown") const;

        };
    }
}


#endif
