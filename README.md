# CPack Test

Just a simple test of using <a target="_blank" href="http://www.cmake.org/">CMake</a> CPack to package the project for distribution. This is of 
no use or concern for the casual builder. This test-app binary does really nothing. It is a 
test of package building and a source distribution zip.

## Building

This simple CPack Test is built using <a target="_blank" href="http://www.cmake.org/">CMake</a> as the configuration and generation of 
native build files.

#### In Unix/OSX

1. `cd build`

2. `cmake .. [-DCMAKE_INSTALL_PREFIX=/root/path/for/install] [-G "Generator of choice"]`

3. `make`

4. `[sudo] make install`

#### In Windows

1. `cd build`

2. `cmake .. [-DCMAKE_INSTALL_PREFIX=/root/path/for/install] [-G "Generator of choice"]`

3. `cmake --build . --config Release`

4. `cmake --build . --config Release --target INSTALL`

#### Alterntatively, using cmake-gui

1. `Load GUI`

2. `Set path to source`

3. `Set path to source/build folder`

4. `Choose/Set Generator of choice`

5. `Click [Configure]` Maybe needed more than once

6. `Click [Generation]`

7. `Load or run build tools`

For example, if in Windows with MSVC installed, this last step would be to load the MSVC IDE, and load the test-cpack.sln file, and proceed with the building of various configurations.

## Package Building

This is the extra step to generate the distribution package

#### Windows

`cmake --build . --config Release --target PACKAGE`

In windows this should generate a test-cpack-3.0.0-win32.exe, using NSIS, if installed, and available, or a test-cpack-3.0.0-win32.msi, using WIX, if installed and available, for installing the exe, and the headers, or other dev components...

#### Unix/OS-X

`make package`

In linux this shoudl generate a test-cpack-3.0.0-Linux.deb, for installing the binary, and 
the headers, or other dev components...

## Source Packaging

To generate the source archive, a zip in windows, and a tar.gz in linux -

`cpack --config CPackSourceConfig.cmake`

This should generate a source archive for distribution. Take care all backup files and 
other non-source files are removed before running this. All items is the .git and 
build directories are already ignored.

## Additional Notes

In Windows the CPack generators normally include -

  1. **NSIS** - (Nullsoft Scriptable Install System) - Generates an installer EXE - see <a target="_blank" href="http://nsis.sourceforge.net/Main_Page">nsis.sourceforge</a> - needs to be installed.
  2. **WIX** - WiX Toolset - Generates an installer MSI - see <a target="_blank" href="  https://wix.codeplex.com/releases/view/610859">wix.codeplex</a> - needs to be installed and a PATH added to candle.exe

Both these generator need special variables set in the CMakeLists.txt file before including the CPack module.

;eof
