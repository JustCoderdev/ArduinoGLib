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

	shellHook = ''
		echo -e "\033[34mAccessing C shell\033[0m"
		export LD_LIBRARY_PATH="$LD_LIBRARY_PATH:/home/ryuji/Developer/Projects/ArduinoGLib/lib/raylib"
		ldconfig -C ldcache
		zsh
	'';
		#export LD_LIBRARY_PATH="$LD_LIBRARY_PATH:${pkgs.glib.out}/lib"
}

