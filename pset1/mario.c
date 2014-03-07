#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int height;
    do
    {
        printf("Height: ");
        height = GetInt();
    }
    while (height < 0 || height > 23);
    
    for (int i = height; i > 0; --i)
    {
        for (int x = 0; x <= height; ++x)
        {
            if (x < i-1)
            {
                printf(" ");
            }
            else
            {
                printf("#");
            }
        }
        printf("\n");
    }
}
