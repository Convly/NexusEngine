/*
** Directory.hpp for cpp_arcade in /Users/antoine/rendu/cpp/cpp_arcade
**
** Made by Antoine Dury
** Login   <antoine.dury@epitech.eu>
**
** Started on  Thu Mar 16 14:57:34 2017 Antoine Dury
** Last update Fri Dec 22 22:23:48 2017 Quentin Metge
*/

#ifndef DIRRENT_NOT_OPEN
# define DIRRENT_NOT_OPEN "Dirrent not open"

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <sys/types.h>
#include <dirent.h>

class Directory
{
public:
  Directory(const std::string &file){
    this->path = file;
    this->dirent = nullptr;
  }

  Directory(const Directory &oth){
    this->path = oth.path;
    this->dirent = nullptr;
  }

  ~Directory(void){
    this->close();
  }

  /*
  ** Open directory in parameters
  ** Return: true -> Success else false;
  */
  bool open(void)
  {
    if (this->path.empty() || nullptr == (this->dirent = opendir(this->path.c_str())))
    {
      return false;
    }
    return true;
  }

  /*
  ** Close directory in parameters
  ** Return: true -> Success else false;
  */
  bool close(void)
  {
    bool res = true;

    if (this->dirent)
    {
      if (-1 == closedir(this->dirent))
      {
        return false;
      }
      else
      {
        this->dirent = nullptr;
      }
    }
    return res;
  }

  /*
  ** Read all element in directory and load vector in parameter.
  ** Don't take "." and ".." in directory, no recursion in sub directory.
  */
  void getFiles(std::vector<std::string> &toFile) const
  {
    if (nullptr == this->dirent)
    {
      throw std::runtime_error(DIRRENT_NOT_OPEN);
    }
    std::string fileName;
    for (struct dirent *tmp = readdir(this->dirent); nullptr != tmp; tmp = readdir(this->dirent))
    {
      fileName = tmp->d_name;
      if ("." != fileName && ".." != fileName)
      {
        toFile.push_back(move(fileName));
      }
    }
  }

  std::string const & getPath(void) const{
    return this->path;
  }

private:
  std::string path;
  DIR *dirent;
};

inline void getComponentFilesNames(const Directory &dir, std::vector<std::string>& filesNames)
{
  std::vector<std::string> filesDir;

  dir.getFiles(filesDir);
  std::for_each(filesDir.begin(), filesDir.end(),
		[&](std::string &file){
		  file = dir.getPath() + "/" + file;
		});

  for (auto const &elem: filesDir)
    {
      Directory dirTmp(elem);
      if (true == dirTmp.open())
    	{
    	  getComponentFilesNames(dirTmp, filesNames);
    	  dirTmp.close();
    	}
      else
    	{
    	  filesNames.push_back(elem);
    	}
    }
}

inline bool getComponentFilesName(const std::string& path, std::vector<std::string>& filesNames)
{
  filesNames.clear();
  if (path.empty())
    return false;
  Directory dir(path);
  if (false == dir.open())
    return true;
  getComponentFilesNames(dir, filesNames);
  if (false == dir.close()){
    std::cerr << "Error can't close file" << std::endl;
    return false;
  }
  return true;
}

#endif
