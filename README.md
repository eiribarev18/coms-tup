# CoMS &ndash; TUP

Corporate Management System &ndash; Teams-Users-Projects

---
## Instructions for setting up the project
1. Clone the repository using `git clone --recurse-submodules`
1. Open the appropriate VS Developer Console (still don't know which one is the most appropriate)
1. Navigate to the `libs/nanodbc/` subdirectory of the repository
1. `cmake -DNANODBC_DISABLE_TESTS=TRUE ..`
1. `cmake --build .`
1. You should be able to open the `.sln` file located under `coms-tup-application/` (relative to the repo root) and build it