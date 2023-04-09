# Symbolic link checks

[![ci](https://github.com/scivision/symlink-checks/actions/workflows/ci.yml/badge.svg)](https://github.com/scivision/symlink-checks/actions/workflows/ci.yml)

Checking for platform-specific issues with symbolic links using Python [pathlib](https://docs.python.org/3/library/pathlib.html),
a robust high-level Python standard library interface that works on any platform.

[C++ filesystem](https://en.cppreference.com/w/cpp/filesystem) symbolic links are demonstrated in
[ffilesystem-concepts](https://github.com/scivision/ffilesystem-concepts).

## Windows symlinks

Python &ge; 3.8 is generally required to work with symbolic links on Windows.
Additionally, either
[group permissions (Windows Pro) or Developer Mode (Windows non-Pro) need to be enabled](https://www.scivision.dev/windows-symbolic-link-permission-enable)
for non-admin users to use symbolic links on Windows in general (even without Python).
To help avoid confusing error messages, we use functions from
[test_symlink.py](./test_symlink.py)
in our programs to help ensure meaningful error messages are generated if necessary symbolic links are not available.

Enable
[Windows symbolic links](https://blogs.windows.com/windowsdeveloper/2016/12/02/symlinks-windows-10/)
by enabling
[Windows developer mode](https://learn.microsoft.com/en-us/windows/apps/get-started/developer-mode-features-and-debugging#additional-developer-mode-features).
