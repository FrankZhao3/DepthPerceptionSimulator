/*
 * PROJ1-1: YOUR TASK B CODE HERE
 *
 * Feel free to define additional helper functions.
 */

#include <stdlib.h>
#include <stdio.h>
#include "quadtree.h"
#include "make_qtree.h"
#include "utils.h"

#define ABS(x) (((x) < 0) ? (-(x)) : (x))
qNode* Build_Tree_Node(int section_width, int x, int y, int color);
void quad_insert(qNode* quad_Node, unsigned char *depth_map, int map_width, int x, int y, int section_width);


// homogenous function
int homogenous(unsigned char *depth_map, int map_width, int x, int y, int section_width) {
    int color = depth_map[x + y * map_width];
    for(int row = y; row < section_width + y; row++){
        for(int col = x; col < section_width + x; col++){
            if(color != depth_map[row * map_width + col])
                return 256;
        }
    }
    return color;
}

qNode *depth_to_quad(unsigned char *depth_map, int map_width) {
    /* YOUR CODE HERE */
    qNode* quadTree = NULL;
    int section_width = map_width/2;
    int color;
    
    if(homogenous(depth_map, map_width, 0, 0, map_width) != 0)
    {
        color = homogenous(depth_map, map_width, 0, 0, map_width);
        quadTree = Build_Tree_Node(map_width, 0, 0, color);
        
    }
    
    if(section_width > 1){
        quad_insert(quadTree, depth_map, map_width, 0, 0, section_width);
    }
    return quadTree;
}

//to build a new node
qNode* Build_Tree_Node(int section_width, int x, int y, int color)
{
    qNode* newNode;
    newNode = (qNode*)malloc(sizeof(qNode));
    if(!newNode)
    {
        allocation_failed();
    }
    newNode->size = section_width;
    newNode->gray_value = color;
    newNode->x = x;
    newNode->y = y;
    newNode->child_NW = NULL;
    newNode->child_NE = NULL;
    newNode->child_SE = NULL;
    newNode->child_SW = NULL;
    if(color == 256){
        newNode->leaf = 0;
    }else{
        newNode->leaf = 1;
    }
    return newNode;
}

void quad_insert(qNode* quad_Node, unsigned char *depth_map, int map_width, int x, int y, int section_width){
    int color_NW = homogenous(depth_map, map_width, x, y, section_width);
    int color_SW = homogenous(depth_map, map_width, x, y + section_width, section_width);
    int color_NE = homogenous(depth_map, map_width, x + section_width, y, section_width);
    int color_SE = homogenous(depth_map, map_width, x + section_width, y + section_width, section_width);
    // child_NW
    if(color_NW == 256)
    {
        quad_Node->child_NW = Build_Tree_Node(section_width, x, y, 256);
        quad_insert(quad_Node -> child_NW, depth_map, map_width, x, y, section_width / 2);  //@@@@@ quad_Node -> child_NW!!
    }
    else{
        quad_Node->child_NW = Build_Tree_Node(section_width, x, y, color_NW);
    }
    // child_SW
    if(color_SW == 256)
    {
        quad_Node->child_SW = Build_Tree_Node(section_width, x, y + section_width, 256);
        quad_insert(quad_Node->child_SW, depth_map, map_width, x, y + section_width,  section_width / 2); // @@@@@@@ y + section_width
    }
    else{
        quad_Node->child_SW = Build_Tree_Node(section_width, x, y + section_width, color_SW);
    }
    
    // child_NE
    if(color_NE == 256)
    {
        quad_Node->child_NE = Build_Tree_Node(section_width, x + section_width, y, 256); // @@@@@ child_NE
        quad_insert(quad_Node->child_NE, depth_map, map_width, x + section_width, y,  section_width / 2); // @@@@@@@ x + section_width
    }
    else{
        quad_Node->child_NE = Build_Tree_Node(section_width, x + section_width, y, color_NE);
    }
    
    
    // child_SE
    if(color_SE == 256)
    {
        quad_Node->child_SE = Build_Tree_Node(section_width, x + section_width, y + section_width, homogenous(depth_map, map_width, x + section_width, y + section_width, section_width));
        quad_insert(quad_Node->child_SE, depth_map, map_width, x + section_width, y + section_width, section_width / 2);
    }
    else{
        quad_Node->child_SE = Build_Tree_Node(section_width, x + section_width, y + section_width, color_SE);
    }
    
}

void free_qtree(qNode *qtree_node) {
    if(qtree_node) {
        if(!qtree_node->leaf){
            free_qtree(qtree_node->child_NW);
            free_qtree(qtree_node->child_NE);
            free_qtree(qtree_node->child_SE);
            free_qtree(qtree_node->child_SW);
        }
        free(qtree_node);
    }
}
