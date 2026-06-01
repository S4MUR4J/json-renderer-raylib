# json-renderer-raylib

3D renderer that reads ECS-style JSON scenes and renders them with raylib. Designed for declarative scene creation — write JSON by hand, generate it with an LLM, or modify it live and watch the view update instantly.

Inspired by [LayoutGPT](https://arxiv.org/abs/2305.15393) — spatial scenes as structured text that language models can reason about and generate.

<p align="center">
  <img src="demo.gif" alt="demo">
</p>

## How it works

You describe a scene as a list of entities. Each entity has an `id` and a set of components. The renderer reads the file, builds the scene, and hot-reloads whenever the file changes.

```json
{
  "entities": [
    {
      "id": "camera",
      "components": {
        "camera": {
          "position": [10, 10, 10],
          "target": [0, 0, 0],
          "up": [0, 1, 0],
          "fovy": 45,
          "projection": 0
        }
      }
    },
    {
      "id": "box",
      "components": {
        "transform": { "position": [0, 0, 0], "scale": [1, 1, 1] },
        "material": { "rgb": [100, 200, 100], "a": 255 }
      }
    }
  ]
}
```

## Components

| Component   | Fields                                            | Description              |
|-------------|---------------------------------------------------|--------------------------|
| `camera`    | `position`, `target`, `up`, `fovy`, `projection`  | Scene camera             |
| `transform` | `position`, `scale`                               | Position and size in 3D  |
| `material`  | `rgb`, `a`                                        | RGBA color               |

## Features

- **Hot-reload** — edit the JSON file, renderer updates without restart
- **ECS-style schema** — entities and components, no hardcoded scene structure
- **LLM-friendly format** — flat, readable JSON that models can generate and modify

## Requirements

- CMake 3.25+
- C++23 compiler
- Ninja

## Build & Run

```bash
make configure
make build
make run SCENE=examples/valid_scene.json
```

## Controls

| Action             | Key |
|--------------------|-----|
| Toggle camera mode | E   |
| Quit               | ESC |
