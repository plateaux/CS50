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
            if (x > height)
            {
                /*
                Debug:
                printf("In the if x is: %i\n", x);
                printf(" ");
                */
            }
            else
            {
                /*
                Debug:
                printf("In the else x is: %i and i is: %i", x, i);
                printf("#\n");
                */
                if (x < i)
                {
                    printf(" ");
                }
                else
                {
                    printf("#");
                }
            }
        }
        printf("#\n");
    }
}
