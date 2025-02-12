
cd ../../libs/73_gnome-icon-theme
tar xfvJ gnome-icon-theme-3.6.2.tar.xz
cd gnome-icon-theme-3.6.2


echo Compile...

./configure --host=x86_64-w64-mingw32 --enable-static --enable-shared  --prefix="$PREFIX"
make clean
make 2>&1 | tee ../../../z_Install/win64_build/logs/73_gnome-icon-theme-make.log
make install 2>&1 | tee ../../../z_Install/win64_build/logs/73_gnome-icon-theme-makeinstall.log


cd ..
rm -rf gnome-icon-theme-3.6.2
