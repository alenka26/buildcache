Name: buildcache
Version: 0.18.0
Release: alt1

Summary: a simple compiler accelerator
License: zlib
Group: Development/Tools

Url: https://github.com/mbitsnbites/buildcache
Source: %name-%version.tar.gz
Packager: Ivan Savin <svn17@altlinux.org>

Patch: %name-%version-alt.patch

BuildRequires: cmake gcc-c++

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
* Tue Jun 23 2020 Ivan Savin <svn17@altlinux.org> 0.18.0-alt1
- Initial build for Sisyphus

