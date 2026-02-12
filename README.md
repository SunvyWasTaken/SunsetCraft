# SunsetCraft — Prototype voxel C++/OpenGL

> **Projet personnel de moteur + jeu voxel** construit pour approfondir l’architecture C++, le rendu temps réel et l’optimisation système.

![Status](https://img.shields.io/badge/status-prototype-orange)
![Language](https://img.shields.io/badge/C%2B%2B-20-blue)
![Build](https://img.shields.io/badge/build-CMake-informational)
![Graphics](https://img.shields.io/badge/graphics-OpenGL-success)

---

**SunsetCraft** est un projet sandbox inspiré des jeux voxel, développé en **C++20** avec un moteur maison (**SunsetEngine**).
L’objectif n’est pas seulement de “faire un jeu”, mais de démontrer ma capacité à :

- concevoir une architecture modulaire (moteur / gameplay),
- profiler et optimiser des systèmes data-oriented,
- apprendre de manière autonome des sujets bas niveau (GPU, mémoire, génération procédurale),
- faire évoluer un prototype vers une base solide de produit.

---

## Ce que le projet démontre déjà

### Architecture & engineering
- Séparation claire entre **Engine** (render, core, math, utils) et **jeu** (`SunsetCraft/`).
- Organisation par systèmes : caméra, chunk manager, génération de monde, couches UI/debug.
- Configuration externalisée via JSON (inputs, registre de blocs).

### Temps réel & rendu
- Pipeline OpenGL avec shaders dédiés au rendu des chunks.
- Caméra FPS + frustum utilisé pour limiter le coût de rendu.
- Construction de meshes de chunks pour éviter un rendu bloc-par-bloc naïf.

### Génération procédurale
- Système de génération de chunks piloté par des générateurs (hauteur/biome/world).
- Chargement/déchargement dynamique autour du joueur selon une distance configurable.

---

## Focus optimisation

Le projet est volontairement orienté vers des enjeux de performance concrets :

- **Culling frustum** pour ne soumettre que les chunks visibles.
- **Streaming monde** avec `Load/Unload` des chunks autour de la caméra.
- **Réduction du coût draw-call** via meshes agrégés côté chunk.
- **Précompilation** (PCH) et build CMake structuré pour améliorer les itérations dev.
- **Base propice aux futures optimisations** :
  - greedy meshing,
  - instancing,
  - job system/thread pool pour génération asynchrone,
  - cache locality (layout de données),
  - profiling CPU/GPU systématique.

---

## Apprentissage autonome

Ce projet illustre ma manière d’apprendre :

- Appropriation autonome d’un stack bas niveau complet (**OpenGL + C++20 + tooling CMake/vcpkg**).
- Itération continue par expérimentation (features, refactors, micro-optimisations).
- Construction d’un socle technique réutilisable (moteur + gameplay découplés).
- Capacité à transformer une idée en système exécutable, mesurable et extensible.

**Intention long terme :** continuer à enrichir SunsetCraft comme terrain d’expérimentation technique (performance, architecture, outils).

---

## Roadmap

### Court terme
- Interaction bloc complète (placer/casser).
- Outils de debug perf in-engine (timings, compteurs, overlays).
- Stabilisation gameplay de base (boucle de jeu, UX minimale).

### Moyen terme
- Génération asynchrone (chunks en tâche de fond).
- Optimisation mesh (greedy meshing / réduction triangles).
- Système d’inventaire plus complet + feedback visuel.

### Long terme
- Sauvegarde/chargement du monde.
- Pipeline de contenu plus robuste (assets/config).
- Tests techniques ciblés (non-régression des systèmes clés).

---

## Stack technique

- **C++20**
- **CMake** (>= 3.31)
- **vcpkg** (manifest)
- **OpenGL**, **GLFW**, **GLAD**, **GLM**, **stb**
- **nlohmann-json**, **spdlog**, **ImGui**

---

## Build & run

### Prérequis
1. CMake 3.31+
2. Compilateur C++20 (MSVC / Clang / GCC récent)
3. vcpkg

### Compilation
```bash
cmake -S . -B build \
  -DCMAKE_TOOLCHAIN_FILE=/path/to/vcpkg/scripts/buildsystems/vcpkg.cmake
cmake --build build -j
```

### Exécution
```bash
./build/SunsetCraft/SunsetCraft
```

---

## Contrôles actuels

- `W` avancer
- `S` reculer
- `A` gauche
- `D` droite
- `E` monter
- `Q` descendre
- Souris : orientation caméra

---

## Structure du dépôt

```text
.
├── Engine/          # moteur maison
├── SunsetCraft/     # logique jeu, shaders, world/chunks/layers
├── Textures/        # assets textures
├── CMakeLists.txt
└── vcpkg.json
```

---

## Pourquoi ce projet compte pour moi

SunsetCraft est plus qu’un prototype : c’est une **preuve de progression technique continue**.
Je veux continuer à le pousser, l’optimiser, et l’utiliser comme laboratoire pour aller vers des problématiques de plus en plus exigeantes (runtime perf, tooling, architecture scalable).
