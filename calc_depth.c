/*
 * PROJ1-1: YOUR TASK A CODE HERE
 *
 * Feel free to define additional helper functions.
 */

#include "calc_depth.h"
#include "utils.h"
#include <math.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

/* Implements the normalized displacement function */
unsigned char normalized_displacement(int dx, int dy,
                                      int maximum_displacement) {
    
    double squared_displacement = dx * dx + dy * dy;
    double normalized_displacement = round(255 * sqrt(squared_displacement) / sqrt(2 * maximum_displacement * maximum_displacement));
    return (unsigned char) normalized_displacement;
    
}

void calc_depth(unsigned char *depth_map, // output buffer    2D array that we represent as 1D array
                unsigned char *left, // input images     string array, array of numbers betwen 0~255 inclusive {0, 0, 128, 255..}
                unsigned char *right, // input images      string array, array of numbers betwen 0~255 inclusive {0, 0, 128, 255..}
                int image_width,
                int image_height,
                int feature_width,
                int feature_height,
                int maximum_displacement){// search over ( 2 * maximum_displacement + 1)^2 patches in the second image to compare with
    
    /* YOUR CODE HERE */
    //initialize all variables
    int searchbox_row1 = 0;
    int searchbox_row2 = 0;
    int searchbox_col1 = 0;
    int searchbox_col2 = 0;
    int similiarty = 0;
    int min = 1000000;
    int dx = 0;
    int dy = 0;
    int k = 0;
    int l = 0;
    int i = 0;
    int j = 0;
    int f_r_l = 0;
    int f_c_l = 0;
    int pixel_col;
    int pixel_row;
    int mini_normalized_distance = 1000000;
    //int search_box[maximum_displacement * 2 + 1][maximum_displacement * 2 + 1];
    for(pixel_row = 0; pixel_row < image_height; pixel_row++){
        for(pixel_col = 0; pixel_col < image_width; pixel_col++){
            //check feature box out of boundary
            if((pixel_row - feature_height) < 0)
            {
                depth_map[pixel_row * image_width + pixel_col]
                = 0;
                continue;
            }
            if((pixel_col - feature_width) < 0)
            {
                depth_map[pixel_row * image_width + pixel_col]
                = 0;
                continue;
            }
            if(pixel_row + feature_height > image_height - 1)
            {
                depth_map[pixel_row * image_width + pixel_col]
                = 0;
                continue;
            }
            if((pixel_col + feature_width) > image_width - 1)
            {
                depth_map[pixel_row * image_width + pixel_col]
                = 0;
                continue;
            }
            //set up search box boundary
            searchbox_row1 = pixel_row - maximum_displacement - feature_height;
            searchbox_row2 = pixel_row + maximum_displacement + feature_height;
            searchbox_col1 = pixel_col - maximum_displacement - feature_width;
            searchbox_col2 = pixel_col + maximum_displacement + feature_width;
            
            
            if (searchbox_row1 < 0)
                searchbox_row1 = 0;
            if (searchbox_row2 > image_height - 1)
                searchbox_row2 = image_height - 1;
            if (searchbox_col1 < 0)
                searchbox_col1 = 0;
            if (searchbox_col2 > image_width - 1)
                searchbox_col2 = image_width - 1;
            
            
            //move red box
            
            for(i = searchbox_row1 + feature_height; i <= searchbox_row2 - feature_height; i++)  // i = red box center row
            {
                for(j = searchbox_col1 + feature_width; j <= searchbox_col2 - feature_width; j++) // j = red box center col
                {
                    
                    for(k = i, f_r_l = pixel_row - feature_height; f_r_l <= pixel_row + feature_height; f_r_l++, k++){
                        for(l = j, f_c_l = pixel_col - feature_width; f_c_l <= pixel_col + feature_width; f_c_l++, l++){
                            
                            
                            similiarty += pow(left[f_r_l * image_width + f_c_l]  // @@@@@@@@@@@@@@not moving the pixel
                                              - right[(k - feature_height) * image_width + (l - feature_width)], 2);
                        }
                    } // finished calculating similiarty
                    
                    if(similiarty < min){
                        min = similiarty;
                        dy = abs(pixel_row - i);
                        dx = abs(pixel_col - j);
                        depth_map[pixel_row * image_width + pixel_col] = normalized_displacement(dx, dy, maximum_displacement);
                        mini_normalized_distance = normalized_displacement(dx, dy, maximum_displacement);
                    }
                    else if(similiarty == min){
                        min = similiarty;
                        dy = abs(pixel_row - i);
                        dx = abs(pixel_col - j);
                        //  printf("normalized_displacement: %d\n\n", normalized_displacement(dx, dy, maximum_displacement));
                        if(normalized_displacement(dx, dy, maximum_displacement) < mini_normalized_distance){
                            mini_normalized_distance = normalized_displacement(dx, dy, maximum_displacement);
                            depth_map[pixel_row * image_width + pixel_col] = mini_normalized_distance;
                        }
                    }
                    similiarty = 0;
                }
            } // finished moving red box in the search space
            
            
            mini_normalized_distance = 1000000;
            min = 1000000;
        }
    }
} 





















