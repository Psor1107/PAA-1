#include <stdio.h>
#include <stdlib.h>

long long countInversionsAux(long long v[], long long aux[], int left, int mid, int right)
{
    int i = left, j = mid + 1, k = left;
    long long inversions = 0;

    while (i <= mid && j <= right)
    {
        if (v[i] <= v[j])
            aux[k++] = v[i++];
        else
        {
            aux[k++] = v[j++];
            inversions += (mid - i + 1);
        }
    }

    while (i <= mid)
        aux[k++] = v[i++];
    while (j <= right)
        aux[k++] = v[j++];

    for (i = left; i <= right; i++)
        v[i] = aux[i];

    return inversions;
}

long long countInversions(long long v[], long long aux[], int left, int right)
{
    long long inversions = 0;
    if (left < right)
    {
        int mid = left + (right - left) / 2;

        inversions += countInversions(v, aux, left, mid);
        inversions += countInversions(v, aux, mid + 1, right);
        inversions += countInversionsAux(v, aux, left, mid, right);
    }
    return inversions;
}

long long distanciaGenomica(int v1[], int v2[], int n)
{
    long long *index_map = (long long *)malloc(n * sizeof(long long));
    for (int i = 0; i < n; i++)
        index_map[v1[i]] = i;

    long long *matched = (long long *)malloc(n * sizeof(long long));
    for (int i = 0; i < n; i++)
        matched[i] = index_map[v2[i]];

    long long *aux = (long long *)malloc(n * sizeof(long long));
    long long result = countInversions(matched, aux, 0, n - 1);

    free(index_map);
    free(matched);
    free(aux);

    return result;
}

int main()
{
    int n;

    scanf("%d", &n);

    int *v1 = (int *)malloc(n * sizeof(int));
    int *v2 = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++)
        scanf("%d", &v1[i]);
    for (int i = 0; i < n; i++)
        scanf("%d", &v2[i]);

    printf("%lld\n", distanciaGenomica(v1, v2, n));

    free(v1);
    free(v2);

    return 0;
}
