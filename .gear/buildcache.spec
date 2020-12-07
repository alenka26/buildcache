Name: buildcache
Version: 0.23.0
Release: alt2

Summary: a simple compiler accelerator
License: Zlib
Group: Development/Tools

Url: https://github.com/mbitsnbites/buildcache
Source: %name-%version.tar.gz
Packager: Ivan Savin <svn17@altlinux.org>

Patch: %name-%version-alt.patch

BuildRequires: cmake gcc-c++ libhiredis-devel liblz4-devel libzstd-devel lua5.3-devel libxxhash-devel

%description
This is a simple compiler accelerator that caches and reuses build results to avoid
unnecessary re-compilations, and thereby speeding up the build process.


%prep
%setup
%patch -p1

%build
cd src
%cmake -DCMAKE_BUILD_TYPE=Release
%cmake_build

%install
cd src
%cmakeinstall_std

%files
%doc doc/*.md lua-examples
%_bindir/buildcache

%changelog
* Fri Dec 04 2020 Ivan Savin <svn17@altlinux.org> 0.23.0-alt2
- Add system library (xxhash) instead of bundled.

* Fri Dec 04 2020 Ivan Savin <svn17@altlinux.org> 0.23.0-alt1
- Merge remote-tracking branch 'upstream/master' into sisyphus.

* Wed Nov 18 2020 Ivan Savin <svn17@altlinux.org> 0.18.0-alt2
- Add system libraries (zstd, lz4, hiredis, lua) instead of bundled.

* Tue Jun 23 2020 Ivan Savin <svn17@altlinux.org> 0.18.0-alt1
- Initial build for Sisyphus

