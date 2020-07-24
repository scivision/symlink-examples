# Symbolic link checks

Checking for platform-specific issues with symbolic links using Python.
Python
[pathlib](https://docs.python.org/3/library/pathlib.html)
is generally a robust high-level Python standard library interface that works on any platform.
There were a few bugs with the filesystem on Windows that weren't fixed until Python 3.8.

## Windows Developer Mode

Python &ge; 3.8 is generally required to work with symbolic links on Windows.
Additionally, either
[group permissions (Windows 10 Pro) or Developer Mode (Windows 10 non-Pro) need to be enabled](https://www.scivision.dev/windows-symbolic-link-permission-enable)
for non-admin users to use symbolic links on Windows in general (even without Python).
To help avoid confusing error messages, we use functions from
[softlink_check.py](./softlink_checks.py)
in our programs to help ensure meaningful error messages are generated if necessary symbolic links are not available.
Perhaps it would be better to include such functionality in Python itself going forward.
