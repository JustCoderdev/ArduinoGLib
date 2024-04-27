# To build raylib
# cd raylib/src
# make clean
# make PLATFORM=PLATFORM_DESKTOP RAYLIB_LIBTYPE=SHARED GLFW_LINUX_ENABLE_WAYLAND=OFF

{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
	# nativeBuildInputs is usually what you want -- tools you need to run
	nativeBuildInputs = with pkgs; [
		glibcInfo
		glibc

		arduino
		screen # serial console

		gnumake
		libGL
		gcc

		xorg.libXinerama
		xorg.libX11.dev
		xorg.libXft
		xorg.libXcursor
		xorg.libXrandr
		xorg.libXi.dev
	];

	#export LD_LIBRARY_PATH="$LD_LIBRARY_PATH:${pkgs.glib.out}/lib"
	shellHook = ''
		export LD_LIBRARY_PATH+=":$(pwd)/lib/raylib"
		rm -f .ldcache
		ldconfig -C .ldcache

		zsh
		echo -ne "\033[32m\$ \033[0m"
	'';
}

