int min(int a, int b)
{
  if (a < b)
    return a;
  return b;
}

int max(int a, int b)
{
  if (a > b)
    return a;
  return b;
}

// Trapping rainwater in O(n)
int trap(int *height, int heightSize)
{
  int trap = 0;
  int maxHeightLeft[heightSize], maxHeightRight[heightSize];
  memset(maxHeightLeft, 0, sizeof(int) * heightSize);
  memset(maxHeightRight, 0, sizeof(int) * heightSize);

  if (heightSize > 2)
  {
    maxHeightLeft[0] = height[0];
    for (int i = 1; i < heightSize; i++)
    {
      maxHeightLeft[i] = max(maxHeightLeft[i - 1], height[i]);
    }

    maxHeightRight[heightSize - 1] = height[heightSize - 1];
    for (int i = heightSize - 2; i >= 0; i--)
    {
      maxHeightRight[i] = max(maxHeightRight[i + 1], height[i]);
    }

    for (int i = 0; i < heightSize; i++)
    {
      int waterCollected = min(maxHeightLeft[i], maxHeightRight[i]) - height[i];
      trap += waterCollected;
    }
  }
  return trap;
}
