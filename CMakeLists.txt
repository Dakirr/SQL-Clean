cmake_minimum_required(VERSION 3.5)	 
project(SQL)			

##########################################################################
set(COMMON_LIB ./Common/Error/Error.h ./Common/Error/Error.cpp)
set(OBJECT_TYPE_LIB ./ObjectType/ObjectType.h ./ObjectType/ObjectType.cpp ./ObjectType/Tests.cpp)
set(GENERIC_OBJECT_LIB ./GenericObject/GenericObject.h ./GenericObject/GenericObject.cpp ./GenericObject/Tests.cpp)
set(COLLUMN_LIB ./Collumn/Collumn.h ./Collumn/Collumn.cpp ./Collumn/Tests.cpp)
set(TABLE_LIB ./Table/Table.h ./Table/Table.cpp ./Table/Tests.cpp)
set(PARCER_LIB ./Parcer/Tokenizer.h ./Parcer/Tokenizer.cpp ./Parcer/Parse.h ./Parcer/Parse.cpp ./Parcer/Global/Global.h ./Parcer/Global/Global.cpp)
set(STATEMENT_LIB ./Parcer/Statement.h ./Parcer/Statement.cpp)
set(GET_TYPE_ST_LIB ./Parcer/GetTypeSt/GetTypeSt.h ./Parcer/GetTypeSt/GetTypeSt.cpp)
set(GET_VALUE_ST_LIB ./Parcer/GetValueSt/GetValueSt.h ./Parcer/GetValueSt/GetValueSt.cpp)
set(CREATE_COLLUMN_ST_LIB ./Parcer/CreateCollumnSt/CreateCollumnSt.h ./Parcer/CreateCollumnSt/CreateCollumnSt.cpp)
set(CREATE_TABLE_ST_LIB ./Parcer/CreateTableSt/CreateTableSt.h ./Parcer/CreateTableSt/CreateTableSt.cpp)
set(INSERT_ST_LIB ./Parcer/InsertSt/InsertSt.h ./Parcer/InsertSt/InsertSt.cpp)
set(SOURCE_TESTS ./Common/Test/Test.cpp)
set(SOURCE_PARSER_TESTS ./Parcer/Main.cpp ./Parcer/Parse.h ./Parcer/Parse.cpp)		
##########################################################################
add_library(CommonLib STATIC ${COMMON_LIB})
add_library(ObjectTypeLib STATIC ${OBJECT_TYPE_LIB} ${COMMON_LIB})
add_library(GenericObjectLib STATIC ${GENERIC_OBJECT_LIB} ${OBJECT_TYPE_LIB} ${COMMON_LIB})
add_library(CollumnLib STATIC ${COLLUMN_LIB} ${GENERIC_OBJECT_LIB} ${OBJECT_TYPE_LIB} ${COMMON_LIB})
add_library(TableLib STATIC ${SOURCE_TESTS} ${TABLE_LIB} ${COLLUMN_LIB} ${GENERIC_OBJECT_LIB} ${OBJECT_TYPE_LIB} ${COMMON_LIB})
add_library(ParcerLib STATIC ${PARCER_LIB} ${STATEMENT_LIB} ${GET_TYPE_ST_LIB} ${OBJECT_TYPE_LIB})
add_library(GetValueStLib STATIC ${GET_VALUE_ST_LIB} ${GENERIC_OBJECT_LIB} ${OBJECT_TYPE_LIB} ${COMMON_LIB} ${GET_TYPE_ST_LIB} ${STATEMENT_LIB} ${PARCER_LIB} )
add_library(CreateCollumnStLib STATIC ${CREATE_COLLUMN_ST_LIB} ${GET_VALUE_ST_LIB} ${COLLUMN_LIB} ${GENERIC_OBJECT_LIB} ${OBJECT_TYPE_LIB} ${COMMON_LIB} ${GET_TYPE_ST_LIB} ${STATEMENT_LIB} ${PARCER_LIB} )
add_library(CreateTableStLib STATIC ${CREATE_TABLE_ST_LIB} ${INSERT_ST_LIB} ${CREATE_COLLUMN_ST_LIB} ${GET_VALUE_ST_LIB} ${TABLE_LIB} ${COLLUMN_LIB} ${GENERIC_OBJECT_LIB} ${OBJECT_TYPE_LIB} ${COMMON_LIB} ${GET_TYPE_ST_LIB} ${STATEMENT_LIB} ${PARCER_LIB} )
##########################################################################

# add_executable(TESTS ${SOURCE_TESTS})	
# set_target_properties(
# 	TESTS PROPERTIES
# 	CXX_STANDARD 17
# 	CXX_STANDARD_REQUIRED ON
# )
# target_link_libraries(TESTS TableLib ParcerLib)

add_executable (MAIN ${SOURCE_PARSER_TESTS})
set_target_properties(
	MAIN PROPERTIES
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED ON
)
target_link_libraries(MAIN CreateTableStLib)



