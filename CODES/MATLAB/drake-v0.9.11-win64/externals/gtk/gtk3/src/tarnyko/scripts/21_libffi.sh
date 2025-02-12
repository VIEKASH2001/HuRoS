
cd ../../libs/21_libffi
tar xfvz libffi-3.0.12.tar.gz
cd libffi-3.0.12


echo Compile...

./configure --host=x86_64-w64-mingw32 --enable-static --enable-shared --prefix="$PREFIX"
make clean
make 2>&1 | tee ../../../z_Install/win64_build/logs/21_libffi-make.log
make install 2>&1 | tee ../../../z_Install/win64_build/logs/21_libffi-makeinstall.log


cd ..
rm -rf libffi-3.0.12
