#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#define RAYGUI_SUPPORT_ICONS
#include "raygui.h"
#include "BinaryTree.h"

#include <iostream>
#include <string>

/*Draws the provided binary tree as gui buttons.*/
void drawTree(BinaryTree* theTree);

/*used to draw the binary tree, draws the provided node and its children.
  left bool and depth int are used to determine the on screen position of
  the node.*/
void drawNodesRecursive(float parentX, float parentY, Node* root, bool isStart);

/*toggles the provided boolean if button is true*/
void toggleBooleanOnButtonPress(bool button, bool& booleanToToggle);

int main(int argc, char* argv[])
{
    // Initialization
    //--------------------------------------------------------------------------------------
    int screenWidth = 800;
    int screenHeight = 450;
    BinaryTree* theTree = new BinaryTree();
    theTree->addNode(1);

    theTree->addNode(4);
    theTree->addNode(3);
    theTree->addNode(2);
    theTree->addNode(1);

    theTree->addNode(6);
    theTree->addNode(7);
    theTree->addNode(8);
    theTree->addNode(9);
    theTree->addNode(12);
    theTree->addNode(11);
    theTree->addNode(0);
    theTree->addNode(-5);
    theTree->addNode(-10);
    theTree->addNode(-7);
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

        //TODO: add and impliment buttons for adding and removing nodes. Also button for checking if node is contained
        //TODO: add text for displaying count and isempty
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

static constexpr float nodeSize = 30;
static constexpr float childXOffset = 15;//space to offset a child from the center of the parent node, left and right.
static constexpr float childYOffset = 35;//space to offset a child downwards from the parent node

void drawTree(BinaryTree* theTree)
{
    if (theTree->getIsEmpty())
    {
        return;
    }
    //TODO: draw lines and nodes

    float nodesStartX = 400;
    float nodesStartY = 60;
    drawNodesRecursive(nodesStartX, nodesStartY, theTree->getRoot(), true);
}

void drawNodesRecursive(float posX, float posY, Node* root, bool isStart)
{
    if (root == nullptr)
    {
        return;
    }

    if (!isStart)
    {
        if (isRightChild(root) && root->leftChild != nullptr)
        {
            posX += getLeftChildCount(root) * childXOffset;
        }
        else if (!isRightChild(root) && root->rightChild != nullptr)
        {
            posX -= getRightChildCount(root) * childXOffset;
        }
    }

    GuiButton(Rectangle{ posX, posY, nodeSize, nodeSize }, std::to_string(root->data).c_str());//drawing each node as a button

    drawNodesRecursive(posX + childXOffset, posY + childYOffset, root->rightChild, false);
    drawNodesRecursive(posX - childXOffset, posY + childYOffset, root->leftChild, false);
}

void toggleBooleanOnButtonPress(bool button, bool& booleanToToggle)
{
    if (button)
    {
        booleanToToggle = !booleanToToggle;
    }
}