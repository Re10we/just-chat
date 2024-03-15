with import <nixpkgs> {};
 mkShell { 
  nativeBuildInputs = [
    pkg-config
    qt6.full
    qtcreator

    cmake
    cmake-language-server

    clang-tools
    gcc
 ];

  shellHook = ''
    export PATH="${qt6.full}/libexec:$PATH"
    export PATH="${qt6.full}/lib/cmake:$PATH"
    clangd &
  '';
 }