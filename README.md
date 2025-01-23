# Theme 3 - Cappadocian Balloons

This project involves creating a virtual scene inspired by the famous Cappadocian hot air balloons, aiming to deepen the understanding of lighting and texturing concepts in computer graphics. The scene will include a textured terrain with height modification via a shader, hot air balloons, and a setting sun.

## Virtual Scene

The scene will consist of the following elements:

- **Terrain**: A plane whose height will be modified using a shader.
- **Balloons**: Built from 3D primitives such as cuboids and deformed spheres.
- **Sun**: Represented by a simple sphere.

### Camera Positioning

The perspective camera should be positioned to include all the main elements of the scene: the terrain, the balloons, and the sun. It is not required to allow control of the camera's position or rotation during the application's runtime; it can remain fixed.

## Building the Balloons

The balloons will be constructed using the following components:

1. **Basket**: A cuboid serving as the basket of the balloon.
2. **Balloon Body**: A sphere that will be deformed to resemble the real shape of a hot air balloon.
3. **Connectors**: Four cuboids connecting the basket to the balloon body.

### Deformation in Vertex Shader

To achieve the specific shape of the balloon, deformation will be applied to the sphere in the **Vertex Shader**. The vertices in the lower half of the sphere will be displaced vertically based on the object's coordinates.

### Texturing

Each balloon component will be textured as follows:

- **Basket and Connectors**: Can use the same texture for all balloons.
- **Balloon Body**: Will be textured differently for each balloon, randomly choosing from a set of at least 5 textures.

### Balloon Behavior

The balloons will exhibit the following behaviors:

- **Circular Motion**: They will move along circular trajectories parallel to the XOZ plane, sharing a common center.
- **Vertical Oscillation**: They will oscillate along the OY axis following the formula Δy = A ⋅ sin(ω ⋅ Δt), where A and ω are chosen to create a realistic visual effect.

## Building the Terrain

The terrain will initially be a flat plane subdivided into a 256×256 grid of quads, allowing the modification of vertex heights in the **Vertex Shader** using a height map.

### Deformation in Vertex Shader Using a Height Map

The terrain's deformation will be performed in the **Vertex Shader**, using height data from a texture and applying a scaling factor to achieve the desired relief.

### Texturing

The terrain will be textured using two color textures and a height map. Each fragment will be colored based on height, performing linear interpolation between textures for a smooth transition.

### Normal Recalculation

After terrain deformation, surface normals must be recalculated to ensure proper lighting. This will be done using the finite differences method, sampling the height map and computing tangents and bitangents in object space, then transforming them into world space.

## Lighting

The scene will be illuminated using at least two types of light sources:

- **Point Light**: Each balloon will have a point light source, fixed relative to the balloon, with random color and intensity.
- **Directional Light**: Represents the ambient light of the scene, simulating the sunlight at sunset.

Lighting must be implemented using the Phong shading model and the Phong reflection model.

## Resources

- **Subdivided Plane**: [plane256.zip](https://ocw.cs.pub.ro/courses/egc/teme/2024/03/plane256.zip)
- **Height Map**: [heightmap256.zip](https://ocw.cs.pub.ro/courses/egc/teme/2024/03/heightmap256.zip)

