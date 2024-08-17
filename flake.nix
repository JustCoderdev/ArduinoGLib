{
	description = "ArduinoGLib";

	inputs = {
		nixpkgs.url = "nixpkgs/nixos-24.05";
		flake-utils.url = "github:numtide/flake-utils";
	};

	outputs = { self, nixpkgs, flake-utils }:
		flake-utils.lib.eachDefaultSystem (system:
			let pkgs = nixpkgs.legacyPackages.${system}; in
			{
				devShells.default = import ./.arduino-make.nix { inherit pkgs; };
			}
	);
}


