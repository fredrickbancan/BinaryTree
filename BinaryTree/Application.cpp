#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#define RAYGUI_SUPPORT_ICONS
#include "raygui.h"
#include "BinaryTree.h"

#include <iostream>
#include <string>
#include <random>

/*Draws the provided binary tree as gui buttons.*/
void drawTree(BinaryTree* theTree);

/*used to draw the binary tree, draws the provided node and its children.
  pos X and Y are used to determine where to put the node and
  thus their children. bool isStart is used to keep the root node in center of screen.*/
void drawNodesRecursive(float posX, float posY, Node* root, bool isStart);

/*used to draw the lines between nodes in the binary tree. Draws the lines between the
  provided nodes and its children. */
void drawNodeLinesRecursive(float prevX, float prevY, float posX, float posY, Node* root, bool isStart);

/*toggles the provided boolean if button is true*/
void toggleBooleanOnButtonPress(bool button, bool& booleanToToggle);

/*fills the provided tree with random data, if the tree is not empty, re-builds the tree.*/
void randomizeTree(BinaryTree*& theTree);

static constexpr float nodeSize = 20;
static constexpr float childXOffset = 20;//space to offset a child from the center of the parent node, left and right.
static constexpr float childYOffset = 35;//space to offset a child downwards from the parent node
static constexpr float halfNodeSize = nodeSize / 2;

