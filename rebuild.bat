@echo off
echo Destroid ols build...
if exist build rmdir /s /q build

echo Creating...
mkdir build
cd build
cmake .. -G "MinGW Makefiles" -DCMAKE_PREFIX_PATH=C:/Qt/6.11.0/mingw_64
cmake --build .

echo Complite!
pause