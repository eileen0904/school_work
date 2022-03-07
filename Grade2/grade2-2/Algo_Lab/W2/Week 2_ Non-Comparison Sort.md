# Week 2: Non-Comparison Sort

## Implementation
Laguage:C
```c
void sort_by_digit(int *A, int n, int r, int p)
{
    int base = 1;
    while (p > 0)
    {
        --p;
        base *= r;
    }
    int count[r], B[n], m = 0;
    for (int j = 0; j < r; ++j)
        count[j] = 0;
    for (int i = 0; i < n; ++i)
        count[(A[i] / base) % r]++;
    for (int j = 0, psum = 0, sum = 0; j < r; ++j)
    {
        psum = sum;
        sum += count[j];
        count[j] = psum;
    }
    for (int i = 0; i < n; ++i)
        B[count[(A[i] / base) % r]++] = A[i];
    for (int i = 0; i < n; ++i)
        A[i] = B[i];
}

void radix_sort(int *A, int n, int r, int d)
{
    for (int i = 0; i < d; ++i)
        sort_by_digit(A, n, r, i);
}
```
## Questions
* Function **sort_by_digit** is a stable counting sort. If we rewrite the function to an unstable version, can radix sort still work correctly? 
    * No. e.g. A=[13,12]，如果用unstable version去排，以10為底，從個位數開始，因為2<3，A=[12,13]，再從十位數開始，因為兩個的十位數相同，都為1，所以A有可能變成A=[12,13]或A=[13,12]。
* This radix implement is processing through least significant digit to most significant digit. Can’t you design radix algorithm which start at most significant digit?
    * radix sort by MSD
        ```c
        void sort_by_digit(int *A, int n, int r, int base, vector<int>& sorted)
        {
            if(base<=0) return;

            int count[r];
            int Bucket[r][n];
            for (int j = 0; j < r; ++j)
                count[j] = 0;
            for (int i = 0; i < n; i++){
                int digit  = A[i] / base % r;
                Bucket[digit][count[digit]] = A[i];
                count[digit]++;
            }

            for (int i = 0; i < r; i++){
                if(count[i]==1){
                    sorted.push_back(Bucket[i][0]);
                }
                if(count[i]>1){
                    int arr[count[i]];
                    for(int j=0; j < count[i]; j++){
                        arr[j] = Bucket[i][j];
                    }
                    sort_by_digit(arr, count[i], r, base/r, sorted);
                }
            }
        }

        int get_base(int *A, int r){

            int max = A[0];
            for (int i = 1; i < A.size(); i++){
                if (A[i] > max) {
                    max = A[i];
                }
            }
            int base = 1;
            while (max >= r){
                max = max / r;
                base = base * r;
            }
            return base;
        }
        void radix_sort(int *A, int n, int r, vector<int>& sorted)
        {
            int base = get_base(A, 10);
            sort_by_digit(A, n, r, base, sorted);
        }
        ```
* Please design an algorithm to measure minimum usable 𝑑 of list 𝐴 and radix 𝑟.
    * $d = (\log_{r}{m})+1$ (m is the maximum number of *A*)
    ```c
    int get_d(int *A, int r){

        int max = A[0];
        int d = 0;
        for (int i = 1; i < A.size(); i++){
            if (A[i] > max) {
                max = A[i];
            }
        }
        d = log(max)/log(r) + 1;

        return d;
    }
    ```
* Please analysis the space complexity and the time complexity. (should be functions with arguments 𝑛, 𝑟, 𝑑)
    ```c
    void sort_by_digit(int *A, int n, int r, int p)
    {
        int base = 1; 
        while (p > 0) //d(d-1)/2
        {
            --p;
            base *= r;
        }
        int count[r], B[n], m = 0;
        for (int j = 0; j < r; ++j) //r
            count[j] = 0;
        for (int i = 0; i < n; ++i) //n
            count[(A[i] / base) % r]++;
        for (int j = 0, psum = 0, sum = 0; j < r; ++j)
        {
            //r
            psum = sum;
            sum += count[j];
            count[j] = psum;
        }
        for (int i = 0; i < n; ++i) //n
            B[count[(A[i] / base) % r]++] = A[i];
        for (int i = 0; i < n; ++i) //n
            A[i] = B[i];
    }

    void radix_sort(int *A, int n, int r, int d)
    {
        for (int i = 0; i < d; ++i) //d
            sort_by_digit(A, n, r, i);
    }
    ```
    * Space complexity
        A[ ]需要n個空間，count[ ]需要r個空間，B[ ]需要n個空間
        變數n、r、p、d、base、i、j、m、psum、sum各需要1個空間
        總共需要n+r+n+10個空間
        O(2n+r+10) = n+r
    * Time complexity
        Best case:
        * 如果r已知，例如r=10，則時間複雜度為O(d(n+20)) = dn
        * e.g. A=[5,4,3,2,1]，r=10，則$d=(\log_{10}{4})+1=1$，時間複雜度為O(1(n+r)) = n+r
        
        Worst case:
        * 如果所有的數字有相同的位數，除了一個數字的位數特別多，則時間複雜度為O(d(3n+2r)+(d(d-1)/2)) = d(n+r)