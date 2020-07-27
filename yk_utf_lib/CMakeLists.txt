cmake_minimum_required(VERSION 3.1)
project(
	ykUTF_lib
    VERSION 0.1.0
    DESCRIPTION "Yk UTF library"
    LANGUAGES CXX
)
add_library(
	ykUTF
	SHARED 
	./src/canonicalCombiningClass.cpp
	./src/generalCategoryProperty.cpp
	./src/lowerCase.cpp
	./src/upperCase.cpp
	./src/cType.cpp                    
	./src/graphemeProperty.cpp         
	./src/regex_utf.cpp
	./src/decompData.cpp               
	./src/lineBreakProperty.cpp        
	./src/ttyWidth.cpp
	./src/unicodeStr.cpp
)
set_property(GLOBAL
	PROPERTY PUBLIC_HEADER
	./include/Yk/utf/canonicalCombiningClass.hpp
	./include/Yk/utf/generalCategoryProperty.hpp
	./include/Yk/utf/lowerCase.hpp
	./include/Yk/utf/unicodeStr.hpp
	./include/Yk/utf/cType.hpp
	./include/Yk/utf/graphemeProperty.hpp
	./include/Yk/utf/regex_utf.hpp
	./include/Yk/utf/upperCase.hpp
	./include/Yk/utf/decompData.hpp
	./include/Yk/utf/lineBreakProperty.hpp
	./include/Yk/utf/ttyWidth.hpp
)
target_compile_features(ykUTF PRIVATE cxx_std_11)
target_include_directories(
	ykUTF PUBLIC ./include 
#	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
#	$<INSTALL_INTERFACE:include/Yk/UTF>
)
include(GNUInstallDirs)
install(
	TARGETS ykUTF
	EXPORT ykUTF-config
	ARCHIVE DESTINATION lib
	LIBRARY DESTINATION lib
	PUBLIC_HEADER DESTINATION include
)
install(FILES
	./include/Yk/utf/canonicalCombiningClass.hpp
	./include/Yk/utf/generalCategoryProperty.hpp
	./include/Yk/utf/lowerCase.hpp
	./include/Yk/utf/unicodeStr.hpp
	./include/Yk/utf/cType.hpp
	./include/Yk/utf/graphemeProperty.hpp
	./include/Yk/utf/regex_utf.hpp
	./include/Yk/utf/upperCase.hpp
	./include/Yk/utf/decompData.hpp
	./include/Yk/utf/lineBreakProperty.hpp
	./include/Yk/utf/ttyWidth.hpp
	DESTINATION include/Yk/utf
)
set(CMAKE_BUILD_TYPE Debug)
set_target_properties(
	ykUTF
  PROPERTIES
  VERSION ${PROJECT_VERSION}
)
