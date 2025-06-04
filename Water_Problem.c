#include <stdio.h>

int trap(int* height, int heightSize) {
    if (heightSize <= 2) return 0;

    int left = 0, right = heightSize - 1;
    int leftMax = 0, rightMax = 0;
    int water = 0;

    while (left < right) {
        if (height[left] < height[right]) {
            if (height[left] >= leftMax)
                leftMax = height[left];
            else
                water += leftMax - height[left];
            left++;
        } else {
            if (height[right] >= rightMax)
                rightMax = height[right];
            else
                water += rightMax - height[right];
            right--;
        }
    }

    return water;
}

int main() {
    
    int height1[] = {0,1,0,2,1,0,1,3,2,1,2,1};
    int size1 = sizeof(height1) / sizeof(height1[0]);
    printf("Output (Ejemplo 1): %d\n", trap(height1, size1));  

    
    int height2[] = {4,2,0,3,2,5};
    int size2 = sizeof(height2) / sizeof(height2[0]);
    printf("Output (Ejemplo 2): %d\n", trap(height2, size2));  

    return 0;
}