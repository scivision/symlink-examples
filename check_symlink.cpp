// Check that filesystem is capable of symbolic links with this compiler.

#include <iostream>
#include <cstdlib>

#ifndef __has_include
#error "Compiler not C++17 compliant"
#endif

#if __has_include(<filesystem>)
#include <filesystem>
namespace fs = std::filesystem;
#elif __has_include(<experimental/filesystem>)
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;
#else
#error "No C++17 filesystem support"
#endif



int main(int argc, char **argv){

auto tgt = fs::canonical(argv[0]);

if(!fs::is_regular_file(tgt)) {
  std::cerr << "ERROR: target " << tgt << " is not a regular file" << std::endl;
  return EXIT_FAILURE;
}

auto lnk = tgt.parent_path() / "test.lnk";

std::error_code ec;

if(!fs::exists(lnk)) {
  fs::create_symlink(tgt, lnk, ec);
  if (ec) {
    std::cerr << "ERROR: could not create_symlink: " << ec.message() << std::endl;
    #ifdef __MINGW32__
    std::cerr << "ERROR: this is a known issue with MinGW GCC" << std::endl;
    return 77;
    #endif
    return EXIT_FAILURE;
  }
  std::cout << "created symlink: " << lnk << std::endl;
}

auto s = fs::status(lnk);

if(fs::is_symlink(s)) {
  std::cout << lnk << " is a symlink" << std::endl;
  return EXIT_SUCCESS;
}

// WORKAROUND: C++ filesystem bug by read_symlink and equivalence
auto t = fs::read_symlink(lnk, ec);
if (ec) {
  std::cerr << "ERROR: could not read_symlink: " << lnk << " " << ec.message() << std::endl;
}
else if(fs::equivalent(tgt, t)) {
  std::cout << lnk << " is a symlink, but is_symlink didn't recognize this -- C++ stdlib filesystem bug." << std::endl;
  return EXIT_SUCCESS;
}
// END WORKAROUND

// Unexpected failure, diagnose
if (fs::is_regular_file(s)) {
  std::cerr << lnk << " detected as regular file instead of symlink" << std::endl;
}
else if (!fs::exists(s)) {
  std::cerr << lnk << " does not exist" << std::endl;
}
else {
  std::cerr << lnk << " is not a symlink" << std::endl;
}

return EXIT_FAILURE;
}
