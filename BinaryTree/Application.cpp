#include "raylib.h"
#include "BinaryTree.h"
#define RAYGUI_IMPLEMENTATION
#define RAYGUI_SUPPORT_ICONS
#include "raygui.h"

#include <iostream>
#include <string>

/*Draws the provided binary tree as gui buttons.*/
void drawTree(BinaryTree* theTree);

/*used to draw the binary tree, draws the provided node and its children.
  left bool and depth int are used to determine the on screen position of
  the node.*/
void drawNodesRecursive(float parentX, float parentY, Node* root);

/*toggles the provided boolean if button is true*/
void toggleBooleanOnButtonPress(bool button, bool& booleanToToggle);

int main(int argc, char* argv[])
{
    // Initialization
    //--------------------------------------------------------------------------------------
    int screenWidth = 800;
    int screenHeight = 450;
    BinaryTree* theTree = new BinaryTree();
    theTree->addNode(5);
    theTree->addNode(3);
    theTree->addNode(4);
    theTree->addNode(10);
    theTree->addNode(6);
    theTree->addNode(2);
    theTree->addNode(8);
    theTree->addNode(7);

    bool buttonAddNodePressed = false;
    bool buttonRemoveNodePressed = false;
    InitWindow(screenWidth, screenHeight, "Fredrick Binary Tree - ints");
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        toggleBooleanOnButtonPress(GuiButton(Rectangle{ 350, 400, 115, 20 }, "Add node"), buttonAddNodePressed);
        toggleBooleanOnButtonPress(GuiButton(Rectangle{ 350, 420, 115, 20 }, "Remove node"), buttonRemoveNodePressed);
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
    delete theTree;
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
    return 0;
}

void drawTree(BinaryTree* theTree)
{
    if (theTree->getIsEmpty())
    {
        return;
    }
    //TODO: draw lines and nodes

    drawNodesRecursive(400, 60, theTree->getRoot());
}
static constexpr int nodeSize = 30;
static constexpr int childXOffset = 40;//space to offset a child from the center of the parent node, left and right.
static constexpr int childYOffset = 40;//space to offset a child downwards from the parent node
void drawNodesRecursive(float parentX, float parentY, Node* root)
{
    if (root == nullptr)
    {
        return;
    }
    drawNodesRecursive(parentX + childXOffset, parentY + childYOffset, root->rightChild);
    drawNodesRecursive(parentX - childXOffset, parentY + childYOffset, root->leftChild);
    GuiButton(Rectangle{ parentX, parentY, nodeSize, nodeSize }, std::to_string(root->data).c_str());//drawing each node as a button
    //TODO: impliment
}

void toggleBooleanOnButtonPress(bool button, bool& booleanToToggle)
{
    if (button)
    {
        booleanToToggle = !booleanToToggle;
    }
}