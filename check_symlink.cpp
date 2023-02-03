// Check that filesystem is capable of symbolic links with this compiler.

#include <iostream>
#include <cstdlib>

#ifdef __MINGW32__
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <system_error>
#endif

#if __has_include(<filesystem>)
#include <filesystem>
namespace fs = std::filesystem;
#else
#error "No C++17 filesystem support"
#endif


int main(int argc, char **argv){

auto tgt = fs::canonical(argv[0]);
auto lnk = tgt.parent_path() / "test.lnk";

if(!fs::is_regular_file(tgt)) {
  std::cerr << "ERROR: target " << tgt << " is not a regular file" << std::endl;
  return EXIT_FAILURE;
}

std::error_code ec;

if(!fs::exists(lnk)) {

#ifdef __MINGW32__
  auto p = SYMBOLIC_LINK_FLAG_ALLOW_UNPRIVILEGED_CREATE;
  if(fs::is_directory(tgt))
    p |= SYMBOLIC_LINK_FLAG_DIRECTORY;

  auto s = CreateSymbolicLink(lnk.string().c_str(), tgt.string().c_str(), p);

  if (!s) {
    DWORD err = GetLastError();
    std::string message = std::system_category().message(err);
    std::cerr << "ERROR:CreateSymbolicLink: " << err << ": " << message << std::endl;
    if(err == ERROR_PRIVILEGE_NOT_HELD)
      std::cerr << R"(Enable Windows developer mode to use symbolic links:
      https://learn.microsoft.com/en-us/windows/apps/get-started/developer-mode-features-and-debugging)" << std::endl;

    return EXIT_FAILURE;
  }
#else
  fs::create_symlink(tgt, lnk, ec);
  if (ec) {
    std::cerr << "ERROR: could not create_symlink: " << ec.message() << std::endl;
    return EXIT_FAILURE;
  }
#endif
  std::cout << "created symlink: " << lnk << std::endl;
}

// auto s = fs::status(lnk);
// this is a bug, doesn't work for is_symlink on Windows

if(fs::is_symlink(lnk)) {
  std::cout << lnk << " is a symlink" << std::endl;
  return EXIT_SUCCESS;
}

// Unexpected failure, diagnose
if (fs::is_regular_file(lnk)) {
  std::cerr << lnk << " detected as regular file instead of symlink" << std::endl;
}
else if (!fs::exists(lnk)) {
  std::cerr << lnk << " does not exist" << std::endl;
}
else {
  std::cerr << lnk << " is not a symlink" << std::endl;
}

return EXIT_FAILURE;
}
