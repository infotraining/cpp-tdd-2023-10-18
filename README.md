# Szkolenie - Test-Driven Development w C++ #

## Dokumentacja + slajdy

* https://infotraining.bitbucket.io/cpp-tdd

## Konfiguracja środowiska

Proszę wybrać jedną z poniższych opcji:

### Lokalna

Przed szkoleniem należy zainstalować:

#### Kompilator C++ wspierający C++20 - do wyboru:
  * Visual Studio 2022
    * przy instalacji należy zaznaczyć opcje:
      * Desktop development with C++
      * C++ CMake tools for Windows
      * vcpkg package manager

  * gcc-13
    * [CMake > 3.25](https://cmake.org/)
    * proszę sprawdzić wersję w linii poleceń        
  
      ```
      cmake --version
      ```
      
    * IDE: Visual Studio Code
      * [Visual Studio Code](https://code.visualstudio.com/)
      * Zainstalować wtyczki
        * C/C++ Extension Pack
        * Live Share

### Docker + Visual Studio Code

Jeśli uczestnicy szkolenia korzystają w pracy z Docker'a, to należy zainstalować:

#### Docker Desktop (Windows)

* https://www.docker.com/products/docker-desktop/

#### Visual Studio Code

* [Visual Studio Code](https://code.visualstudio.com/)
* Zainstalować wtyczki
  * Live Share
  * Dev Containers ([wymagania](https://code.visualstudio.com/docs/devcontainers/containers#_system-requirements))
    * po instalacji wtyczki - należy otworzyć w VS Code folder zawierający sklonowane repozytorium i
      z palety poleceń (Ctrl+Shift+P) wybrać opcję **Dev Containers: Rebuild and Reopen in Container**
