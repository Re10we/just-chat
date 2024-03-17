with import <nixpkgs> {};
 mkShell {

  name_project = "just-chat";
  PROJECT_ROOT = builtins.toString ./.;
  
  
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
    alias b="cmake -S $PROJECT_ROOT -B $PROJECT_ROOT/build"
    alias r="cmake -S $PROJECT_ROOT -B $PROJECT_ROOT/build && make --directory=$PROJECT_ROOT/build && $PROJECT_ROOT/build/$name_project"
   '';
 }