#ifndef RESOURCE_MANAGER_HPP
#define RESOURCE_MANAGER_HPP

#include <string>
#include <vector>
#include <memory>
#include <fstream>
#include <stdexcept>
#include <iostream>

namespace rm
{
    class Resource
    {
    public:
        virtual ~Resource() noexcept = default;
        virtual std::string getInfo() const = 0;
        virtual std::unique_ptr<Resource> clone() const = 0;
    };

    class FileResource : public Resource
    
    {
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

        FileResource(const FileResource &other) : filename_(other.filename_)
        {
            file_.open(filename_);
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

        std::unique_ptr<Resource> clone() const override
        {
            return std::make_unique<FileResource>(*this);
        }

        std::string getInfo() const override
        {
            return "FileResource: " + filename_;
        }
    };

    class ResourceManager
    {
    private:
        std::vector<std::unique_ptr<Resource>> resources_;

    public:
        void add(Resource &resource)
        {
            resources_.emplace_back(resource.clone());
        }

        void add(FileResource &&resource)
        {
            resources_.emplace_back(std::make_unique<FileResource>(std::move(resource)));
        }

        void remove(size_t index)
        {
            if (index < resources_.size())
            {
                resources_.erase(resources_.begin() + index);
            }
            else
            {
                throw std::out_of_range("Index out of range");
            }
        }

        void printResources()
        {
            for (const auto &resource : resources_)
            {
                std::cout << resource->getInfo() << std::endl;
            }
        }
    };

} // namespace rm

#endif // RESOURCE_MANAGER_HPP