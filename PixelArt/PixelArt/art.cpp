///Name: Tadhg Murphy
///Number: C00273712
/// 
///
#define RAYGUI_IMPLEMENTATION
#define _CRT_SECURE_NO_WARNINGS
#include "raylib.h"
#include "raygui.h"

#define GRID_SIZE 20
#define CELL_SIZE 20

#define MAX_RECTS 1000

// Function to save the grid data to a binary file
void SaveGrid(Color grid[GRID_SIZE][GRID_SIZE], const char* filename) {
    FILE* file = fopen(filename, "wb");
    if (file) {
        for (int i = 0; i < GRID_SIZE; i++) {
            fwrite(grid[i], sizeof(Color), GRID_SIZE, file);
        }
        fclose(file);
    }
}
// Function to load grid data from a binary file
void LoadGrid(Color grid[GRID_SIZE][GRID_SIZE], const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (file) {
        for (int i = 0; i < GRID_SIZE; i++) {
            fread(grid[i], sizeof(Color), GRID_SIZE, file);
        }
        fclose(file);
    }
}

int main() {
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Drawing App");

    // Grid and palette setup
    Color grid[GRID_SIZE][GRID_SIZE] = { 0 };
    Color palette[] = { BLACK, RED, GREEN, BLUE, YELLOW, ORANGE, PURPLE, MAROON, WHITE };
    int paletteSize = sizeof(palette) / sizeof(palette[0]);
    int selectedColorIndex = 0;

    bool erasing = false;
    bool isDrawing = false;
    bool rectangleTool = false;

    Vector2 rectStart = { -1, -1 };  // For rectangle drawing

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        // Handle mouse input
        Vector2 mousePosition = GetMousePosition();

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            isDrawing = true;
            rectStart = mousePosition;
        }

        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
            isDrawing = false;
            rectStart = Vector2{ -1, -1 };
        }

        // Check for grid drawing
        if (!rectangleTool && isDrawing && CheckCollisionPointRec(mousePosition, Rectangle{ 0, 0, GRID_SIZE * CELL_SIZE, GRID_SIZE * CELL_SIZE })) {
            int gridX = mousePosition.x / CELL_SIZE;
            int gridY = mousePosition.y / CELL_SIZE;
            if (gridX >= 0 && gridX < GRID_SIZE && gridY >= 0 && gridY < GRID_SIZE) {
                grid[gridX][gridY] = erasing ? RAYWHITE : palette[selectedColorIndex];
            }
        }

        if (rectangleTool && isDrawing && rectStart.x >= 0) {
            int startX = rectStart.x / CELL_SIZE;
            int startY = rectStart.y / CELL_SIZE;
            int endX = mousePosition.x / CELL_SIZE;
            int endY = mousePosition.y / CELL_SIZE;

            for (int i = startX; i <= endX; i++) {
                for (int j = startY; j <= endY; j++) {
                    if (i >= 0 && i < GRID_SIZE && j >= 0 && j < GRID_SIZE) {
                        grid[i][j] = erasing ? RAYWHITE : palette[selectedColorIndex];
                    }
                }
            }
        }

        // Palette selection
        for (int i = 0; i < paletteSize; i++) {
            Rectangle colorButton = { screenWidth - 40 * (paletteSize - i), 10, 30, 30 };
            if (CheckCollisionPointRec(mousePosition, colorButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                selectedColorIndex = i;
                erasing = false;
            }
        }

        // Eraser button
        if (GuiButton(Rectangle { 10, screenHeight - 40, 80, 30 }, "Eraser")) {
            erasing = true;
        }

        // Save and load buttons
        if (GuiButton(Rectangle{ 100, screenHeight - 40, 80, 30 }, "Save")) {
            SaveGrid(grid, "grid_save.bin");
        }

        if (GuiButton(Rectangle { 200, screenHeight - 40, 80, 30 }, "Load")) {
            LoadGrid(grid, "grid_save.bin");
        }

        if (GuiButton(Rectangle{ 300, screenHeight - 40, 120, 30 }, "RectangleTool")) {
            rectangleTool = !rectangleTool;
        }

        // Drawing
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw grid
        for (int i = 0; i < GRID_SIZE; i++) {
            for (int j = 0; j < GRID_SIZE; j++) {
                DrawRectangle(i * CELL_SIZE, j * CELL_SIZE, CELL_SIZE, CELL_SIZE, grid[i][j]);
                DrawRectangleLines(i * CELL_SIZE, j * CELL_SIZE, CELL_SIZE, CELL_SIZE, LIGHTGRAY);
            }
        }

        // Draw palette
        for (int i = 0; i < paletteSize; i++) {
            Rectangle colorButton = { screenWidth - 40 * (paletteSize - i), 10, 30, 30 };
            DrawRectangleRec(colorButton, palette[i]);
            if (i == selectedColorIndex) {
                DrawRectangleLinesEx(colorButton, 2, BLACK);  // Highlight selected color
            }
        }

        // Rectangle drawing mode
        if (rectangleTool) {
            DrawText("RECTANGLE MODE ENABLED", 10, screenHeight - 80, 20, GRAY);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
