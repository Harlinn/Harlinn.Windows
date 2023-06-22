#pragma once
#ifndef HARLINN_COMMON_CORE_HCCDIRECTORYUTILS_H_
#define HARLINN_COMMON_CORE_HCCDIRECTORYUTILS_H_

#include "HCCIO.h"
#include "HCCString.h"


namespace Harlinn::Common::Core
{
    template<typename StringT>
    requires (IsWideString<StringT> || IsAnsiString<StringT>)
    class ApplicationDirectories
    {
    public:
        using StringType = std::remove_cvref_t<StringT>;
        using CharType = typename StringType::value_type;
        static constexpr CharType DirectorySeparator = static_cast<CharType>('\\');
        static constexpr CharType AltDirectorySeparator = static_cast<CharType>('/');
    private:
        static constexpr bool IsWide = IsWideString<StringType>;
        StringType executableDirectory_;
        StringType executableBaseName_;
        StringType rootDirectory_;
    public:
        ApplicationDirectories()
        {
            auto executable = IO::File::GetExecutableFilename<StringType>();
            IO::SplitPath<StringType> splitPath(executable);
            executableDirectory_ = splitPath.DirectoryPath();
            executableBaseName_ = splitPath.Name();

            rootDirectory_ = GetRootDirectory(executableDirectory_);
        }

        static WideString GetRootDirectory(const WideString& executableDirectory)
        {
            auto dir = ToLower(executableDirectory);
            static WideString toRemove[] = { L"bin\\",L"bin",L"x64\\release\\",L"x64\\release",L"x64\\debug\\", L"x64\\debug", L"release\\",L"release",L"debug\\", L"debug" };
            for (auto& str : toRemove)
            {
                if (dir.ends_with(str))
                {
                    return executableDirectory.substr(0, executableDirectory.size() - str.size());
                }
            }
            return executableDirectory;
        }
        static AnsiString GetRootDirectory(const AnsiString& executableDirectory)
        {
            auto dir = ToLower(executableDirectory);
            static AnsiString toRemove[] = { "bin\\","bin","x64\\release\\","x64\\release","x64\\debug\\", "x64\\debug", "release\\","release","debug\\", "debug" };
            for (auto& str : toRemove)
            {
                if (dir.ends_with(str))
                {
                    return executableDirectory.substr(0, executableDirectory.size() - str.size());
                }
            }
            return executableDirectory;
        }


        /// <summary>
        /// The name of the directory containing the current executable with the trailing directory separator '\\'.
        /// </summary>
        const StringType& ExecutableDirectory() const noexcept
        {
            return executableDirectory_;
        }
        /// <summary>
        /// The base name of the current executable.
        /// </summary>
        const StringType& ExecutableBaseName() const noexcept
        {
            return executableBaseName_;
        }

        /// <summary>
        /// The name of the installation root directory with the trailing directory separator '\\'.
        /// </summary>
        const StringType& RootDirectory() const noexcept
        {
            return rootDirectory_;
        }

        /// <summary>
        /// Expands the name of a directory relative to the path returned by RootDirectory(), 
        /// the result includes the trailing directory separator '\\'.
        /// </summary>
        StringType ExpandDirectory(const StringType& subDirectory) const
        {
            if (subDirectory.length() == 0 || IO::Path::IsDirectorySeparator(subDirectory))
            {
                return RootDirectory();
            }
            else
            {
                auto result = RootDirectory() + (IO::Path::StartsWithDirectorySeparator(subDirectory) ? subDirectory.substr(1, subDirectory.size() - 1) : subDirectory);
                if (IO::Path::EndsWithDirectorySeparator(subDirectory) == false)
                {
                    result += DirectorySeparator;
                }
                return result;
            }
        }

        /// <summary>
        /// <p>
        /// Expands the name of a directory relative to the path returned by 
        /// ExpandDirectory() for the subDirectory arguement. 
        /// </p>
        /// <p>
        /// This function is intended to form application specific directory paths, where
        /// executableBaseName is supposed to hold the base name of the executable for
        /// an application.
        /// </p>
        /// The result includes the trailing directory separator '\\'.
        /// </summary>
        StringType ExpandApplicationDirectoryEx(const StringType& subDirectory, const StringType& executableBaseName) const
        {
            return ExpandDirectory(subDirectory) + executableBaseName + DirectorySeparator;
        }
        StringType ExpandApplicationDirectoryEx(const StringType& subDirectory, const StringType& executableBaseName, const StringType& applicationSubDirectory) const
        {
            auto dir = ExpandApplicationDirectoryEx(subDirectory, executableBaseName);
            auto result = dir + (IO::Path::StartsWithDirectorySeparator(applicationSubDirectory) ? applicationSubDirectory.substr(1, applicationSubDirectory.size() - 1) : applicationSubDirectory);
            if (IO::Path::EndsWithDirectorySeparator(applicationSubDirectory) == false)
            {
                result += DirectorySeparator;
            }
            return result;
        }

        StringType ExpandApplicationDirectory(const StringType& subDirectory) const
        {
            return ExpandApplicationDirectoryEx(subDirectory, ExecutableBaseName());
        }
        StringType ExpandApplicationDirectory(const StringType& subDirectory, const StringType& applicationSubDirectory) const
        {
            return ExpandApplicationDirectoryEx(subDirectory, ExecutableBaseName(), applicationSubDirectory);
        }

    };
}

#endif
