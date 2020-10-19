mkfile_path := $(dir $(lastword $(MAKEFILE_LIST)))

APPL_COBJS +=

# ここにファイルを追加する
APPL_CXXOBJS += \
    Controller.o \
    Curvature.o \
    Display.o \
    Distance.o \
    EtRobocon2020.o \
    Filter.o \
    MotionSequencer.o \
    MoveStraight.o \
    LineTracer.o \
    NormalCourse.o \
    Pid.o \
    TurnControl.o \
    Navigator.o \
    Rotation.o \
    BlockBingoData.o \
    RouteCalculator.o \

SRCLANG := c++

ifdef CONFIG_EV3RT_APPLICATION

# Include libraries
include $(EV3RT_SDK_LIB_DIR)/libcpp-ev3/Makefile

endif

APPL_DIRS += \
    $(mkfile_path)app \
    $(mkfile_path)module \
    $(mkfile_path)module/api \

INCLUDES += \
    -I$(mkfile_path)app \
    -I$(mkfile_path)module \
    -I$(mkfile_path)module/api \
    -I$(ETROBO_HRP3_WORKSPACE)/etroboc_common \

COPTS += -std=gnu++11
