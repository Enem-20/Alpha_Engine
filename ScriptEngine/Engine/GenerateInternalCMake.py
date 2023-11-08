import os;

def generate(name : str):
    directory = os.path.dirname(__file__) + "/internal/" + name
    cmakeListsName = "CMakeLists.txt"
    cmakeListsText = """cmake_minimum_required(VERSION 3.8.0 FATAL_ERROR)

project({})

add_library(${{PROJECT_NAME}} INTERFACE)

FILE(GLOB_RECURSE headers "src/*.h")
FILE(GLOB_RECURSE sources "src/*.cpp")

target_sources(${{PROJECT_NAME}} INTERFACE
	${{headers}}
	${{sources}}
)""".format(name)
    os.mkdir(directory)
    f = open(directory + "/" + cmakeListsName, "w")
    f.write(cmakeListsText)
    f.flush()
    f.close()

generate("API")