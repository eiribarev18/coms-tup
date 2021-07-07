# CoMS &ndash; TUP

Corporate Management System &ndash; Teams-Users-Projects

---
## Instructions for setting up the project
1. Clone the repository using `git clone --recurse-submodules https://github.com/eiribarev18/coms-tup.git`
1. Open a Developer Command Prompt
1. Navigate to the `libs/nanodbc/` subdirectory of the repository
1. `mkdir build`
1. `cd build`
1. `cmake -DNANODBC_DISABLE_TESTS=TRUE -A x64 ..`
1. `cmake --build .`
1. You should be able to open the `.sln` file located under `coms-tup-application/` (relative to the repo root) and build it. *Make sure you are building for x64!*