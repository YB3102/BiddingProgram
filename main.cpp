#include "Driver.h"


int main() {
    //Driver Set up
    Driver &driver = Driver::GetInstance();
    driver.driverStart();

    // Verify .csv initialization
}