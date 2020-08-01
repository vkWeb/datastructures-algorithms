#include <stdio.h>

// Find right max position
int findRightMaxPos(int *height, int heightSize, int trapPos)
{
  int rightMaxPos = heightSize - 1;
  for (int i = rightMaxPos - 1; i > trapPos; --i)
  {
    if (height[i] > height[rightMaxPos])
      rightMaxPos = i;
  }
  return rightMaxPos;
}

// Calculate the trapped water
int trap(int *height, int heightSize)
{
  int trappedWater = 0, leftMaxPos = 0, trapPos = 1;
  int rightMaxPos = findRightMaxPos(height, heightSize, trapPos);

  while (trapPos < (heightSize - 1))
  {
    if (height[trapPos] < height[leftMaxPos] && height[trapPos] < height[rightMaxPos])
    {
      if (height[leftMaxPos] <= height[rightMaxPos])
      {
        trappedWater += height[leftMaxPos] - height[trapPos];
        height[trapPos] = height[leftMaxPos];
      }
      else
      {
        trappedWater += height[rightMaxPos] - height[trapPos];
        height[trapPos] = height[rightMaxPos];
      }
    }
  }

  ++leftMaxPos;
  ++trapPos;

  if (rightMaxPos == trapPos)
    rightMaxPos = findRightMaxPos(height, heightSize, trapPos);

  return trappedWater;
}

// Input:  [0,1,0,2,1,0,1,3,2,1,2,1]
// Output: 6
int main(void)
{
  int height[] = {1, 0, 2, 0, 5, 0, 2};
  printf("Trapped water = %d", trap(height, (sizeof height / sizeof height[0])));
  return 0;
}
