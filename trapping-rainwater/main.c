#include <stdio.h>
#include <stdbool.h>

int maxTrapValue(int *height, int heightSize, int pos)
{
    int maxTrap = height[pos + 1];
    for (int i = pos + 2; i < heightSize; ++i)
    {
        if (height[i] > maxTrap)
        {
            if (height[i] >= height[pos])
            {
                maxTrap = height[pos];
                break;
            }
            maxTrap = height[i];
        }
    }
    return maxTrap;
}

// Input:  [0,1,0,2,1,0,1,3,2,1,2,1]
// Output: 6
int trap(int *height, int heightSize)
{
    int trap = 0, maxTrap = 0;

    for (int i = 0; (i + 1) < heightSize; ++i)
    {
        if (height[i] > height[i + 1] && (maxTrap = maxTrapValue(height, heightSize, i)))
        {
            trap += maxTrap - height[i + 1];
            height[i + 1] = maxTrap;
        }
    }

    return trap;
}

int main(void)
{
    int height[6] = {2, 0, 4, 2, 5, 2};
    printf("Trapped water = %d", trap(height, 6));
    return 0;
}
