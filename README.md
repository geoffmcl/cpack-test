# CPack Test

Just a simple test of using CMake CPack to package the project for distribution. This is of 
no concern for the casual builder. This test-app binary does really nothing. It is a 
test of package building and a source distribution zip.

## Building

This simple CPack Test is built using [CMake][1] as the configuration and generation of native build files.

   [1]: http://www.cmake.org/

- In Unix/OSX

1. `cd build`

2. `cmake .. [-DCMAKE_INSTALL_PREFIX=/root/path/for/install] [-G "Generator of choice"]`

3. `make`

4. `[sudo] make install`

- In Windows

1. `cd build`

2. `cmake .. [-DCMAKE_INSTALL_PREFIX=/root/path/for/install] [-G "Generator of choice"]`

3. `cmake --build . --config Release`

4. `cmake --build . --config Release --target INSTALL`

- Alterntatively, using cmake-gui

1. `Load GUI'

2. `Set path to source`

3. `Set path to source/build folder`

4. `Choose/Set Generator of choice`

5. `Click [Configure]` Maybe needed more than once

6. 'Click [Generation]`

7. `Load or run build tools`

For example, if in Windows with MSVC installed, this last step would be to load the MSVC IDE, and load the test-cpack.sln file, and
proceed with the building of various configurations.

## Package Building

This is the extra step to generate the distribution package

- cmake --build . --config Release --target PACKAGE

In windows thsi should generate a test-cpack-3.0.0-win32.exe using NSIS, for installing the exe, and 
the headers, or other dev components...

## Source Packaging

To generate the source archive, a zip in this case -

- cpack --config CPackSourceConfig.cmake

This should generate a source zip for distribution. Take care all backup files 
are removed before running this.

;eof