int main(int argc, char* argv[])
{
    // Initialization
    //--------------------------------------------------------------------------------------
    int screenWidth = 800;
    int screenHeight = 450;
    BinaryTree* theTree = new BinaryTree();
    bool buttonFindNodePressed = false;
    bool buttonAddNodePressed = false;
    bool buttonRemoveNodePressed = false;
    //bool for detecting value box editing
    bool valueBoxEditing0 = false;
    bool valueBoxEditing1 = false;

    //int for holding input values
    int inputValue0 = 0;
    int inputValue1 = 0;

    InitWindow(screenWidth, screenHeight, "Fredrick Binary Tree - ints");
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        //Update buttons
        toggleBooleanOnButtonPress(GuiButton(Rectangle{ 350, 380, 115, 20 }, "Find node"), buttonFindNodePressed);
        toggleBooleanOnButtonPress(GuiButton(Rectangle{ 350, 400, 115, 20 }, "Add node"), buttonAddNodePressed);
        toggleBooleanOnButtonPress(GuiButton(Rectangle{ 350, 420, 115, 20 }, "Remove node"), buttonRemoveNodePressed);
        if (GuiButton(Rectangle{ 465, 420, 115, 20 }, "Randomize Tree"))randomizeTree(theTree);
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(LIGHTGRAY);

        DrawText("Binary Tree", 350, 30, 20, BLACK);
        DrawText((std::string("Tree count: ") + std::to_string(theTree->getCount())).c_str(), 5, 430, 20, BLACK);
        DrawText((std::string("Tree is empty: ") + std::string(theTree->getIsEmpty() ? "True" : "False")).c_str(), 5, 410, 20, BLACK);

        drawTree(theTree);//draw binary tree

        //Handling button presses

        //Handling find node button
        if (buttonFindNodePressed)
        {
            toggleBooleanOnButtonPress(GuiValueBox(Rectangle{ 360, 315, 115, 20 }, "Input the value for the node to find.", &inputValue0, 0, INT32_MAX, valueBoxEditing0), valueBoxEditing0);
            
            bool found = theTree->contains(inputValue0);
            DrawText((std::string("Node with value found: ") + std::string(found ? "True" : "False")).c_str(), 360, 335, 10, found ? DARKGREEN : RED);
            
            if (GuiButton(Rectangle{ 360, 345, 95, 30 }, "Close"))
            {
                valueBoxEditing0 = false;
                inputValue0 = 0;
                buttonFindNodePressed = false;
            }
        }

        //handling add node button
        if (buttonAddNodePressed)
        {
            toggleBooleanOnButtonPress(GuiValueBox(Rectangle{ 360, 320, 115, 20 }, "Input the value for the node.", &inputValue0, 0, INT32_MAX, valueBoxEditing0), valueBoxEditing0);
            if (GuiButton(Rectangle{ 360, 340, 95, 30 }, "Add node"))
            {
                theTree->addNode(inputValue0);
                valueBoxEditing0 = false;
                inputValue0 = 0;
                buttonAddNodePressed = false;
            }
            if (GuiButton(Rectangle{ 360, 370, 95, 30 }, "Cancel"))
            {
                valueBoxEditing0 = false;
                inputValue0 = 0;
                buttonAddNodePressed = false;
            }
        }

        //handling remove node button
        if (buttonRemoveNodePressed)
        {
            toggleBooleanOnButtonPress(GuiValueBox(Rectangle{ 360, 320, 115, 20 }, "Input the value for the node to remove.", &inputValue0, 0, INT32_MAX, valueBoxEditing0), valueBoxEditing0);
            if (GuiButton(Rectangle{ 360, 340, 95, 30 }, "Remove node"))
            {
                theTree->remove(inputValue0);
                valueBoxEditing0 = false;
                inputValue0 = 0;
                buttonRemoveNodePressed = false;
            }
            if (GuiButton(Rectangle{ 360, 370, 95, 30 }, "Cancel"))
            {
                valueBoxEditing0 = false;
                inputValue0 = 0;
                buttonRemoveNodePressed = false;
            }
        }

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



void drawTree(BinaryTree* theTree)
{
    if (theTree->getIsEmpty())
    {
        return;
    }

    float nodesStartX = 400;
    float nodesStartY = 60;
    drawNodeLinesRecursive(nodesStartX, nodesStartY, nodesStartX, nodesStartY, theTree->getRoot(), true);
    drawNodesRecursive(nodesStartX, nodesStartY, theTree->getRoot(), true);
}

void drawNodeLinesRecursive(float prevX, float prevY, float posX, float posY, Node* root, bool isStart)
{
    if (root == nullptr)
    {
        return;
    }

    if (!isStart)
    {
        //adjust node position to accomodate child tree
        if (isRightChild(root) && root->leftChild != nullptr)
        {
            posX += getLeftChildCount(root) * childXOffset;
        }
        else if (!isRightChild(root) && root->rightChild != nullptr)
        {
            posX -= getRightChildCount(root) * childXOffset;
        }
    }

    //draw line to parent with appropriate color
    DrawLine(posX + halfNodeSize, posY + halfNodeSize, prevX + halfNodeSize, prevY + halfNodeSize, isRightChild(root) ? DARKGREEN : RED);
    
    //draw childrens lines
    drawNodeLinesRecursive(posX, posY, posX + childXOffset, posY + childYOffset, root->rightChild, false);
    drawNodeLinesRecursive(posX, posY, posX - childXOffset, posY + childYOffset, root->leftChild, false);
}

void drawNodesRecursive(float posX, float posY, Node* root, bool isStart)
{
    if (root == nullptr)
    {
        return;
    }

    if (!isStart)
    {
        //adjust line position to accomodate child tree
        if (isRightChild(root) && root->leftChild != nullptr)
        {
            posX += getLeftChildCount(root) * childXOffset;
        }
        else if (!isRightChild(root) && root->rightChild != nullptr)
        {
            posX -= getRightChildCount(root) * childXOffset;
        }
    }
    else
    {
        //This draws the golden recangle at the root node
        DrawRectangle(posX-3, posY-3, nodeSize+6, nodeSize+6, GOLD);
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

void randomizeTree(BinaryTree*& theTree)
{
    if (!theTree->getIsEmpty())
    {
        delete theTree;
        theTree = new BinaryTree();
    }
    theTree->addNode(50);
    for (int i = 0; i < 10; i++)
    {
        theTree->addNode(rand() % 100);
    }
}