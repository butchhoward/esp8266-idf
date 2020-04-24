# We will use these variables later

# The name of the executable file that will run our tests
SET(PROJECT_TEST ${PROJECT_NAME}-test)

SET(MOCK_DIR ${PROJECT_SOURCE_DIR}/mock)
SET(UNITY_DIR ${PROJECT_SOURCE_DIR}/unity)
SET(LIB_UNITY unity)

# Tells cmake to run in the test and unity folders.
add_subdirectory(test)
add_subdirectory(unity)

# The Unity library build needs to have completed 
# before we can build our own code
add_dependencies(${PROJECT_TEST} ${LIB_UNITY})
