#include "raylib.h"
#include "BinaryTree.h"
#define RAYGUI_IMPLEMENTATION
#define RAYGUI_SUPPORT_ICONS
#include "raygui.h"

#include <iostream>

/*Draws the provided binary tree as gui buttons.*/
void drawTree(BinaryTree* theTree);

/*used to draw the binary tree, draws the provided node and its children.
  left bool and depth int are used to determine the on screen position of
  the node.*/
void drawNodesRecursive(bool left, int depth, Node* root);

int main(int argc, char* argv[])
{
    // Initialization
    //--------------------------------------------------------------------------------------
    int screenWidth = 800;
    int screenHeight = 450;
    BinaryTree* theTree = new BinaryTree();
    InitWindow(screenWidth, screenHeight, "Fredrick Binary Tree - ints");

    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(LIGHTGRAY);

        DrawText("Binary Tree", 350, 30, 20, BLACK);

        drawTree(theTree);

        //TODO: add and impliment buttons for adding and removing nodes.

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------   
    CloseWindow();        // Close window and OpenGL context
    delete theTree;
    //--------------------------------------------------------------------------------------
    system("PAUSE");
    return 0;
}

void drawTree(BinaryTree* theTree)
{
    if (theTree->getIsEmpty())
    {
        return;
    }
    //TODO: impliment
    //TODO: draw lines

    drawNodesRecursive(true, 0, theTree->getRoot());
    
}

void drawNodesRecursive(bool left, int depth, Node* root)
{
    //TODO: impliment
}