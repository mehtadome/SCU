// Name: Ruchir Mehta
// Date: 9/28/2020
// Title: Lab1: Circuit/Packet Switching
// Description: Implements quantitative comparisons between circuit and packet switching

#include <stdio.h>
#include <math.h>
#include <stdlib.h>


// fact function for binomial func
int fact(int input)
{
//    printf("\nThe input to the factorial function is %e", input);
    int res = 1;
    int i;
    for (i = 1; i <= input; ++i)
    {
        res = (res * i);
    }
//    printf("\nThe factorial result is equal to %e", res);
    return res;
}

// binomial equation for 7g.
double bine(double x, double y)
{   
    double res = (fact(x) / (fact(y) * fact(x-y) ) );
    return res;
}

int main()
{
    int linkBandwidth = 200;
    int userBandwidth = 20;
    double tPSusers = 0.10;
    int nPSusers = 19;

    // 6
    int nCSusers = linkBandwidth / userBandwidth;
    printf("\n6: %d", nCSusers);

    // 7a
    double pPSusers = tPSusers;
    printf("\n7a: %e", pPSusers);

    // 7b
    double pPSusersNotBusy = 1 - pPSusers;
    printf("\n7b: %e", pPSusersNotBusy, "\n");

    // 7c
    double all = pow((1 - pPSusers), (nPSusers - 1));
    printf("\n7c: %e", all);

    // 7d
    double notTransmitting = pPSusers * pow(pPSusersNotBusy, (nPSusers - 1));
    printf("\n7d: %e", notTransmitting);

    // 7e
    double exactOne = nPSusers * notTransmitting;
    printf("\n7e: %e", exactOne);

    // 7f
    double exactTen = pow(pPSusers, 10) * pow(pPSusersNotBusy, (nPSusers - 10));
    printf("\n7f: %e", exactTen);

    // 7g

//    printf("\nnPSusers is equal tp %e", nPSusers);
//    printf("\npPSusers is equal to %e", pPSusers);
//    printf("\npPSusersNotBusy is equal to %e", pPSusersNotBusy);
    double coeff = bine(nPSusers, 10);
//    printf("\ncoeff is equal to %e:", coeff);
    double anyTen = coeff * pow(pPSusers, 10) * pow(pPSusersNotBusy, (nPSusers - 10));
    printf("\n7g: %d", anyTen);

    // 7h
    double sum = 0;
    int i;
    for (i = 11; i <= nPSusers; i++)
    {
        sum += bine(nPSusers, i) * pow(pPSusers, i) * pow(pPSusersNotBusy, (nPSusers- i));
    }
    printf("\n7h: %d\n", sum);

    return 0;

}
