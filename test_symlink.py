#!/usr/bin/env python3
"""
check that symbolic links are OK on your system.

For example, Windows may restrict users from creating symbolic links.
"""
from pathlib import Path
import tempfile
import os
import sys


def main():

    try:
        test_symlink()
    except OSError:
        symlink_help()

    test_bad_link()


def symlink_help():

    msg = "Symbolic links are not working on your system."
    if os.name == "nt":
        if sys.version_info < (3, 8):
            msg += "\n Python >= 3.8 required for symlinks in non-admin mode on Windows"
        msg += "\n You may need to enable Windows Developer Mode in Windows Control Panel for symlinks to work."

    raise OSError(msg)


def test_symlink():
    """
    checks if filesystem and permissions allow symlinks
    This can be an issue on Windows
    """

    with tempfile.TemporaryDirectory() as d:
        r = Path(d)

        f1 = r / "actual_file.txt"
        f2 = r / "link.txt"
        f1.touch()
        f2.symlink_to(f1)

        if not f2.is_symlink():
            symlink_help()


def test_bad_link():

    with tempfile.TemporaryDirectory() as d:
        r = Path(d)

        not_exist_file = r / "not-exist.txt"
        broken_link = r / "bad.txt"

        broken_link.symlink_to(not_exist_file)

        if not broken_link.is_symlink():
            raise OSError("Symbolic links are not working on your system.")


if __name__ == "__main__":
    main()
