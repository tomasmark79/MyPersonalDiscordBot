This folder

### Utilities

is part of a template intended to host files that are not currently actively used in the default template settings, but they should be useful for some specific scenarios.

---

## Tips

When cross-compiling to Windows, you need these three libraries for your project. It is important to use the ones against which the cross-compilation was performed. So, these are generally the libraries you find in the sysroot for the target platform.

```bash
/home/tomas/x-tools/x86_64-w64-mingw32/x86_64-w64-mingw32/sysroot/lib/libgcc_s_seh-1.dll
/home/tomas/x-tools/x86_64-w64-mingw32/x86_64-w64-mingw32/sysroot/lib/libstdc++-6.dll
/home/tomas/x-tools/x86_64-w64-mingw32/x86_64-w64-mingw32/sysroot/mingw/bin/libwinpthread-1.dll
```