#include <string>
#include "unmixing/unmixing.h"

#include <dirent.h>
#include <cstring>
#include <iostream>
#include <vector>
#include <memory>

#include <bits/stdc++.h>
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>

namespace {
std::vector<std::string> GetDirectoryFiles(const std::string& dir) {
  std::vector<std::string> files;
  std::shared_ptr<DIR> directory_ptr(opendir(dir.c_str()), [](DIR* dir){ dir && closedir(dir); });
  struct dirent *dirent_ptr;
  if (!directory_ptr) {
    std::cout << "Error opening : " << std::strerror(errno) << dir << std::endl;
    return files;
  }

  while ((dirent_ptr = readdir(directory_ptr.get())) != nullptr) {
    files.push_back(std::string(dirent_ptr->d_name));
  }
  return files;
}
}  // namespace

std::string remove_extension(const std::string& filename) {
    size_t lastdot = filename.find_last_of(".");
    if (lastdot == std::string::npos) return filename;
    return filename.substr(0, lastdot);
}

int main1(int argc, char** argv)
{
    const std::string image_file_path(argv[1]);
    const std::string output_directory_path(argv[2]);

    ColorUnmixing::compute_color_unmixing(image_file_path, output_directory_path);

    return 0;
}


int main2(int argc, char** argv)
{
    const std::string input_dir(argv[1]);
    const std::string output_dir(argv[2]);

    const auto& image_names = GetDirectoryFiles(input_dir);
    for (const auto& image_name : image_names) {
        if (image_name.compare(".") == 0 || image_name.compare("..") == 0)
            continue;
        std::string image_file_path = input_dir + "/" + image_name;
        std::string image_output_dir = output_dir + "/" + remove_extension(image_name) + "/";
        mkdir(image_output_dir.c_str(), 0777);
        std::cout << image_name << " " << image_file_path << " " << image_output_dir << std::endl;
        ColorUnmixing::compute_color_unmixing(image_file_path, image_output_dir);
    }

    return 0;
}

int main(int argc, char** argv)
{
    // main1(argc, argv);
    main2(argc, argv);
}
