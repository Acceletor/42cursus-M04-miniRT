# miniRT

## 🖥️ Description

**miniRT** is a simple ray tracing program written in C.  
It renders a 3D scene from a text-based scene description file by simulating light rays from a virtual camera and calculating their interactions with objects.

This project introduces the fundamentals of computer graphics such as ray–object intersection, vector mathematics, lighting, and shading.

---

## ✨ Features

- Ray tracing engine written in C
- Support for basic geometric objects:
  - Spheres
  - Planes
  - Cylinders
- Ambient and diffuse lighting
- Camera and light source handling
- Scene parsing from `.rt` files
- Real-time rendering using MiniLibX
- Window management and clean exit handling


---

## 📁 Scene Description (.rt)

The program takes a `.rt` file as input, which defines:
- Resolution
- Ambient lighting
- Camera position and orientation
- Light sources
- Objects with position, orientation, color, and size

Example:
```txt
  A 0.2 255,255,255
  C 0,0,0 0,0,1 70
  L 10,10,10 0.6 255,255,255
  sp 0,0,20 10 255,0,0
```
---

### 🛠️ Installation
Requirements
- macOS or Linux
- GCC or Clang
- minilibx
  
---
### Build
```bash
  make
```

▶️ Usage
```bash
./miniRT scenes/example.rt
```
Controls:
- ESC or window close button to exit
---

### 📚 What I Learned
- Vector math and 3D geometry
- Ray–object intersection algorithms
- Basic lighting models
- Parsing structured input files
- Graphics programming with MiniLibX
- Memory management and error handling in C
  
---
### ⚠️ Error Handling
- Invalid .rt files are detected and handled
- Program exits cleanly with proper memory cleanup
- Invalid arguments or unsupported elements are rejected

👤 Author
- ksuebtha (42 Warsaw)







