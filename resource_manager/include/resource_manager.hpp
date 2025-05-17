#ifndef RESOURCE_MANAGER_HPP
#define RESOURCE_MANAGER_HPP

#include <string>
#include <vector>
#include <memory>
#include <fstream>
#include <stdexcept>

namespace rm
{

    class Resource
    {
    public:
        virtual ~Resource() noexcept = default;
        virtual std::string getInfo() const = 0;
    };

    class FileResource : public Resource
    {
        // TODO: Ajouter membres et méthodes

    private:
        std::ofstream file_;
        std::string filename_;

    public:
        FileResource(const std::string &filename) : filename_(filename)
        {
            file_.open(filename_);
            if (!file_)
            {
                throw std::runtime_error("Could not open file: " + filename_);
            }
        }

        ~FileResource() noexcept override
        {
            if (file_.is_open())
            {
                file_.close();
            }
        }

        FileResource(FileResource &&other) : filename_(std::move(other.filename_)), file_(std::move(other.file_))
        {
            other.filename_.clear();
            other.file_.close();
        }

        FileResource &operator=(FileResource &&other)
        {
            if (this != &other)
            {
                if (file_.is_open())
                {
                    file_.close();
                }
                filename_ = std::move(other.filename_);
                file_ = std::move(other.file_);
                other.filename_.clear();
                other.file_.close();
            }
            return *this;
        }

        std::string getInfo() const override
        {
            return "FileResource: " + filename_;
        }
    };

    class ResourceManager
    {
        // TODO: Ajouter membres et méthodes
    };

} // namespace rm

#endif // RESOURCE_MANAGER_HPP