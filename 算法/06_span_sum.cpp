#include<iostream>
#include<vector>
using namespace std;

int main(int argc, char const *argv[])
{
    int n,a,b;
    scanf("%d",&n);
    vector<int> vec(n);
    vector<int> p(n);
    int presum = 0;
    for(int i = 0;i<n;i++)
    {
        scanf("%d",&vec[i]);
        presum+=vec[i];
        p[i] = presum;
    }

    while(~scanf("%d%d",&a,&b))
    {
        if(a == 0) printf("%d\n",p[b]);
        else printf("%d\n",p[b]-p[a-1]);
    }
    return 0;
}
