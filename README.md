# ENEMzandia

Projeto de estudo da disciplina **Programação II (SINF0064) da UFS**. O ENEMzandia é uma aplicação desktop em desenvolvimento para organizar dados de participantes do ENEM. Atualmente, o projeto tem uma janela inicial e estruturas para representar dados e respostas.

## Tecnologias

[![C++20](https://img.shields.io/badge/C%2B%2B-20-00599C?style=for-the-badge&logo=cplusplus&logoColor=white)](https://isocpp.org/)
[![CMake](https://img.shields.io/badge/CMake-build-064F8C?style=for-the-badge&logo=cmake&logoColor=white)](https://cmake.org/)
![Dear ImGui](https://img.shields.io/badge/Dear%20ImGui-interface-5B6DCD?style=for-the-badge)
![GLFW](https://img.shields.io/badge/GLFW-janela-3C3C3C?style=for-the-badge)
[![OpenGL](https://img.shields.io/badge/OpenGL-gr%C3%A1ficos-5586A4?style=for-the-badge&logo=opengl&logoColor=white)](https://www.opengl.org/)

## Como executar

### Windows

Instale o **CMake** e o **Visual Studio** com a carga de trabalho “Desenvolvimento para desktop com C++”. Na pasta do projeto, execute:

```bat
build.bat
```

### Linux (Ubuntu/Debian)

Instale as ferramentas e bibliotecas necessárias:

```bash
sudo apt update
sudo apt install build-essential cmake git libgl-dev libwayland-dev libwayland-bin wayland-protocols libxkbcommon-dev xorg-dev
```

Na pasta do projeto, configure, compile e execute:

```bash
cmake -S . -B build
cmake --build build
./build/ENEMzandia
```

Na primeira configuração, o CMake baixa o GLFW pela internet.
