/*
Luis Alfonso Rodriguez Rodriguez---luis.rodriguezr@udc.es
Alberto Paz Perez---a.pazp@udc.es
Sergio Rego Criado---sergio.rego.criado@udc.es
*/



#include <stdio.h>
#include <sys/time.h>
#include <math.h>
#include <stdbool.h>

int fib1(int n)
{
    if (n < 2)
        return n;
    else
        return fib1(n - 1) + fib1(n - 2);
}

int fib2(int n)
{
    int i, j;
    i = 1;
    j = 0;
    for (int k = 1; k <= n; k++)
    {
        j = i + j;
        i = j - i;
    }
    return j;
}

int fib3(int n)
{
    int i, j, k, h, t;
    i = 1;
    j = 0;
    k = 0;
    h = 1;
    t = 0;
    while (n > 0)
    {
        if (n % 2 != 0)
        {
            t = j * h;
            j = i * h + j * k + t;
            i = i * k + t;
        }
        t = h * h;
        h = 2 * k * h + t;
        k = k * k + t;
        n = n / 2;
    }
    return j;
}

double microsegundos()
{
    struct timeval t;
    if (gettimeofday(&t, NULL) < 0)
        return 0.0;
    return (t.tv_usec + t.tv_sec * 1000000.0);
}

void testFib1()
{
    double t1, t2, t, x, y, z;
    bool esMenor;
    printf("%12s%16s%16s%15s%15s\n", "n", "t(n)", "t(n)/1.1^n", "t(n)/1.61^n", "t(n)/2^n");
    for (int n = 2; n <= 32; n += n)
    {
        esMenor = false;
        t1 = microsegundos();
        fib1(n);
        t2 = microsegundos();
        t = t2 - t1;
        if (t < 500)
        {
            esMenor = true;
            t1 = microsegundos();
            for (int i = 0; i < 1000; i++)
            {
                fib1(n);
            }
            t2 = microsegundos();
            t = (t2 - t1) / 1000.0;
        }
        x = t / pow(1.1, n);
        y = t / pow(1.61, n);
        z = t / pow(2.0, n);
        if (esMenor)
        {
            printf("%12d %15.3f*%15.6f%15.6f%15.6f\n", n, t, x, y, z);
        }
        else
        {
            printf("%12d %15.3f %15.6f%15.6f%15.6f\n", n, t, x, y, z);
        }
    }
}

void testFib2()
{
    double t1, t2, t, x, y, z;
    bool esMenor;
    printf("%12s%16s%16s%15s%18s\n", "n", "t(n)", "t(n)/n^0.8", "t(n)/n", "t(n)/(n*log(n))");
    for (int n = 1000; n <= 10000000; n *= 10)
    {
        esMenor = false;
        t1 = microsegundos();
        fib2(n);
        t2 = microsegundos();
        t = t2 - t1;
        if (t < 500)
        {
            esMenor = true;
            t1 = microsegundos();
            for (int i = 0; i < 1000; i++)
            {
                fib2(n);
            }
            t2 = microsegundos();
            t = (t2 - t1) / 1000.0;
        }
        x = t / pow(n, 0.8);
        y = t / n;
        z = t / (n * log(n));
        if (esMenor)
        {
            printf("%12d %15.3f*%15.6f%15.6f%15.6f\n", n, t, x, y, z);
        }
        else
        {
            printf("%12d %15.3f %15.6f%15.6f%15.6f\n", n, t, x, y, z);
        }
    }
}

void testFib3()
{
    double t1, t2, t, x, y, z;
    bool esMenor;
    printf("%12s%16s%20s%13s%13s\n", "n", "t(n)", "t(n)/sqrt(log(n))", "t(n)/log(n)", "t(n)/n^0.5");
    for (int n = 1000; n <= 10000000; n *= 10)
    {
        esMenor = false;
        t1 = microsegundos();
        fib3(n);
        t2 = microsegundos();
        t = t2 - t1;
        if (t < 500)
        {
            esMenor = true;
            t1 = microsegundos();
            for (int i = 0; i < 1000; i++)
            {
                fib3(n);
            }
            t2 = microsegundos();
            t = (t2 - t1) / 1000.0;
        }
        x = t / sqrt(log(n));
        y = t / log(n);
        z = t / pow(n, 0.5);
        if (esMenor)
        {
            printf("%12d %15.3f*%15.6f%15.6f%15.6f\n", n, t, x, y, z);
        }
        else
        {
            printf("%12d %15.3f%15.6f%15.6f%15.6f\n", n, t, x, y, z);
        }
    }
}

int main()
{
    for (int i = 0; i < 5; i++)
    {
        testFib1();
        printf("\n");
        testFib2();
        printf("\n");
        testFib3();
        printf("\n");
    }
}