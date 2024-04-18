# What is qtCannelloniCanBus ?

qtCannelloniCanBus is a qtCanBus plugin that can communicate through Cannelloni (https://github.com/mguentner/cannelloni) protocol.

# What are the requirements ?

To compile qtCannelloni you need a recent Qt 6 library, cmake and a compiler that supports C++14.

For Android, any properly configured Android Kit in Qt 

# How to use qtCannelloniCanBus?

You should be able to load the plugin through standard Qt CanBus facilities:

```cpp
QCanBus::instance()->createDevice(plugin, interfaceName)
```
where `plugin` is a string `cannelloni` and interfaceName is a string of format `local_ip,local_port,remote_ip,remote_port`.


## Compilation x86

For x86, Go to project directory and type:

```bash
mkdir build
cd build
cmake ..
make
```

For x86, library file `libqtCannelloniCanBusPlugin.so` was created. Copy this file to your Qt CanBus plugins directory (e.g. `PATH_TO_QT_INSTALLATION_DIR/6.5.3/gcc_64/plugins/canbus/libqtCannelloniCanBusPlugin.so`).

## Compilation Android

Open Qt creator.

Open your any Android project.

Click on "projects" on the left

Select your "Android kit" as "build" in the "build&run" section on the left.

Click on "details" in the "build environment" section on the right.

Click "open terminal" from the window that opens.

Change directory(cd) in terminal of Qt to the cloned sources.

And compile & install.

```bash
mkdir build
cd build
/PATH_TO_QT_INSTALLATION_DIR/6.5.3/android_arm64_v8a/bin/qt-cmake ..
make
```

For arm64-v8a Android, library file `plugins_canbus_qtcannellonicanbus_arm64-v8a.so` was created. Copy this file to your Qt CanBus plugins directory (e.g. `/PATH_TO_QT_INSTALLATION_DIR/6.5.3/android_arm64_v8a/plugins/canbus/plugins_canbus_qtcannellonicanbus_arm64-v8a.so`)

My 1st Android : Oneplus5(Snapdragon 835), Android 12.1 PixelExperience, Custom Compiled 4.4.302 Kernel with Socketcan Support

My 2nd Android : Samsung a52q(Snapdragon 720G), Android 14 Official, No Socketcan Support

I compiled via NDK 26.1 and I tested the library via Qt 6.5.3 for both device. Works Fine!


