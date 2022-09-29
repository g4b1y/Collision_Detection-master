#include "./Run/Run.h"

void remove(); 

int main() {
    col::Run r;
    remove(); 
}


void remove() {
    //remove("./main.exe"); 
    remove("./main.o"); 
    remove("./Collision/Collision.o"); 
    remove("./Run/Run.o"); 
}
