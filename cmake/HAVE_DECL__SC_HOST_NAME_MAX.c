#include <unistd.h>

int main()
{
    long len = sysconf(_SC_HOST_NAME_MAX);
    return 0;
}
