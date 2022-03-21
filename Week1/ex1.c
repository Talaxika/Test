#include <stdio.h>
#include <math.h>

int cylinder (double, double, double*, double *);

int main(void) {
    double r, h, S, V;
    printf("Enter radius, height: \n");
    while (scanf("%lf %lf", &r, &h) != EOF)
    {
        
        if (cylinder(r, h, &V, &S) == -1)
        {
            fprintf(stderr, "Invalid sides.");

        }
        else{
            printf("V = %.2lf, S = %.2lf\n", V, S);
        }
        
        printf("Enter radius, height: \n");
    }

    return 0;
}


int cylinder (double r, double h, double* V, double* S){

    if (r<=0 || h<=0)
    {   
        return -1;
    }


    *V = M_PI*h*r*r;
    *S = 2*M_PI*r*(r+h);
    return 0;
}
