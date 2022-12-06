#include <iostream>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <string>

using namespace std;
using namespace boost::interprocess;

int main(int argc, char *argv[])
{
    if (argc == 1) {
        shared_memory_object::remove("Lucky number");
        managed_shared_memory managed_shm(open_or_create, "Lucky number", 1024);
        int* shared_int = managed_shm.construct<int>("Mason's lucky number")(7);
        cout << *shared_int << endl;
        
        pair<int*, size_t> p = managed_shm.find<int>("Mason's lucky number");
        if (p.first) {
            cout << "Parent: " << *p.first << endl;
        }
        
        // Launch child process
        string s(argv[0]);
        s += " child ";
        if (0 != system(s.data())) {
            return 1;
        }
        
    } else {
        managed_shared_memory managed_shm(open_only, "Lucky number");
        pair<int*, size_t> p = managed_shm.find<int>("Mason's lucky number");
        if (p.first) {
            cout << "Child: " << *p.first << endl;
        }
    }
    
    return 0;
}

