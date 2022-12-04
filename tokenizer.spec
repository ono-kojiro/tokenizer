%global _binaries_in_noarch_packages_terminate_build 0
%global __os_install_post /usr/lib/rpm/brp-compress

%global debug_package %{nil}

%define _build_id_links none

%global target x86_64-linux-gnu

Name: tokenizer
Version: 0.0.1
Release: 1%{?dist}
Summary: RPM example
Group: none
License: BSD	
URL: http://example.com
Source0: %{name}-%{version}.tar.gz

#BuildArch: noarch
#BuildRequires: libmylib
#Requires: libmylib

AutoReq: no

Prefix: /usr

%description
RPM sample program

%prep
%setup -n %{name}-%{version}

%build
autoreconf -vi

#rm -rf build
#mkdir -p build

#cd build

sh ./configure \
	--prefix=%{_prefix} \
	--host=%{_target} 

make %{?_smp_mflags}
#cd ..

%install
#cd build
%make_install
rm -rf %{buildroot}/%{_prefix}/lib/.build-id/
#cd ..

%check

%clean
echo INFO : clean

%files
%doc
%{_prefix}/bin/*
%{_prefix}/lib/libparser.*
%{_prefix}/lib/libscanner.*

%changelog

