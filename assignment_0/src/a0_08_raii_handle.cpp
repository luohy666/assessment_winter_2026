#include <cstdio>
#include <iostream>
#include <string>
#include <utility>

class FileHandle {
public:
    FileHandle() = default;
    FileHandle(const char* path, const char* mode) {
        fp_ = std::fopen(path, mode);
    }
    ~FileHandle() {
        if (fp_) {
            std::fclose(fp_);
            fp_ = nullptr;
        }
    }

    FileHandle(const FileHandle&) = delete;
    FileHandle& operator=(const FileHandle&) = delete;

    FileHandle(FileHandle&& other) noexcept
        : fp_(other.fp_) {
        other.fp_ = nullptr;
    }

    FileHandle& operator=(FileHandle&& other) noexcept {
        if (this != &other) {
            if (fp_) {
                std::fclose(fp_);
            }
            fp_ = other.fp_;
            other.fp_ = nullptr;
        }
        return *this;
    }

    bool valid() const {
        return fp_ != nullptr;
    }

    FILE* get() const {
        return fp_;
    }

private:
    FILE* fp_ = nullptr;
};

bool CopyFile(const std::string& in_path, const std::string& out_path) {
    FileHandle in(in_path.c_str(), "rb");
    if (!in.valid()) {
        return false;
    }

    FileHandle out(out_path.c_str(), "wb");
    if (!out.valid()) {
        return false;
    }

    char buffer[4096];
    size_t bytes_read;

    while ((bytes_read = std::fread(buffer, 1, sizeof(buffer), in.get())) > 0) {
        size_t bytes_written = std::fwrite(buffer, 1, bytes_read, out.get());
        if (bytes_written != bytes_read) {
            return false;
        }
    }

    if (std::ferror(in.get())) {
        return false;
    }

    return true;
}

int main() {
    std::string in_path, out_path;
    if (!(std::cin >> in_path >> out_path)) {
        return 0;
    }

    if (CopyFile(in_path, out_path)) {
        std::cout << "OK" << std::endl;
    } else {
        std::cout << "FAIL" << std::endl;
    }

    return 0;
}