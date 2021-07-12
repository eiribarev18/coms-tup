# CoMS &ndash; TUP

Corporate Management System &ndash; Teams-Users-Projects

---
## Instructions for setting up the project
1. Clone the repository using `git clone --recurse-submodules https://github.com/eiribarev18/coms-tup.git`
1. Open the `./coms-tup-application/com-tup-application.sln` file in Visual Studio
1. Open a Developer terminal (PS or CMD) using `shift + ~`
1. `cd ..\libs\nanodbc`
1. `mkdir build`
1. `cd build`
1. `cmake -DNANODBC_DISABLE_TESTS=TRUE -A x64 ..`
1. `cmake --build .`
1. The *nanodbc* library should now link correctly when building the project. *Make sure you are building for x64!*
1. Copy the `env.h.example` file as `env.h` in the same directory, open it and set the macros to the appropriate values for your configuration
