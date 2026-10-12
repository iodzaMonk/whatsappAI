{pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
  buildInputs = with pkgs; [
    drogon
    libpqxx
    openssl
    postgresql
  ];
  nativeBuildInputs = with pkgs; [
    cmake
    ninja
    pkg-config
    gcc13
  ];
}