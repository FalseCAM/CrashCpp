
# Check if examples are enabled
if(NOT OPTION_BUILD_EXAMPLES)
    return()
endif()

# Example applications
add_subdirectory(crashcppgui)
add_subdirectory(crashcpplog)
add_subdirectory(crashcppmail)
add_subdirectory(crashcpppost)
