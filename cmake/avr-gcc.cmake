set(CMAKE_C_COMPILER avr-gcc)
set(CMAKE_AR avr-ar)
set(CMAKE_C_FLAGS "-mmcu=${MCU} -Wall -Os -fshort-enums --param=min-pagesize=0")
