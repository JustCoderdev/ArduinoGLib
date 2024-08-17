{
	description = "ArduinoGLib";

	inputs = {
		nixpkgs.url = "nixpkgs/nixos-24.05";
		flake-utils.url = "github:numtide/flake-utils";
	};

	outputs = { self, nixpkgs, flake-utils }:
		flake-utils.lib.eachDefaultSystem (system:
			let
				#pkgs = nixpkgs.legacyPackages.${system};
				pkgs = import nixpkgs {
					inherit system;
					config.permittedInsecurePackages = [
						"python-2.7.18.8"
					];
				};
			in
			{
				nixpkgs.config.permittedInsecurePackages = [ "python-2.7.18.8" ];
				devShells.default = import ./.arduino-make.nix { inherit pkgs; };
			}
	);
}


