#include <gtest/gtest.h>
#include <algorithm>
#include "exceptions/BadFileFormat.hpp"
#include "filesystem/ZipFilesystem.hpp"
#include "exceptions/NoSuchFile.hpp"

TEST(ZipFilesystem, openValidFile) {
    gplib::filesystem::ZipFilesystem fs;

    ASSERT_FALSE(fs.isOpen());
    ASSERT_NO_THROW(fs.open("assets/testfile.zip"));
    ASSERT_TRUE(fs.isOpen());
}

TEST(ZipFilesystem, openUnexistingFile) {
    gplib::filesystem::ZipFilesystem fs;

    ASSERT_FALSE(fs.isOpen());
    ASSERT_THROW(fs.open("assets/nonExistingFile.zip"), gplib::exceptions::NoSuchFile);
}

TEST(ZipFilesystem, openNonZipFile) {
    gplib::filesystem::ZipFilesystem fs;

    ASSERT_FALSE(fs.isOpen());
    ASSERT_THROW(fs.open("assets/testfile.txt"), gplib::exceptions::BadFileFormat);
}

TEST(ZipFilesystem, isOpenOpendedFile) {
    gplib::filesystem::ZipFilesystem fs;

    fs.open("assets/testfile.zip");
    ASSERT_TRUE(fs.isOpen());
}

TEST(ZipFilesystem, isOpenNotOpenedFile) {
    gplib::filesystem::ZipFilesystem fs;

    ASSERT_FALSE(fs.isOpen());
}

TEST(ZipFilesystem, isOpenClosedFile) {
    gplib::filesystem::ZipFilesystem fs;

    fs.open("assets/testfile.zip");
    fs.close();
    ASSERT_FALSE(fs.isOpen());
}

TEST(ZipFilesystem, closeNotOpenedFile) {
    gplib::filesystem::ZipFilesystem fs;

    fs.close();
    EXPECT_FALSE(fs.isOpen());
}

TEST(ZipFilesystem, closeOpenedFile) {
    gplib::filesystem::ZipFilesystem fs;

    fs.open("assets/testfile.zip");
    EXPECT_TRUE(fs.isOpen());
    fs.close();
    EXPECT_FALSE(fs.isOpen());
}

TEST(ZipFilesystem, getFileNamesHaveFileNames) {
    gplib::filesystem::ZipFilesystem fs;

    fs.open("assets/testfile.zip");
    auto fileNames = fs.getFileNames();
    EXPECT_TRUE(std::find(fileNames.begin(), fileNames.end(), "file1") != fileNames.end());
    EXPECT_TRUE(std::find(fileNames.begin(), fileNames.end(), "file2") != fileNames.end());
    EXPECT_TRUE(std::find(fileNames.begin(), fileNames.end(), "file3") != fileNames.end());
}

TEST(ZipFilesystem, getFileNamesDoesntHaveFolderNames) {
    gplib::filesystem::ZipFilesystem fs;

    fs.open("assets/testfile.zip");
    auto fileNames = fs.getFileNames();
    EXPECT_FALSE(std::find(fileNames.begin(), fileNames.end(), "folder/") != fileNames.end());
}

TEST(ZipFilesystem, getDirectoryNamesHaveirectoryNames) {
    gplib::filesystem::ZipFilesystem fs;

    fs.open("assets/testfile.zip");
    auto fileNames = fs.getFolderNames();
    EXPECT_TRUE(std::find(fileNames.begin(), fileNames.end(), "folder") != fileNames.end());
}

TEST(ZipFilesystem, getDirectoryNamesDoesntHaveFileNames) {
    gplib::filesystem::ZipFilesystem fs;

    fs.open("assets/testfile.zip");
    auto fileNames = fs.getFolderNames();
    EXPECT_FALSE(std::find(fileNames.begin(), fileNames.end(), "file1") != fileNames.end());
    EXPECT_FALSE(std::find(fileNames.begin(), fileNames.end(), "file2") != fileNames.end());
    EXPECT_FALSE(std::find(fileNames.begin(), fileNames.end(), "file3") != fileNames.end());
}
