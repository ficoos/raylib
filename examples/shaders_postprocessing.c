/*******************************************************************************************
*
*   raylib [shaders] example - Apply a postprocessing shader to a scene
*
*   NOTE: This example requires raylib OpenGL 3.3 or ES2 versions for shaders support,
*         OpenGL 1.1 does not support shaders, recompile raylib to OpenGL 3.3 version.
*
*   NOTE: Shaders used in this example are #version 330 (OpenGL 3.3), to test this example
*         on OpenGL ES 2.0 platforms (Android, Raspberry Pi, HTML5), use #version 100 shaders
*         raylib comes with shaders ready for both versions, check raylib/shaders install folder
*
*   This example has been created using raylib 1.3 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2015 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"

int main()
{
    // Initialization
    //--------------------------------------------------------------------------------------
    int screenWidth = 800;
    int screenHeight = 450;
    
    SetConfigFlags(FLAG_MSAA_4X_HINT);      // Enable Multi Sampling Anti Aliasing 4x (if available)

    InitWindow(screenWidth, screenHeight, "raylib [shaders] example - postprocessing shader");

    // Define the camera to look into our 3d world
    Camera camera = {{ 3.0, 3.0, 3.0 }, { 0.0, 1.5, 0.0 }, { 0.0, 1.0, 0.0 }};
    
    Model dwarf = LoadModel("resources/model/dwarf.obj");                   // Load OBJ model
    Texture2D texture = LoadTexture("resources/model/dwarf_diffuse.png");   // Load model texture
    SetModelTexture(&dwarf, texture);                                       // Bind texture to model

    Vector3 position = { 0.0, 0.0, 0.0 };                                   // Set model position
    
    Shader shader = LoadShader("resources/shaders/base.vs", 
                               "resources/shaders/bloom.fs");               // Load postpro shader

    SetPostproShader(shader);               // Set fullscreen postprocessing shader
    
    // Setup orbital camera
    SetCameraMode(CAMERA_ORBITAL);          // Set an orbital camera mode
    SetCameraPosition(camera.position);     // Set internal camera position to match our camera position
    SetCameraTarget(camera.target);         // Set internal camera target to match our camera target

    SetTargetFPS(60);                       // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())            // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        UpdateCamera(&camera);              // Update internal camera and our camera
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            Begin3dMode(camera);

                DrawModel(dwarf, position, 2.0f, WHITE);   // Draw 3d model with texture

                DrawGrid(10.0, 1.0);     // Draw a grid

            End3dMode();
            
            DrawText("(c) Dwarf 3D model by David Moreno", screenWidth - 200, screenHeight - 20, 10, BLACK);

            DrawFPS(10, 10);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadShader(shader);       // Unload shader
    UnloadTexture(texture);     // Unload texture
    UnloadModel(dwarf);         // Unload model

    CloseWindow();              // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}