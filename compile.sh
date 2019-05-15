#!/bin/sh

case "$(uname)" in
'Linux')
	if [ ! -d 'bin/i686-elf-tools' ]; then
		if [ ! -e 'bin/i686-elf-tools-linux.zip' ]; then
			echo 'downloading toolchain...'
			wget -P bin/ 'https://github.com/lordmilko/i686-elf-tools/releases/download/7.1.0/i686-elf-tools-linux.zip'
		fi

		echo 'decompressing toolchain...'
		unzip bin/i686-elf-tools-linux.zip -d bin/i686-elf-tools/
	fi

	if [ ! -x "$(command -v qemu-system-i386)" ]; then
		echo 'error: qemu-system-i386 was not found, please install qemu using your package manager or update your PATH variable'
		exit 1
	fi
	;;
'Darwin')
	if [ ! -x "$(command -v brew)" ]; then
		echo 'downloading and installing homebrew...'
		/usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"
	fi

	if [ ! -x "$(command -v wget)" ]; then
		echo 'installing wget using brew...'
		brew install wget
	fi

	if [ ! -d 'bin/i686-elf-tools' ]; then
		if [ ! -d 'bin/i386-elf-binutils' ]; then
			if [ ! -e 'bin/i386-elf-binutils-apple-darwin-x86_64.tar.bz2' ]; then
				echo 'downloading binutils...'
				wget -P bin/ 'https://github.com/nativeos/i386-elf-toolchain/releases/download/preview/i386-elf-binutils-apple-darwin-x86_64.tar.bz2'
			fi

			echo 'decompressing binutils...'
			tar xf bin/i386-elf-binutils-apple-darwin-x86_64.tar.bz2 -C bin/
		fi

		if [ ! -d 'bin/i386-elf-gcc' ]; then
			if [ ! -e 'bin/i386-elf-gcc-apple-darwin-x86_64.tar.bz2' ]; then
				echo 'downloading gcc...'
				wget -P bin/ 'https://github.com/nativeos/i386-elf-toolchain/releases/download/preview/i386-elf-gcc-apple-darwin-x86_64.tar.bz2'
			fi

			echo 'decompressing gcc...'
			tar xf bin/i386-elf-gcc-apple-darwin-x86_64.tar.bz2 -C bin/
		fi

		echo 'setting up toolchain...'
		mkdir bin/i686-elf-tools
		rsync -a bin/i386-elf-binutils/* bin/i686-elf-tools/
		rsync -a bin/i386-elf-gcc/* bin/i686-elf-tools/
		ln -s i386-elf-as bin/i686-elf-tools/bin/i686-elf-as
		ln -s i386-elf-gcc bin/i686-elf-tools/bin/i686-elf-gcc

		echo 'cleaning up...'
		rm -rf bin/i386-elf-binutils/ bin/i386-elf-gcc/
	fi

	if [ ! -x "$(command -v qemu-system-i386)" ]; then
		echo 'installing qemu using brew...'
		brew install qemu
	fi
	;;
*)
	echo 'error: your operating system is not supported :('
	exit 1
	;;
esac

echo 'compiling...'
make run
