#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int coins = 0;
    float change = 0.0;
    int cents = 0;
    
    do
    {
    printf("How much change is due? ");
    change = GetFloat();
    }
    while (change < 0);
    
    cents = change * 100.01; //100.01 is a hack to avoid buggy float rounding i.e. 3.30, 4.20, 4.70
    
    for (int quarters = cents; quarters >= 25; quarters -= 25)
    {
        coins += 1;
        cents -= 25;
    }
    
    for (int dimes = cents; dimes >= 10; dimes -= 10)
    {
        coins += 1;
        cents -= 10;
    }
    
    for (int nickels = cents; nickels >= 5; nickels -= 5)
    {
        coins += 1;
        cents -= 5;
    }
    
    for (int pennies = cents; pennies >= 1; pennies -= 1)
    {
        coins += 1;
        cents -= 1;
    }
    
    printf("%i\n",coins);
}

