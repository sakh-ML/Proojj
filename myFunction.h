#ifndef MYFUNC_H
#define MYFUNC_H


double myFunc(int i) {
    // srand(1);
    // int r = rand();
    double arg1 = sin(((double)(i % 360)));
    double arg2 = cos(((double)(i % 360)));

    arg1 = pow(arg1, 5);
    arg2 = log(arg2);

    double result = log(sqrt((arg1 + 17 * arg2)));

    return (result);
}

#endif

