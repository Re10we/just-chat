with import <nixpkgs> {};
 mkShell {

  name_project = "just-chat";
  root_project = builtins.toString ./.;

  
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
    alias b="cmake -S $root_project -B $root_project/build && make --directory=$root_project/build" 
    alias r="$root_project/build/$name_project"
    alias rs="$root_project/build/$name_project --server"
   '';
 }